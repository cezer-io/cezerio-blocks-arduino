/*
  cezerioBlocks.cpp
  2017 Copyright (c) RFtek Electronics Ltd.  All right reserved.

  Authors	: Huseyin Ulvi AYDOGMUS, Ozgur BOSTAN
  Date		: 2017-03-20
  Version  : 1.0.0
            - generic function for data request
            - generic function for data receive and data sent
            - main functions for output blocks

  Date    : 2017-03-21
  Version : 1.1.0
            - generic function for data request
            - generic function for data receive and data sent
            - main functions for output blocks (removed)
            - block specific functions for both input and output blocks added

  Date    : 2017-03-22
  Version : 1.2.0
            - initCezerioBlocks() function added to simplfy startup process

  Date    : 2017-03-23
  Version : 1.2.1
            - minor change; timer and can interrupt definitions moved to
              "cezerioBlocks.h" from "cezerioBlocks.cpp"

  Date    : 2017-03-30
  Version : 1.2.2
            - new blocks and related functions added (TILT, COLOUR, SLIDE, FOLLOW, BIRRR)

  Date    : 2017-04-03
  Version : 1.3.0
            - new library added for BLUE BLOCK (SoftwareSerial)

  Date    : 2017-04-27
  Version : 1.4.0
            - new library added for bluetooth communication (DataTransferFunctions)
	    - functions: getSmartBlueData, sendSmartBlueData

  Date    : 2017-04-28
  Version : 1.4.1
            - new functions added for bluetooth communication (DataTransferFunctions)
	    - new example sketch: SendReceiveBluetooth.ino


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

#include "cezerioBlocks.h"
#include "SoftwareSerial.h"
#include "DataTransferFunctions.h"

long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];
unsigned char rx2Buf[8];

MCP_CAN CAN(10);                                 // Set CS to pin 10, instance for CAN class

SoftwareSerial theSmartBlue(8, 9);				 // Set Software TX-RX to pins 8-9, instance for SoftwareSerial class
capturedPacketType capturedPacket;

/*********************************************************************************************************
 *  INIT FUNCTIONS
 *********************************************************************************************************/


/**
  * @brief  Initialization for the blocks to be ready for operation
  * @param  None
  * @retval None
  */
void initCezerioBlocks(void)
{
  Serial.begin(UART_BAUD_RATE);

  // Initialize MCP2515 running at 16MHz with a baudrate of 1000kb/s and the masks and filters disabled.
  if(CAN.begin(MCP_ANY, CAN_1000KBPS, MCP_16MHZ) == CAN_OK)
    Serial.println("MCP2515 Initialized Successfully!");
  else
    Serial.println("Error Initializing MCP2515...");

  CAN.setMode(MCP_NORMAL);                      // Set operation mode to normal so the MCP2515 sends acks to received data.

#if defined(CAN_RECEIVE_INTERRUPT_ENABLE)
  pinMode(CAN_INT, INPUT);                      // Configuring pin for /INT input
#endif

  Serial.println("MCP2515 Library Receive Example...");

#if defined(TIMER_INTERRUPT_ENABLE)
  // initialize timer1
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = (31250/TIMER_INTERRUPT_FREQ) - 1;     // 50Hz interrupt frequency [(8MHz/prescaler/frequency) - 1]
  TCCR1B |= (1 << WGM12);                       // capture compare mode
  TCCR1B |= (1 << CS12);                        // prescaler = 256
  TIMSK1 |= (1 << OCIE1A);                      // enable timer compare interrupt
  interrupts();
#endif
}

/**
  * @brief  Initialization for BLUE BLOCK to be ready for operation
  * @param  None
  * @retval None
  */
void initSmartBlue(void)
{
  theSmartBlue.begin(BLUE_BLOCK_BAUD_RATE);
}

/*********************************************************************************************************
 *  BLE FUNCTIONS
 *********************************************************************************************************/


/**
  * @brief  Get data from bluetooth device
  * @param  None
  * @retval None
  */
void getSmartBlueData(void)
{
  unsigned char ssRxVals[1] = {0};

  if(theSmartBlue.available())
  {
    ssRxVals[0] = theSmartBlue.read();
    captureData(&capturedPacket, ssRxVals, 1);
  }
}

/**
  * @brief  Send data to bluetooth device
  * @param  None
  * @retval None
  */
