#include <Tone32.h>
#include <ezButton.h>
#include "pitches.h"

// speaker pins
#define SPKR 25  
#define SPKR_CH 0
#define REST 0

// ultrasonic pins
#define trigPin 5
#define echoPin 18

// button pin
#define BTN 12
ezButton button(BTN); 

float duration, distance;
bool armed = false;

unsigned long debounceDelay = 2000;
unsigned long lastDebounceTime = 0;

void IRAM_ATTR isr() {  // the function to be called when interrupt is triggered
  if (armed == false){
    armed = true;
  }
  else {
    armed = false;
  }
  Serial.println("Pressed!");
  Serial.println(armed);
}

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // configure button to activate when pressed
  button.setDebounceTime(debounceDelay); 
  attachInterrupt(BTN, isr, RISING);
  Serial.begin(115200);
}

// melodies for greeting + alarm
int melody[] = {
  NOTE_A4,4, NOTE_F4,-8, NOTE_C5,16, NOTE_A4,2,//4
  NOTE_E5,4, NOTE_E5,4, NOTE_E5,4, NOTE_F5,-8, NOTE_C5,16,
  NOTE_A4,4, NOTE_F4,-8, NOTE_C5,16, NOTE_A4,2,
  
  NOTE_A5,4, NOTE_A4,-8, NOTE_A4,16, NOTE_A5,4, NOTE_GS5,-8, NOTE_G5,16, //7 
  NOTE_DS5,16, NOTE_D5,16, NOTE_DS5,8, REST,8, NOTE_A4,8, NOTE_DS5,4, NOTE_D5,-8, NOTE_CS5,16,

  NOTE_C5,16, NOTE_B4,16, NOTE_C5,16, REST,8, NOTE_F4,8, NOTE_GS4,4, NOTE_F4,-8, NOTE_A4,-16,//9
  NOTE_C5,4, NOTE_A4,-8, NOTE_C5,16, NOTE_E5,2,
};

int melody_2[] = {
  NOTE_C4,4, NOTE_C4,8, 
  NOTE_D4,-4, NOTE_C4,-4, NOTE_F4,-4,
  NOTE_E4,-2, NOTE_C4,4, NOTE_C4,8, 
  NOTE_D4,-4, NOTE_C4,-4, NOTE_G4,-4,
  NOTE_F4,-2, NOTE_C4,4, NOTE_C4,8,
};

void Greeting() {
  int divider = 0, noteDuration = 0;
  int tempo = 400;
  int notes = sizeof(melody) / sizeof(melody[0]) / 2;
  int wholenote = (60000 * 4) / tempo;

  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
    divider = melody[thisNote + 1];  // calculates the duration of each note
    if (divider > 0) {
      noteDuration = (wholenote) / divider;  // regular note, just proceed
    } 
    else if (divider < 0) {
      noteDuration = (wholenote) / abs(divider);  // dotted notes are represented with negative durations!!
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }
    tone(SPKR, melody[thisNote], noteDuration * 0.9, SPKR_CH);  // we only play the note for 90% of the duration, leaving 10% as a pause
    delay(noteDuration);  // Wait for the specief duration before playing the next note.
    noTone(SPKR, SPKR_CH);  // stop the waveform generation before the next note.
  }
}

void Alarm(){
  int divider = 0, noteDuration = 0;
  int tempo = 300;
  int notes = sizeof(melody_2) / sizeof(melody_2[0]) / 2;
  int wholenote = (60000 * 4) / tempo;

  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
    divider = melody_2[thisNote + 1];  // calculates the duration of each note
    if (divider > 0) {
      noteDuration = (wholenote) / divider;  // regular note, just proceed
    } 
    else if (divider < 0) {
      noteDuration = (wholenote) / abs(divider);  // dotted notes are represented with negative durations!!
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }
    tone(SPKR, melody_2[thisNote], noteDuration * 0.9, SPKR_CH);  // we only play the note for 90% of the duration, leaving 10% as a pause
    delay(noteDuration);  // Wait for the specief duration before playing the next note.
    noTone(SPKR, SPKR_CH);  // stop the waveform generation before the next note.
  }
}

void loop() {
  button.loop();
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
  Serial.println(distance);

  if (distance < 10) {
    if (armed == true){
      Alarm();
    }
    else {
      Greeting();
    }
  }
  if (button.isPressed()) {
    attachInterrupt(BTN, isr, RISING); 
  }
  
  delay(1000);
}
