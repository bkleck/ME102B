#include <Tone32.h>
#include "pitches.h"

#define SPKR 25  // change this to whichever pin you want to use
#define SPKR_CH 0

int tempo = 200;  // change this to make the song slower or faster. The larger the faster

// notes of the moledy followed by the duration.
// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
// !!negative numbers are used to represent dotted notes,
// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
int melody[] = {
  NOTE_C4, 4, NOTE_G3, 8, NOTE_G3, 8, NOTE_A3, 4, NOTE_G3, 4, 0, 4, NOTE_B3, 4, NOTE_C4, 4
};

int notes = sizeof(melody) / sizeof(melody[0]) / 2;  // sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
int wholenote = (60000 * 4) / tempo;  // this calculates the duration of a whole note in ms
int divider = 0, noteDuration = 0;

void setup() {
  /* iterate over the notes of the melody. */
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

void loop() {
  // no need to repeat the melody.
}
