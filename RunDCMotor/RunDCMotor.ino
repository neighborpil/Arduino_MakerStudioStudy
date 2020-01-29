/* - */
#define SHOW_LOG true

#define EN 11
#define IN1 9
#define IN2 8

const int INPUT_DIGITAL_PINS[] = {};
const int OUTPUT_DIGITAL_PINS[] = { IN1, IN2 };

void setup() {
  if (SHOW_LOG) {
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

  // Go Forward
  analogWrite(EN, 153);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  delay(5000);

  digitalWrite(EN, LOW);

  delay(200);

  // Go Backward
  analogWrite(EN, 255);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  delay(5000);
}

void ShowLog(String message) {
  if (SHOW_LOG) {
    Serial.println(message);
  }
}
