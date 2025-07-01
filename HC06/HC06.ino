#include <SoftwareSerial.h>

SoftwareSerial BTserial (2,3);
String message = "";

void setup() {
  Serial.begin(9600);
  Serial.println("Started");
  BTserial.begin(9600);
}

void loop() {
  if (BTserial.available()) {
    Serial.println("detected");

    message += BTserial.readString();
    Serial.println(message);
  }
  /*
  // Keep reading from HC-06 and send to Arduino Serial Monitor
  if (BTserial.available()) {
    Serial.write(BTserial.read());
  }

  // Keep reading from Arduino Serial Monitor and send to HC-06
  if (Serial.available()) {
    BTserial.write(Serial.read());
  }
}