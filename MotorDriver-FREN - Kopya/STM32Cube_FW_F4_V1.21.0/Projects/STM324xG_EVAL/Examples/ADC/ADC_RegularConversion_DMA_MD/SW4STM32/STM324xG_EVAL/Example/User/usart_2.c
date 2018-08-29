/*
 * usart_2.c
 *
 *  Created on: 3 May 2018
 *      Author: USER
 */

#include "usart_2.h"
#include "stdio.h"
#include "config.h"

extern char analog_message[ANALOG_MESSAGE_READ_SIZE], digital_message[DIGITAL_MESSAGE_READ_SIZE];
char sendUSART2[DEBUG_SEND_MESSAGE_SIZE];
char readUSART2[DEBUG_READ_MESSAGE_SIZE];

extern UART_HandleTypeDef Uart2Handle;
extern char testUartBuffer[32];

uint8_t isUSART2DataApproved(void){
	return 1; // TO-DO : Some condition can be added
}
uint8_t isNewUSART2DataReceived(void){
	return 0;//return DMA_GetFlagStatus(DMA1_Stream5, DMA_FLAG_TCIF5);
}
void enableUSART2Read(void){
	/*DMA_ClearFlag(DMA1_Stream5, DMA_FLAG_TCIF5);
	DMA_Cmd(DMA1_Stream5, ENABLE);*/
}
void disableUSART2Read(void){
	//DMA_Cmd(DMA1_Stream5, DISABLE);
}
void enableUSART2Write(void){
	/*DMA_ClearFlag(DMA1_Stream6, DMA_FLAG_TCIF6);
	DMA_Cmd(DMA1_Stream6, ENABLE);*/
}
void disableUSART2Write(void){
	//DMA_Cmd(DMA1_Stream6, DISABLE);
}
void updateUSART2Write(void){
	int counter_interim=0;

	sendUSART2[0]=PREFIX;
	sendUSART2[1]=DIGITAL_PREFIX;

	for(counter_interim=0; counter_interim<16; counter_interim++){
		sendUSART2[counter_interim+2]=digital_message[counter_interim];
	}
	sendUSART2[18]=ANALOG_PREFIX;

	for(counter_interim=0; counter_interim<12; counter_interim++){
			sendUSART2[counter_interim+19]=analog_message[counter_interim];
		}

	sendUSART2[31]=SUFFIX;
		
	HAL_UART_Transmit_IT(&Uart2Handle, (uint8_t *)testUartBuffer, 32);
	//HAL_UART_Transmit_IT(&Uart2Handle, (uint8_t *) sendUSART2, 32);
	//sprintf(sendUSART2,"%c%c%s%c%s%c",PREFIX,DIGITAL_PREFIX,digital_message,ANALOG_PREFIX,analog_message, SUFFIX);
}
