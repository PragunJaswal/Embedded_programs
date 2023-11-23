

void setup()
{
Serial.begin(9600);
while (!Serial); // For Yun/Leo/Micro/Zero/…
delay(100);
Serial.println(“\n\nFingerprint sensor enrollment”);

// set the data rate for the sensor serial port
finger.begin(57600);

if (finger.verifyPassword()) {
Serial.println(“Found fingerprint sensor!”);
} else {
Serial.println(“Did not find fingerprint sensor :(“);
while (1) { delay(1); }
}
}

uint8_t readnumber(void) {
uint8_t num = 0;

while (num == 0) {
while (! Serial.available());
num = Serial.parseInt();
}
return num;
}

void loop() // program wil repeat this part (loop here)
{
Serial.println(“Ready to enroll a fingerprint!”);
Serial.println(“Please type in the ID # (from 1 to 127) you want to save this finger as…”);
id = readnumber();
if (id == 0) {// ID #0 not allowed, try again!
return;
}
Serial.print(“Enrolling ID #”);
Serial.println(id);

while (! getFingerprintEnroll() );
}

uint8_t getFingerprintEnroll() {

int p = -1;
Serial.print(“Waiting for valid finger to enroll as #”); Serial.println(id);
while (p != FINGERPRINT_OK) {
p = finger.getImage();
switch (p) {
case FINGERPRINT_OK:
Serial.println(“Image taken”);
break;
case FINGERPRINT_NOFINGER:
Serial.println(“.”);
break;
case FINGERPRINT_PACKETRECIEVEERR:
Serial.println(“Communication error”);
break;
case FINGERPRINT_IMAGEFAIL:
Serial.println(“Imaging error”);
break;
default:
Serial.println(“Unknown error”);
break;
}
}

// OK success!

p = finger.image2Tz(1);
switch (p) {
case FINGERPRINT_OK:
Serial.println(“Image converted”);
break;
case FINGERPRINT_IMAGEMESS:
Serial.println(“Image too messy”);
return p;
case FINGERPRINT_PACKETRECIEVEERR:
Serial.println(“Communication error”);
return p;
case FINGERPRINT_FEATUREFAIL:
Serial.println(“Could not find fingerprint features”);
return p;
case FINGERPRINT_INVALIDIMAGE:
Serial.println(“Could not find fingerprint features”);
return p;
default:
Serial.println(“Unknown error”);
return p;
}

Serial.println(Remove finger);
delay(2000);
p = 0;
while (p != FINGERPRINT_NOFINGER) {
p = finger.getImage();
}
Serial.print(ID); Serial.println(id);
p = -1;
Serial.println(Place same finger again);
while (p != FINGERPRINT_OK) {
p = finger.getImage();
switch (p) {
case FINGERPRINT_OK:
Serial.println(Image taken);
break;
case FINGERPRINT_NOFINGER:
break;
case FINGERPRINT_PACKETRECIEVEERR:
Serial.println(Communication error);
break;
case FINGERPRINT_IMAGEFAIL:
Serial.println(Imaging error);
break;
default:
Serial.println(Unknown error);
break;
}
}

// OK success!

p = finger.image2Tz(2);
switch (p) {
case FINGERPRINT_OK:
Serial.println(Image converted);
break;
case FINGERPRINT_IMAGEMESS:
Serial.println(Image too messy);
return p;
case FINGERPRINT_PACKETRECIEVEERR:
Serial.println(Communication error);
return p;
case FINGERPRINT_FEATUREFAIL:
Serial.println(Could not find fingerprint features);
return p;
case FINGERPRINT_INVALIDIMAGE:
Serial.println(Could not find fingerprint features);
return p;
default:
Serial.println(Unknown error);
return p;
}

// OK converted!
Serial.print(Creating model for #); Serial.println(id);
