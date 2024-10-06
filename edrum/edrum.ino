#include <MIDI.h>
#include <hellodrum.h>

// Create and bind the MIDI interface to the default hardware Serial port
MIDI_CREATE_DEFAULT_INSTANCE();

//The piezo named snare is connected to the A0 pin
HelloDrum snare(1);

//Setting
byte SNARE[6] = {
  40,  //sensitivity
  5,  //threshold
  20,  //scantime
  12,  //masktime
  38,  //note
  3    //curve type
};

void setup() {
  MIDI.begin(1);  // Listen to all incoming messages
  Serial.begin(38400);
  snare.setCurve(SNARE[5]);
}

void loop() {
  snare.singlePiezo(SNARE[0], SNARE[1], SNARE[2], SNARE[3]);  //(sensitivity, threshold, scantime, masktime)

  if (snare.hit == true) {
    MIDI.sendNoteOn(SNARE[4], snare.velocity, 1);  //(note, velocity, channel)
    MIDI.sendNoteOff(SNARE[4], 0, 1);
  }
}


