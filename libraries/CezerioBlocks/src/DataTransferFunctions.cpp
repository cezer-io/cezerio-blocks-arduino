#include "DataTransferFunctions.h"
unsigned char resolvePacketFlag = 0;

/**
  * @brief  Capture packet from Serial Data
  * @param  None
  * @retval None
  */
void captureData(capturedPacketType*	capturedPacket,
                 const unsigned char*	capturedData,
                 const unsigned char 	capturedDataSize)
{
  unsigned char i = 0;

  for(i = 0; i < capturedDataSize; i++)
  {
    switch(capturedPacket->data_capture_status)
    {
      case CAPTURE_START:
      {
        if(START_BYTE == capturedData[i])
        {
          capturedPacket->data_packet.start_byte       = capturedData[i];
          capturedPacket->data_capture_status          = CAPTURE_ROBOT_ID;
        }
		else
		{
		  capturedPacket->data_capture_status          = CAPTURE_START;
		  capturedPacket->data_counter		       = 0;
		}

        break;
      }

      case CAPTURE_ROBOT_ID:
      {
        capturedPacket->data_packet.robot_id           = capturedData[i];
        capturedPacket->data_capture_status            = CAPTURE_PACKET_ID;

        break;
      }

      case CAPTURE_PACKET_ID:
      {
        capturedPacket->data_packet.packet_id          = capturedData[i];
        capturedPacket->data_capture_status            = CAPTURE_DATA;

        break;
      }

      case CAPTURE_DATA:
      {
        capturedPacket->data_packet.data[capturedPacket->data_counter] = capturedData[i];
        capturedPacket->data_counter++;

        if(capturedPacket->data_counter >= 1)
        {
          capturedPacket->data_capture_status          = CAPTURE_STOP;
        }

        break;
      }

      case CAPTURE_STOP:
      {
        if(STOP_BYTE == capturedData[i])
        {
          capturedPacket->data_packet.stop_byte        = capturedData[i];

          // packet resolve
          //resolvePacket(&(capturedPacket->data_packet));
	  resolvePacketFlag = 1;
        }

        capturedPacket->data_capture_status            = CAPTURE_START;
        capturedPacket->data_counter                   = 0;

        break;
      }

      default:
      {
        capturedPacket->data_capture_status            = CAPTURE_START;
        capturedPacket->data_counter                   = 0;
      }
    }
  }
}

/**
  * @brief  Pack data with a given format
  * @param  None
  * @retval None
  */
void packData(dataPacketType* data_packet, unsigned char robotID, unsigned char packetID)
{
  data_packet->start_byte       = START_BYTE;
  data_packet->robot_id		= robotID;
  data_packet->packet_id	= packetID;
  data_packet->stop_byte        = STOP_BYTE;
}

/**
  * @brief  Resolve captured Serial Data
  * @param  None
  * @retval None
  */
void resolvePacket(const dataPacketType* capturedPacket)
{
  dataPacketType packet = {0};

  switch(capturedPacket->packet_id)
  {
    case BLE_ROBOT_NAME:

      break;

    case BLE_MOVE_FORWARD:

      break;

    case BLE_MOVE_BACKWARD:

      break;

    case BLE_MOVE_RIGHT:

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
}

/*********************************************************************************************************
 *  END FILE
 *********************************************************************************************************/
