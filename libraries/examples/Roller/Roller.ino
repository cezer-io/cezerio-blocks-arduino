/**********************************************  ROLLER  ******************************************/
/* 2xMotionBlock, 2xCubeBlock, 1xMainBlock */

#include "SmartBlockFunctions.h"
#include "DataTransferFunctions.h"

unsigned char timerFlag = 0;
extern unsigned char resolvePacketFlag;
extern capturedPacketType capturedPacket;

void setup()
{ 
  initSmartBlocks(); 
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
          sendRollerData(BLE_ROBOT_NAME, 0xFF);
        }
        break; 
    
    case BLE_MOVE_FORWARD:
  setMotion(0x140, motorDirectionForward, capturedPacket.data_packet.data[0], motorDriverEnable); /*Front_Left Wheel*/
    setMotion(0x141, motorDirectionForward, capturedPacket.data_packet.data[0], motorDriverEnable); /*Front_Right Wheel*/
    break;
    
    case BLE_MOVE_BACKWARD:
  setMotion(0x140, motorDirectionBackward, capturedPacket.data_packet.data[0], motorDriverEnable); /*Front_Left Wheel*/
    setMotion(0x141, motorDirectionBackward, capturedPacket.data_packet.data[0], motorDriverEnable); /*Front_Right Wheel*/
    break;
    
    case BLE_MOVE_RIGHT:
  setMotion(0x140,motorDirectionForward,capturedPacket.data_packet.data[0],motorDriverEnable); /*Front_Left Wheel*/
  setMotion(0x141,motorDirectionForward,(capturedPacket.data_packet.data[0])/2,motorDriverEnable); /*Front_Right Wheel*/
    break;
    
    case BLE_MOVE_LEFT:
  setMotion(0x140,motorDirectionForward,(capturedPacket.data_packet.data[0])/2,motorDriverEnable); /*Front_Left Wheel*/
  setMotion(0x141,motorDirectionForward,capturedPacket.data_packet.data[0],motorDriverEnable); /*Front_Right Wheel*/
    break;
    
    case BLE_MOVE_FORWARD_RIGHT:
  setMotion(0x140,motorDirectionForward,capturedPacket.data_packet.data[0],motorDriverEnable); /*Front_Left Wheel*/
  setMotion(0x141,motorDirectionForward,(capturedPacket.data_packet.data[0])*0.75,motorDriverEnable); /*Front_Right Wheel*/
    break;
    
    case BLE_MOVE_FORWARD_LEFT:
  setMotion(0x140,motorDirectionForward,(capturedPacket.data_packet.data[0])*0.75,motorDriverEnable); /*Front_Left Wheel*/
  setMotion(0x141,motorDirectionForward,capturedPacket.data_packet.data[0],motorDriverEnable); /*Front_Right Wheel*/
    break;
    
    case BLE_MOVE_BACKWARD_RIGHT:
  setMotion(0x140, motorDirectionBackward, capturedPacket.data_packet.data[0], motorDriverEnable); /*Front_Left Wheel*/
    setMotion(0x141, motorDirectionBackward, (capturedPacket.data_packet.data[0])*0.75, motorDriverEnable); /*Front_Right Wheel*/
    break;
    
    case BLE_MOVE_BACKWARD_LEFT:
  setMotion(0x140, motorDirectionBackward, (capturedPacket.data_packet.data[0])*0.75, motorDriverEnable); /*Front_Left Wheel*/
    setMotion(0x141, motorDirectionBackward, capturedPacket.data_packet.data[0], motorDriverEnable); /*Front_Right Wheel*/
    break;
    
    case BLE STOP:
  setMotion(0x140, motorDirectionForward, 0, motorDriverEnable); /*Front_Left Wheel*/
    setMotion(0x141, motorDirectionForward, 0, motorDriverEnable); /*Front_Right Wheel*/
    break;
    
    case BLE_TURN_360CW:
  setMotion(0x140, motorDirectionForward, 255, motorDriverEnable); /*Front_Left Wheel*/
    setMotion(0x141, motorDirectionBackward, 255, motorDriverEnable); /*Front_Right Wheel*/
    break;
    
    case BLE_TURN_360CCW:
  setMotion(0x140, motorDirectionBackward, 255, motorDriverEnable); /*Front_Left Wheel*/
    setMotion(0x141, motorDirectionForward, 255, motorDriverEnable); /*Front_Right Wheel*/
    break;
    
  }
}
