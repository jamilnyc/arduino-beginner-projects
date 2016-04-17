/**
 * Reads an analog value and uses it to dim a color of an RGB
 * LED. The color is controlled by a button.
 * 
 * Connections:
 * 1) Pin 1 of 50k potentiometer (POT) to ground (GND)
 * 2) Pin 3 of POT to 5 volts (VCC)
 * 3) Pin 2 of POT to analog input A0
 * 4) Pin 1 of push button to VCC
 * 5) Pin 2 of push button to digital pin 2
 * 6) Digital pin 2 to pin 1 of resistor R4 (10M)
 * 7) R4 pin 2 to GND
 * 8) Pin 11 to pin 1 of R1 (220 ohms)
 * 9) Pin 2 of R1 to RGB LED red pin
 * 10) Pin 10 to pin 1 of R2 (220 ohms)
 * 11) Pin 2 of R2  to RGB LED green pin
 * 12) Pin 11 to pin 1 of R3 (220 ohms)
 * 13) Pin 2 of R3 to RGB LED blue pin
 * 14) Cathode of RGB LED to GND
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
  

  // Cycle through color modes
  if (buttonValue == HIGH) {
    if (buttonMode == BUTTON_RED) {
      buttonMode = BUTTON_GREEN;
    } else if (buttonMode == BUTTON_GREEN) {
      buttonMode = BUTTON_BLUE;
    } else {
      buttonMode = BUTTON_RED;
    }
  }

  // Read value from potentiometer and convert it to range 0-255
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

