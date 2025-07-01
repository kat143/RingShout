#include <FastLED.h>
#include <SoftwareSerial.h>

#define NUM_LEDS 4
#define LED_PIN 4

CRGB leds[NUM_LEDS];
SoftwareSerial BTserial(2, 3);
const byte numChars = 64;
char charStorage[numChars];
boolean unshownData = false;
float numericalData[2];

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

//TODO: string processing to get just the numbers from the input string
/*
https://forum.arduino.cc/t/serial-input-basics-updated/382007/3
https://www.geeksforgeeks.org/how-to-split-a-string-in-cc-python-and-java/
https://docs.arduino.cc/language-reference/en/variables/data-types/stringObject/

https://www.tinkercad.com/things/cqjUZh0w34x/editel?returnTo=%2Fdashboard
https://wokwi.com/projects/434859420768083969
*/

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

        if (index >= numChars) {
          // force "quit" accepting information
          /*
          charStorage[index] = '\0';
          receiving = false;
          index = 0;
          unshownData = true;
          */

          // given code (keeps replacing last char)
          /**/
          index = numChars - 1;
          /**/
        }
      } else {
        charStorage[index] = '\0';  // terminate the string
        receiving = false;
        index = 0;
        unshownData = true;
      }
    } else if (c == starter) {
      receiving = true;
    }
  }
}

void showData() {
  //Serial.println("showing");

  if (unshownData == true) {
    /*
    leds[0] = CRGB::Blue;
    FastLED.show();

    Serial.print("new: ");
    Serial.println(charStorage);
    */

    /**/
    numericalize();
    Serial.print(numericalData[0]);
    Serial.print(" ");
    Serial.println(numericalData[1]);
    trigLed();
    /**/

    unshownData = false;
  } else {
    //Serial.println("nothing to show");

    /*
    leds[0] = CRGB::Yellow;
    FastLED.show();
    */
    delay(250);
  }
}

/**/
void numericalize() {
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

void trigLed() {
  float longitude = numericalData[0] + 180.0;
  float altitude = numericalData[1];

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
  delay(250);

  leds[turnOn] = CRGB::Black;
  leds[index] = CRGB::Black;
  FastLED.show();
}
/**/