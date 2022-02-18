#include <Arduino.h>
#define BTN 27  // declare the button ED pin number

void IRAM_ATTR isr() {  // the function to be called when interrupt is triggered
  Serial.println("Pressed!");
}

void setup() {
  // put your setup code here, to run once:
  pinMode(BTN, INPUT);  // configures the specified pin to behave either as an input or an output
  attachInterrupt(BTN, isr, RISING);  // set the "BTN" pin as the interrupt pin; call function named "isr" when the interrupt is triggered; "Rising" means triggering interrupt when the pin goes from LOW to HIGH
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  // nothing has to be running continuously since the interrupt takes care of that
}
