#include "main.h"
#include "io_config.h"
#include "general_purpose_func.h"
#include "io_read_write.h"
#include "usart_2.h"
#include "usart_3.h"
#include "can.h"
#include "motor.h"
#include <string.h>

static void SystemClock_Config(void);

extern uint16_t joystick_y_value, timeout_counter;
extern uint16_t message_counter, measure_counter,hearbeat_counter,CAN_message_counter,stabilize_counter, init_counter;
extern short int motor_position_flag;
extern uint8_t mesaj[CAN_MESAJ_ALMA_SIZE];
extern short int emergency_start_flag;

extern uint16_t encoder_value;

int32_t first_encoder_value;

uint8_t firstRunFlag = 0;
uint8_t firstRunCounter = 0;
uint8_t firstRunCounterFlag = 1;
uint8_t isMotorStabilized = 0;

int main(void)
{
	HAL_Init();
	SystemClock_Config();
	ADC_DMA_CONFIG();
	DIGITAL_OUT_CONFIG();
	USART2_CONFIG(115200);
	USART3_CONFIG(115200);
	CAN1_CONFIG();
	PWM_CONFIG();
	
	/* Infinite loop */
	while(1)
	{
		if (CAN_message_counter > CAN_MSG_TIME)
		{
			CAN1_RX(mesaj,72);
			//isAllZero(mesaj,72);
			CAN_message_counter = 0;
		}
		
		if (message_counter > MSG_TIME)
		{
			if(mesaj_dogrulama())
			{
				updateUSART2Write();
				updateUSART3Write();
			}
			message_counter = 0;
		}
		
		if(measure_counter > MEASURE_TIME)
		{
			ReadAnalogPins();
			parse_CAN_message();			
			measure_counter=0;
		}
		
		if (firstRunFlag)
		{
			//first_encoder_value = encoder_value - 500;
			//first_encoder_value = 650 - 500;
			encoder_start();
			firstRunFlag = 0;
			isMotorStabilized = 1;
		}
		
		#if 0
		if(timeout_counter > TIMEOUT_TIME)
		{
			if(emergency_start_flag)
			{
				//acil_duruma_gec();
				//motor_position_flag=0;
			}
			timeout_counter = 0;
		}
		#endif
		
		if (isMotorStabilized)
		{
			if(stabilize_counter > STABILIZER_TIME && init_counter > 3000)
			{
				//stabilize_motor();
				motor_stabilize_deneme();
				stabilize_counter=0;
			}
		}
		
		if(hearbeat_counter > HEARTBEAT)
		{
			beatHeart();
			hearbeat_counter = 0;
		}
	}
}

static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);
 
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4);

  if (HAL_GetREVID() == 0x1001)
  {
    __HAL_FLASH_PREFETCH_BUFFER_ENABLE();
  }
}

/**
  * @brief  Conversion complete callback in non blocking mode 
  * @param  AdcHandle : AdcHandle handle
  * @note   This example shows a simple way to report end of conversion, and 
  *         you can add your own implementation.    
  * @retval None
  */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* AdcHandle)
{
}
