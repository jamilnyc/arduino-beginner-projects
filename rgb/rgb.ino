/**
 * Reads an analog value and uses it to dim a color of an RGB
 * LED. The color is controlled by a button.
 */

#define BUTTON_RED 0
#define BUTTON_GREEN 1
#define BUTTON_BLUE 2

int redPin = 11;
int greenPin = 10;
int bluePin = 9;

int sensorPin = A0;
int sensorValue = 0;

int buttonMode = BUTTON_RED;
int redValue = 0;
int greenValue = 0;
int blueValue = 0;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Read in Button
  // TODO Add debouncing
  int buttonValue = digitalRead(2);
  

  if (buttonValue == HIGH) {
    if (buttonMode == BUTTON_RED) {
      buttonMode = BUTTON_GREEN;
    } else if (buttonMode == BUTTON_GREEN) {
      buttonMode = BUTTON_BLUE;
    } else {
      buttonMode = BUTTON_RED;
    }
  }
  sensorValue = analogRead(sensorPin);
  sensorValue = map(sensorValue, 0, 1023, 0, 255);
  
  Serial.print("Sensor Value = ");
  Serial.print(sensorValue);
  Serial.print("; Button Mode (Color) = ");
  Serial.println(buttonMode);

  if (buttonMode == BUTTON_RED) {
    redValue = sensorValue;
  } else if (buttonMode == BUTTON_GREEN) {
    greenValue = sensorValue;
  } else {
    blueValue = sensorValue;
  }

  setColor(redValue, greenValue, blueValue);
}

// Works with base ten integers and hex values
void setColor(int red, int green, int blue)
{
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

// Not used
// Cycles through all colors
void cycle() {
  int interval = 10;
  for (int i = 0; i <= 255; i += interval) {
    for (int j = 0; j <= 255; j += interval) {
      for (int k = 0; k <= 255; k += interval) {
        setColor(i, j, k);
        delay(10);
      }
    }
  }
}

