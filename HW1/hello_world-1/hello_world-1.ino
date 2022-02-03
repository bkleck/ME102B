void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);  // set the data rate in bits per second (baud) for serial data transmission to 115200
}

void loop() {
  // put your main code here, to run repeatedly:
  //  Serial.println("Hello World!");  // print whatever is in the bracket and a newline
  Serial.print("Hello World!" + String(10));
  Serial.println('\n');
  //  Serial.write(100);

  /* method 1 */
  delay(2000);  // do nothing for 2000ms

  /* method 1 */
  long current_time = millis();
  while (millis() - current_time < 2000) {

  }
}
