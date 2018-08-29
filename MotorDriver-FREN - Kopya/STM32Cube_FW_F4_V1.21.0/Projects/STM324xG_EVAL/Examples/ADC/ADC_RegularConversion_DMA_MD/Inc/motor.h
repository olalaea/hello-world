/*
 * motor.h
 *
 *  Created on: 16 May 2018
 *      Author: USER
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include "stm32f4xx.h"

void motoru_istenilen_pozisyona_gotur(uint16_t position);
void set_motor_direction_of_rotation(uint8_t direction_value);
void stabilize_motor(void);
void acil_duruma_gec(void);
uint8_t acil_durum_mu_kontrol_et(void);
uint16_t encoderCalibration (uint16_t encoderValue);
void motor_sur_deneme(int16_t pwmdegeri);
	void motor_stabilize_deneme(void);
	void encoder_start(void);

#endif /* MOTOR_H_ */
