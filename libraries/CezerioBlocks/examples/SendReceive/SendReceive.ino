/*
  SendReceive.ino
  2017 Copyright (c) RFtek Electronics Ltd.  All right reserved.
  
  Authors	: Huseyin Ulvi AYDOGMUS, Ozgur BOSTAN
  Date		: 2017-03-21
  
  This sketch is a demo template for the logical operations of 
  SmartBlock functions. SmartBlockFunctions.cpp v1.3.0 is used.
  
  the SmartBlocks: 2x Knob Block, 1x Detect Block (Input Blocks)
				           1x Lıght Block, 1x Bipp Block, 1x Motion Block (Output Blocks)

  Note: Any of the interrupt capabilities can be used by uncommenting the 
        #define statements (TIMER and/or CAN RECEIVE interrupt)
  
*/

#include "SmartBlockFunctions.h"

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
   unsigned char motorSpeed = getKnob(MESSAGE_ID_KNOB_BLOCK);
   setMotion(MESSAGE_ID_MOTION_BLOCK, motorDirectionForward, motorSpeed, motorDriverEnable);
  
   unsigned char ledState = (getKnob(MESSAGE_ID_KNOB_BLOCK + 1) < 0x7F) ? 0 : 1;
   setLight(MESSAGE_ID_LIGHT_BLOCK, ledState);
  
   unsigned char buzzerState = !getDetect(MESSAGE_ID_DETECT_BLOCK);
   setBipp(MESSAGE_ID_BIPP_BLOCK, buzzerState);

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
