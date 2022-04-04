#include <string>
#include <cstdlib>

using namespace std;

/* PID gains */
float kp = 10;
float ki = 0.1;
float kd = 1;

String gain;
String amount;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    String reading = Serial.readStringUntil('\n');  // read from the Serial Monitor
    int N = 10;
    for (int i=0; i<N; i++) {
      if (i==0) {
        gain = gain + reading[i];
      }
      else {
        amount = amount + reading[i];
      }
    }
  }

  if (gain == "p") {
    kp = amount.toFloat();
  }
  else if (gain == "i") {
    ki = amount.toFloat();
  }
  else if (gain == "d") {
    kd = amount.toFloat();
  }
  
  Serial.println(gain);
  Serial.println(amount);
  Serial.println("kp = " + String(kp) + ", ki = " + String(ki) + ", kd = " + String(kd));
  delay(500);
}

/* useful functions */
//myString.substring(from, to)
//myString.length()
//myString.toFloat()
//myString.charAt(n)
