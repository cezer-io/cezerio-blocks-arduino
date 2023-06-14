#include "cezerioBlocks.h"

unsigned char timerFlag = 0;

void setup()
{
  initcezerioBlocks();
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
