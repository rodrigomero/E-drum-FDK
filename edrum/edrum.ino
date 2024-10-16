#include <USB-MIDI.h>
#include <hellodrum.h>

//Gera instancia MIDI no canal 1
USBMIDI_CREATE_DEFAULT_INSTANCE();

//The piezo named snare is connected to the A1 pin
HelloDrum snare(1,2);  //DEFINIR PINOS!!!!!!!!!!!!!!
HelloDrum hihat(3);
HelloDrum hihatPedal(5);
HelloDrum kick(0);

//Setting
byte SNARE[10] = {
  40,  //sensitivity (1 - 100)
  5,   //threshold (1 - 100)
  20,  //scantime (1 - 100) (tempo que passa scaneando o pico do valor do piezo)
  12,  //masktime (1 - 100) (tempo que passa ignorando valores do piezo apos o midi ser enviado)
  3,   //Velocity Curve Type (0 - 4)
  10,  //rim sensitivity (1-100)
  3,   //rim threshold (1-100)
  38,  //note basic (0 - 127)
  40,  //note of rim shot (0-127)
  37   //note of cross stick (0-127)
};

byte HIHAT[7] = {
  40,  //sensitivity
  5,   //threshold
  10,   //scan time
  30,   //mask time
  0,    //curve type
  46,   //note of open
  42    //note of close
};

byte HIHAT_PEDAL[7] = {
  100,  //sensitivity (Hold the pedal at the position where you want to send 127(full open) in the MIDI CC, and read the Analog Read value in the TCRT5000. Divide the value by 10 and enter the value.)
  40,  //threshold (Hold the pedal at the position where you want to send 0(close) in the MIDI CC, and read the Analog Read value in the TCRT5000. Divide the value by 10 and enter the value.)
  70,  //scan start (When the analogRead value reaches this value * 10, the scan will start and the time will be recorded.)
  90,  //scan end (When the analogRead value reaches this value * 10, the scan is finished and the time taken for the scan is referenced to determine the velocity.Then noteOn will be sent.The default value is 90, the same as Sensitivity. This means that the pedal is closed at the point where MIDI CC is 127.)
  10,  //pedal sensitivity (This value multiplied by 100 is the time used to determine the velocity of the pedal. If the time taken from the scan start position to the scan end position is more than 1000 milliseconds, the velocity will be set to 1. So, if you feel that the velocity is low, either increase pedalSensitivity or increase the value of scan start.)
  1,   //curve type
  44   //note of pedal
};

byte KICK[6] = {
  30,  //sensitivity (1 - 100)
  5,   //threshold (1 - 100)
  20,  //scantime (1 - 100) (tempo que passa scaneando o pico do valor do piezo)
  12,  //masktime (1 - 100) (tempo que passa ignorando valores do piezo apos o midi ser enviado)
  35,   //note (pitch) (0 - 127)
  4    //Velocity Curve Type (0 - 4)
};

void setup() {
  MIDI.begin(1);  // Listen to all incoming messages
  Serial.begin(9600);
  snare.setCurve(SNARE[4]);
  hihat.setCurve(HIHAT[4]);
  hihatPedal.setCurve(HIHAT_PEDAL[5]);
  kick.setCurve(KICK[5]);
}

void loop() {
  snare.dualPiezo(SNARE[0], SNARE[1], SNARE[2], SNARE[3], SNARE[5], SNARE[6]);  //dualPiezo(byte sens, byte thre, byte scan, byte mask, byte rimSens, byte rimThre);
  kick.singlePiezo(KICK[0], KICK[1], KICK[2], KICK[3]);
  hihat.HH(HIHAT[0], HIHAT[1], HIHAT[2], HIHAT[3]);
  hihatPedal.hihatControl(HIHAT_PEDAL[0], HIHAT_PEDAL[1], HIHAT_PEDAL[2], HIHAT_PEDAL[3], HIHAT_PEDAL[4]);  //hihatControl(byte sens, byte thre, byte scanStart, byte scanEnd, byte pedalSens);

  //-----------------SNARE
  if (snare.hit == true) {
    MIDI.sendNoteOn(SNARE[7], snare.velocity, 10);  //(note, velocity, channel)
    MIDI.sendNoteOff(SNARE[7], 0, 10);
  }
  //RIM
  else if (snare.hitRim == true) {
    if (snare.velocity > 60) {
      MIDI.sendNoteOn(SNARE[8], snare.velocity, 10);  //(note, velocity, channel)
      MIDI.sendNoteOff(SNARE[8], 0, 10);
    } else {
      MIDI.sendNoteOn(SNARE[9], snare.velocity * 2, 10);  //(note, velocity, channel)
      MIDI.sendNoteOff(SNARE[9], 0, 10);
    }
  }

  //-----------------KICK
  if (kick.hit == true) {
    MIDI.sendNoteOn(KICK[4], kick.velocity, 1);  //(note, velocity, channel)
    MIDI.sendNoteOff(KICK[4], 0, 1);
  }

  //-----------------HI-HAT
  if (hihat.hit == true) {
    //check open or close
    //1.open
    if (hihatPedal.openHH == true) {
      MIDI.sendNoteOn(HIHAT[6], hihat.velocity, 10);  //(note, velocity, channel)
      MIDI.sendNoteOff(HIHAT[6], 0, 10);
    }
    //2.close
    else if (hihatPedal.closeHH == true) {
      MIDI.sendNoteOn(HIHAT[5], hihat.velocity, 10);  //(note, velocity, channel)
      MIDI.sendNoteOff(HIHAT[5], 0, 10);
    }
  }

  //when pedal is closed
  if (hihatPedal.hit == true) {
    MIDI.sendNoteOn(HIHAT_PEDAL[6], hihatPedal.velocity, 10);  //(note, velocity, channel)
    MIDI.sendNoteOff(HIHAT_PEDAL[6], 0, 10);
  }

  //sending state of pedal with controll change
  if (hihatPedal.moving == true) {
    MIDI.sendControlChange(4, hihatPedal.pedalCC, 10);
  }
}
