#define LED 15  // declare the LED pin number, CHANGE THIS!
#define POT 12  // declare the potentiometer pin number, CHANGE THIS!
const int threshold = 50;
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  pinMode(POT, INPUT);

  // setup the LED PWM functionalities for ESP32
  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(LED, ledChannel);
}

void loop() {
  // put your main code here, to run repeatedly:

  int val = analogRead(POT);
  int led_val = map(val, 0, 4095, 0, 255); //map potentiometer values to LED values
  ledcWrite(ledChannel, led_val);
  
}

/* useful functions */
//pinMode(LED, OUTPUT);  // configures the specified pin to behave either as an input or an output.
//pinMode(POT, INPUT);
//digitalWrite(LED, HIGH);  // write a HIGH or a LOW value to a digital pin.
//digitalWrite(LED, LOW);
//int val = analogRead(POT);  // reads the value from the specified analog pin. This means that it will map input voltages between 0 and the operating voltage(5V or 3.3V) into integer values between 0 and 4095. 
