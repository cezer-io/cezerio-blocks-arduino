#include "cezerioBlocks.h"

#define mic   0x060
#define birr  0x160

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

  unsigned char micValue = getMic(mic);
  Serial.println(micValue);

    if(micValue >= 200|| micValue <= 100)
    {
      setBirrr(birr, motorDirectionForward, 255, motorDriverEnable);
      delay(1500);
    }
    else
    {
      setBirrr(birr, motorDirectionForward, 0, motorDriverEnable);
      delay(1000);
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
