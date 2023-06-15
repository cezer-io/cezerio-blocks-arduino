/*
  cezerioBlocks.h
  2017 Copyright (c) RFtek Electronics Ltd.  All right reserved.

  Authors	: Huseyin Ulvi AYDOGMUS, Ozgur BOSTAN
  Date		: 2017-03-20
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
#ifndef CEZERIOBLOCKS_H_
#define CEZERIOBLOCKS_H_

#include "mcp_can.h"

#define TIMER_INTERRUPT_ENABLE
//#define CAN_RECEIVE_INTERRUPT_ENABLE

#if defined(CAN_RECEIVE_INTERRUPT_ENABLE)
#define CAN_INT 2                               // Set INT to pin 2
#endif

/*********************************************************************************************************
 *  Definitions
 *********************************************************************************************************/

#define SYNC_BYTE_START            0x75
#define SYNC_BYTE_STOP             0x1B
#define STM32_DATA_PACKET_TYPE	   0x06
#define UART_BAUD_RATE             115200
#define SERIAL_BAUD_RATE  		   9600
#define BLUE_BLOCK_BAUD_RATE  	   9600
#define TIMER_INTERRUPT_FREQ       40     // in Hz (no more than 30000)

#define motorDirectionForward      0x01
#define motorDirectionBackward	   0x00
#define motorDriverEnable          0x01
#define motorDriverDisable         0x00

/* Block Message IDs */
#define MESSAGE_ID_REQUEST         0x005
#define MESSAGE_ID_MAIN_BLOCK      0x00F

/* Input Blocks */
#define MESSAGE_ID_BALANCE_BLOCK   0x010
#define MESSAGE_ID_DETECT_BLOCK    0x020
#define MESSAGE_ID_EYE_BLOCK       0x030
#define MESSAGE_ID_GESTURE_BLOCK   0x040
#define MESSAGE_ID_KNOB_BLOCK      0x050
#define MESSAGE_ID_MIC_BLOCK       0x060
#define MESSAGE_ID_PHOTO_BLOCK     0x070
#define MESSAGE_ID_TEMP_BLOCK      0x080
#define MESSAGE_ID_TILT_BLOCK      0x090
#define MESSAGE_ID_COLOUR_BLOCK    0x0A0
#define MESSAGE_ID_SLIDE_BLOCK     0x0B0
#define MESSAGE_ID_FOLLOW_BLOCK    0x0C0

/* Output Blocks */
#define MESSAGE_ID_360_BLOCK       0x0D0
#define MESSAGE_ID_BIPP_BLOCK      0x0E0
#define MESSAGE_ID_COLOR_BLOCK     0x0F0
#define MESSAGE_ID_GRIPP_BLOCK     0x100
#define MESSAGE_ID_LEVEL_BLOCK     0x110
#define MESSAGE_ID_LIGHT_BLOCK     0x120
#define MESSAGE_ID_LINK_BLOCK      0x130
#define MESSAGE_ID_MOTION_BLOCK    0x140
#define MESSAGE_ID_ROLL_BLOCK      0x150
#define MESSAGE_ID_BIRRR_BLOCK     0x160

/*********************************************************************************************************
 *  Variables
 *********************************************************************************************************/

/*********************************************************************************************************
 *  Functions
 *********************************************************************************************************/

/* GENERIC FUNCTIONS */
void createDataRequestPacket(unsigned int blockMessageId);
void getInputDataAndDriveOutput(void);
unsigned char asciiToHex(unsigned char asciiData);
unsigned char hexToAscii(unsigned char hexData);

/* INIT FUNCTIONS */
void initCezerioBlocks(void);
void initSmartBlue(void);
void createBlockDataRequestPacket(unsigned int requestMessageId);
uint16_t getBlockID();

/* BLE FUNCTIONS */
void getSmartBlueData(void);
void sendSmartBlueData(unsigned char robotID, unsigned char packetID, unsigned char data);
void sendRollerData(unsigned char packetID, unsigned char data);
void sendChariotData(unsigned char packetID, unsigned char data);
void sendSumoData(unsigned char packetID, unsigned char data);
void sendBalanceData(unsigned char packetID, unsigned char data);
void sendWindmillData(unsigned char packetID, unsigned char data);
void sendFlyingCarData(unsigned char packetID, unsigned char data);
void sendSpindleData(unsigned char packetID, unsigned char data);
void sendTruckData(unsigned char packetID, unsigned char data);
void sendTankData(unsigned char packetID, unsigned char data);
void sendLineTrackerData(unsigned char packetID, unsigned char data);
void sendArmData(unsigned char packetID, unsigned char data);
void sendLoaderData(unsigned char packetID, unsigned char data);
void sendSnakeData(unsigned char packetID, unsigned char data);
void sendExcavatorData(unsigned char packetID, unsigned char data);
void sendMazerData(unsigned char packetID, unsigned char data);

/* INPUT FUNCTIONS */
int* getAcc(unsigned int balanceBlockID);
int* getGyro(unsigned int balanceBlockID);
unsigned char getDetect(unsigned int detectBlockID);
unsigned char getEye(unsigned int eyeBlockID);
unsigned char getGesture(unsigned int gestureBlockID);
unsigned char getKnob(unsigned int knobBlockID);
unsigned char getMic(unsigned int micBlockID);
unsigned char getPhoto(unsigned int photoBlockID);
unsigned char getTemp(unsigned int tempBlockID);
unsigned char getTilt(unsigned int tiltBlockID);
unsigned char getColour(unsigned int colourBlockID);
unsigned char getSlide(unsigned int slideBlockID);
unsigned char getFollow(unsigned int followBlockID);

/* OUTPUT FUNCTIONS */
void set360(unsigned int motor360BlockID, unsigned char motorDirection, unsigned char motorSpeed, unsigned char motorEnable);
void setBipp(unsigned int bippBlockID, unsigned char buzzerState);
void setColor(unsigned int colorBlockID, unsigned char redLedState, unsigned char greenLedState, unsigned char blueLedState);
void setGrip(unsigned int gripBlockID, unsigned char motorAngle, unsigned char motorEnable);
void setLevel(unsigned int levelBlockID, unsigned char barGraphData);
void setLight(unsigned int lightBlockID, unsigned char ledState);
void setLink(unsigned int linkBlockID, unsigned char motorAngle, unsigned char motorEnable);
void setMotion(unsigned int motionBlockID, unsigned char motorDirection, unsigned char motorSpeed, unsigned char motorEnable);
void setRoll(unsigned int rollBlockID, unsigned char motorDirection, unsigned char motorSpeed, unsigned char motorEnable);
void setBirrr(unsigned int birrrBlockID, unsigned char motorDirection, unsigned char motorSpeed, unsigned char motorEnable);

#endif
/*********************************************************************************************************
 *  END FILE
 *********************************************************************************************************/
