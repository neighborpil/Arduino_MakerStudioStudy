#include <core_build_options.h>
#include <swRTC.h>

#include <LiquidCrystal.h>

/* Turn On LED */
#define SHOWLOG true
#define PIEZO_OUTPUT 13
#define SWITCH_INPUT 12
#define VARIABLE_REGISTER_INPUT A0

const int INPUT_DIGITAL_PINS[] = { SWITCH_INPUT };
const int OUTPUT_DIGITAL_PINS[] = { PIEZO_OUTPUT };


void setup() {
  if (SHOWLOG) {
    Serial.begin(9600);
  }

  SetDigitalPins();


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
  //  lcd.noDisplay();
  //  delay(500);
  //
  //  lcd.display();
  //  delay(500);

  Test_SwitchAndPiezoSpeaker();
  Test_VariableRegister();

  delay(1000);
}

void Test_SwitchAndPiezoSpeaker() {
  if (digitalRead(SWITCH_INPUT) == HIGH) {
    ShowLog("High");
    digitalWrite(13, HIGH);
    //tone(PIEZO_OUTPUT, 3000, 100);
  } else {
    //noTone(PIEZO_OUTPUT);

    ShowLog("LOw");
    digitalWrite(13, LOW);
  }
}

void Test_VariableRegister() {
  int variableRegisterValue = analogRead(VARIABLE_REGISTER_INPUT);
  ShowLog("Variable Register Value: " + String(variableRegisterValue));
}

void ShowLog(String message) {

  if (SHOWLOG == true) {
    Serial.println(message);
  }
}
