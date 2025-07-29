#include <FastLED.h>
#include <SoftwareSerial.h>

#define NUM_LEDS 172 // 172 LEDs is approx. 2.8 m, which is approx. 113 in., which is approx. circumference of 36 in. diameter
#define LED_PIN 4 // the pin on the Arduino connected (through a resistor) to the Din pad on the LED

CRGB leds[NUM_LEDS];
SoftwareSerial BTserial(2, 3);
const byte numChars = 64;
char charStorage[numChars];
boolean unshownData = false;
float numericalData[2] = {NULL, NULL};
boolean pastFlag = false;
float pastData[2];
boolean pattern = true;
int fakeData = 0;

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(15);

  Serial.begin(9600);
  BTserial.begin(9600);
  Serial.println("Started");
}

void loop() {
  receiveData();
  showData();
}

void receiveData() {
  static boolean receiving = false;
  static byte index = 0;
  char starter = '<';
  char ender = '>';
  char c;

  while (BTserial.available() > 0 && unshownData == false) {
    c = BTserial.read();

    if (receiving == true) {
      if (c != ender) {
        charStorage[index] = c;
        index++;

        if (index >= numChars) { // (keeps replacing last char)
          index = numChars - 1;
        }
      }
      else {
        charStorage[index] = '\0';  // terminate the string
        receiving = false;
        index = 0;
        unshownData = true;
      }
    }
    else if (c == starter) {
      receiving = true;
    }
    else if (c == 'a') {
      pattern = !pattern;
      break;
    }
  }
}

void showData() { // comes w/ a 1s delay, regardless of what happens
  if (unshownData == true) {
    numericalize();

    float altitude = numericalData[0];
    float longitude = numericalData[1] + 180.0;
    int turnOn = longitude / (360.0 / NUM_LEDS); turnOn = turnOn % NUM_LEDS;
    if (pattern) PatternOne(altitude, turnOn);
    else PatternTwo(altitude, turnOn);

    unshownData = false;
    fakeData = 0;
    /*
    pastFlag = true;
    pastData[0] = numericalData[0];
    pastData[1] = numericalData[1];
    */
  }
  else {
    if (!pastFlag) {
      delay(1000);
    }
    else {
      fakeData++;

      float altitude = pastData[0];
      float longitude = pastData[1] + 180.0;
      int turnOn = longitude / (360.0 / NUM_LEDS);// if ((fakeData % 6) < 1) turnOn += (fakeData * (360.0 / NUM_LEDS)); turnOn = turnOn % NUM_LEDS;
      if (pattern) PatternOne(altitude, turnOn);
      else PatternTwo(altitude, turnOn);
    }
  }
}

void numericalize() {
  Serial.println("charStorage");

  String temporary = String("");
  int dataIndex = 0;
  for (int i = 0; i < sizeof(charStorage); i++) {
    if (charStorage[i] != ' ') {
      temporary.concat(charStorage[i]);
    }
    else {
      numericalData[dataIndex] = temporary.toDouble();

      temporary = String("");
      dataIndex++;
      if (dataIndex == 2) break;
    }
  }
  numericalData[dataIndex] = temporary.toDouble();
}

void PatternOne(float altitude, int turnOn) {
  Serial.print("p1: ");
  Serial.println(turnOn);
  delay(1000);

  if (altitude > 1000) leds[turnOn] = CRGB::Red;
  else leds[turnOn] = CRGB::Blue;

  int index1 = ((turnOn - 1) + NUM_LEDS) % NUM_LEDS; // 75% brightness
  if (altitude > 1000) leds[index1] = CRGB::Red;
  else leds[index1] = CRGB::Blue;
  leds[index1].fadeLightBy(64);
  int index2 = ((turnOn - 2) + NUM_LEDS) % NUM_LEDS; // 50% brightness
  if (altitude > 1000) leds[index2] = CRGB::Red;
  else leds[index2] = CRGB::Blue;
  leds[index2].fadeLightBy(128);
  int index3 = ((turnOn - 3) + NUM_LEDS) % NUM_LEDS; // 25% brightness
  if (altitude > 1000) leds[index3] = CRGB::Red;
  else leds[index3] = CRGB::Blue;
  leds[index3].fadeLightBy(192);
  FastLED.show();

  delay(1000);

  leds[turnOn] = CRGB::Black;
  leds[index1] = CRGB::Black;
  leds[index2] = CRGB::Black;
  leds[index3] = CRGB::Black;
  FastLED.show();

  pastFlag = true;
  pastData[0] = numericalData[0];
  pastData[1] = numericalData[1];
}

void PatternTwo(float altitude, int turnOn) {
  Serial.print("p2: ");
  Serial.println(turnOn);
  delay(1000);

  for (int i = 10; i >= 1; i--) {
    leds[(turnOn + i) % NUM_LEDS] = CRGB::Yellow;
    leds[((turnOn - i) + NUM_LEDS) % NUM_LEDS] = CRGB::Yellow;
    FastLED.show();

    delay(50);

    leds[(turnOn + i) % NUM_LEDS] = CRGB::Black;
    leds[((turnOn - i) + NUM_LEDS) % NUM_LEDS] = CRGB::Black;
    FastLED.show();
  }
  if (altitude > 1000) leds[turnOn] = CRGB::Red;
  else leds[turnOn] = CRGB::Blue;
  FastLED.show();

  delay(1000 - (50 * 10));

  leds[turnOn] = CRGB::Black;
  FastLED.show();

  pastFlag = true;
  pastData[0] = numericalData[0];
  pastData[1] = numericalData[1];
}

/*
void pastTrigLed() {
  float altitude = pastData[0];
  float longitude = pastData[1] + 180.0;

  int turnOn = longitude / (360.0 / NUM_LEDS);
  turnOn = turnOn % NUM_LEDS;
  if (altitude > 1000) {
    leds[turnOn] = CRGB::Red;
  }
  else {
    leds[turnOn] = CRGB::Blue;
  }

  int index = ((turnOn - 1) + NUM_LEDS) % NUM_LEDS;
  if (altitude > 1000) leds[index] = CRGB::Red;
  else leds[index] = CRGB::Blue;
  leds[index].fadeLightBy(128);
  FastLED.show();

  delay(1000);

  leds[turnOn] = CRGB::Black;
  leds[index] = CRGB::Black;
  FastLED.show();
}
*/