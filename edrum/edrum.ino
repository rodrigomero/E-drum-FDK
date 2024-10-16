#include <USB-MIDI.h>
#include <hellodrum.h>

// Create and bind the MIDI interface to the default hardware Serial port
USBMIDI_CREATE_DEFAULT_INSTANCE();

//The piezo named snare is connected to the A1 pin
HelloDrum snare(1);

//Setting
byte SNARE[6] = {
  40,  //sensitivity (1 - 100)
  5,   //threshold (1 - 100)
  20,  //scantime (1 - 100) (tempo que passa scaneando o pico do valor do piezo)
  12,  //masktime (1 - 100) (tempo que passa ignorando valores do piezo apos o midi ser enviado)
  38,  //note (pitch) (0 - 127)
  3    //Velocity Curve Type (0 - 4)
};

void setup() {
  MIDI.begin(1);  // Listen to all incoming messages
  Serial.begin(9600);
  snare.setCurve(SNARE[5]);
}

void loop() {
  snare.singlePiezo(SNARE[0], SNARE[1], SNARE[2], SNARE[3]);  //(sensitivity, threshold, scantime, masktime)

  if (snare.hit == true) {
    MIDI.sendNoteOn(SNARE[4], snare.velocity, 1);  //(note, velocity, channel)
    MIDI.sendNoteOff(SNARE[4], 0, 1);
  }
}
