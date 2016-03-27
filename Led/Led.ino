/**
 * Simple circuit that fades an LED in and out by default
 * and blinks the LED on/off rapidly when the push button
 * is pressed.
 * 
 * Connections:
 * 1) Pin 9 to LED anode
 * 2) LED cathode to 1K resistor (R1)
 * 3) Other end of R1 to GND
 * 4) Pin 10 to 1 side of push button and 10K resistor (R2)
 * 5) Other side of push button to VDD (5V)
 * 6) Other Side of R2 to GND
 */

const int ledPin = 9;
const int buttonPin = 10;
const int BLINK_MODE = HIGH; // Switch to change the default behavior

int digitalLedValue = LOW;
unsigned long previousTime = 0;
long interval = 30; // Initialized to fade interval
bool fadeIn = true; // Either fade in or out
int fadeValue = 0;
const int fadeIncrement = 5; // Adjust to fade faster or slower

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Is the button pressed?
  int buttonValue = digitalRead(buttonPin);

  // Print current button value to Serial Monitor
  Serial.println(buttonValue);
  delay(1);
  
  unsigned long currentTime = millis();

  // If 30 milliseconds have passed
  if (currentTime - previousTime >= interval) {
    // Reset the previous time
    previousTime = currentTime;

    // If button is pressed
    if (buttonValue == BLINK_MODE) {
      // Slow down the interval for blinking
      interval = 200;
      digitalWrite(ledPin, digitalLedValue);

      // If the LED was on, turn it off and vice-versa
      digitalLedValue = !digitalLedValue;
    } else {
      // Speed up interval for fading
      interval = 30;
      
      // Incrementally increase/decrease the brightness of the LED
      fadeValue += fadeIn ? fadeIncrement : -fadeIncrement;
  
      // Switch fading direction once you've reached
      // the maximum or minimum brightness
      if (fadeValue >= 255 || fadeValue <= 0) {
        fadeIn = !fadeIn;
      }
      analogWrite(ledPin, fadeValue);
    }
  }
}
