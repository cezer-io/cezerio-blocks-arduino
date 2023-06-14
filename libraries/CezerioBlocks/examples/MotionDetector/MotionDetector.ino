#include "cezerioBlocks.h"

#define bipp       0x0E0
#define gesture    0x040

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
unsigned char hareket = getGesture(gesture);

  if (hareket == 1)
  {
    setBipp(bipp, 1);
    hareket = getGesture(gesture);
  }
  else
  {
    setBipp(bipp, 0);
    hareket = getGesture(gesture);
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
