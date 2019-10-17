#include <core_build_options.h>
#include <swRTC.h>

#include <LiquidCrystal.h>

/* Turn On LED */
#define SHOWLOG true
#define PIEZO_OUTPUT 8
#define SWITCH_INPUT 9 
#define VARIABLE_REGISTER_INPUT A0

const int INPUT_DIGITAL_PINS[] = { SWITCH_INPUT };
const int OUTPUT_DIGITAL_PINS[] = { PIEZO_OUTPUT };

LiquidCrystal lcd(12, 11, 2, 3, 4, 5 ); // LiquidCrystal(rs, enable, data0, data1, data2, data3)
String lcdString = "";

swRTC rtc;

int temp;


void setup() {
  if (SHOWLOG) {
    Serial.begin(9600);
  }

  SetDigitalPins();

  lcd.begin(16, 2); // col, row
  lcd.print("Test");
  //lcd.clear();

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

//  Test_SwitchAndPiezoSpeaker();
//  Test_VariableRegister();

  delay(1000);
}

void Test_SwitchAndPiezoSpeaker(){
  if(digitalRead(SWITCH_INPUT) == HIGH){
    
    tone(PIEZO_OUTPUT, 3000, 100);
  } else{
    noTone(PIEZO_OUTPUT);
  }
}

void Test_VariableRegister(){
  int variableRegisterValue = analogRead(VARIABLE_REGISTER_INPUT);
  ShowLog("Variable Register Value: " + String(variableRegisterValue));
}

// AM_PM 구분
void SetAM_PM(int hour){
  if(hour > 12)
  lcd.print("PM");
  else
  lcd.print("AM");

  lcd.print(hour%12, DEC);
}

// 유효한 알람인지 체크
int checkTheAalrmClock(int time){
  if(time / 100 < 24 &&  time & 100 < 60){
    Serial.println("Success");
    return time;
  } else{
    Serial.println("Failed");
    return 0;
  }
}

// 알람이 울릴 시간인지 체크
void checkTheAlarmTime(int alarmHour, int alarmMinute){
  if(alarmHour == rtc.getHours() && alarmMinute == rtc.getMinutes()){
    analogWrite(PIEZO_OUTPUT, 128);
  }
}

void ShowLog(String message) {

  if (SHOWLOG == true) {
    Serial.println(message);
  }
}
