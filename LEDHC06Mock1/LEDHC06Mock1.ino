#include <FastLED.h>
#include <SoftwareSerial.h>

#define NUM_LEDS 4
#define LED_PIN 4

CRGB leds[NUM_LEDS];
SoftwareSerial BTserial (2,3);
const byte numChars = 248;
char receivedChars[numChars];
boolean newData = false;

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(15);

  Serial.begin(9600);
  BTserial.begin(9600);
  Serial.println("<Arduino is ready>");
}

void loop() {
  recvWithStartEndMarkers();
  showNewData();
}

void recvWithStartEndMarkers() {
  static boolean recvInProgress = false;
  static byte ndx = 0;
  char startMarker = '<';
  char endMarker = '>';
  char rc;

  while (BTserial.available() > 0 && newData == false) {
    rc = BTserial.read();

    if (recvInProgress == true) {
      if (rc != endMarker) {
        receivedChars[ndx] = rc;
        ndx++;
        if (ndx >= numChars) {
          ndx = numChars - 1;
        }
      }
      else {
        receivedChars[ndx] = '\0'; // terminate the string
        recvInProgress = false;
        ndx = 0;
        newData = true;
      }
    }

    else if (rc == startMarker) {
      recvInProgress = true;
    }
  }
}

void showNewData() {
  if (newData == true) {
    leds[0] = CRGB::Blue;
    FastLED.show();

    Serial.print("This just in ... ");
    Serial.println(receivedChars);
    newData = false;
  }
  else {
    leds[0] = CRGB::Yellow;
    FastLED.show();
  }

  delay(100);
}