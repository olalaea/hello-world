/*
 * io.c
 *
 *  Created on: 3 May 2018
 *      Author: Ayyuce
 */


#include "io_read_write.h"
#include "stm32f4xx.h"
#include "stdio.h"
#include "config.h"
#include "io_config.h"
#include "general_purpose_func.h"
#include "io_pin.h"
//#include "timer.h"
#include <stdio.h>
#include <stdlib.h>

char analog_message[ANALOG_MESSAGE_READ_SIZE+1]; uint8_t  digital_message[DIGITAL_MESSAGE_READ_SIZE+1];
extern uint16_t ADC1ConvertedValue[ANALOG_PIN_AMOUNT];

void ReadAnalogPins(void){
	//DMA her bir analog degeri ADC1ConvertedValue[] arrayinin adresinde tutar.
	//ADC1ConvertedValue[] icerisindeki deger ADC_RegularChannelConfig() fonksiyonunda tanimladigimiz okuma sirasidir.
	shiftIntArray(ANALOG1.BUFFER);
	ANALOG1.BUFFER[0] = ADC1ConvertedValue[0];
	ANALOG1.VALUE = map1000(averageArray(ANALOG1.BUFFER));

	shiftIntArray(ANALOG2.BUFFER);
	ANALOG2.BUFFER[0] = ADC1ConvertedValue[1];
	ANALOG2.VALUE = map1000(averageArray(ANALOG2.BUFFER));

	shiftIntArray(ANALOG3.BUFFER);
	ANALOG3.BUFFER[0] = ADC1ConvertedValue[2];
	ANALOG3.VALUE = map1000(averageArray(ANALOG3.BUFFER));

	sprintf(analog_message,"%04d%04d%04d",ANALOG1.VALUE,ANALOG2.VALUE ,ANALOG3.VALUE);
}

void ReadDigitalPins(void){
	//bu fonksiyonda okunan tum digital degerler int tipinde Digital_IN_Buffer isminde bir arrayin icinde tutulmustur
	//bu arrayin tum elemanlari char tipinde digital_message isminde bir arrayin icine birebir kopyalanmistir
	uint8_t Digital_IN_Buffer[DIGITAL_MESSAGE_READ_SIZE];
	Digital_IN_Buffer[0]= !HAL_GPIO_ReadPin(DIGITAL_IN1.PORT, DIGITAL_IN1.PIN);
	Digital_IN_Buffer[1]= !HAL_GPIO_ReadPin(DIGITAL_IN2.PORT, DIGITAL_IN2.PIN);
	Digital_IN_Buffer[2]= !HAL_GPIO_ReadPin(DIGITAL_IN3.PORT, DIGITAL_IN3.PIN);
	Digital_IN_Buffer[3]= !HAL_GPIO_ReadPin(DIGITAL_IN4.PORT, DIGITAL_IN4.PIN);
	Digital_IN_Buffer[4]= !HAL_GPIO_ReadPin(DIGITAL_IN5.PORT, DIGITAL_IN5.PIN);
	Digital_IN_Buffer[5]= !HAL_GPIO_ReadPin(DIGITAL_IN6.PORT, DIGITAL_IN6.PIN);
	Digital_IN_Buffer[6]= !HAL_GPIO_ReadPin(DIGITAL_IN7.PORT, DIGITAL_IN7.PIN);
	Digital_IN_Buffer[7]= !HAL_GPIO_ReadPin(DIGITAL_IN8.PORT, DIGITAL_IN8.PIN);
	Digital_IN_Buffer[8]= !HAL_GPIO_ReadPin(DIGITAL_IN9.PORT, DIGITAL_IN9.PIN);
	Digital_IN_Buffer[9]= !HAL_GPIO_ReadPin(DIGITAL_IN10.PORT, DIGITAL_IN10.PIN);
	Digital_IN_Buffer[10]= !HAL_GPIO_ReadPin(DIGITAL_IN11.PORT, DIGITAL_IN11.PIN);
	Digital_IN_Buffer[11]= !HAL_GPIO_ReadPin(DIGITAL_IN12.PORT, DIGITAL_IN12.PIN);
	Digital_IN_Buffer[12]= !HAL_GPIO_ReadPin(DIGITAL_IN13.PORT, DIGITAL_IN13.PIN);
	Digital_IN_Buffer[13]= !HAL_GPIO_ReadPin(DIGITAL_IN14.PORT, DIGITAL_IN14.PIN);
	Digital_IN_Buffer[14]= !HAL_GPIO_ReadPin(DIGITAL_IN15.PORT, DIGITAL_IN15.PIN);
	Digital_IN_Buffer[15]= !HAL_GPIO_ReadPin(DIGITAL_IN16.PORT, DIGITAL_IN16.PIN);

	
	for (int i = 0; i < 16; i++)
	{
		digital_message[i] = '0' + Digital_IN_Buffer[i];
	}
	
	//sprintf((char *)digital_message,"%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d",testPinState, Digital_IN_Buffer[1],Digital_IN_Buffer[2],Digital_IN_Buffer[3],Digital_IN_Buffer[4],Digital_IN_Buffer[5],Digital_IN_Buffer[6],Digital_IN_Buffer[7],Digital_IN_Buffer[8],Digital_IN_Buffer[9],Digital_IN_Buffer[10],Digital_IN_Buffer[11],Digital_IN_Buffer[12],Digital_IN_Buffer[13],Digital_IN_Buffer[14],Digital_IN_Buffer[15]);
	//sprintf(digital_message,"%01u%01u%01u%01u%01u%01u%01u%01u%01u%01u%01u%01u%01u%01u%01u%01u",Digital_IN_Buffer[0], Digital_IN_Buffer[1],Digital_IN_Buffer[2],Digital_IN_Buffer[3],Digital_IN_Buffer[4],Digital_IN_Buffer[5],Digital_IN_Buffer[6],Digital_IN_Buffer[7],Digital_IN_Buffer[8],Digital_IN_Buffer[9],Digital_IN_Buffer[10],Digital_IN_Buffer[11],Digital_IN_Buffer[12],Digital_IN_Buffer[13],Digital_IN_Buffer[14],Digital_IN_Buffer[15]);
}

void WriteDigitalPins(void){

	HAL_GPIO_WritePin(DIGITAL_OUT1.PORT, DIGITAL_OUT1.PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(DIGITAL_OUT2.PORT, DIGITAL_OUT2.PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(DIGITAL_OUT3.PORT, DIGITAL_OUT3.PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(DIGITAL_OUT4.PORT, DIGITAL_OUT4.PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(DIGITAL_OUT5.PORT, DIGITAL_OUT5.PIN, GPIO_PIN_SET);
}

void beatHeart(void){
	HAL_GPIO_TogglePin(BLINK.PORT, BLINK.PIN);
}

