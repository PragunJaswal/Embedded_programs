/****************************************************************************************************************************
  TCPClientSingle.ino
  For WizFi360/ESP8266/ESP32-AT-command running shields

  ESP_AT_Lib is a wrapper library for the WizFi360/ESP8266/ESP32 AT-command shields

  Based on and modified from ESP8266 https://github.com/esp8266/Arduino/releases
  Built by Khoi Hoang https://github.com/khoih-prog/ESP_AT_Lib
  Licensed under MIT license

  @example TCPClientSingle.ino
  @brief The TCPClientSingle demo of library WeeESP8266.
  @author Wu Pengfei<pengfei.wu@itead.cc>
  @date 2015.02

  @par Copyright:
  Copyright (c) 2015 ITEAD Intelligent Systems Co., Ltd. \n\n
  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License as
  published by the Free Software Foundation; either version 2 of
  the License, or (at your option) any later version. \n\n
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
 *****************************************************************************************************************************/

#include "defines.h"

#include "ESP_AT_Lib.h"

#define HOST_NAME   "www.yahoo.com"
#define HOST_PORT   (80)

ESP8266 wifi(&EspSerial);

// Your board <-> ESP_AT baud rate:
#define ESP_AT_BAUD       115200

void setup(void)
{
  Serial.begin(115200);

  while (!Serial && millis() < 5000);

#if defined(BOARD_NAME)
  Serial.println("\nStart TCPClientSingle on " + String(BOARD_NAME));
#else
  Serial.println("\nStart TCPClientSingle");
#endif

  Serial.println(ESP_AT_LIB_VERSION);

  // initialize serial for ESP module
  EspSerial.begin(ESP_AT_BAUD);

  Serial.print("FW Version:");
  Serial.println(wifi.getVersion().c_str());

  Serial.print("Set AP/STA Mode ");

  if (wifi.setOprToStationSoftAP())
  {
    Serial.println("OK");
  }
  else
  {
    Serial.println("failed");
  }

  if (wifi.joinAP(SSID, PASSWORD))
  {
    Serial.println("Connect to WiFi OK");
    Serial.print("IP: ");
    Serial.println(wifi.getLocalIP().c_str());
  }
  else
  {
    Serial.println("Connect to WiFi failed");
  }

  Serial.print("enableMUX ");
  
  if (wifi.enableMUX())
  {
    Serial.println("OK");
  }
  else
  {
    Serial.println("failed");
  }
  
  Serial.println("Done");
}

void loop()
{
  uint8_t buffer[128] = {0};

  static uint8_t mux_id = 0;

  Serial.print("Create TCP ");

  if (wifi.createTCP(mux_id, HOST_NAME, HOST_PORT))
  {
    Serial.println("OK");
  }
  else
  {
    Serial.println("failed");
  }

  char hello[] = "Hello, this is client!";

  if (wifi.send(mux_id, (const uint8_t*)hello, strlen(hello)))
  {
    Serial.println("Send OK");
  }
  else
  {
    Serial.println("Send failed");
  }

  uint32_t len = wifi.recv(mux_id, buffer, sizeof(buffer), 10000);

  if (len > 0)
  {
    Serial.print("Received:[");

    for (uint32_t i = 0; i < len; i++)
    {
      Serial.print((char)buffer[i]);
    }

    Serial.println("]");
  }

  Serial.print("Release TCP ");

  if (wifi.releaseTCP(mux_id))
  {
    Serial.println("OK");
  }
  else
  {
    Serial.println("failed");
  }

  delay(5000);
}
