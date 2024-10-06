
/*
  EXAMPLE - Initialization of EEPROM

  With this sample code, you can initialize the EEPROM.
  Please write this code befor making your e-drum, if you want to use setting mode with this library.
  When writing is completed, the initial value setting is completed.
  
  The values after initialization are as follows.
    
    Sensitivity = 100
    Threshold = 10
    Scan Time = 10
    Mask Time = 30
    Rim Sensitivity = 20
    Rim Threshold = 3
    Curve type = 0
    Note = 38
    Note of rim/Edge = 39
    Note of cup = 40

  https://github.com/RyoKosaka/HelloDrum-arduino-Library
*/

#include <hellodrum.h>

//input number
HelloDrum pad_0(0);
HelloDrum pad_1(1);
HelloDrum pad_2(2);
HelloDrum pad_3(3);
HelloDrum pad_4(4);
HelloDrum pad_5(5);
HelloDrum pad_6(6);
HelloDrum pad_7(7);
HelloDrum pad_8(8);
HelloDrum pad_9(9);
HelloDrum pad_10(10);
HelloDrum pad_11(11);
HelloDrum pad_12(12);
HelloDrum pad_13(13);
HelloDrum pad_14(14);
HelloDrum pad_15(15);

//if you have more pads, just add code like this
//HelloDrum pad_16(16);
//HelloDrum pad_17(17);
//HelloDrum pad_18(18);

void setup()
{

  //if you use ESP32, uncomment below line.
  //EEPROM_ESP.begin(512);

  //Initialize
  pad_0.initMemory();
  pad_1.initMemory();
  pad_2.initMemory();
  pad_3.initMemory();
  pad_4.initMemory();
  pad_5.initMemory();
  pad_6.initMemory();
  pad_7.initMemory();
  pad_8.initMemory();
  pad_9.initMemory();
  pad_10.initMemory();
  pad_11.initMemory();
  pad_12.initMemory();
  pad_13.initMemory();
  pad_14.initMemory();
  pad_15.initMemory();

  //if you have more pads, just add code like this
  //pad_16.initMemory();
  //pad_17.initMemory();
  //pad_18.initMemory();
}

void loop()
{
}
