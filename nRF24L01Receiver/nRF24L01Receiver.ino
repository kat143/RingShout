#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 8); // CE, CSN pins
const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  
  Serial.println("setup started");

  radio.begin();
  //radio.openReadingPipe(0, address);

  radio.setChannel(0x76);
  const uint64_t pipe = 0xE0E0F1F1E0LL;
  radio.openReadingPipe(1, pipe);

  radio.setPALevel(RF24_PA_LOW);
  radio.startListening();

  Serial.println("radio started");
}

void loop() {
  Serial.println("test!");
  delay(1000);

  if (!radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    //Serial.println(text);
    Serial.println("radio not getting anything");

    delay(1000); // 1 second
  }
}