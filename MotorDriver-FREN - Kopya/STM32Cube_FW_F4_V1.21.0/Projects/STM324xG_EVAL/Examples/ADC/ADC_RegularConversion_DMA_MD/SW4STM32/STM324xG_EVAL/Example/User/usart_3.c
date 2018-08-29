/*
 * usart_3.c
 *
 *  Created on: 3 May 2018
 *      Author: Ayyuce
 */

#include "usart_3.h"
#include "config.h"
#include "stdio.h"

char sendUSART3[SEND_MESSAGE_SIZE];
char readUSART3[READ_MESSAGE_SIZE];
char approved_message[READ_MESSAGE_SIZE];

extern char analog_message[ANALOG_MESSAGE_READ_SIZE], digital_message[DIGITAL_MESSAGE_READ_SIZE];

char testUartBuffer[32] = "12345678901234567890123456789012";

extern UART_HandleTypeDef Uart3Handle;

uint8_t isNewUSART3DataReceived(void){
	return 0;//return DMA_GetFlagStatus(DMA1_Stream1, DMA_FLAG_TCIF1);
}

uint8_t isUSART3DataApproved(void){
return 1; // readUSART3[0] == PREFIX && readUSART3[1] == DIGITAL_PREFIX && readUSART3[7] == ACCEL_PREFIX && readUSART3[12] == ACCEL_SUFFIX &&
		//	readUSART3[13] == BRAKE_PREFIX && readUSART3[18] == BRAKE_SUFFIX && readUSART3[19] == GEAR_PREFIX && readUSART3[24] == GEAR_SUFFIX &&
		//	readUSART3[25] == STEERING_PREFIX && readUSART3[30] == STEERING_SUFFIX && readUSART3[31] == SUFFIX;
}

void updateUSART3Write(void){

	int counter_interim=0;

	sendUSART3[0]=PREFIX;
	sendUSART3[1]=DIGITAL_PREFIX;

	for(counter_interim=0; counter_interim<16; counter_interim++){
		sendUSART3[counter_interim+2]=digital_message[counter_interim];
	}
	sendUSART3[18]=ANALOG_PREFIX;

	for(counter_interim=0; counter_interim<12; counter_interim++){
			sendUSART3[counter_interim+19]=analog_message[counter_interim];
		}

	sendUSART3[31]=SUFFIX;
		
	HAL_UART_Transmit_DMA(&Uart3Handle, (uint8_t *)testUartBuffer, 32);
	//HAL_UART_Transmit_DMA(&Uart3Handle, (uint8_t *)sendUSART3, 32);

//sprintf(sendUSART3,"%c%c%s%c%s%c", PREFIX, DIGITAL_PREFIX ,digital_message, ANALOG_PREFIX, analog_message, SUFFIX);
		//sprintf(sendUSART3,"%c%c%s%c%s%c",PREFIX,DIGITAL_PREFIX,digital_message,ANALOG_PREFIX,analog_message, SUFFIX);

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

void parseUSART3Data(void){
	/*copyCharArray(approved_message, readUSART3, READ_MESSAGE_SIZE, 0);
	zeroCharArray(readUSART3, READ_MESSAGE_SIZE);*/
}
