/*
 * general_purpose_func.c
 *
 *  Created on: 3 May 2018
 *      Author: Ayyuce
 *
 */

#include "config.h"
#include "general_purpose_func.h"

short int emergency_start_flag=0;

uint16_t averageArray(uint16_t par[]){
	uint32_t sum=0; uint8_t i=0;
	while(i < SAMPLING_RATE){
		sum += par[i];
		i++;
	}
	return sum/SAMPLING_RATE;
}

float averageFloatArray(float par[]){
	float sum=0; uint8_t i=0;
	while(i < 100){
		sum += par[i];
		i++;
	}
	return sum/100;
}

void shiftIntArray(uint16_t param[]){
	for(uint8_t var = SAMPLING_RATE-1; var > 0; var--){
		param[var] = param[var-1];
	}
	param[0] = 0;
}

void shiftFloatArray(float param[]){
	for(uint8_t var = 99; var > 0; var--){
		param[var] = param[var-1];
	}
	param[0] = 0;
}

uint8_t isAllSame(uint8_t par[]){
	uint8_t a = par[0];
	for (int i = 1; i < SAMPLING_RATE; i++){
		if (par[i] != a){
			return 0;
		}
	}
	return 1;
}

void shiftCharArray(uint8_t param[]){
	for(uint8_t var = SAMPLING_RATE-1; var > 0; var--){
		param[var] = param[var-1];
	}
	param[0] = 0;
}

void copyChar(char to[], char from[], uint8_t length, uint8_t start){
	for (uint8_t var = 0; var < length; ++var) {
		to[var] = from[var + start];
	}
}

void copyArray(char to[], char from[], uint8_t length, uint8_t start){
	for (uint8_t var = 0; var < length; ++var) {
		to[var] = from[var + start];
	}
}

void zeroChar(char array[], uint8_t length) {
	for (uint8_t var = 0; var < length; ++var) {
		array[var] = 0;
	}
}
uint16_t map1000(uint16_t analog_read_value){

	uint16_t JOYSTICK1_ORTA= (JOYSTICK1_MAX-JOYSTICK1_MIN)/2;

	if (analog_read_value > (JOYSTICK1_ORTA - JOYSTICK1_DEADBAND) && analog_read_value < (JOYSTICK1_ORTA + JOYSTICK1_DEADBAND)){
		analog_read_value = JOYSTICK1_ORTA;
	} else if (analog_read_value <50) {
		analog_read_value = JOYSTICK1_MIN;
	} else if (analog_read_value > 4020){
		analog_read_value= JOYSTICK1_MAX;
	}

	return ((JOYSTICK1_SET_MAX-JOYSTICK1_SET_MIN)*(analog_read_value-JOYSTICK1_MIN)/(JOYSTICK1_MAX-JOYSTICK1_MIN)) + JOYSTICK1_SET_MIN;
}

uint8_t isAllZero(uint8_t par[], uint16_t numberofchar){	//eger mesaj paketi 0 ise flag 1, mesaj paketinde elemanlar var ise flag 0
	#if 0
	/*int sum=0 , i= 0;
	
	for (i = 0; i < numberofchar; ++i) {
	  sum += par[i];
	}
	if (sum == 0){
		emergency_start_flag=1;
		return 1;
	}
	else{
		emergency_start_flag=0;
		return 0;
	}*/
	#else
	int i = 0;
	
	for (i = 0; i < numberofchar; i++)
	{
		if (par[i] != 0)
		{
			emergency_start_flag=0;
			return 0;
		}
	}
	
	emergency_start_flag=1;
	return 1;
	#endif
}
