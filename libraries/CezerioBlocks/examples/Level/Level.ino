#include "cezerioBlocks.h"

#define knob    0x050
#define level   0x110

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

  unsigned char knobValue = getKnob(knob);
  setLevel(level,knobValue);

  timerFlag = 0;
 }
}

#if defined(TIMER_INTERRUPT_ENABLE)
ISR(TIMER1_COMPA_vect)
{
  timerFlag = 1;
}
#endif
