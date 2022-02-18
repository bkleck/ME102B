#include <Arduino.h>
#define BTN 12   // declare the button ED pin number

int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 1000;

void IRAM_ATTR isr() {  // the function to be called when interrupt is triggered
  Serial.println("Pressed!");
}

void setup() {
  // put your setup code here, to run once:
  pinMode(BTN, INPUT);  // configures the specified pin to behave either as an input or an output
  Serial.begin(115200);
}

void loop() {
  int reading = digitalRead(BTN);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        attachInterrupt(BTN, isr, RISING);
      }
    }
  }
  lastButtonState = reading;
}