void sendSmartBlueData(unsigned char robotID, unsigned char packetID, unsigned char data)
{
  theSmartBlue.write('$');
  theSmartBlue.write(robotID);
  theSmartBlue.write(packetID);
  theSmartBlue.write(data);
  theSmartBlue.write('#');
}

/**
  * @brief  Send Roller data to bluetooth device
  * @param  None
  * @retval None
  */
void sendRollerData(unsigned char packetID, unsigned char data)
{
  sendSmartBlueData(ROLLER, packetID, data);
}

/**
  * @brief  Send Chariot data to bluetooth device
  * @param  None
  * @retval None
  */
void sendChariotData(unsigned char packetID, unsigned char data)
{
  sendSmartBlueData(CHARIOT, packetID, data);
}

/**
  * @brief  Send Sumo data to bluetooth device
  * @param  None
  * @retval None
  */
void sendSumoData(unsigned char packetID, unsigned char data)
{
  sendSmartBlueData(SUMO, packetID, data);
}

/**
  * @brief  Send Balance data to bluetooth device
  * @param  None
  * @retval None
  */
void sendBalanceData(unsigned char packetID, unsigned char data)
{
  sendSmartBlueData(BALANCE, packetID, data);
}

/**
  * @brief  Send Windmill data to bluetooth device
  * @param  None
  * @retval None
  */
void sendWindmillData(unsigned char packetID, unsigned char data)
{
  sendSmartBlueData(WINDMILL, packetID, data);
}

/**
  * @brief  Send FlyingCar data to bluetooth device
  * @param  None
  * @retval None
  */
void sendFlyingCarData(unsigned char packetID, unsigned char data)
{
  sendSmartBlueData(FLYING_CAR, packetID, data);
}

/**
  * @brief  Send Spindle data to bluetooth device
  * @param  None
  * @retval None
  */
void sendSpindleData(unsigned char packetID, unsigned char data)
{
  sendSmartBlueData(SPINDLE, packetID, data);
}

/**
  * @brief  Send Truck data to bluetooth device
  * @param  None
  * @retval None
  */
void sendTruckData(unsigned char packetID, unsigned char data)
{
  sendSmartBlueData(TRUCK, packetID, data);
}

/**
  * @brief  Send Tank data to bluetooth device
  * @param  None
  * @retval None
  */
void sendTankData(unsigned char packetID, unsigned char data)
{
  sendSmartBlueData(TANK, packetID, data);
}

/**
  * @brief  Send LineTracker data to bluetooth device
  * @param  None
  * @retval None
  */
void sendLineTrackerData(unsigned char packetID, unsigned char data)
{
  sendSmartBlueData(LINE_TRACKER, packetID, data);
}

/**
  * @brief  Send Arm data to bluetooth device
  * @param  None
  * @retval None
  */
void sendArmData(unsigned char packetID, unsigned char data)
{
  sendSmartBlueData(ARM, packetID, data);
}

/**
  * @brief  Send Loader data to bluetooth device
  * @param  None
  * @retval None
  */
void sendLoaderData(unsigned char packetID, unsigned char data)
{
  sendSmartBlueData(LOADER, packetID, data);
}

/**
  * @brief  Send Snake data to bluetooth device
  * @param  None
  * @retval None
  */
void sendSnakeData(unsigned char packetID, unsigned char data)
{
  sendSmartBlueData(SNAKE, packetID, data);
}

/**
  * @brief  Send Excavator data to bluetooth device
  * @param  None
  * @retval None
  */
void sendExcavatorData(unsigned char packetID, unsigned char data)
{
  sendSmartBlueData(EXCAVATOR, packetID, data);
}

/**
  * @brief  Send Mazer data to bluetooth device
  * @param  None
  * @retval None
  */
void sendMazerData(unsigned char packetID, unsigned char data)
{
  sendSmartBlueData(MAZER, packetID, data);
}

/*********************************************************************************************************
 *  GENERIC FUNCTIONS
 *********************************************************************************************************/

/**
  * @brief  Sends data request for input blocks
  * @param  INPUT BLOCK MESSAGE IDs
  * @retval None
  */
void createDataRequestPacket(unsigned int inputBlockMessageId)
{
  unsigned char sendData[4] = {SYNC_BYTE_START, STM32_DATA_PACKET_TYPE, 0x00, SYNC_BYTE_STOP};
  CAN.sendMsgBuf(inputBlockMessageId, 0, 4, sendData);
}

/**
  * @brief  Reads values from input blocks and drives
			output blocks with these data based on message IDs
  * @param  None
  * @retval None
  */
