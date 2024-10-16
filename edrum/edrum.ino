#include <USB-MIDI.h>
#include <hellodrum.h>

// Create and bind the MIDI interface to the default hardware Serial port
USBMIDI_CREATE_DEFAULT_INSTANCE();

//The piezo named snare is connected to the A1 pin
HelloDrum snare(); //DEFINIR PINOS!!!!!!!!!!!!!!
HelloDrum hihat();
HelloDrum hihatPedal();
HelloDrum kick();


//Setting
byte SNARE[6] = {
  40,  //sensitivity (1 - 100)
  5,   //threshold (1 - 100)
  20,  //scantime (1 - 100) (tempo que passa scaneando o pico do valor do piezo)
  12,  //masktime (1 - 100) (tempo que passa ignorando valores do piezo apos o midi ser enviado)
  38,  //note (pitch) (0 - 127)
  3    //Velocity Curve Type (0 - 4)
};

byte HIHAT[7] = {
    100, //sensitivity
    10,  //threshold
    10,  //scan time
    30,  //mask time
    0,   //curve type
    46,  //note of open
    42   //note of close
};

byte HIHAT_PEDAL[7] = {
    90, //sensitivity (Hold the pedal at the position where you want to send 127(full open) in the MIDI CC, and read the Analog Read value in the TCRT5000. Divide the value by 10 and enter the value.)
    30, //threshold (Hold the pedal at the position where you want to send 0(close) in the MIDI CC, and read the Analog Read value in the TCRT5000. Divide the value by 10 and enter the value.)
    70, //scan start (When the analogRead value reaches this value * 10, the scan will start and the time will be recorded.)
    90, //scan end (When the analogRead value reaches this value * 10, the scan is finished and the time taken for the scan is referenced to determine the velocity.Then noteOn will be sent.The default value is 90, the same as Sensitivity. This means that the pedal is closed at the point where MIDI CC is 127.)
    10, //pedal sensitivity (This value multiplied by 100 is the time used to determine the velocity of the pedal. If the time taken from the scan start position to the scan end position is more than 1000 milliseconds, the velocity will be set to 1. So, if you feel that the velocity is low, either increase pedalSensitivity or increase the value of scan start.)
    0,  //curve type
    44  //note of pedal
};

byte KICK[6] = {
  70,  //sensitivity (1 - 100)
  5,   //threshold (1 - 100)
  20,  //scantime (1 - 100) (tempo que passa scaneando o pico do valor do piezo)
  12,  //masktime (1 - 100) (tempo que passa ignorando valores do piezo apos o midi ser enviado)
  3,  //note (pitch) (0 - 127)
  3    //Velocity Curve Type (0 - 4)
};

void setup() {
  MIDI.begin(1);  // Listen to all incoming messages
  Serial.begin(9600);
  snare.setCurve(SNARE[5]);
  hihat.setCurve(HIHAT[4]);
  hihatPedal.setCurve(HIHAT_PEDAL[5]);
  kick.setCurve(KICK[5]);
}

void loop() {
  snare.singlePiezo(SNARE[0], SNARE[1], SNARE[2], SNARE[3]);  //(sensitivity, threshold, scantime, masktime)
  kick.singlePiezo(KICK[0], KICK[1],KICK[2],KICK[3]);
  hihat.HH(HIHAT[0], HIHAT[1], HIHAT[2], HIHAT[3]);
  hihatPedal.hihatControl(HIHAT_PEDAL[0], HIHAT_PEDAL[1], HIHAT_PEDAL[2], HIHAT_PEDAL[3], HIHAT_PEDAL[4]); //hihatControl(byte sens, byte thre, byte scanStart, byte scanEnd, byte pedalSens);

  if (snare.hit == true) {
    MIDI.sendNoteOn(SNARE[4], snare.velocity, 1);  //(note, velocity, channel)
    MIDI.sendNoteOff(SNARE[4], 0, 1);
  }

  if (kick.hit == true) {
    MIDI.sendNoteOn(KICK[4], kick.velocity, 1);  //(note, velocity, channel)
    MIDI.sendNoteOff(KICK[4], 0, 1);
  }

  if (hihat.hit == true)
  {
    //check open or close
    //1.open
    if (hihatPedal.openHH == true)
    {
      MIDI.sendNoteOn(HIHAT[5], hihat.velocity, 10); //(note, velocity, channel)
      MIDI.sendNoteOff(HIHAT[5], 0, 10);
    }
    //2.close
    else if (hihatPedal.closeHH == true)
    {
      MIDI.sendNoteOn(HIHAT[6], hihat.velocity, 10); //(note, velocity, channel)
      MIDI.sendNoteOff(HIHAT[6], 0, 10);
    }
  }

  //when pedal is closed
  if (hihatPedal.hit == true)
  {
    MIDI.sendNoteOn(HIHAT_PEDAL[6], hihatPedal.velocity, 10); //(note, velocity, channel)
    MIDI.sendNoteOff(HIHAT_PEDAL[6], 0, 10);
  }

  //sending state of pedal with controll change
  if (hihatPedal.moving == true)
  {
    MIDI.sendControlChange(4, hihatPedal.pedalCC, 10);
  }
}
