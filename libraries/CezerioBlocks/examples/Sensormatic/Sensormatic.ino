#include "cezerioBlocks.h"

#define knob                0x050
#define mic                 0x060
#define photo               0x070
#define bipp                0x0E0
#define level               0x110
#define light               0x120
#define propellerMotor      0x144

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
   unsigned char motorSpeed = getKnob(knob);
   unsigned char photoLevel = getPhoto(photo);
   unsigned char soundLevel = getMic(mic);

   if(photoLevel>200)
   {
     setMotion(propellerMotor, motorDirectionForward, motorSpeed, motorDriverDisable);
     setLight(light, 1);
     setLevel(level,motorSpeed);
   }
    if(photoLevel<=200)
   {
     setMotion(propellerMotor, motorDirectionForward, motorSpeed, motorDriverEnable);
     setLight(light, 0);
     setLevel(level,soundLevel);
   }

   if(soundLevel>200 || soundLevel<100)
   {
    setBipp(bipp,1);
    setLevel(level,soundLevel);
   }
     else
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
