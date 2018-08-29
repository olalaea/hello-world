/*
 * io_config.h
 *
 *  Created on: 8 May 2018
 *      Author: USER
 */

#ifndef IO_CONFIG_H_
#define IO_CONFIG_H_

#include <stdint.h>
#include "config.h"

void ADC2_DMA_CONFIG(void);
void ADC_DMA_CONFIG(void);
void DIGITAL_OUT_CONFIG(void);
void USART2_CONFIG(uint32_t baudrate);
void USART3_CONFIG(uint32_t baudrate);
void PWM_CONFIG(void);
void CAN1_CONFIG(void);
void ADC_CHANNEL_CONFIG (ADC_HandleTypeDef *hadc, uint32_t ADC_CHANNEL, uint32_t RANK, uint32_t ADC_SAMPLETIME_xCYCLES, uint32_t OFFSET);

extern ADC_HandleTypeDef AdcHandle;
extern UART_HandleTypeDef Uart2Handle;
extern UART_HandleTypeDef Uart3Handle;
extern CAN_HandleTypeDef CanHandle;
extern ADC_HandleTypeDef Adc2Handle;

#endif /* IO_CONFIG_H_ */
