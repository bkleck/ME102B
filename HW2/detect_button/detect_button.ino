const int inputPin = 13;
int button_state;

void setup() {
  Serial.begin(115200); 
  pinMode(inputPin, INPUT); 
}

void loop() {
  button_state = digitalRead(inputPin);
  Serial.print(button_state);
  delay(500);
}
