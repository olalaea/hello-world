/*
 * usart_3.h
 *
 *  Created on: 3 May 2018
 *      Author: Ayyuce
 */

#ifndef USART_3_H_
#define USART_3_H_

#include "stm32f4xx.h"

void USART3_CONFIG(uint32_t baudrate);
void updateUSART3Write(void);
void enableUSART3Read(void);
void disableUSART3Read(void);
void enableUSART3Write(void);
void disableUSART3Write(void);
void readUSART3Data(void);
uint8_t isUSART3DataApproved(void);
uint8_t isNewUSART3DataReceived(void);

void parseMotorValues(void);
void setDefaultMessage(void);


#endif /* USART_3_H_ */
