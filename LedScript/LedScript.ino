#include <FastLED.h>  // so that the FastLED library can be used
#include <ArduinoJson.h>

#define NUM_LEDS 1  // number of LEDs in the strip
#define LED_PIN 4   // pin connected to the strip's data pin (via a resistor)

CRGB leds[NUM_LEDS];  // array representing the strip of LEDs, where leds[0] is the first LED on the strip

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);  // tell FastLED that the LED array is "leds"
  FastLED.setBrightness(25);                               // set brightness of LEDs to 50 (can be any value from 0-255)
}

void loop() {
  char input[] = "{\"rightAscension\":176,\"declination\":-22}";  // both values are in degrees; right ascension goes from 0-359 and declination goes from -90 to 90
  StaticJsonDocument<16> doc;
  DeserializationError error = deserializeJson(doc, input);
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }

  int rA = doc["rightAscension"];  // analogous to "longitude"
  int d = doc["declination"];      // analogous to "latitude"
  
  // change LED state based on satellite location (given by rA and d)
  if (rA < 180 && d >= 0) {
    leds[0] = CRGB::Yellow;
  } else if (rA < 180 && d < 0) {
    leds[0] = CRGB::Red;
  } else if (rA >= 180 && d >= 0) {
    leds[0] = CRGB::Blue;
  } else {
    leds[0] = CRGB::Green;
  }

  FastLED.show();
  delay(500); // show current display for 500 ms (0.5 seconds); can be changed in accordance to how often the satellite transmits data
  leds[0] = CRGB::Black;
}

/*
useful links:
JSON parsing: https://arduinojson.org/v6/example/parser, https://arduinojson.org/v6/assistant
right ascension, declination explanation: https://www.youtube.com/watch?v=ACHACvEAXUE
*/