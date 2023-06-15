#include "cezerioBlocks.h"

unsigned char timerFlag = 0;

void setup()
{
  initCezerioBlocks();
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
  Serial.println(getBlockID(),HEX);
  timerFlag = 0;
  }
}

#if defined(TIMER_INTERRUPT_ENABLE)
ISR(TIMER1_COMPA_vect)
{
  timerFlag = 1;
}
#endif
