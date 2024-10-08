#include <MIDI.h>
#include <hellodrum.h>

// Create and bind the MIDI interface to the default hardware Serial port
MIDI_CREATE_DEFAULT_INSTANCE();

// The piezo named snare is connected to the A1 pin
HelloDrum snare(1);

// Setting
byte SNARE[6] = {
    40, // sensitivity (1 - 100)
    5,  // threshold (1 - 100)
    20, // scantime (1 - 100) (tempo que passa scaneando o pico do valor do piezo)
    12, // masktime (1 - 100) (tempo que passa ignorando valores do piezo apos o midi ser enviado)
    38, // note (pitch) (0 - 127)
    3   // Velocity Curve Type (0 - 4)
};

void setup() {
  // Listen to all incoming messages
  MIDI.begin(1);
  Serial.begin(38400);
  snare.setCurve(SNARE[5]);
}

void loop() {
  // (sensitivity, threshold, scantime, masktime)
  snare.singlePiezo(SNARE[0], SNARE[1], SNARE[2], SNARE[3]);
  
  if (snare.hit == true) {
  //Comment the lines below, and uncomment the if's for using the unique piezo for different sounds varying with force
  //if you want "standard" don't change anything 
    MIDI.sendNoteOn(SNARE[4], snare.velocity, 1);  //(note, velocity, channel)
    MIDI.sendNoteOff(SNARE[4], 0, 1);
    // if (snare.velocity < 32) {
  //     MIDI.sendNoteOn(38, snare.velocity + 64, 1);
  //     MIDI.sendNoteOff(38, 0, 1);
  //   } else if (snare.velocity < 64) {
  //     MIDI.sendNoteOn(39, snare.velocity + 32, 1);
  //     MIDI.sendNoteOff(39, 0, 1);
  //   } else if (snare.velocity < 96) {
  //     MIDI.sendNoteOn(40, snare.velocity + 16, 1);
  //     MIDI.sendNoteOff(40, 0, 1);
  //   } else {
  //     MIDI.sendNoteOn(41, snare.velocity, 1);
  //     MIDI.sendNoteOff(41, 0, 1);
  //   }
  } 
}
