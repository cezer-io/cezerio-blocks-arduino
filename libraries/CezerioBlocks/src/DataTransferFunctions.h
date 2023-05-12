/*
  DataTransferFunctions.h
  2017 Copyright (c) RFtek Electronics Ltd.  All right reserved.
  
  Authors	: Huseyin Ulvi AYDOGMUS, Ozgur BOSTAN
  Date		: 2017-04-27
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-
  1301  USA
*/
#ifndef DATATRANSFERFUNCTIONS_H_
#define DATATRANSFERFUNCTIONS_H_

/*********************************************************************************************************
 *  Definitions
 *********************************************************************************************************/

#define START_BYTE              0x24		// '$' in ASCII
#define STOP_BYTE	        	0x23		// '#' in ASCII
#define PACKET_DATA_SIZE        1
#define ROBOT_ID_REQUEST		0x00
#define ROBOT_ID_REQUEST_DATA	0xFF

enum dataPacketCaptureStatus
{
  CAPTURE_START = 0,
  CAPTURE_ROBOT_ID,
  CAPTURE_PACKET_ID,
  CAPTURE_DATA,
  CAPTURE_STOP
};

enum dataRobotIDs
{
  ROLLER = 1,
  CHARIOT,
  SUMO,
  BALANCE,
  WINDMILL,
  FLYING_CAR,
  SPINDLE,
  TRUCK,
  TANK,
  LINE_TRACKER,
  ARM,
  LOADER,
  SNAKE,
  EXCAVATOR, 
  MAZER
};

enum dataPacketIDs
{
  BLE_ROBOT_NAME = 0,
  BLE_MOVE_FORWARD,
  BLE_MOVE_BACKWARD,
  BLE_MOVE_RIGHT,
  BLE_MOVE_LEFT,
  BLE_MOVE_FORWARD_RIGHT,
  BLE_MOVE_FORWARD_LEFT,
  BLE_MOVE_BACKWARD_RIGHT,
  BLE_MOVE_BACKWARD_LEFT,
  BLE_TURN_360CW,
  BLE_TURN_360CCW,
  BLE_TURN_180CW,
  BLE_TURN_180CCW,
  BLE_TURN_90CW,
  BLE_TURN_90CCW,
  BLE_FLIP,
  BLE_STOP,
  BLE_ROTATE,
  BLE_PUSH_PULL,
  BLE_ELEVATE_LAND,
  BLE_FORWARD_BACKWARD,
  BLE_LINKAGE,
  BLE_GRIPP,
  BLE_SPEED,
  BLE_BIRR,
  BLE_LIGHT,
  BLE_BIPP,
  BLE_LEVEL,
  BLE_RED_COLOR,
  BLE_GREEN_COLOR,
  BLE_BLUE_COLOR,
  BLE_MIC_DATA,
  BLE_KNOB_DATA,
  BLE_SLIDE_DATA,
  BLE_FOLLOW_DATA,
  BLE_DETECT_DATA,
  BLE_GESTURE_DATA,
  BLE_PHOTO_DATA,
  BLE_TEMP_DATA,
  BLE_EYE_DATA,
  BLE_TILT_DATA,
  BLE_COLOUR_RED_DATA,
  BLE_COLOUR_GREEN_DATA,
  BLE_COLOUR_BLUE_DATA,
  BLE_ACC_X_DATA,
  BLE_ACC_Y_DATA,
  BLE_ACC_Z_DATA,
  BLE_GYRO_X_DATA,
  BLE_GYRO_Y_DATA,
  BLE_GYRO_Z_DATA
};

/*********************************************************************************************************
 *  Structs 
 *********************************************************************************************************/

typedef struct
{
  unsigned char       start_byte;
  unsigned char       robot_id;
  unsigned char       packet_id;
  unsigned char       data[PACKET_DATA_SIZE];
  unsigned char       stop_byte;
} dataPacketType;

typedef struct
{
  unsigned char       data_capture_status;
  unsigned char       data_counter;
  dataPacketType      data_packet;
} capturedPacketType;

/*********************************************************************************************************
 *  DataTransferFunctions 
 *********************************************************************************************************/


void captureData(capturedPacketType*	capturedPacket,
                 const unsigned char*	capturedData,
                 const unsigned char 	capturedDataSize);

void packData(dataPacketType* data_packet, unsigned char robotID, unsigned char packetID);
void resolvePacket(const dataPacketType* capturedPacket);

#endif
/*********************************************************************************************************
 *  END FILE
 *********************************************************************************************************/
