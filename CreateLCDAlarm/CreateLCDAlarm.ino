#include <core_build_options.h>
#include <swRTC.h>
#include <LiquidCrystal.h>

/* Turn On LED */
#define SHOWLOG true
#define PIEZO_OUTPUT 8
#define SWITCH_INPUT 9

const int INPUT_DIGITAL_PINS[] = { SWITCH_INPUT };
const int OUTPUT_DIGITAL_PINS[] = { PIEZO_OUTPUT };

#define TIME_MSG_LEN 11

#define TIME_HEADER 255

LiquidCrystal lcd(12, 11, 2, 3, 4, 5 ); // LiquidCrystal(rs, enable, data0, data1, data2, data3)
swRTC rtc;

int alarmTime;


void setup() {
  if (SHOWLOG) {
    Serial.begin(9600);
  }

  SetDigitalPins();

  InitializeLCD();

  InitializeRTC();

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

void InitializeLCD() {
  lcd.begin(16, 2); // col, row
  lcd.clear();
}

void InitializeRTC() {

  rtc.stopRTC();
  rtc.setTime(07, 38, 0);
  rtc.setDate(17, 10, 2019);
  rtc.startRTC();
}

void loop() {
  int currentTime;
  lcd.setCursor(0, 0);

  // 1초단위 갱신하며 시간 표시
  ShowCurrentTime();
  ShowCurrentDate();

  // 알람 시간 표시
  ShowSavedAlarm();

  CheckTheAlarmTime();

  // todo: refactor after this line

  // 스위치 버튼이 눌렸을 때 피에조 스피커의 소리를 0으로 하고 알람 시간 초기화
  if (digitalRead(SWITCH_INPUT)) {
    alarmTime = 0;
    day = 0;
    analogWrite(PIEZO_OUTPUT, 0);
    Serial.println("Alarm clock is initialized");
    Serial.println("AM00:00");
  }

  // 시리얼 통신을 통해 알람시간을 입력받고 시리얼 모니터에 출력
  char theDay[4];
  int i = 0;
  if (Serial.available()) {
    while (Serial.available()) {
      theDay[i] = Serial.read();
      i++;
    }

    day = atoi(theDay);

    if (day / 100 > 12) {
      Serial.print("PM");
      Serial.print((day / 100) - 12);
    }
    else {
      Serial.print("AM");
      Serial.print(day / 100);
    }

    Serial.print(":");
    if (day % 100 < 10)
      Serial.print("0");
    Serial.println(day % 100);

    alarmTime = checkTheAlarmClock(day);
  }


  // 1초마다 갱신
  delay(1000);
}

void ShowCurrentTime() {
  SetAM_PM(rtc.getHours());
  lcd.print(":");
  SetLowThanTen(rtc.getMinutes());
  lcd.print(":");
  SetLowThanTen(rtc.getSeconds());
}

// AM_PM 구분, 시간
void SetAM_PM(int hour) {
  if (hour > 12)
    lcd.print("PM");
  else
    lcd.print("AM");

  lcd.print(hour % 12, DEC); // BIN: 2, DEC: decimal, OCT: 8, HEX: 12
}

// 10ㄷ보다 작은 수를 출력할 때 앞에 0을 출력
void SetLowThanTen(int time) {
  if (time < 10) {
    lcd.print("0");
    lcd.print(time % 10);
  } else {
    lcd.print(time);
  }
}

void ShowCurrentDate() {
  lcd.print("[");
  SetLowThanTen(rtc.getMonth());
  lcd.print("/");
  SetLowThanTen(rtc.getDay());
  lcd.print("]");
}

// 알람이 울릴 시간인지 체크
void CheckTheAlarmTime() {
  int alarmHour = alarmTime / 100;
  int alarmMinute = alarmTime % 100;

  if (alarmHour == rtc.getHours() && alarmMinute == rtc.getMinutes()) {
    analogWrite(PIEZO_OUTPUT, 128);
  }
}

void ShowSavedAlarm() {
  lcd.setCursor(0, 1);
  lcd.print("Alarm ");
  SetAM_PM(alarmTime / 100);
  lcd.print("0");
  SetLowThanTen(alarmTime % 100);
}

// 유효한 알람인지 체크
int checkTheAlarmClock(int time) {
  if (time / 100 < 24 && time % 100 < 60) {
    Serial.println("Success");
    return time;
  } else {
    Serial.println("Failed");
    return 0;
  }
}


void ShowLog(String message) {

  if (SHOWLOG == true) {
    Serial.println(message);
  }
}
