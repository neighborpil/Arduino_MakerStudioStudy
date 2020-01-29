/* - */
#define SHOW_LOG true
#define DEBUG false

#define POT A0 // switch
#define EN 9 // enable
#define MC1 3 // 1A 
#define MC2 2 // 2A

const int INPUT_DIGITAL_PINS[] = {};
const int OUTPUT_DIGITAL_PINS[] = { EN, MC1, MC2 };

void setup() {
  if (SHOW_LOG) {
    Serial.begin(9600);
  }

  SetDigitalPins();

  //Brake();

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

  ChangeMotorSpeedAndDirection();

}

void ChangeMotorSpeedAndDirection() {

  int switchValue = GetSwitchValue();
  
  ChangeSpeedAndDirection(switchValue);
}

int GetSwitchValue() {

  int switchValue = analogRead(POT);
  if (DEBUG) {
    ShowLog("Switch Value: " + String(switchValue));
  }

  return switchValue;
}

void ChangeSpeedAndDirection(int switchValue){
  int velocity;
  if (switchValue > 562) {
    velocity = map(switchValue, 563, 1023, 0, 255);
    Forward(velocity);
  } else if (switchValue < 462) {

    velocity = map(switchValue, 0, 461, 0, 255);
    Backward(velocity);
  } else {
    Brake();
  }
}

void Forward(int velocity){
  digitalWrite(EN, LOW);
  digitalWrite(MC1, HIGH);
  digitalWrite(MC2, LOW);
  analogWrite(EN, velocity);

  if(DEBUG){
    ShowLog("Velocity :" + velocity);
  }
}

void Backward(int velocity){
  digitalWrite(EN, LOW);
  digitalWrite(MC1, LOW);
  digitalWrite(MC2, HIGH);
  analogWrite(EN, velocity);

  if(DEBUG){
    ShowLog("Velocity :" + velocity);
  }
}

void Brake(){
  digitalWrite(EN, LOW);
}

void ShowLog(String message) {
  if (SHOW_LOG) {
    Serial.println(message);
  }
}