void getInputDataAndDriveOutput(void)
{
  unsigned char motorSpeed 		= 0;
  unsigned char motorAngle 		= 0;
  unsigned char ledState		  = 0;
  unsigned char redLedState 	= 0;
  unsigned char greenLedState	= 0;
  unsigned char blueLedState	= 0;
  unsigned char buzzerState	  = 0;
  unsigned char	barGraphData	= 0;

  CAN.readMsgBuf(&rxId, &len, rxBuf);      // Read data: len = data length, buf = data byte(s)

  switch(rxId)
  {
  	case MESSAGE_ID_BALANCE_BLOCK:

  	  break;

  	case MESSAGE_ID_BALANCE_BLOCK + 1:

  	  break;

  	case MESSAGE_ID_DETECT_BLOCK:

  	  break;

  	case MESSAGE_ID_DETECT_BLOCK + 1:

  	  break;

  	case MESSAGE_ID_EYE_BLOCK:

  	  break;

  	case MESSAGE_ID_EYE_BLOCK + 1:

  	  break;

  	case MESSAGE_ID_GESTURE_BLOCK:

  	  break;

  	case MESSAGE_ID_GESTURE_BLOCK + 1:

  	  break;

  	case MESSAGE_ID_KNOB_BLOCK:

  	  break;

  	case MESSAGE_ID_KNOB_BLOCK + 1:

  	  break;

  	case MESSAGE_ID_MIC_BLOCK:

  	  break;

  	case MESSAGE_ID_MIC_BLOCK + 1:

  	  break;

  	case MESSAGE_ID_PHOTO_BLOCK:

  	  break;

  	case MESSAGE_ID_PHOTO_BLOCK + 1:

  	  break;

  	case MESSAGE_ID_TEMP_BLOCK:

  	  break;

  	case MESSAGE_ID_TEMP_BLOCK + 1:

  	  break;

  	default:
  	  break;
  }
}

/**
  * @brief  Converts ASCII numbers to hex (integer value)
  * @param  Captured ASCII data
  * @retval Converted hex value
  */
unsigned char asciiToHex(unsigned char asciiData)
{
  unsigned char hexData = 0;

  if((asciiData >= 0x30) && (asciiData <= 0x39))
  {
    hexData = asciiData - 0x30;
  }

  return hexData;
}

/**
  * @brief  Converts hex (integer value) numbers to ASCII
  * @param  Captured hex data
  * @retval Converted ASCII value
  */
unsigned char hexToAscii(unsigned char hexData)
{
  unsigned char asciiData = 0;

  if((hexData >= 0x00) && (hexData <= 0x09))
  {
    asciiData = asciiData + 0x30;
  }

  return asciiData;
}

/*********************************************************************************************************
 *  INPUT FUNCTIONS
 *********************************************************************************************************/

/**
  * @brief  Returns acceleration values of 3 axis (x, y, z) from BALANCE BLOCK
  * @param  MESSAGE_ID_BALANCE_BLOCK
  * @retval Acceleration values in array
  */
int* getAcc(unsigned int balanceBlockID)
{
  createDataRequestPacket(balanceBlockID);

  CAN.readMsgBuf(&rxId, &len, rxBuf);      // Read data: len = data length, buf = data byte(s)
  CAN.readMsgBuf(&rxId, &len, rx2Buf);     // Read data: len = data length, buf = data byte(s)
  static int accData[3];
  accData[0] = (rxBuf[3] << 8) + rxBuf[4];
  accData[1] = (rxBuf[5] << 8) + rxBuf[6];
  accData[2] = (rxBuf[7] << 8) + rx2Buf[0];

  return accData;
}

/**
  * @brief  Returns gyro values of 3 axis (x, y, z) from BALANCE BLOCK
  * @param  MESSAGE_ID_BALANCE_BLOCK
  * @retval Gyro values in array
  */
int* getGyro(unsigned int balanceBlockID)
{
  createDataRequestPacket(balanceBlockID);

  CAN.readMsgBuf(&rxId, &len, rxBuf);      // Read data: len = data length, buf = data byte(s)
  CAN.readMsgBuf(&rxId, &len, rx2Buf);     // Read data: len = data length, buf = data byte(s)
  static int gyroData[3];
  gyroData[0] = (rx2Buf[1] << 8) + rx2Buf[2];
  gyroData[1] = (rx2Buf[3] << 8) + rx2Buf[4];
  gyroData[2] = (rx2Buf[5] << 8) + rx2Buf[6];

  return gyroData;
}

