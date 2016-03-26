/**
 * Requirements: Fade in and out the LED under normal conditions.
 * Under "emergency" conditions, press the button and flash he LED quickly!
 */

const int ledPin = 9;
const int buttonPin = 10;
const int EMERGENCY_MODE = HIGH;

int digitalLedValue = LOW;
unsigned long previousTime = 0;
long interval = 30;
bool fadeIn = true;
int fadeValue = 0;
const int fadeIncrement = 5;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int buttonValue = digitalRead(buttonPin);
  Serial.println(buttonValue);
  delay(1);
  
  // put your main code here, to run repeatedly:
  unsigned long currentTime = millis();

  // Every 30 milliseconds
  if (currentTime - previousTime >= interval) {
    previousTime = currentTime;

    if (buttonValue == EMERGENCY_MODE) {
      interval = 200;
      digitalWrite(ledPin, digitalLedValue);
      digitalLedValue = !digitalLedValue;
    } else {
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
