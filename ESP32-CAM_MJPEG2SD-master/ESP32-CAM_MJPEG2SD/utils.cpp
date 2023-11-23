#include <stdio.h>
#include <string.h>
#include <esp_system.h>
//#include <ESP_LOG.h>
#include <WiFi.h>
#include <SD_MMC.h>
#include <ESPmDNS.h>
#include <DNSServer.h>
#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include <lwip/netdb.h>

#define TAG "utils"
//#include "esp32-hal-log.h"
#include "esp_log.h"
#include "remote_log.h"
extern char hostName[]; //Host name for ddns
extern char ST_SSID[]; //Router ssid
extern char ST_Pass[]; //Router passd

extern char ST_ip[]; //Leave blank for dhcp
extern char ST_sn[];
extern char ST_gw[];
extern char ST_ns1[];
extern char ST_ns2[];

extern String AP_SSID;
extern char   AP_Pass[];
extern char   AP_ip[];
extern char   AP_sn[];
extern char   AP_gw[];

DNSServer dnsAPServer; //DDNS server for name resolution

bool loadConfig();

// Remote loggging
byte dbgMode = 0; //0 - Disabled, log to serial port only, 1 - Internal log to sdcard file, 2 - Remote telnet on port 443
static int log_serv_sockfd = -1;
static int log_sockfd = -1;
static struct sockaddr_in log_serv_addr, log_cli_addr;
static char fmt_buf[LOG_FORMAT_BUF_LEN];
static vprintf_like_t orig_vprintf_cb;
const char *log_file_name = "/sdcard/log.txt";
FILE *_log_remote_fp = NULL;

//Remote log to telnet 443
static int remote_log_vprintf_cb(const char *str, va_list list)
{
    int ret = 0, len = 0;
    char task_name[16];

    // Can't really understand what the hell is this...
    char *cur_task = pcTaskGetTaskName(xTaskGetCurrentTaskHandle());
    strncpy(task_name, cur_task, 16);
    task_name[15] = 0;

    // Why need to compare the task name anyway??
    if (strncmp(task_name, "tiT", 16) != 0) {

        len = vsprintf((char*)fmt_buf, str, list);

        // Send off the formatted payload
        if(send(log_sockfd, fmt_buf, len, 0) < 0) {
            remote_log_free();
        }
    }

    return vprintf(str, list);
}

int vprintf_into_spiffs_sync(const char *fmt, va_list args) {
    static bool static_fatal_error = false;
    static const uint32_t WRITE_CACHE_CYCLE = 5;
    static uint32_t counter_write = 0;
    int iresult;
    //Open remote file
    if(_log_remote_fp == NULL){
     _log_remote_fp = fopen(log_file_name, "wb");
    }
    // #1 Write to SPIFFS
    if (_log_remote_fp == NULL) {
        printf("%s() ABORT. file handle _log_remote_fp is NULL\n", __FUNCTION__);
        return -1;
    }
    if (static_fatal_error == false) {
        iresult = vfprintf(_log_remote_fp, fmt, args);
        if (iresult < 0) {
            printf("%s() ABORT. failed vfprintf() -> disable future vfprintf(_log_remote_fp) \n", __FUNCTION__);
            // MARK FATAL
            static_fatal_error = true;
            return iresult;
        }

        // #2 Smart commit after x writes
        counter_write++;
        if (counter_write % WRITE_CACHE_CYCLE == 0) {
            /////printf("%s() fsync'ing log file on SPIFFS (WRITE_CACHE_CYCLE=%u)\n", WRITE_CACHE_CYCLE);
            fsync(fileno(_log_remote_fp));
        }
    }

    // #3 ALWAYS Write to stdout!
    return vprintf(fmt, args);
}

