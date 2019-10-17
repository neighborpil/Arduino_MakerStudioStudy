#define SWITCH_INPUT 2
#define LED_OUTPUT 7

const int INPUT_DIGITAL_PINS[] = { SWITCH_INPUT };
const int OUTPUT_DIGITAL_PINS[] = { LED_OUTPUT };

void setup() {
  Serial.begin(9600);

  SetDigitalPins();

  ShowLog("ProgramStarted");
}

bool isPressed = false;

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

  ChangeSwitchButtonValue();

  ChangeLEDLight();

  delay(1000);
}

void ChangeSwitchButtonValue() {
  int inputValue = digitalRead(SWITCH_INPUT);

  if (inputValue) {
    ShowLog("Button Pressed");
    isPressed = !isPressed;
  }
}

void ChangeLEDLight() {
  if (isPressed) {
    digitalWrite(LED_OUTPUT, HIGH);
  }
  else {
    digitalWrite(LED_OUTPUT, LOW);
  }
}

void ShowLog(String message) {
  Serial.println(message);
}
