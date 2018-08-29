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

char analog_message[ANALOG_MESSAGE_READ_SIZE];
extern uint16_t ADC1ConvertedValue[ANALOG_PIN_AMOUNT];
uint16_t encoder_value;
float inputCurrent = 0;
extern ANALOG_IO_PIN ANALOG1;		extern DIGITAL_IO_PIN BLINK;		extern DIGITAL_IO_PIN CLUTCH;

float inputCurrentArray[100];

void ReadAnalogPins(void){
	//DMA her bir analog degeri ADC1ConvertedValue[] arrayinin adresinde tutar.
	//ADC1ConvertedValue[] icerisindeki deger ADC_RegularChannelConfig() fonksiyonunda tanimladigimiz okuma sirasidir.
	shiftIntArray(ANALOG1.BUFFER);
	ANALOG1.BUFFER[0] = ADC1ConvertedValue[0];
	//encoder_value = map1000(averageArray(ANALOG1.BUFFER)); //motora bagliyken saat yonunde cevirince encoder degeri artar.
	encoder_value = map1000(ANALOG1.BUFFER[0]);
	
	sprintf(analog_message,"%04u", encoder_value); //bu satira gerek var mi tekrar bak
	
	
	shiftFloatArray(inputCurrentArray);
	inputCurrentArray[0] = ADC1ConvertedValue[1];
	inputCurrent = currentCalculation(averageFloatArray(inputCurrentArray));
}

float currentCalculation (uint16_t adcValue)
{
	float currentValue = 0;
	
	currentValue = (((adcValue * 0.805860) - 330) / 39.6);
	
	return currentValue;	
}

void beatHeart(void){
	HAL_GPIO_TogglePin(BLINK.PORT, BLINK.PIN);
}

/* Clutch Enable Function */
void enableClutch(void){
	HAL_GPIO_WritePin(CLUTCH.PORT, CLUTCH.PIN, GPIO_PIN_SET);
}

/* Clutch Disable Function */
void disableClutch(void){
	HAL_GPIO_WritePin(CLUTCH.PORT, CLUTCH.PIN, GPIO_PIN_RESET);
}

void stillHeart(void){
	HAL_GPIO_WritePin(BLINK.PORT, BLINK.PIN, GPIO_PIN_SET);
}
