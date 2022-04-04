void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  /* read function 1 */
  if (Serial.available()) {
    Serial.println(Serial.read());
  }
  /* read function 2 */
//  if (Serial.available()) {
//    Serial.println(Serial.readStringUntil('\n'));
//  }
}
