/*
  SendReceiveBluetooth.ino
  2017 Copyright (c) RFtek Electronics Ltd.  All right reserved.
  
  Authors	: Huseyin Ulvi AYDOGMUS, Ozgur BOSTAN
  Date		: 2017-04-28
  
  This sketch is a demo template for the logical operations of 
  SmartBlock Bluetooth functions. 
  
  the SmartBlocks: 2x Knob Block, 1x Detect Block (Input Blocks)
				           2x Lıght Block, 1x Bipp Block, 1x Motion Block (Output Blocks)

  Note: Any of the interrupt capabilities can be used by uncommenting the 
        #define statements (TIMER and/or CAN RECEIVE interrupt)
  
*/

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
      case BLE_ROBOT_NAME:	// gelen robot id "0x00" ve data değeri "0xFF" ise robot id'sini gönderir
		    if(capturedPacket.data_packet.robot_id == 0x00 && capturedPacket.data_packet.data[0] == 0xFF)
		    {
		      sendRollerData(BLE_ROBOT_NAME, 0xFF);
		    }
    
        break; 

      case BLE_MOVE_FORWARD:
      
        break;

      case BLE_MOVE_BACKWARD:

        break;

      case BLE_MOVE_RIGHT:
    		setMotion(MESSAGE_ID_MOTION_BLOCK, motorDirectionForward, 0xFF, motorDriverEnable);
    		setMotion(MESSAGE_ID_MOTION_BLOCK, motorDirectionForward, 0x80, motorDriverEnable);
    		setMotion(MESSAGE_ID_MOTION_BLOCK, motorDirectionForward, 0xFF, motorDriverEnable);
    		setMotion(MESSAGE_ID_MOTION_BLOCK, motorDirectionForward, 0x80, motorDriverEnable);

        break;

      case BLE_MOVE_LEFT:

        break;

      case BLE_MOVE_FORWARD_RIGHT:

        break;

      case BLE_MOVE_FORWARD_LEFT:
    
        break;

      case BLE_MOVE_BACKWARD_RIGHT:

        break;

      case BLE_MOVE_BACKWARD_LEFT:

        break;

      case BLE_TURN_360CW:

        break;

      case BLE_TURN_360CCW:

        break;

      case BLE_TURN_180CW:

        break;

      case BLE_TURN_180CCW:

        break;

      case BLE_TURN_90CW:

        break;

      case BLE_TURN_90CCW:

        break;

      case BLE_FLIP:
 
        break;

      case BLE_STOP:

        break;

      case BLE_ROTATE:

        break;

      case BLE_PUSH_PULL:

        break;

      case BLE_ELEVATE_LAND:

        break;

      case BLE_FORWARD_BACKWARD:

        break;

      case BLE_LINKAGE:

        break;

      case BLE_GRIPP:

        break;

      case BLE_SPEED:

        break;

      case BLE_BIRR:

        break;

      case BLE_LIGHT:

        break;

      case BLE_BIPP:
    		setBipp(MESSAGE_ID_BIPP_BLOCK, capturedPacket.data_packet.data[0]);

        break;

      case BLE_LEVEL:

        break;

      case BLE_RED_COLOR:

        break;

      case BLE_GREEN_COLOR:

        break;

      case BLE_BLUE_COLOR:

        break;

      case BLE_MIC_DATA:

        break;

      case BLE_KNOB_DATA:
    		sendRollerData(BLE_KNOB_DATA, getKnob(MESSAGE_ID_KNOB_BLOCK));

        break;

      case BLE_SLIDE_DATA:

        break;

      case BLE_FOLLOW_DATA:

        break;

      case BLE_DETECT_DATA:

        break;

      case BLE_GESTURE_DATA:

        break;

      case BLE_PHOTO_DATA:

        break;

      case BLE_TEMP_DATA:

        break;

      case BLE_EYE_DATA:

        break;

      case BLE_TILT_DATA:

        break;

      case BLE_COLOUR_RED_DATA:

        break;

      case BLE_COLOUR_GREEN_DATA:

        break;

      case BLE_COLOUR_BLUE_DATA:

        break;

      case BLE_ACC_X_DATA:

        break;

      case BLE_ACC_Y_DATA:

        break;

      case BLE_ACC_Z_DATA:

        break;

      case BLE_GYRO_X_DATA:

        break;

      case BLE_GYRO_Y_DATA:

        break;

      case BLE_GYRO_Z_DATA:

        break;

      default:
      
        break;
    } 

    resolvePacketFlag = 0;
  }
}

#if defined(TIMER_INTERRUPT_ENABLE)
ISR(TIMER1_COMPA_vect)
{
  timerFlag = 1;
}
#endif
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
