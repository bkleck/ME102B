#define LED 13

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);  // configures the specified pin to behave either as an input or an output.
}

void loop() {
  // put your main code here to run repeatedly:
  digitalWrite(LED, HIGH);  // write a HIGH or a LOW value to a digital pin.
  delay(1000);
  digitalWrite(LED, LOW);
  delay(1000);
}

/* useful functions */
//digitalWrite(LED, HIGH);  // write a HIGH or a LOW value to a digital pin.
//digitalWrite(LED, LOW);
//delay(1000);  // let the microcontroller idle for 1000ms
