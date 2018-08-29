/*
 * motor.c
 *
 *  Created on: 16 May 2018
 *      Author: USER
 */

#include <io_read_write.h>
#include "stm32f4xx.h"
#include "stdio.h"
#include "config.h"
#include "general_purpose_func.h"
#include "io_pin.h"
#include "io_read_write.h"
#include "motor.h"
#include "can.h"
#include <stdlib.h>

extern TIM_HandleTypeDef 	Tim4Handle;
extern DIGITAL_IO_PIN IN1;			extern DIGITAL_IO_PIN IN2;
extern uint16_t encoder_value, joystick_y_value;
uint16_t motor_value;
int16_t error_old;
int16_t output_value;
short int motor_position_flag=0;	//motor istenilen pozisyona ulastiysa 1 ulasmadiysa 0 degerini alir
extern short int emergency_start_flag;	//acil duruma gecilmesi durumunda 1 normal durumlarda 0 degerini alir
int16_t position_error;

uint32_t motorTimeout = 0;
uint8_t motorTimeoutFlag = 0;

extern uint16_t first_encoder_value;

int32_t integralErr = 0;
int32_t derivativeErr = 0;

float Kp = 1;
float Ki = 0;
float Kd = 0;
int16_t pwmValue = 0;
int16_t errorDebug = 0;

uint8_t fastMovingFLag = 0;

uint16_t oldJoystick = 0;
uint32_t steadyStateCounter = 0;


void motoru_istenilen_pozisyona_gotur(uint16_t position){
	if(position > ENCODER_MAX_LIMIT){
		position=ENCODER_MAX_LIMIT;
	}else if(position < ENCODER_MIN_LIMIT){
		position=ENCODER_MIN_LIMIT;
	}
	//position_error=position-encoderCalibration(encoder_value);

	position_error=position-encoder_value;
	
	if(position_error!=0){
			motor_position_flag=0;
	}
		if(position_error < 0){
			set_motor_direction_of_rotation(CLOCKWISE);
			motor_value=170;
		}else if(position_error > 0){
			set_motor_direction_of_rotation(COUNTERCLOCKWISE);
			motor_value=170;
		}

	if(position_error == 0){
		set_motor_direction_of_rotation(NONE);
		motor_position_flag=1;
		motor_value = 0;
	}
	
	__HAL_TIM_SET_COMPARE(&Tim4Handle, TIM_CHANNEL_1, motor_value);
}

