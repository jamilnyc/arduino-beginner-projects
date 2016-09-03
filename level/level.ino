/**
 * TODO:
 * Wiring Schematic
 * More Comments
 * ReadMe file
 */

const int X_PIN = A0; // x-axis of the accelerometer
const int Y_PIN = A1; // y-axis
const int Z_PIN = A2; // z-axis

// Digital output pins for the LEDs
const int LED_LEFT = 7;
const int LED_CENTER = 6;
const int LED_RIGHT = 5;
const int LED_TOP = 4;
const int LED_BOTTOM = 3;

// How far past 0 until we consider it
// tilted. May be adjusted for your needs.
// Used for all dimensions;
const int TOLERANCE = 5;

/**
 * These constants are substracted from the value
 * read in from the accelerometer. They are the result
 * of some experimentation and are what values are
 * necessary to make the accelerometer read 0 on all
 * axes when on a level surface.
 * 
 * To figure out your values: Initially set these 
 * values to 0 and place the board on a known
 * level surface and see how far the values read in deviate
 * from 0. Then adjust accordingly. Make sure you don't move
 * or tilt the accelerometer chip after you've calibrated it.
 */
const int X_CALIBRATION = -335;
const int Y_CALIBRATION = -335;
const int Z_CALIBRATION = -404;

// Stores the current value read in from the accelerometer
int x, y, z;

void setup()
{
  // Initialize the serial monitor
  Serial.begin(9600);

  // Set output pins
  pinMode(LED_LEFT, OUTPUT);
  pinMode(LED_CENTER, OUTPUT);
  pinMode(LED_RIGHT, OUTPUT);
  pinMode(LED_TOP, OUTPUT);
  pinMode(LED_BOTTOM, OUTPUT);
  
}

void loop()
{
  readAccelerometerValues();
  printAccelerometerValues();
  
  if (isLevel()) {
    digitalWrite(LED_LEFT, LOW);
    digitalWrite(LED_CENTER, HIGH);
    digitalWrite(LED_RIGHT, LOW);
    digitalWrite(LED_TOP, LOW);
    digitalWrite(LED_BOTTOM, LOW);
  } else if (isTiltedLeft()) {
    digitalWrite(LED_LEFT, HIGH);
    digitalWrite(LED_CENTER, LOW);
    digitalWrite(LED_RIGHT, LOW);
    digitalWrite(LED_TOP, LOW);
    digitalWrite(LED_BOTTOM, LOW);
  } else if (isTiltedRight()) {
    digitalWrite(LED_LEFT, LOW);
    digitalWrite(LED_CENTER, LOW);
    digitalWrite(LED_RIGHT, HIGH);
    digitalWrite(LED_TOP, LOW);
    digitalWrite(LED_BOTTOM, LOW);
  } else if (isTiltedForward()) {
    digitalWrite(LED_LEFT, LOW);
    digitalWrite(LED_CENTER, LOW);
    digitalWrite(LED_RIGHT, LOW);
    digitalWrite(LED_TOP, HIGH);
    digitalWrite(LED_BOTTOM, LOW);
  } else {
    digitalWrite(LED_LEFT, LOW);
    digitalWrite(LED_CENTER, LOW);
    digitalWrite(LED_RIGHT, LOW);
    digitalWrite(LED_TOP, LOW);
    digitalWrite(LED_BOTTOM, HIGH);
  }
  
  delay(100); 
}

bool isLevel()
{
  return (x > -TOLERANCE && x < TOLERANCE) &&  (y > -TOLERANCE && y < TOLERANCE);
}

bool isTiltedRight()
{
  return x <= -TOLERANCE;
}

bool isTiltedLeft()
{
  return x >= TOLERANCE;
}

bool isTiltedForward()
{
  return y <= -TOLERANCE;
}

bool isTiltedBack()
{
  return y >= TOLERANCE;
}

void readAccelerometerValues()
{
  x = analogRead(X_PIN) + X_CALIBRATION;
  delay(1);
  y = analogRead(Y_PIN) + Y_CALIBRATION;
  delay(1); 
  z = analogRead(Z_PIN) + Z_CALIBRATION;
}

void printAccelerometerValues()
{
  Serial.print("X: ");
  Serial.print(x); 
  Serial.print("\t");
  Serial.print("Y: ");
  Serial.print(y);
  Serial.print("\t");
  Serial.print("Z: ");
  Serial.print(z); 
  Serial.print("\n");
}



