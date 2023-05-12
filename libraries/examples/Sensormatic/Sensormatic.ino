/*
  SmartBlockSTM32ArduinoDemo.ino
  2017 Copyright (c) RFtek Electronics Ltd.  All right reserved.
  
  Authors  : Huseyin Ulvi AYDOGMUS, Ozgur BOSTAN
  Date    : 2017-03-21
  
  This sketch is a demo template for the logical operations of 
  SmartBlock functions. SmartBlockFunctions.cpp v1.1.0 is used.
  
  the SmartBlocks: 1x KnobBlock, 1x PhotoBlock, 1x MicBlock  (Input Blocks)
                   1x LıghtBlock, 1xBippBlock, 1xLevelBlock, 1x MotionBlock (Output Blocks)

  Note: Any of the interrupt capabilities can be used by uncommenting the 
        #define statements (TIMER and/or CAN RECEIVE interrupt)
*/

#include "SmartBlockFunctions.h"

#define blackDetect         0x020
#define redDetect           0x021
#define knob                0x050
#define mic                 0x060
#define photo               0x070
#define bipp                0x0E0
#define level               0x110 
#define light               0x120
#define purpleMotor         0x140
#define orangeMotor         0x141
#define redMotor            0x142
#define blueMotor           0x143
#define propellerMotor      0x144

unsigned char timerFlag = 0;

void setup()
{ 
  initSmartBlocks();
}

void loop()
{
#if defined(CAN_RECEIVE_INTERRUPT_ENABLE)  
  if(!digitalRead(CAN_INT))
  {
       
  }
#endif

  if(timerFlag)
  {
   unsigned char motorSpeed = getKnob(knob);
   unsigned char photoLevel = getPhoto(photo);
   unsigned char soundLevel = getMic(mic);
  
   if(photoLevel<15)
   {
     setMotion(propellerMotor, motorDirectionForward, motorSpeed, motorDriverDisable);
     setLight(light, 1); 
     setLevel(level,motorSpeed); 
   }
    if(photoLevel>=15)
   {
     setMotion(propellerMotor, motorDirectionForward, motorSpeed, motorDriverEnable);
     setLight(light, 0);  
     setLevel(level,soundLevel);
   }

   if(soundLevel>10)
   {
    setBipp(bipp,1);
    setLevel(level,soundLevel);
   }
     if(soundLevel<=10)
   {
    setBipp(bipp,0);
   }
   timerFlag = 0;
 }
}

#if defined(TIMER_INTERRUPT_ENABLE)
ISR(TIMER1_COMPA_vect)
{
  timerFlag = 1;
}
#endif

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
