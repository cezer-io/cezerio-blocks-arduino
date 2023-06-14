/**********************************************  WINDMILL ******************************************/
/* 1xMotionBlock, 3xCubeBlock, 1xMainBlock, 1xDetectBlock, 1xLightBlock, 1xBippBlock, 1xLevelBlock, 1xMicBlock, 1xPhotoBlock, 1xKnobBlock */

#include "cezerioBlocks.h"
#include "DataTransferFunctions.h"

unsigned char timerFlag = 0;
extern unsigned char resolvePacketFlag;
extern capturedPacketType capturedPacket;

void setup()
{
  initCezerioBlocks();
  initSmartBlue();
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

    timerFlag = 0;
  }

  getSmartBlueData();

  if(resolvePacketFlag)
  {
    switch(capturedPacket.data_packet.packet_id)
    {
    case BLE_ROBOT_NAME:  // gelen robot id "0x00" ve data değeri "0xFF" ise robot id'sini gönderir
        if(capturedPacket.data_packet.robot_id == 0x00 && capturedPacket.data_packet.data[0] == 0xFF)
        {
          sendWindmillData(BLE_ROBOT_NAME, 0xFF);
        }
        break;

    case BLE_FLIP:
  setMotion(0x142, motorDirectionForward, capturedPacket.data_packet.data[0], motorDriverEnable); /*Propeller*/
    break;

    case BLE_BIPP:
  setBipp(0x0E0,capturedPacket.data_packet.data[0]);
    break;

    case BLE_LIGHT:
  setLight(0x120,capturedPacket.data_packet.data[0]);
    break;

    case BLE_LEVEL:
  setLevel(0x110,capturedPacket.data_packet.data[0]);
    break;

    case BLE_DETECT_DATA:
  sendWindmillData(BLE_DETECT_DATA, getDetect(0x020));
    break;

    case BLE_PHOTO_DATA:
  sendWindmillData(BLE_PHOTO_DATA, getPhoto(0x070));
    break;

    case BLE_MIC_DATA:
  sendWindmillData(BLE_MIC_DATA, getMic(0x060));
    break;

    case BLE_KNOB_DATA:
  sendWindmillData(BLE_KNOB_DATA, getKnob(0x050));
    break;
    }
  }
}