/**
  * @brief  Returns infrared state from DETECT BLOCK
  * @param  MESSAGE_ID_DETECT_BLOCK
  * @retval Infrared state ("0" or "1")
  */
unsigned char getDetect(unsigned int detectBlockID)
{
  createDataRequestPacket(detectBlockID);

  CAN.readMsgBuf(&rxId, &len, rxBuf);      // Read data: len = data length, buf = data byte(s)
  unsigned char irData = rxBuf[3];

  return irData;
}

/**
  * @brief  Returns ultrasonic distance value from EYE BLOCK
  * @param  MESSAGE_ID_EYE_BLOCK
  * @retval Ultrasonic distance value(0x00 - 0xFF)
  */
unsigned char getEye(unsigned int eyeBlockID)
{
  createDataRequestPacket(eyeBlockID);

  CAN.readMsgBuf(&rxId, &len, rxBuf);      // Read data: len = data length, buf = data byte(s)
  unsigned char ultrasonicData = rxBuf[3];

  return ultrasonicData;
}

/**
  * @brief  Returns passive infrared state from GESTURE BLOCK
  * @param  MESSAGE_ID_GESTURE_BLOCK
  * @retval Passive infrared state ("0" or "1")
  */
unsigned char getGesture(unsigned int gestureBlockID)
{
  createDataRequestPacket(gestureBlockID);

  CAN.readMsgBuf(&rxId, &len, rxBuf);      // Read data: len = data length, buf = data byte(s)
  unsigned char pirData = rxBuf[3];

  return pirData;
}

/**
  * @brief  Returns potentiometer value from KNOB BLOCK
  * @param  MESSAGE_ID_KNOB_BLOCK
  * @retval Potentiometer value(0x00 - 0xFF)
  */
unsigned char getKnob(unsigned int knobBlockID)
{
  createDataRequestPacket(knobBlockID);

  CAN.readMsgBuf(&rxId, &len, rxBuf);      // Read data: len = data length, buf = data byte(s)
  unsigned char knobData = rxBuf[3];

  return knobData;
}

/**
  * @brief  Returns microphone sound value from MIC BLOCK
  * @param  MESSAGE_ID_MIC_BLOCK
  * @retval Microphone sound value(0x00 - 0xFF) or ("0" or "1")
  */
unsigned char getMic(unsigned int micBlockID)
{
  createDataRequestPacket(micBlockID);

  CAN.readMsgBuf(&rxId, &len, rxBuf);      // Read data: len = data length, buf = data byte(s)
  unsigned char micData = rxBuf[3];

  return micData;
}

/**
  * @brief  Returns photosensor value from PHOTO BLOCK
  * @param  MESSAGE_ID_PHOTO_BLOCK
  * @retval Photosensor value(0x00 - 0xFF)
  */
unsigned char getPhoto(unsigned int photoBlockID)
{
  createDataRequestPacket(photoBlockID);

  CAN.readMsgBuf(&rxId, &len, rxBuf);      // Read data: len = data length, buf = data byte(s)
  unsigned char photoData = rxBuf[3];

  return photoData;
}

/**
  * @brief  Returns temperature value from TEMP BLOCK
  * @param  MESSAGE_ID_TEMP_BLOCK
  * @retval Temperature value(0x00 - 0xFF)
  */
unsigned char getTemp(unsigned int tempBlockID)
{
  createDataRequestPacket(tempBlockID);

  CAN.readMsgBuf(&rxId, &len, rxBuf);      // Read data: len = data length, buf = data byte(s)
  unsigned char tempData = rxBuf[3];

  return tempData;
}

/**
  * @brief  Returns tilt state from TILT BLOCK
  * @param  MESSAGE_ID_TILT_BLOCK
  * @retval Tilt state("0" or "1")
  */
unsigned char getTilt(unsigned int tiltBlockID)
{
  createDataRequestPacket(tiltBlockID);

  CAN.readMsgBuf(&rxId, &len, rxBuf);      // Read data: len = data length, buf = data byte(s)
  unsigned char tiltData = rxBuf[3];

  return tiltData;
}

