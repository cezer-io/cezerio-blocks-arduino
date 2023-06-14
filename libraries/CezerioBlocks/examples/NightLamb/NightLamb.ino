#include "cezerioBlocks.h"

#define photo   0x070
#define light   0x120

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

   unsigned char photoLevel = getPhoto(photo);

   if(photoLevel>=200)
   {
     setLight(light, HIGH);
   }
   else
   {
     setLight(light, LOW);
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
