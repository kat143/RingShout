#include <FastLED.h>  // so that the FastLED library can be used

#define NUM_LEDS 15  // number of LEDs in the strip
#define LED_PIN 4   // pin connected to the strip's data pin (via a resistor)

CRGB leds[NUM_LEDS];  // array representing the strip of LEDs, where leds[0] is the first LED on the strip

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);  // tell FastLED that the LED array is "leds"
  FastLED.setBrightness(25);                               // set brightness of LEDs to 50 (can be any value from 0-255)
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

  /**/
  for (int led = 0; led < 20; led++) {
    int turnOn = led % NUM_LEDS;
    for (int i = 5; i >= 1; i--) {
      leds[(turnOn + i) % NUM_LEDS] = CRGB::Yellow;
      leds[((turnOn - i) + NUM_LEDS) % NUM_LEDS] = CRGB::Yellow;
      FastLED.show();

      delay(50);

      leds[(turnOn + i) % NUM_LEDS] = CRGB::Black;
      leds[((turnOn - i) + NUM_LEDS) % NUM_LEDS] = CRGB::Black;
      FastLED.show();
    }
    leds[turnOn] = CRGB::Red;
    FastLED.show();

    delay(1000 - (50 * 5));

    leds[turnOn] = CRGB::Black;
    FastLED.show();
  }
}