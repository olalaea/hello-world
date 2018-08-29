/*
 * io.h
 *
 *  Created on: 3 May 2018
 *      Author: Ayyuce
 */

#ifndef IO_READ_WRITE_H_
#define IO_READ_WRITE_H_

#include "stm32f4xx.h"

void ReadAnalogPins(void);
void beatHeart(void);
void stillHeart(void);
void enableClutch(void);
void disableClutch(void);
float currentCalculation (uint16_t adcValue);

#endif /* IO_READ_WRITE_H_ */