int remote_log_init_telnet()
{
    int ret = 0;
    ESP_LOGV(TAG, "Initialize telnet remote log");
    memset(&log_serv_addr, 0, sizeof(log_serv_addr));
    memset(&log_cli_addr, 0, sizeof(log_cli_addr));

    log_serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    log_serv_addr.sin_family = AF_INET;
    log_serv_addr.sin_port = htons(LOG_PORT);

    if((log_serv_sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP)) < 0) {
        ESP_LOGE(TAG, "Failed to create socket, fd value: %d", log_serv_sockfd);
        return log_serv_sockfd;
    }

    ESP_LOGI(TAG, "Socket FD is %d", log_serv_sockfd);

    int reuse_option = 1;
    if((ret = setsockopt(log_serv_sockfd, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse_option, sizeof(reuse_option))) < 0) {
        ESP_LOGE(TAG, "Failed to set reuse, returned %d, %s", ret, strerror(errno));
        remote_log_free();
        return ret;
    }

    if((ret = bind(log_serv_sockfd, (struct sockaddr *)&log_serv_addr, sizeof(log_serv_addr))) < 0) {
        ESP_LOGE(TAG, "Failed to bind the port, maybe someone is using it?? Reason: %d, %s", ret, strerror(errno));
        remote_log_free();
        return ret;
    }

    if((ret = listen(log_serv_sockfd, 1)) != 0) {
        ESP_LOGE(TAG, "Failed to listen, returned: %d", ret);
        return ret;
    }

    // Set timeout
    struct timeval timeout = {
            .tv_sec = 30,
            .tv_usec = 0
    };

    // Set receive timeout
    if ((ret = setsockopt(log_serv_sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout))) < 0) {
        ESP_LOGE(TAG, "Setting receive timeout failed");
        remote_log_free();
        return ret;
    }

    // Set send timeout
    if ((ret = setsockopt(log_serv_sockfd, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(timeout))) < 0) {
        ESP_LOGE(TAG, "Setting send timeout failed");
        remote_log_free();
        return ret;
    }

    ESP_LOGI(TAG, "Server created, please use telnet to debug me in 30 seconds!");

    size_t cli_addr_len = sizeof(log_cli_addr);
    if((log_sockfd = accept(log_serv_sockfd, (struct sockaddr *)&log_cli_addr, &cli_addr_len)) < 0) {
        ESP_LOGE(TAG, "Failed to accept, returned: %d, %s", ret, strerror(errno));
        remote_log_free();
        return ret;
    }

    // Bind vprintf callback
    orig_vprintf_cb = esp_log_set_vprintf(remote_log_vprintf_cb);    
    ESP_LOGI(TAG, "Logger vprintf function bind to telnet successful!");

    return 0;
}

int remote_log_free_telnet()
{
    int ret = 0;
    if(log_serv_sockfd != -1 && (ret = close(log_serv_sockfd)) != 0) {
        ESP_LOGE(TAG, "Cannot close the socket! Have you even open it?");
        return ret;
    }

    if(orig_vprintf_cb != NULL) {
        esp_log_set_vprintf(orig_vprintf_cb);
    }

    return ret;
}

int remote_log_init()
{
    if(dbgMode==0)
      return 0;
    if(dbgMode==2)
      return remote_log_init_telnet();
      
    //if(SD_MMC.exists(log_file_name)) SD_MMC.remove(log_file_name);
    /// Bind vprintf callback    
    orig_vprintf_cb = esp_log_set_vprintf(&vprintf_into_spiffs_sync);
    Serial.printf("Logger bind sdcard file: %d\n", (int)orig_vprintf_cb); 
    ESP_LOGI(TAG, "Logger vprintf function bind successful!");
    return dbgMode;
}

