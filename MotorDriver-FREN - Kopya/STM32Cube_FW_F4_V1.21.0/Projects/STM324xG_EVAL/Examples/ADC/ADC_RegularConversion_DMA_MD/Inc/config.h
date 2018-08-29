/*
 * config.h
 *
 *  Created on: 3 May 2018
 *      Author: Ayyuce
 */

#ifndef CONFIG_H_
#define CONFIG_H_


#include "stm32f4xx.h"

#define MEASURE_TIME 				20		// Each 1 ms DMA status is controlled
#define SAMPLING_RATE 				20 		// Each moving average array have 20 element
#define MSG_TIME 					100 		// Each 5 ms all values are refreshed
#define CAN_MSG_TIME				20
#define HEARTBEAT 					100		// Each 100 ms hearbeat led is toggled
#define INIT_TIME					500		// Initialization time
#define TELEMETRY					500		// Telemetry monitoring time
#define TIMEOUT_TIME 				100		// If control message doesn't come within 1000 ms timeout will occur, DEFAULT_MESSAGE is written to all output
#define TIM_PERIOD_DIVIDER 			250
#define STABILIZER_TIME				20

#define ANALOG_PIN_AMOUNT			2		// Total number of used pins

#define READ_MESSAGE_SIZE			32		// Received message size = 32
#define SEND_MESSAGE_SIZE			32		// Transmitted message size = 71
#define ANALOG_MESSAGE_READ_SIZE 	12
#define DIGITAL_MESSAGE_READ_SIZE 	4
#define REMOTE_WRITE_SIZE	27				//can tx size

#define CAN_FIFO_AZAMI_BOYUT 		1024
#define CAN_MESAJ_ALMA_SIZE 		128
#define CAN_KENDI_ADRESI			0x00E0
#define STX 0x82
#define ETX 0x80
#define ADR 0x00
#define ADR2 0x00

#define MOTOR_CODE				ACCEL_MOTOR_CODE // Change for each motor type
#define ACCEL_MOTOR_CODE		0x00A0
#define BRAKE_MOTOR_CODE		0x00B0
#define GEAR_MOTOR_CODE			0x00C0
#define STEERING_MOTOR_CODE		0x00D0
#define MAIN_BOARD_CODE			0x00E0

#define ENCODER_MAX_LIMIT			875
#define ENCODER_MIN_LIMIT			125
#define NONE 						0x00
#define CLOCKWISE 					0x01
#define COUNTERCLOCKWISE 			0x02

#define BASLA 		1
#define ADRES 		2
#define DATA 		3
#define SON 		4
#define CHECKSUM 	5

#define PREFIX 						'M'		// Control message Prefix
#define DIGITAL_PREFIX				'D'		// Digital message Prefix
#define ANALOG_PREFIX				'A'		// Analog message Prefix
#define SUFFIX 						'S'		// Suffix of control message

#define JOYSTICK1_DEADBAND			50		//joystick deadband degeri
#define JOYSTICK1_MIN				0		//joystick minimum degeri
#define JOYSTICK1_MAX				4096	//joystick maximum degeri
#define JOYSTICK1_SET_MIN 			0		//joysticki map etmek istedigimiz minimum degeri
#define JOYSTICK1_SET_MAX 			1000	//joysticki map etmek istedigimiz maximum degeri

#define RANGE_JOYSTICK_MAX 			875
#define RANGE_JOYSTICK_MIN 			125

#define DEBUG_READ_MESSAGE_SIZE		32	// USART2'de test icin kullanildi
#define DEBUG_SEND_MESSAGE_SIZE		32	// USART2'de test icin kullanildi

#define DEFAULT_MESSAGE			"DEFAULT MESSAGE\n"

/* Definition for ADCx clock resources */
#define ADCx                            ADC1
#define ADCx_CLK_ENABLE()               __HAL_RCC_ADC1_CLK_ENABLE()
#define DMAx_CLK_ENABLE()               __HAL_RCC_DMA2_CLK_ENABLE()     
#define ADCx_CHANNEL_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOA_CLK_ENABLE()
     
#define ADCx_FORCE_RESET()              __HAL_RCC_ADC_FORCE_RESET()
#define ADCx_RELEASE_RESET()            __HAL_RCC_ADC_RELEASE_RESET()

/* Definition for ADCx's Channel */
#define ADCx_CHANNEL_1                  ADC_CHANNEL_0

/* Definition for ADCx's DMA */
#define ADCx_DMA_CHANNEL                DMA_CHANNEL_0
#define ADCx_DMA_STREAM                 DMA2_Stream0

/* Definition for ADCx's NVIC */
#define ADCx_DMA_IRQn                   DMA2_Stream0_IRQn
#define ADCx_DMA_IRQHandler             DMA2_Stream0_IRQHandler

#define USART2_RX_BUFFER_SIZE						32
#define USART3_RX_BUFFER_SIZE						32

typedef struct DIGITAL_IO_PINS {
	uint16_t PIN;					// Pin Number, ex = GPIO_Pin_12
	GPIO_TypeDef* PORT;				// GPIO Port name, ex = GPIOC, GPIOD
}DIGITAL_IO_PIN;

typedef struct ANALOG_IO_PINS {
	uint8_t INDEX;					// Buffer Array Index
	uint16_t PIN;					// Pin Number, ex = GPIO_Pin_12
	GPIO_TypeDef* PORT;				// GPIO Port name, ex = GPIOC, GPIOD
	uint16_t BUFFER[SAMPLING_RATE];	// Buffer array for Moving average
	uint16_t VALUE;					// Final pin value
}ANALOG_IO_PIN;

typedef struct USART_IO_PINS {
	uint16_t PIN;					// Pin Number, ex = GPIO_Pin_12
	GPIO_TypeDef* PORT;				// GPIO Port name, ex = GPIOC, GPIOD
}USART_IO_PIN;

typedef struct CAN_IO_PINS {
	uint16_t PIN;					// Pin Number, ex = GPIO_Pin_12
	GPIO_TypeDef* PORT;				// GPIO Port name, ex = GPIOC, GPIOD
}CAN_IO_PIN;

typedef struct PWM_IO_PINS {
	uint8_t INDEX;					// Buffer Array Index
	uint16_t PIN;					// Pin Number, ex = GPIO_Pin_12
	GPIO_TypeDef* PORT;				// GPIO Port name, ex = GPIOC, GPIOD
	uint16_t VALUE;					// Final pin value
	TIM_TypeDef* TIMER;				// Timer Peripheral
}PWM_IO_PIN;

#endif /* CONFIG_H_ */

