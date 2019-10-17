/* Turn On LED */
#define SHOWLOG true

#define SWITCH_INPUT 2

#define LED_RED_OUTPUT 9
#define LED_GREEN_OUTPUT 10
#define LED_BLUE_OUTPUT 11

#define RED 0
#define GREEN 1
#define BLUE 2

#define ON 0
#define OFF 1

const int INPUT_DIGITAL_PINS[] = { SWITCH_INPUT };
const int OUTPUT_DIGITAL_PINS[] = { };

void setup() {
  if (SHOWLOG) {
    Serial.begin(9600);
  }

  SetDigitalPins();

  ShowLog("ProgramStarted");
}

bool isPressed = false;
int currentColor = RED;

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


  if (inputValue && !isPressed) {
    isPressed = true;

    currentColor++;

    if (currentColor > BLUE) {
      currentColor = RED;
    }

    isPressed = false;

    ShowLog("Button Pressed.");
  }
}


void ChangeLEDLight() {

  int red = OFF, green = OFF, blue = OFF;

  switch (currentColor) {
    case RED: red = ON; break;
    case GREEN: green = ON; break;
    case BLUE: blue = ON; break;
  }

  //TurnOnLight(red, green, blue);
  TurnOnLightGradually(red, green, blue);

  ShowLog("Current Color: R(" + String(red) + "), G(" + String(green) + "), B(" + String(blue) + ")");
}

void TurnOnLight(int red, int green, int blue) {
  analogWrite(LED_RED_OUTPUT, red);
  analogWrite(LED_GREEN_OUTPUT, green);
  analogWrite(LED_BLUE_OUTPUT, blue);
}


void TurnOnLightGradually(int red, int green, int blue) {

  int redVal = 255, greenVal = 255, blueVal = 255;
  for (int i = 255; i >= 0; i--) {

    if(red == ON){
      redVal = i;
    } else if(green == ON){
      greenVal = i;
    } else if(blue == ON){
      blueVal = i;
    }

    TurnOnLight(redVal, greenVal, blueVal);
    
    delay(15);
  }
}

void ShowLog(String message) {

  if (SHOWLOG == true) {
    Serial.println(message);
  }
}