///**
//  * @brief  Returns colour type from COLOUR BLOCK
//  * @param  MESSAGE_ID_COLOUR_BLOCK
//  * @retval Colour type(0x00 - 0xFF)
//  */
//unsigned char getTemp(unsigned int tempBlockID)
//{
//  createDataRequestPacket(tempBlockID);
//
//  CAN.readMsgBuf(&rxId, &len, rxBuf);      // Read data: len = data length, buf = data byte(s)
// unsigned char tempData = rxBuf[3];
//
//  return tempData;
//}

/**
  * @brief  Returns slider value from SLIDE BLOCK
  * @param  MESSAGE_ID_SLIDE_BLOCK
  * @retval Slider value(0x00 - 0xFF)
  */
unsigned char getSlide(unsigned int slideBlockID)
{
  createDataRequestPacket(slideBlockID);

  CAN.readMsgBuf(&rxId, &len, rxBuf);      // Read data: len = data length, buf = data byte(s)
  unsigned char sliderData = rxBuf[3];

  return sliderData;
}

/**
  * @brief  Returns infrared state from FOLLOW BLOCK
  * @param  MESSAGE_ID_FOLLOW_BLOCK
  * @retval Infrared state ("0" or "1")
  */
unsigned char getFollow(unsigned int followBlockID)
{
  createDataRequestPacket(followBlockID);

  CAN.readMsgBuf(&rxId, &len, rxBuf);      // Read data: len = data length, buf = data byte(s)
  unsigned char irData = rxBuf[3];

  return irData;
}

/*********************************************************************************************************
 *  OUTPUT FUNCTIONS
 *********************************************************************************************************/

/**
  * @brief  Sets DC motor speed and direction values for 360 BLOCK
  * @param  MESSAGE_ID_360_BLOCK
			motorDirection	: forward or backward
			motorSpeed	: PWM value (0x00 - 0xFF)
			motorEnable	: enable or disable
  * @retval None
  */
void set360(unsigned int motor360BlockID, unsigned char motorDirection, unsigned char motorSpeed, unsigned char motorEnable)
{
  unsigned char sendData[7] = {SYNC_BYTE_START, STM32_DATA_PACKET_TYPE, 0x03, motorDirection, motorSpeed, motorEnable, SYNC_BYTE_STOP};
  CAN.sendMsgBuf(motor360BlockID, 0, 7, sendData);
}

/**
  * @brief  Sets buzzer state for BIPP BLOCK
  * @param  MESSAGE_ID_BIPP_BLOCK
			buzzerState : "0" or "1"
  * @retval None
  */
void setBipp(unsigned int bippBlockID, unsigned char buzzerState)
{
  unsigned char sendData[5] = {SYNC_BYTE_START, STM32_DATA_PACKET_TYPE, 0x01, buzzerState, SYNC_BYTE_STOP};
  CAN.sendMsgBuf(bippBlockID, 0, 5, sendData);
}

/**
  * @brief  Sets RGB LED states for COLOR BLOCK
  * @param  MESSAGE_ID_COLOR_BLOCK
			redLedState 	: "0" or "1"
			greenLedState 	: "0" or "1"
			blueLedState 	: "0" or "1"
  * @retval None
  */
void setColor(unsigned int colorBlockID, unsigned char redLedState, unsigned char greenLedState, unsigned char blueLedState)
{
  unsigned char sendData[7] = {SYNC_BYTE_START, STM32_DATA_PACKET_TYPE, 0x03, redLedState, greenLedState, blueLedState, SYNC_BYTE_STOP};
  CAN.sendMsgBuf(colorBlockID, 0, 7, sendData);
}

/**
  * @brief  Sets servo motor angle value for GRIP BLOCK
  * @param  MESSAGE_ID_GRIPP_BLOCK
			motorAngle	: PWM value (0x00 - 0xFF)
			motorEnable	: enable or disable
  * @retval None
  */
void setGrip(unsigned int gripBlockID, unsigned char motorAngle, unsigned char motorEnable)
{
  unsigned char sendData[7] = {SYNC_BYTE_START, STM32_DATA_PACKET_TYPE, 0x03, 0x01, motorAngle, motorEnable, SYNC_BYTE_STOP};
  CAN.sendMsgBuf(gripBlockID, 0, 7, sendData);
}

/**
  * @brief  Sets bar graph level value for LEVEL BLOCK
  * @param  MESSAGE_ID_LEVEL_BLOCK
			barGraphData : 0x00 - 0xFF
  * @retval None
  */