int remote_log_free()
{
    if(dbgMode==0)
      return 0;
    if(dbgMode==2)
      return remote_log_free_telnet();
      
    Serial.printf("Logger vprintf unbind sdcard file: %d\n", (int)orig_vprintf_cb); 
    if(orig_vprintf_cb != NULL) {
        esp_log_set_vprintf(orig_vprintf_cb);
    }
    if(_log_remote_fp!=NULL){
      fsync(fileno(_log_remote_fp));
      fflush(_log_remote_fp);
      fclose(_log_remote_fp);
      _log_remote_fp = NULL;
    }
    return 0;
}
char *esp_log_system_timestamp(void)
{
    static char buffer[18] = {0};
    static _lock_t bufferLock = 0;

    if (xTaskGetSchedulerState() == taskSCHEDULER_NOT_STARTED) {
        uint32_t timestamp = esp_log_early_timestamp();
        for (uint8_t i = 0; i < sizeof(buffer); i++) {
            if ((timestamp > 0) || (i == 0)) {
                for (uint8_t j = sizeof(buffer) - 1; j > 0; j--) {
                    buffer[j] = buffer[j - 1];
                }
                buffer[0] = (char)(timestamp % 10) + '0';
                timestamp /= 10;
            } else {
                buffer[i] = 0;
                break;
            }
        }
        return buffer;
    } else {
        struct timeval tv;
        struct tm timeinfo;

        gettimeofday(&tv, NULL);
        localtime_r(&tv.tv_sec, &timeinfo);

        _lock_acquire(&bufferLock);
        snprintf(buffer, sizeof(buffer),
                 "%02d:%02d:%02d.%03ld",
                 timeinfo.tm_hour,
                 timeinfo.tm_min,
                 timeinfo.tm_sec,
                 tv.tv_usec / 1000);
        _lock_release(&bufferLock);

        return buffer;
    }
}

//Wifi settings
String ipToString(IPAddress ip) {
  String s = "";
  for (int i = 0; i < 4; i++)
    s += i  ? "." + String(ip[i]) : String(ip[i]);
  return s;
}
bool setWifiAP() {
  //Set access point if disabled
  if (WiFi.getMode() == WIFI_OFF) WiFi.mode(WIFI_AP);
  else if (WiFi.getMode() == WIFI_STA) WiFi.mode(WIFI_AP_STA);

  //set static ip
 if(strlen(AP_ip)>1){
    ESP_LOGV(TAG, "Setting ap static ip :%s, %s, %s", AP_ip,AP_gw,AP_sn);  
    IPAddress _ip,_gw,_sn,_ns1,_ns2;
    _ip.fromString(AP_ip);
    _gw.fromString(AP_gw);
    _sn.fromString(AP_sn);
    //set static ip
    WiFi.softAPConfig(_ip, _gw, _sn);
  } 
  ESP_LOGI(TAG, "Starting Access point with SSID %s", AP_SSID.c_str());
  WiFi.softAP(AP_SSID.c_str(), AP_Pass );
  ESP_LOGI(TAG, "Done. Connect to SSID: %s and navigate to http://%s", AP_SSID.c_str(), ipToString(WiFi.softAPIP()).c_str());
  /*//Start mdns for AP ?
    ESP_LOGI(TAG, "Starting ddns on port 53: %s", ipToString(WiFi.softAPIP()).c_str() );
    dnsAPServer.start(53, "*", WiFi.softAPIP());
  */
  return true;
}

void setupHost(){  //Mdns services   
  if (MDNS.begin(hostName) ) {
    // Add service to MDNS-SD
    MDNS.addService("http", "tcp", 80);
    MDNS.addService("ws", "udp", 81);
    //MDNS.addService("ftp", "tcp", 21);    
    ESP_LOGI(TAG,"Mdns services http://%s Started.", hostName );
  } else {
    ESP_LOGE(TAG, "Mdns host name: %s Failed.", hostName);
  }
}

