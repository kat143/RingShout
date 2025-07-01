#include <FastLED.h>  // so that the FastLED library can be used
#include <SoftwareSerial.h>

#define NUM_LEDS 4  // number of LEDs in the strip
#define LED_PIN 4   // pin connected to the strip's data pin (via a resistor)

CRGB leds[NUM_LEDS];  // array representing the strip of LEDs, where leds[0] is the first LED on the strip
SoftwareSerial BTserial(2, 3);
float longitude = 125.23;
float altitude = 234;

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);  // tell FastLED that the LED array is "leds"
  FastLED.setBrightness(15);                               // set brightness of LEDs (can be any value from 0-255)

  Serial.begin(9600);
  BTserial.begin(9600);
  Serial.println("Started");
}

void loop() {
  /*
  leds[0] = CRGB::Olive;
  leds[1] = CRGB::DarkOrange;
  leds[2] = CRGB::MediumSpringGreen;
  leds[3] = CRGB::DarkKhaki;
  leds[4] = CRGB::OldLace;
  leds[5] = CRGB::MediumSpringGreen;
  leds[6] = CRGB::CornflowerBlue;
  leds[7] = CRGB::HotPink;
  leds[8] = CRGB::Goldenrod;
  leds[9] = CRGB::Violet;
  FastLED.show();
  delay(1000);
  */

  /*
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Brown;
    FastLED.show();
    delay(250);
  }
  for (int i = (NUM_LEDS - 1); i >= 0; i--) {
    leds[i] = CRGB::Black;
    FastLED.show();
    delay(250);
  }
  delay(500);
  */

  /*
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::OrangeRed;
    FastLED.show();
    delay(100);
    leds[i] = CRGB::Black;
    FastLED.show();
    delay(100);
  }
  delay(500);
  */
  
  int turnOn = longitude / (300.0 / NUM_LEDS);
  turnOn = turnOn % NUM_LEDS;
  if (altitude > 1000) {
    leds[turnOn] = CRGB::Red;
  }
  else {
    leds[turnOn] = CRGB::Blue;
  }

  /*
  for (int i = 1; i <= 3; i++) {
    int index = ((turnOn - i) + NUM_LEDS) % NUM_LEDS;
    if (altitude > 1000) leds[index] = CRGB::Red;
    else leds[index] = CRGB::Blue;

    leds[index].fadeLightBy(64 * i);
  }
  */
  int index = ((turnOn - 1) + NUM_LEDS) % NUM_LEDS;
  if (altitude > 1000) leds[index] = CRGB::Red;
  else leds[index] = CRGB::Blue;
  leds[index].fadeLightBy(128);

  FastLED.show();
  delay(100);

  leds[index] = CRGB::Black;

  //leds[((turnOn - 3) + NUM_LEDS) % NUM_LEDS] = CRGB::Black;
  longitude += 10;
  altitude += 100;
}