void setLevel(unsigned int levelBlockID, unsigned char barGraphData)
{
  unsigned char sendData[5] = {SYNC_BYTE_START, STM32_DATA_PACKET_TYPE, 0x01, barGraphData, SYNC_BYTE_STOP};
  CAN.sendMsgBuf(levelBlockID, 0, 5, sendData);
}

/**
  * @brief  Sets single LED state for LIGHT BLOCK
  * @param  MESSAGE_ID_LIGHT_BLOCK
			ledState : "0" or "1"
  * @retval None
  */
void setLight(unsigned int lightBlockID, unsigned char ledState)
{
  unsigned char sendData[5] = {SYNC_BYTE_START, STM32_DATA_PACKET_TYPE, 0x01, ledState, SYNC_BYTE_STOP};
  CAN.sendMsgBuf(lightBlockID, 0, 5, sendData);
}

/**
  * @brief  Sets servo motor angle value for LINK BLOCK
  * @param  MESSAGE_ID_LINK_BLOCK
			motorAngle	: PWM value (0x00 - 0xFF)
			motorEnable	: enable or disable
  * @retval None
  */
void setLink(unsigned int linkBlockID, unsigned char motorAngle, unsigned char motorEnable)
{
  unsigned char sendData[7] = {SYNC_BYTE_START, STM32_DATA_PACKET_TYPE, 0x03, 0x01, motorAngle, motorEnable, SYNC_BYTE_STOP};
  CAN.sendMsgBuf(linkBlockID, 0, 7, sendData);
}

/**
  * @brief  Sets DC motor speed and direction values for MOTION BLOCK
  * @param  MESSAGE_ID_MOTION_BLOCK
			motorDdirection	: forward or backward
			motorSpeed		: PWM value (0x00 - 0xFF)
			motorEnable		: enable or disable
  * @retval None
  */
void setMotion(unsigned int motionBlockID, unsigned char motorDirection, unsigned char motorSpeed, unsigned char motorEnable)
{
  unsigned char sendData[7] = {SYNC_BYTE_START, STM32_DATA_PACKET_TYPE, 0x03, motorDirection, motorSpeed, motorEnable, SYNC_BYTE_STOP};
  CAN.sendMsgBuf(motionBlockID, 0, 7, sendData);
}

/**
  * @brief  Sets DC motor speed and direction values for ROLL BLOCK
  * @param  MESSAGE_ID_ROLL_BLOCK
			motorDdirection	: forward or backward
			motorSpeed		: PWM value (0x00 - 0xFF)
			motorEnable		: enable or disable
  * @retval None
  */
void setRoll(unsigned int rollBlockID, unsigned char motorDirection, unsigned char motorSpeed, unsigned char motorEnable)
{
  unsigned char sendData[7] = {SYNC_BYTE_START, STM32_DATA_PACKET_TYPE, 0x03, motorDirection, motorSpeed, motorEnable, SYNC_BYTE_STOP};
  CAN.sendMsgBuf(rollBlockID, 0, 7, sendData);
}

/**
  * @brief  Sets DC motor speed and direction values for BIRRR BLOCK
  * @param  MESSAGE_ID_BIRRR_BLOCK
			motorDdirection	: forward or backward
			motorSpeed		: PWM value (0x00 - 0xFF)
			motorEnable		: enable or disable
  * @retval None
  */
void setBirrr(unsigned int birrrBlockID, unsigned char motorDirection, unsigned char motorSpeed, unsigned char motorEnable)
{
  unsigned char sendData[7] = {SYNC_BYTE_START, STM32_DATA_PACKET_TYPE, 0x03, motorDirection, motorSpeed, motorEnable, SYNC_BYTE_STOP};
  CAN.sendMsgBuf(birrrBlockID, 0, 7, sendData);
}

void createBlockDataRequestPacket(unsigned int requestMessageId)
{
  unsigned char sendData[4] = {SYNC_BYTE_START, 0x04, 0x00, SYNC_BYTE_STOP};
  CAN.sendMsgBuf(requestMessageId, 0, 4, sendData);
}

uint16_t getBlockID()
{
  createBlockDataRequestPacket(MESSAGE_ID_REQUEST);

  CAN.readMsgBuf(&rxId, &len, rxBuf);      // Read data: len = data length, buf = data byte(s)
  unsigned char messageIDH = rxBuf[3];
  unsigned char messageIDL = rxBuf[4];

  return (messageIDH << 8 | messageIDL);
}
/*********************************************************************************************************
 *  END FILE
 *********************************************************************************************************/
