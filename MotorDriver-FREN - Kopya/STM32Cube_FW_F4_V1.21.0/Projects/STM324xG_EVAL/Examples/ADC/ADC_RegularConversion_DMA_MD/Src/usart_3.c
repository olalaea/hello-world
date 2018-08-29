/*
 * usart_3.c
 *
 *  Created on: 3 May 2018
 *      Author: Ayyuce
 */

#include "usart_3.h"
#include "io_pin.h"
#include "config.h"
#include "io_config.h"
#include "general_purpose_func.h"
#include "stdio.h"

extern char readUSART3[READ_MESSAGE_SIZE], sendUSART3[SEND_MESSAGE_SIZE];
char approved_message[READ_MESSAGE_SIZE];

extern ANALOG_IO_PIN ANALOG1;
extern uint8_t mesaj_data[CAN_MESAJ_ALMA_SIZE];

//extern char analog_message[ANALOG_MESSAGE_READ_SIZE], digital_message[DIGITAL_MESSAGE_READ_SIZE];

uint8_t isNewUSART3DataReceived(void){
	return 1;//return DMA_GetFlagStatus(DMA1_Stream1, DMA_FLAG_TCIF1);
}

uint8_t isUSART3DataApproved(void){
return  readUSART3[0] == PREFIX && readUSART3[1] == DIGITAL_PREFIX && readUSART3[18] == ANALOG_PREFIX && readUSART3[31] == SUFFIX;
		//	readUSART3[13] == BRAKE_PREFIX && readUSART3[18] == BRAKE_SUFFIX && readUSART3[19] == GEAR_PREFIX && readUSART3[24] == GEAR_SUFFIX &&
		//	readUSART3[25] == STEERING_PREFIX && readUSART3[30] == STEERING_SUFFIX && readUSART3[31] == SUFFIX;
}

void updateUSART3Write(void){
	//sprintf(sendUSART3,"A1: %04u, A2: %04u, A3: %04u, A4: %04u\n",ANALOG1.VALUE, ANALOG2.VALUE, ANALOG3.VALUE, ANALOG4.VALUE);
	copyArray(sendUSART3,(char *) mesaj_data, 32, 0);
	HAL_UART_Transmit_DMA(&Uart3Handle, (uint8_t *)sendUSART3, 32);
}

void enableUSART3Read(void){
	/*DMA_ClearFlag(DMA1_Stream1, DMA_FLAG_TCIF1);
	DMA_Cmd(DMA1_Stream1, ENABLE);*/
}

void disableUSART3Read(void){
	//DMA_Cmd(DMA1_Stream1, DISABLE);
}

void enableUSART3Write(void){
	/*DMA_ClearFlag(DMA1_Stream3, DMA_FLAG_TCIF3);
	DMA_Cmd(DMA1_Stream3, ENABLE);*/
}

void disableUSART3Write(void){
	//DMA_Cmd(DMA1_Stream3, DISABLE);
}

void readUSART3Data(void){
	HAL_UART_Receive_DMA(&Uart3Handle, (uint8_t *)readUSART3, READ_MESSAGE_SIZE);
	copyChar(approved_message, readUSART3, READ_MESSAGE_SIZE, 0);
	zeroChar(readUSART3, READ_MESSAGE_SIZE);
}

/* Parse Motor Values Function */
void parseMotorValues(void){
	/*zeroChar(accelArray, 4);
	copyChar(accelArray, approved_message, 4, 8);
	accelValue = 0;
	accelValue += (accelArray[0] - 48);
	for (uint8_t var = 1; var < 4; var++) {
		accelValue *=10;
		accelValue += (accelArray[var] - 48);
	}

	zeroChar(brakeArray, 4);
	copyChar(brakeArray, approved_message, 4, 14);
	brakeValue = 0;
	brakeValue += (brakeArray[0] - 48);
	for (uint8_t var = 1; var < 4; var++) {
		brakeValue *=10;
		brakeValue += (brakeArray[var] - 48);
	}

	zeroChar(gearArray, 4);
	copyChar(gearArray, approved_message, 4, 20);
	gearValue = 0;
	gearValue += (gearArray[0] - 48);
	for (uint8_t var = 1; var < 4; var++) {
		gearValue *=10;
		gearValue += (gearArray[var] - 48);
	}

	zeroChar(steeringArray, 4);
	copyChar(steeringArray, approved_message, 4, 26);
	steeringValue = 0;
	steeringValue += (steeringArray[0] - 48);
	for (uint8_t var = 1; var < 4; var++) {
		steeringValue *=10;
		steeringValue += (steeringArray[var] - 48);
	}*/
}


void setDefaultMessage(void){
	copyChar(approved_message, DEFAULT_MESSAGE, READ_MESSAGE_SIZE, 0);
}
