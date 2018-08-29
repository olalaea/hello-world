/*
 * general_purpose_func.h
 *
 *  Created on: 3 May 2018
 *      Author: USER
 */
#include <stdint.h>

#ifndef GENERAL_PURPOSE_FUNC_H_
#define GENERAL_PURPOSE_FUNC_H_

void shiftCharArray(uint8_t param[]);
void shiftIntArray(uint16_t param[]);
void shiftFloatArray(float param[]);
uint8_t isAllSame(uint8_t par[]);
uint16_t averageArray(uint16_t par[]);
float averageFloatArray(float par[]);
void copyArray(char to[], char from[], uint8_t length, uint8_t start);
void copyChar(char to[], char from[], uint8_t length, uint8_t start);
void zeroChar(char array[], uint8_t length);
uint16_t map1000(uint16_t analog_read_value);
uint8_t isAllZero(uint8_t par[], uint16_t numberofchar);
void copyArray(char to[], char from[], uint8_t length, uint8_t start);

#endif /* GENERAL_PURPOSE_FUNC_H_ */
