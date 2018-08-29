/*
 * usart_2.c
 *
 *  Created on: 3 May 2018
 *      Author: USER
 */

#include "usart_2.h"
#include "stdio.h"
#include "config.h"
#include "general_purpose_func.h"

char sendUSART2[DEBUG_SEND_MESSAGE_SIZE];
char readUSART2[DEBUG_READ_MESSAGE_SIZE];
extern uint8_t mesaj_data[CAN_MESAJ_ALMA_SIZE];
extern UART_HandleTypeDef	Uart2Handle;

uint8_t isUSART2DataApproved(void){
	return 1; // TO-DO : Some condition can be added
}
uint8_t isNewUSART2DataReceived(void){
	return 1; //return DMA_GetFlagStatus(DMA1_Stream5, DMA_FLAG_TCIF5);
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
	copyArray(sendUSART2,(char *) mesaj_data, 32, 0);
	HAL_UART_Transmit_IT(&Uart2Handle, (uint8_t *) sendUSART2, 32);
	
}
