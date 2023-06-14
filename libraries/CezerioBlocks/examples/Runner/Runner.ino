#include "cezerioBlocks.h"

#define blackDetect         0x020
#define redDetect           0x021
#define purpleMotor         0x140
#define orangeMotor         0x141

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
   unsigned char forwardObject = getDetect(blackDetect);
   unsigned char backwardObject= getDetect(redDetect);

   if(forwardObject>=1 && backwardObject<1)
   {
     setMotion(purpleMotor, motorDirectionBackward, 255, motorDriverEnable);
     setMotion(orangeMotor, motorDirectionBackward, 255, motorDriverEnable);
   }
   else if(backwardObject>=1 && forwardObject<1)
   {
     setMotion(purpleMotor, motorDirectionForward, 255, motorDriverEnable);
     setMotion(orangeMotor, motorDirectionForward, 255, motorDriverEnable);
   }
   else if(forwardObject>=1 && backwardObject>=1)
   {
     setMotion(purpleMotor, motorDirectionForward, 0, motorDriverEnable);
     setMotion(orangeMotor, motorDirectionForward, 0, motorDriverEnable);
   }
   else
   {
     setMotion(purpleMotor, motorDirectionForward, 255, motorDriverEnable);
     setMotion(orangeMotor, motorDirectionBackward, 255, motorDriverEnable);
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
