#include <core_build_options.h>
#include <swRTC.h>

#include <LiquidCrystal.h>

/* Turn On LED */
#define SHOWLOG true

const int INPUT_DIGITAL_PINS[] = { 9 };
const int OUTPUT_DIGITAL_PINS[] = { 8 };

//LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // LiquidCrystal(rs, enable, data0, data1, data2, data3)

void setup() {
  if (SHOWLOG) {
    Serial.begin(9600);
  }

  SetDigitalPins();

  //  lcd.begin(16, 2); // col, row
  //  lcd.print("Hello, World!");

  ShowLog("ProgramStarted");
}

void SetDigitalPins() {

  int inputPinsLength = sizeof(INPUT_DIGITAL_PINS) / sizeof(INPUT_DIGITAL_PINS[0]);
  SetDigitalPins(INPUT_DIGITAL_PINS, inputPinsLength, INPUT);

  int outputPinsLength = sizeof(OUTPUT_DIGITAL_PINS) / sizeof(OUTPUT_DIGITAL_PINS[0]);
  SetDigitalPins(OUTPUT_DIGITAL_PINS, outputPinsLength, OUTPUT);
}

void SetDigitalPins(int pins[], int pinsLength, const int mode) {

  for (int i = 0; i < pinsLength; i++) {
    pinMode(pins[i], mode);
  }
}

void loop() {
  if (digitalRead(9) == true) {
    ShowLog("button pressed");
    tone(8, 3000, 100);
    delay(100);
    noTone(8);
    delay(1000);
  }
  //  lcd.noDisplay();
  //  delay(500);
  //
  //  lcd.display();
  //  delay(500);
}


void ShowLog(String message) {

  if (SHOWLOG == true) {
    Serial.println(message);
  }
}