void set_motor_direction_of_rotation(uint8_t direction_value){
	switch (direction_value){
	case CLOCKWISE:
		HAL_GPIO_WritePin(IN1.PORT, IN1.PIN, GPIO_PIN_SET);
		HAL_GPIO_WritePin(IN2.PORT, IN2.PIN, GPIO_PIN_RESET);
		break;
	case COUNTERCLOCKWISE:
		HAL_GPIO_WritePin(IN1.PORT, IN1.PIN, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(IN2.PORT, IN2.PIN, GPIO_PIN_SET);
		break;
	case NONE:
		HAL_GPIO_WritePin(IN1.PORT, IN1.PIN, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(IN2.PORT, IN2.PIN, GPIO_PIN_RESET);
		break;
	}
}

int16_t error =0;
uint16_t encoder_old=0;

int16_t joystickDebug;



void acil_duruma_gec(void){

	#if MOTOR_CODE == ACCEL_MOTOR_CODE
		if(emergency_start_flag){
			motoru_istenilen_pozisyona_gotur(RANGE_JOYSTICK_MIN);
		}
	#elif MOTOR_CODE == BRAKE_MOTOR_CODE
		if(emergency_start_flag){
			motoru_istenilen_pozisyona_gotur(RANGE_JOYSTICK_MAX);
		}
	#elif MOTOR_CODE == GEAR_MOTOR_CODE
			setMotorDirection(STOP);
	#endif
}

#define DEADBAND 50
#define OVERSHOOT 100
int16_t encoder_bosta_degeri = 200;
int16_t encoder_tam_cekili_degeri = 600;
uint8_t DB_ALT_LIMIT_BOSTA_TASMA, DB_UST_LIMIT_BOSTA_TASMA, OVERSHOOT_ALT_LIMIT_BOSTA_TASMA, OVERSHOOT_UST_LIMIT_BOSTA_TASMA;
uint8_t DEADBAND_ALT_LIMIT_TAM_CEKILI_TASMA, DEADBAND_UST_LIMIT_TAM_CEKILI_TASMA, OVERSHOOT_ALT_LIMIT_TAM_CEKILI_TASMA, OVERSHOOT_UST_LIMIT_TAM_CEKILI_TASMA;

int16_t DEADBAND_ALT_LIMIT_BOSTA=0, DEADBAND_UST_LIMIT_BOSTA=0 , DEADBAND_ALT_LIMIT_TAM_CEKILI=0, DEADBAND_UST_LIMIT_TAM_CEKILI=0;
int16_t OVERSHOOT_ALT_LIMIT_TAM_CEKILI, OVERSHOOT_UST_LIMIT_TAM_CEKILI, OVERSHOOT_ALT_LIMIT_BOSTA, OVERSHOOT_UST_LIMIT_BOSTA;
void encoder_start(void){

	if((encoder_bosta_degeri-DEADBAND) < 0){
		DEADBAND_ALT_LIMIT_BOSTA = 1000-abs(encoder_bosta_degeri-DEADBAND);
	DB_ALT_LIMIT_BOSTA_TASMA = 1;}
	else{
		DEADBAND_ALT_LIMIT_BOSTA = encoder_bosta_degeri - DEADBAND;
		DB_ALT_LIMIT_BOSTA_TASMA= 0;}
	if((encoder_bosta_degeri+DEADBAND) > 1000){
		DEADBAND_UST_LIMIT_BOSTA = DEADBAND - (1000-encoder_bosta_degeri);
	DB_UST_LIMIT_BOSTA_TASMA = 1;}
	else{
		DEADBAND_UST_LIMIT_BOSTA = encoder_bosta_degeri + DEADBAND;
	DB_UST_LIMIT_BOSTA_TASMA = 0;
	}
	
	if(encoder_bosta_degeri - OVERSHOOT < 0){
		OVERSHOOT_ALT_LIMIT_BOSTA = 1000-abs(encoder_bosta_degeri-OVERSHOOT);
	OVERSHOOT_ALT_LIMIT_BOSTA_TASMA = 1;}
	else{
		OVERSHOOT_ALT_LIMIT_BOSTA = encoder_bosta_degeri - OVERSHOOT;	
	OVERSHOOT_ALT_LIMIT_BOSTA_TASMA = 0;}
	if((encoder_bosta_degeri+OVERSHOOT) > 1000){
		OVERSHOOT_UST_LIMIT_BOSTA = OVERSHOOT - (1000-encoder_bosta_degeri);
	OVERSHOOT_UST_LIMIT_BOSTA_TASMA = 1;}
	else{
		OVERSHOOT_UST_LIMIT_BOSTA = encoder_bosta_degeri + OVERSHOOT;
	OVERSHOOT_UST_LIMIT_BOSTA_TASMA = 0;
	}
	
	if(encoder_tam_cekili_degeri - DEADBAND < 0){
		DEADBAND_ALT_LIMIT_TAM_CEKILI = 1000 - abs(encoder_tam_cekili_degeri - DEADBAND);
	 DEADBAND_ALT_LIMIT_TAM_CEKILI_TASMA=1;}
	else{
		DEADBAND_ALT_LIMIT_TAM_CEKILI = encoder_tam_cekili_degeri - DEADBAND;
	DEADBAND_ALT_LIMIT_TAM_CEKILI_TASMA=0;}
	if(encoder_tam_cekili_degeri + DEADBAND > 1000) {
		DEADBAND_UST_LIMIT_TAM_CEKILI = DEADBAND - abs(1000-encoder_tam_cekili_degeri);
	DEADBAND_UST_LIMIT_TAM_CEKILI_TASMA=1;}
	else{
		DEADBAND_UST_LIMIT_TAM_CEKILI = encoder_tam_cekili_degeri-DEADBAND;
	DEADBAND_UST_LIMIT_TAM_CEKILI_TASMA=0;
	}
	if(encoder_tam_cekili_degeri - OVERSHOOT < 0){
		OVERSHOOT_ALT_LIMIT_TAM_CEKILI = 1000-abs(encoder_tam_cekili_degeri-OVERSHOOT);
	OVERSHOOT_ALT_LIMIT_TAM_CEKILI_TASMA=1;}
	else{
		OVERSHOOT_ALT_LIMIT_TAM_CEKILI = encoder_tam_cekili_degeri - OVERSHOOT;	
	OVERSHOOT_ALT_LIMIT_TAM_CEKILI_TASMA=0;}
	if((encoder_tam_cekili_degeri+OVERSHOOT) > 1000){
		OVERSHOOT_UST_LIMIT_TAM_CEKILI = OVERSHOOT - (1000-encoder_tam_cekili_degeri);
	OVERSHOOT_UST_LIMIT_TAM_CEKILI_TASMA=1;}
	else{
		OVERSHOOT_UST_LIMIT_TAM_CEKILI = encoder_tam_cekili_degeri + OVERSHOOT;
	OVERSHOOT_UST_LIMIT_TAM_CEKILI_TASMA=0;
	}
	
/*	if(DB_ALT_LIMIT_BOSTA_TASMA == 0 && DB_UST_LIMIT_BOSTA_TASMA==0 && OVERSHOOT_UST_LIMIT_BOSTA_TASMA==0 && OVERSHOOT_UST_LIMIT_BOSTA_TASMA==0){
	BOSTA_TASMA_YOK;
	}
	if(DB_ALT_LIMIT_BOSTA_TASMA == 0 && DB_UST_LIMIT_BOSTA_TASMA==0 && OVERSHOOT_UST_LIMIT_BOSTA_TASMA==0 && OVERSHOOT_UST_LIMIT_BOSTA_TASMA==0){
	BOSTA_TASMA_YOK;
	}*/
	
}

void motor_sur_deneme(int16_t pwmdegeri){

		if (pwmdegeri > 230){ 
			pwmdegeri = 230;
			__HAL_TIM_SET_COMPARE(&Tim4Handle, TIM_CHANNEL_1, pwmdegeri);
		}
		else if (pwmdegeri < -230){ 
			pwmdegeri = -230;
			__HAL_TIM_SET_COMPARE(&Tim4Handle, TIM_CHANNEL_1, -pwmdegeri);
		}
}

	void motor_stabilize_deneme(void){

		error = joystick_y_value - (encoder_value-encoder_bosta_degeri);
	
		if (joystick_y_value > 0 && joystick_y_value < 480)
		{
			if(joystick_y_value <50){
				
				if(encoder_value < DEADBAND_ALT_LIMIT_TAM_CEKILI){ //600gibi dusun
					set_motor_direction_of_rotation(CLOCKWISE);
						integralErr = integralErr + (error * 0.05);
						derivativeErr = (error - error_old) * 0.05;
						pwmValue = (Kp * 4 * error) + (Ki * integralErr) + (Kd * derivativeErr);
						motor_sur_deneme(pwmValue);
					
				}else if (encoder_value > DEADBAND_UST_LIMIT_TAM_CEKILI && encoder_value < OVERSHOOT_UST_LIMIT_TAM_CEKILI){
					
					set_motor_direction_of_rotation(COUNTERCLOCKWISE);
						integralErr = integralErr + (error * 0.05);
						derivativeErr = (error - error_old) * 0.05;
						pwmValue = (Kp / 4 * error) + (Ki * integralErr) + (Kd * derivativeErr);
						motor_sur_deneme(pwmValue);
				
				}else if(encoder_value >= DEADBAND_ALT_LIMIT_TAM_CEKILI && encoder_value <= DEADBAND_UST_LIMIT_TAM_CEKILI){
					set_motor_direction_of_rotation(NONE);
				}
			}
			else if(joystick_y_value > 450){
				
				if(encoder_value > DEADBAND_UST_LIMIT_BOSTA){ //200gibi dusun
					set_motor_direction_of_rotation(COUNTERCLOCKWISE);
						integralErr = integralErr + (error * 0.05);
						derivativeErr = (error - error_old) * 0.05;
						pwmValue = (Kp * 4 * error) + (Ki * integralErr) + (Kd * derivativeErr);
						motor_sur_deneme(pwmValue);
					
				}else if (encoder_value > DEADBAND_ALT_LIMIT_BOSTA && encoder_value < OVERSHOOT_ALT_LIMIT_BOSTA){
					
					set_motor_direction_of_rotation(CLOCKWISE);
						integralErr = integralErr + (error * 0.05);
						derivativeErr = (error - error_old) * 0.05;
						pwmValue = (Kp / 4 * error) + (Ki * integralErr) + (Kd * derivativeErr);
						motor_sur_deneme(pwmValue);
				
				}else if(encoder_value >= DEADBAND_ALT_LIMIT_TAM_CEKILI && encoder_value <= DEADBAND_UST_LIMIT_TAM_CEKILI){
					set_motor_direction_of_rotation(NONE);
				}
			}
			else{
				if (error < -10){
					set_motor_direction_of_rotation(CLOCKWISE);
						integralErr = integralErr + (error * 0.05);
						derivativeErr = (error - error_old) * 0.05;
						pwmValue = (Kp / 4 * error) + (Ki * integralErr) + (Kd * derivativeErr);
						motor_sur_deneme(pwmValue);
				}
				else if(error > 10){
				set_motor_direction_of_rotation(COUNTERCLOCKWISE);
						integralErr = integralErr + (error * 0.05);
						derivativeErr = (error - error_old) * 0.05;
						pwmValue = (Kp / 4 * error) + (Ki * integralErr) + (Kd * derivativeErr);
						motor_sur_deneme(pwmValue);
				
				}	
			}
			error_old = error;	
			oldJoystick = joystick_y_value;	
		}
		else{
			joystick_y_value = 500; 
			error = joystick_y_value - (encoder_value - first_encoder_value);
		
		if (error < -10)
		{
			set_motor_direction_of_rotation(CLOCKWISE);
			integralErr = integralErr + (error * 0.05);
			derivativeErr = (error - error_old) * 0.05;
			
			pwmValue = (Kp * error) + (Ki * integralErr) + (Kd * derivativeErr);
			motor_sur_deneme(pwmValue);
			enableClutch();
		}
		else if (error > 10)
		{
			set_motor_direction_of_rotation(COUNTERCLOCKWISE);
			integralErr = integralErr + (error * 0.05);
			derivativeErr = (error - error_old) * 0.05;
			
			pwmValue = (Kp * error) + (Ki * integralErr) + (Kd * derivativeErr);
			motor_sur_deneme(pwmValue);
			enableClutch();
		}
		else
		{
			__HAL_TIM_SET_COMPARE(&Tim4Handle, TIM_CHANNEL_1, 0);
			enableClutch();
		}
		
		error_old = error;	
		oldJoystick = joystick_y_value;
	}
}
			
			
			
			//////////////**** SAAT YONUNDE CALISAN ARAC ICIN ****/////////////
			
/* 
*  herhangi bir tasmaya ugramaz ve CLOCKWISE calisir
*  bosta degeri 200 cekili degeri 600
*  200--->600
*/	

	/*if(encoder_value >= DEADBAND_ALT_LIMIT_TAM_CEKILI && encoder_value <= DEADBAND_UST_LIMIT_TAM_CEKILI){
			set_motor_direction_of_rotation(NONE);
	}
	else if( encoder_value > DEADBAND_UST_LIMIT_TAM_CEKILI && encoder_value < OVERSHOOT_UST_LIMIT_TAM_CEKILI){
			set_motor_direction_of_rotation(COUNTERCLOCKWISE);
			pwmValue = (Kp / 4 * error) + (Ki * integralErr) + (Kd * derivativeErr);
				if (pwmValue > 230) pwmValue = 230;
				else if (pwmValue < -230) pwmValue = -230;
		__HAL_TIM_SET_COMPARE(&Tim4Handle, TIM_CHANNEL_1, pwmValue);
		}
	else{
			set_motor_direction_of_rotation(CLOCKWISE);
			pwmValue = (Kp * 4 * error) + (Ki * integralErr) + (Kd * derivativeErr);
				if (pwmValue > 230) pwmValue = 230;
				else if (pwmValue < -230) pwmValue = -230;
		__HAL_TIM_SET_COMPARE(&Tim4Handle, TIM_CHANNEL_1, pwmValue);
	}*/
	
/* 200den 600e gidildikten sonra geri 600den 200e donerken
* herhangi bir tasmaya ugramaz COUNTERCLOCKWISE calisir
* 600--->200
*
*/				

	/*if(encoder_value >= DEADBAND_ALT_LIMIT_BOSTA && encoder_value <= DEADBAND_UST_LIMIT_BOSTA){
			set_motor_direction_of_rotation(NONE);
	}
	else if( encoder_value < DEADBAND_ALT_LIMIT_BOSTA && encoder_value > OVERSHOOT_ALT_LIMIT_BOSTA)	{
			set_motor_direction_of_rotation(CLOCKWISE);
			pwmValue = (Kp / 4 * error) + (Ki * integralErr) + (Kd * derivativeErr);
				if (pwmValue > 230) pwmValue = 230;
				else if (pwmValue < -230) pwmValue = -230;
		__HAL_TIM_SET_COMPARE(&Tim4Handle, TIM_CHANNEL_1, pwmValue);
	}
	else{
			set_motor_direction_of_rotation(COUNTERCLOCKWISE);
			pwmValue = (Kp / 4 * error) + (Ki * integralErr) + (Kd * derivativeErr);
				if (pwmValue > 230) pwmValue = 230;
				else if (pwmValue < -230) pwmValue = -230;
		__HAL_TIM_SET_COMPARE(&Tim4Handle, TIM_CHANNEL_1, pwmValue);
	}			*/	
	
/* 600den 940a giderken
* OVERSHOOT tasmasi var CLOCKWISE calisir
* 600--->940 
*
*/				

	/*if(encoder_value >= DEADBAND_ALT_LIMIT_TAM_CEKILI && encoder_value <= DEADBAND_UST_LIMIT_TAM_CEKILI){
			set_motor_direction_of_rotation(NONE);
	}
	else if( encoder_value > DEADBAND_UST_LIMIT_TAM_CEKILI || encoder_value < OVERSHOOT_UST_LIMIT_TAM_CEKILI)	{
			set_motor_direction_of_rotation(COUNTERCLOCKWISE);
			pwmValue = (Kp / 4 * error) + (Ki * integralErr) + (Kd * derivativeErr);
				if (pwmValue > 230) pwmValue = 230;
				else if (pwmValue < -230) pwmValue = -230;
		__HAL_TIM_SET_COMPARE(&Tim4Handle, TIM_CHANNEL_1, pwmValue);
	}
	else{
			set_motor_direction_of_rotation(CLOCKWISE);
			pwmValue = (Kp * 4 * error) + (Ki * integralErr) + (Kd * derivativeErr);
				if (pwmValue > 230) pwmValue = 230;
				else if (pwmValue < -230) pwmValue = -230;
		__HAL_TIM_SET_COMPARE(&Tim4Handle, TIM_CHANNEL_1, pwmValue);
	}	
	*/
/*
* DEADBAND ve OVERSHOOT yuzunden tasma var CLOCKWISE calisir
* 600--->960 
*
*/				
/*
	if(encoder_value >= DEADBAND_ALT_LIMIT_TAM_CEKILI || encoder_value > encoder_tam_cekili_degeri || encoder_value <= DEADBAND_UST_LIMIT_TAM_CEKILI){
			set_motor_direction_of_rotation(NONE);
	}
	else if( encoder_value > DEADBAND_UST_LIMIT_TAM_CEKILI && encoder_value < OVERSHOOT_UST_LIMIT_TAM_CEKILI)	{
			set_motor_direction_of_rotation(COUNTERCLOCKWISE);
			pwmValue = (Kp / 4 * error) + (Ki * integralErr) + (Kd * derivativeErr);
		if (pwmValue > 230) pwmValue = 230;
				else if (pwmValue < -230) pwmValue = -230;
		__HAL_TIM_SET_COMPARE(&Tim4Handle, TIM_CHANNEL_1, pwmValue);
	}
	else{
			set_motor_direction_of_rotation(CLOCKWISE);
			pwmValue = (Kp * 4 * error) + (Ki * integralErr) + (Kd * derivativeErr);
		if (pwmValue > 230) pwmValue = 230;
				else if (pwmValue < -230) pwmValue = -230;
		__HAL_TIM_SET_COMPARE(&Tim4Handle, TIM_CHANNEL_1, pwmValue);
	}		*/
	
	
/*
* herhangi bir tasma yok CLOCKWISE calisir
* 800--->200
*
*/				

	/*if(encoder_value >= DEADBAND_ALT_LIMIT_TAM_CEKILI && encoder_value <= DEADBAND_UST_LIMIT_TAM_CEKILI){
			set_motor_direction_of_rotation(NONE);
	}
	else if( encoder_value > DEADBAND_UST_LIMIT_TAM_CEKILI && encoder_value < OVERSHOOT_UST_LIMIT_TAM_CEKILI)	{
			set_motor_direction_of_rotation(COUNTERCLOCKWISE);
			pwmValue = (Kp / 4 * error) + (Ki * integralErr) + (Kd * derivativeErr);
		if (pwmValue > 230) pwmValue = 230;
				else if (pwmValue < -230) pwmValue = -230;
		__HAL_TIM_SET_COMPARE(&Tim4Handle, TIM_CHANNEL_1, pwmValue);
	}
	else{
			set_motor_direction_of_rotation(CLOCKWISE);
			pwmValue = (Kp * 4 * error) + (Ki * integralErr) + (Kd * derivativeErr);
		if (pwmValue > 230) pwmValue = 230;
				else if (pwmValue < -230) pwmValue = -230;
		__HAL_TIM_SET_COMPARE(&Tim4Handle, TIM_CHANNEL_1, pwmValue);
	}*/

/*
* DEADBAND yuzunden tasmaya ugramasi durumunda CLOCKWISE calisir
* 800--->40
*
*/	

	/*if(encoder_value >= DEADBAND_ALT_LIMIT_TAM_CEKILI || encoder_value <= encoder_tam_cekili_degeri || encoder_value <= DEADBAND_UST_LIMIT_TAM_CEKILI){
			set_motor_direction_of_rotation(NONE);
	}
	else if( encoder_value > DEADBAND_UST_LIMIT_TAM_CEKILI && encoder_value < OVERSHOOT_UST_LIMIT_TAM_CEKILI){
			set_motor_direction_of_rotation(COUNTERCLOCKWISE);
			pwmValue = (Kp / 4 * error) + (Ki * integralErr) + (Kd * derivativeErr);
		if (pwmValue > 230) pwmValue = 230;
				else if (pwmValue < -230) pwmValue = -230;
		__HAL_TIM_SET_COMPARE(&Tim4Handle, TIM_CHANNEL_1, pwmValue);
		}
	else{
			set_motor_direction_of_rotation(CLOCKWISE);
			pwmValue = (Kp * 4 * error) + (Ki * integralErr) + (Kd * derivativeErr);
		if (pwmValue > 230) pwmValue = 230;
				else if (pwmValue < -230) pwmValue = -230;
		__HAL_TIM_SET_COMPARE(&Tim4Handle, TIM_CHANNEL_1, pwmValue);
	}
	*/
	/***** SAAT YONUNDE GIDIP SAAT YONUNUN TERSINE GERI DONME  ******///		
	
/* 400den 60a geri donerken 
* bos degeri < cekili degeri ve cekili deger DEADBAND tasmasi yok ancak OVERSHOOT yuzunden tasmaya ugramasi durumunda COUNTERCLOCKWISE calisir
* 400--->60 
*
*/				
/*
	if(encoder_value >= DEADBAND_ALT_LIMIT_BOSTA && encoder_value <= DEADBAND_UST_LIMIT_BOSTA){
			set_motor_direction_of_rotation(NONE);
	}
	else if( encoder_value < DEADBAND_ALT_LIMIT_BOSTA || encoder_value > OVERSHOOT_ALT_LIMIT_BOSTA)	{
			set_motor_direction_of_rotation(CLOCKWISE);
			pwmValue = (Kp / 4 * error) + (Ki * integralErr) + (Kd * derivativeErr);
		if (pwmValue > 230) pwmValue = 230;
				else if (pwmValue < -230) pwmValue = -230;
		__HAL_TIM_SET_COMPARE(&Tim4Handle, TIM_CHANNEL_1, pwmValue);
	}
	else{
			set_motor_direction_of_rotation(COUNTERCLOCKWISE);
			pwmValue = (Kp * 4 * error) + (Ki * integralErr) + (Kd * derivativeErr);
		if (pwmValue > 230) pwmValue = 230;
				else if (pwmValue < -230) pwmValue = -230;
		__HAL_TIM_SET_COMPARE(&Tim4Handle, TIM_CHANNEL_1, pwmValue);
	}
	*/
/*400den 40a geri donerken 
* bos degeri < cekili degeri ve cekili deger DEADBAND ve OVERSHOOT yuzunden tasmaya ugramasi durumunda COUNTERCLOCKWISE calisir
* 400--->40 
*
*/				
/*
	if(encoder_value >= DEADBAND_ALT_LIMIT_BOSTA || encoder_value <= encoder_bosta_degeri || encoder_value <= DEADBAND_UST_LIMIT_BOSTA){
			set_motor_direction_of_rotation(NONE);
	}
	else if( encoder_value < DEADBAND_ALT_LIMIT_BOSTA && encoder_value > OVERSHOOT_ALT_LIMIT_BOSTA)	{
			set_motor_direction_of_rotation(CLOCKWISE);
			pwmValue = (Kp / 4 * error) + (Ki * integralErr) + (Kd * derivativeErr);
		if (pwmValue > 230) pwmValue = 230;
				else if (pwmValue < -230) pwmValue = -230;
		__HAL_TIM_SET_COMPARE(&Tim4Handle, TIM_CHANNEL_1, pwmValue);
	}
	else{
			set_motor_direction_of_rotation(COUNTERCLOCKWISE);
			pwmValue = (Kp * 4 * error) + (Ki * integralErr) + (Kd * derivativeErr);
		if (pwmValue > 230) pwmValue = 230;
				else if (pwmValue < -230) pwmValue = -230;
		__HAL_TIM_SET_COMPARE(&Tim4Handle, TIM_CHANNEL_1, pwmValue);
	}	*/
	
/*
* bos degeri > cekili degeri ve cekili deger DEADBAND ve OVERSHOOT yuzunden tasmaya ugramasi durumunda COUNTERCLOCKWISE calisir
* 700--->960
*
*/			/*	

	if(encoder_value >= DEADBAND_ALT_LIMIT_BOSTA || encoder_value >= encoder_bosta_degeri || encoder_value <= DEADBAND_UST_LIMIT_BOSTA){
			set_motor_direction_of_rotation(NONE);
	}
	else if( encoder_value > DEADBAND_UST_LIMIT_BOSTA || encoder_value < OVERSHOOT_UST_LIMIT_BOSTA)	{
			set_motor_direction_of_rotation(COUNTERCLOCKWISE);
			pwmValue = (Kp / 4 * error) + (Ki * integralErr) + (Kd * derivativeErr);
		if (pwmValue > 230) pwmValue = 230;
				else if (pwmValue < -230) pwmValue = -230;
		__HAL_TIM_SET_COMPARE(&Tim4Handle, TIM_CHANNEL_1, pwmValue);
	}
	else{
			set_motor_direction_of_rotation(CLOCKWISE);
			pwmValue = (Kp * 4 * error) + (Ki * integralErr) + (Kd * derivativeErr);
		if (pwmValue > 230) pwmValue = 230;
				else if (pwmValue < -230) pwmValue = -230;
		__HAL_TIM_SET_COMPARE(&Tim4Handle, TIM_CHANNEL_1, pwmValue);
	}	
		*/
	
	
	///**** CLOCKWISE DONME **///
	
	
/*
* hicbir tasma yok COUNTERCLOCKWISE calisir
* 40--->800
*
*/			/*	

	if(encoder_value >= DEADBAND_ALT_LIMIT_TAM_CEKILI && encoder_value <= DEADBAND_UST_LIMIT_TAM_CEKILI){
			set_motor_direction_of_rotation(NONE);
	}
	else if( encoder_value < DEADBAND_ALT_LIMIT_TAM_CEKILI || encoder_value > OVERSHOOT_ALT_LIMIT_TAM_CEKILI)	{
			set_motor_direction_of_rotation(CLOCKWISE);
			pwmValue = (Kp / 4 * error) + (Ki * integralErr) + (Kd * derivativeErr);
		if (pwmValue > 230) pwmValue = 230;
				else if (pwmValue < -230) pwmValue = -230;
		__HAL_TIM_SET_COMPARE(&Tim4Handle, TIM_CHANNEL_1, pwmValue);
	}
	else{
			set_motor_direction_of_rotation(COUNTERCLOCKWISE);
			pwmValue = (Kp * 4 * error) + (Ki * integralErr) + (Kd * derivativeErr);
		if (pwmValue > 230) pwmValue = 230;
				else if (pwmValue < -230) pwmValue = -230;
		__HAL_TIM_SET_COMPARE(&Tim4Handle, TIM_CHANNEL_1, pwmValue);
	}	
	*/
		
/* 
* DEADBAND ve OVERSHOOT TASMA VAR COUNTERCLOCKWISE GIDIS
* 40--->960
*
*/		/*	

	if(encoder_value >= DEADBAND_ALT_LIMIT_TAM_CEKILI || encoder_value <= DEADBAND_UST_LIMIT_TAM_CEKILI){
			set_motor_direction_of_rotation(NONE);
	}
	else if( encoder_value < DEADBAND_ALT_LIMIT_TAM_CEKILI && encoder_value > OVERSHOOT_ALT_LIMIT_TAM_CEKILI)	{
			set_motor_direction_of_rotation(CLOCKWISE);
			pwmValue = (Kp / 4 * error) + (Ki * integralErr) + (Kd * derivativeErr);
		if (pwmValue > 230) pwmValue = 230;
				else if (pwmValue < -230) pwmValue = -230;
		__HAL_TIM_SET_COMPARE(&Tim4Handle, TIM_CHANNEL_1, pwmValue);
	}
	else{
			set_motor_direction_of_rotation(COUNTERCLOCKWISE);
			pwmValue = (Kp * 4 * error) + (Ki * integralErr) + (Kd * derivativeErr);
		if (pwmValue > 230) pwmValue = 230;
				else if (pwmValue < -230) pwmValue = -230;
		__HAL_TIM_SET_COMPARE(&Tim4Handle, TIM_CHANNEL_1, pwmValue);
	}			
	
*/
/*
* 900--->500 COUNTERCLOCKWISE GIDIS
* hicbir TASMA YOK 
*
*/				/*

	if(encoder_value >= DEADBAND_ALT_LIMIT_TAM_CEKILI && encoder_value <= DEADBAND_UST_LIMIT_TAM_CEKILI){
			set_motor_direction_of_rotation(NONE);
	}
	else if( encoder_value < DEADBAND_ALT_LIMIT_TAM_CEKILI && encoder_value > OVERSHOOT_ALT_LIMIT_TAM_CEKILI)	{
			set_motor_direction_of_rotation(CLOCKWISE);
			pwmValue = (Kp / 4 * error) + (Ki * integralErr) + (Kd * derivativeErr);
		if (pwmValue > 230) pwmValue = 230;
				else if (pwmValue < -230) pwmValue = -230;
		__HAL_TIM_SET_COMPARE(&Tim4Handle, TIM_CHANNEL_1, pwmValue);
	}
	else{
			set_motor_direction_of_rotation(COUNTERCLOCKWISE);
			pwmValue = (Kp * 4 * error) + (Ki * integralErr) + (Kd * derivativeErr);
		if (pwmValue > 230) pwmValue = 230;
				else if (pwmValue < -230) pwmValue = -230;
		__HAL_TIM_SET_COMPARE(&Tim4Handle, TIM_CHANNEL_1, pwmValue);
	}			
		
				if (error < -10)
			{
			//	set_motor_direction_of_rotation(CLOCKWISE);/////////////////////////
				__HAL_TIM_SET_COMPARE(&Tim4Handle, TIM_CHANNEL_1, -pwmValue);
			
			}
			else if (error > 10)
			{
				//set_motor_direction_of_rotation(COUNTERCLOCKWISE);
				__HAL_TIM_SET_COMPARE(&Tim4Handle, TIM_CHANNEL_1, pwmValue);
			}
			else
			{
				__HAL_TIM_SET_COMPARE(&Tim4Handle, TIM_CHANNEL_1, 0);
				enableClutch();
			}	

	error_old = error;	
		oldJoystick = joystick_y_value;
		}
		
	}*/



