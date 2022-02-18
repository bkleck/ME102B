#include <Tone32.h>
#include "pitches.h"

#define SPKR 25  // change this to whichever pin you want to use
#define SPKR_CH 0
#define REST 0

int tempo = 200;  // change this to make the song slower or faster. The larger the faster
const int timer = 5000; // only play alarm for 5s

// notes of the moledy followed by the duration.
// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
// !!negative numbers are used to represent dotted notes,
// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
int melody[] = {
  NOTE_A4,-4, NOTE_A4,-4, NOTE_A4,16, NOTE_A4,16, NOTE_A4,16, NOTE_A4,16, NOTE_F4,8, REST,8,
  NOTE_A4,-4, NOTE_A4,-4, NOTE_A4,16, NOTE_A4,16, NOTE_A4,16, NOTE_A4,16, NOTE_F4,8, REST,8,
  NOTE_A4,4, NOTE_A4,4, NOTE_A4,4, NOTE_F4,-8, NOTE_C5,16,

  NOTE_A4,4, NOTE_F4,-8, NOTE_C5,16, NOTE_A4,2,//4
  NOTE_E5,4, NOTE_E5,4, NOTE_E5,4, NOTE_F5,-8, NOTE_C5,16,
  NOTE_A4,4, NOTE_F4,-8, NOTE_C5,16, NOTE_A4,2,
  
  NOTE_A5,4, NOTE_A4,-8, NOTE_A4,16, NOTE_A5,4, NOTE_GS5,-8, NOTE_G5,16, //7 
  NOTE_DS5,16, NOTE_D5,16, NOTE_DS5,8, REST,8, NOTE_A4,8, NOTE_DS5,4, NOTE_D5,-8, NOTE_CS5,16,

  NOTE_C5,16, NOTE_B4,16, NOTE_C5,16, REST,8, NOTE_F4,8, NOTE_GS4,4, NOTE_F4,-8, NOTE_A4,-16,//9
  NOTE_C5,4, NOTE_A4,-8, NOTE_C5,16, NOTE_E5,2,

  NOTE_A5,4, NOTE_A4,-8, NOTE_A4,16, NOTE_A5,4, NOTE_GS5,-8, NOTE_G5,16, //7 
  NOTE_DS5,16, NOTE_D5,16, NOTE_DS5,8, REST,8, NOTE_A4,8, NOTE_DS5,4, NOTE_D5,-8, NOTE_CS5,16,

  NOTE_C5,16, NOTE_B4,16, NOTE_C5,16, REST,8, NOTE_F4,8, NOTE_GS4,4, NOTE_F4,-8, NOTE_A4,-16,//9
  NOTE_A4,4, NOTE_F4,-8, NOTE_C5,16, NOTE_A4,2,
};

int divider = 0, noteDuration = 0;

void Alarm(int melody[], int divider, int noteDuration, int tempo) {
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

void setup() {
  Alarm(melody, divider, noteDuration, tempo);
}

void loop() {
  Alarm(melody, divider, noteDuration, tempo);
  int starttime = millis();
  int endtime = starttime;
  while ((endtime - starttime) <= timer)
  {
    endtime = millis();
  }
  exit(0);
}
