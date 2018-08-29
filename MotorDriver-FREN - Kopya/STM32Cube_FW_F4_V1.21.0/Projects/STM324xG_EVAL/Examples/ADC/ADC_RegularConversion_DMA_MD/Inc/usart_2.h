/*
 * usart_2.h
 *
 * *************************
 * BEST GRUP
 * *************************
 * Project:	Combat Vehicle
 * Author:	Bilge Miraç ATICI
 * Date:	27.09.2017
 * **************************
 */

#ifndef USART_2_H_
#define USART_2_H_

#include "stm32f4xx.h"


void USART2_Config(uint32_t baudrate);
void enableUSART2Read(void);
void enableUSART2Write(void);
void disableUSART2Read(void);
void disableUSART2Write(void);
void updateUSART2Write(void);
uint8_t isNewUSART2DataReceived(void);

#endif /* USART_2_H_ */
