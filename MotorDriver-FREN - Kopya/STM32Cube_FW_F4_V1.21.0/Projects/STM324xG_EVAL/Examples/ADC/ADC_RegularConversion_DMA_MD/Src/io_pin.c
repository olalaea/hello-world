/*
 * io_pin.c
 *
 *  Created on: 8 May 2018
 *      Author: USER
 */

#include "config.h"
#include "io_pin.h"

ANALOG_IO_PIN ANALOG1;			PWM_IO_PIN MOTOR_PWM;
CAN_IO_PIN CAN1_Tx;				CAN_IO_PIN CAN1_Rx;
DIGITAL_IO_PIN IN1;				DIGITAL_IO_PIN IN2;			DIGITAL_IO_PIN BLINK;			DIGITAL_IO_PIN CLUTCH;
USART_IO_PIN USART2_Tx; 		USART_IO_PIN USART2_Rx;		USART_IO_PIN USART3_Tx; 		USART_IO_PIN USART3_Rx;

void CREATE_DIGITAL_PIN(void){ //4 adet digital_in mevcut
	CLUTCH.PORT = GPIOA; 			CLUTCH.PIN = GPIO_PIN_10;
	IN1.PORT = GPIOD;				IN1.PIN = GPIO_PIN_13;		//MOTOR DIRECTION
	IN2.PORT = GPIOD;				IN2.PIN = GPIO_PIN_14;
	BLINK.PORT = GPIOE; 			BLINK.PIN = GPIO_PIN_2;
}

void CREATE_ANALOG_PIN(void){
	ANALOG1.PORT = GPIOA;			ANALOG1.PIN = GPIO_PIN_0;
}

void CREATE_USART_PIN(void){
	USART2_Tx.PORT = GPIOD;			USART2_Tx.PIN = GPIO_PIN_5;
	USART2_Rx.PORT = GPIOD;			USART2_Rx.PIN = GPIO_PIN_6;
	USART3_Tx.PORT = GPIOC;			USART3_Tx.PIN = GPIO_PIN_10;
	USART3_Rx.PORT = GPIOC;			USART3_Rx.PIN = GPIO_PIN_11;
}

void CREATE_PWM_PIN(void){
	MOTOR_PWM.PORT = GPIOD;			MOTOR_PWM.PIN = GPIO_PIN_12;
}

void CREATE_CAN_PIN(void){
	CAN1_Tx.PORT = GPIOD;			CAN1_Tx.PIN = GPIO_PIN_1;
	CAN1_Rx.PORT = GPIOD;			CAN1_Rx.PIN = GPIO_PIN_0;
}