bool startWifi() {
  //No config found. Setup AP to create one
  if (!loadConfig()) return setWifiAP();
  WiFi.persistent(false); //prevent the flash storage WiFi credentials
  WiFi.setAutoReconnect(false); //Set whether module will attempt to reconnect to an access point in case it is disconnected
  WiFi.setAutoConnect(false);
  ESP_LOGV(TAG, "Starting wifi, exist mode: %d", WiFi.getMode() );
  if (WiFi.getMode() == WIFI_OFF) WiFi.mode(WIFI_AP);
  else if (WiFi.getMode() == WIFI_AP) WiFi.mode(WIFI_AP_STA);
  ESP_LOGV(TAG, "Setup wifi, mode: %d", WiFi.getMode() );
  //Setup mdns services
  setupHost();
  //Disconnect if already connected
  if (WiFi.status() == WL_CONNECTED) {
    ESP_LOGI(TAG, "Disconnecting from ssid: %s", (String(WiFi.SSID()).c_str()) );
    WiFi.disconnect();
    delay(1000);
    ESP_LOGV(TAG, "Disconnected from ssid: %s", (String(WiFi.SSID()).c_str()) );
  }
  //Set hostname
  ESP_LOGI(TAG, "Setting wifi hostname: %s", hostName);
  WiFi.setHostname(hostName);

  if (strlen(ST_ip) > 1) {
    ESP_LOGI(TAG, "Setting config static ip :%s, %s, %s, %s", ST_ip,ST_gw,ST_sn, ST_ns1);
    IPAddress _ip, _gw, _sn, _ns1, _ns2;

    _ip.fromString(ST_ip);
    _gw.fromString(ST_gw);
    _sn.fromString(ST_sn);
    _ns1.fromString(ST_ns1);
    _ns2.fromString(ST_ns2);
    //set static ip
    WiFi.config(_ip, _gw, _sn, _ns1); // need DNS for SNTP
  }else{
    ESP_LOGI(TAG, "Getting ip from dhcp..");
  }
  //
  if (strlen(ST_SSID) > 0) {    
    ESP_LOGI(TAG, "Got stored router credentials. Connecting to: %s with pass: %s", ST_SSID, ST_Pass);
  } else {
    ESP_LOGI(TAG, "No stored Credentials. Starting Access point.");
    //Start AP config portal
    return setWifiAP();
  }
  int tries = 3;
  uint8_t timeout;
  while (tries > 0) {
    int ret = 0;
    timeout = 40; // 40 * 200 ms = 8 sec time out
    WiFi.begin(ST_SSID, ST_Pass);
    ESP_LOGI(TAG, "ST waiting for connection. Try %d", tries);
    while ( ((ret = WiFi.status()) != WL_CONNECTED) && timeout ) {
      Serial.print(".");
      delay(200);
      Serial.flush();
      --timeout;
    }
    Serial.println(".");
    if (timeout > 0) {
      tries = 0;
    } else {
      tries--;
      WiFi.disconnect();
      delay(1000);
    }
  }

  if (timeout <= 0) {
    ESP_LOGE(TAG, "wifi ST timeout on connect. Failed.");
    return setWifiAP();
  }
  ESP_LOGI(TAG, "Connected! Got ip: '%s ", String(WiFi.localIP().toString()).c_str());
  return true;
}

//Check for Station disconnections and reboot if not connected for some seconds
//and not ap clients connected. 
unsigned long tmConn=millis();
unsigned long tmReboot=0;
void checkConnection(){
  //Reboot?
  if(tmReboot>0 && millis() - tmReboot > 25000 ){
    int apClients = WiFi.softAPgetStationNum();
    ESP_LOGV(TAG, "Need reboot.. Wifi status: %d Clients active: %d", WiFi.status(), apClients);
    if(apClients < 1 && WiFi.status() != WL_CONNECTED ) //Reboot if no clients and no connection
       ESP.restart();
    else
       tmReboot = 0; 
  }
  
  //Check for wifi station reconnection every 30 seconds
  if(WiFi.status() != WL_CONNECTED && millis() - tmConn > 30000){
    ESP_LOGI(TAG, "Wifi not connected, mode: %d, status: %d, ap clients: %d", WiFi.getMode(), WiFi.status(), WiFi.softAPgetStationNum() );       
    tmConn = millis();   //Recheck
    tmReboot = millis(); //Reboot after 25 seconds      
  }
} 
