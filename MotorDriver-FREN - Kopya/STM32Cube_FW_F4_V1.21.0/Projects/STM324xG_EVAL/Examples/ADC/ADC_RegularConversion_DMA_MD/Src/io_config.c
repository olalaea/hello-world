#include "config.h"
#include "io_config.h"
#include "io_pin.h"

/* ADC handler declaration */
TIM_HandleTypeDef 	Tim4Handle;
CAN_HandleTypeDef	CanHandle;
ADC_HandleTypeDef	AdcHandle;
ADC_HandleTypeDef	Adc2Handle;
UART_HandleTypeDef	Uart2Handle;
UART_HandleTypeDef	Uart3Handle;
uint8_t USART2_Rx_Buffer[USART2_RX_BUFFER_SIZE];
uint8_t USART3_Rx_Buffer[USART3_RX_BUFFER_SIZE];
uint32_t USART2_Rx_Index = 0;

uint16_t ADC1ConvertedValue[ANALOG_PIN_AMOUNT];

uint16_t ADC2ConvertedValue;

char readUSART3[READ_MESSAGE_SIZE], sendUSART3[SEND_MESSAGE_SIZE];
extern char sendUSART2[DEBUG_SEND_MESSAGE_SIZE], readUSART2[DEBUG_READ_MESSAGE_SIZE];

extern ANALOG_IO_PIN ANALOG1;		extern PWM_IO_PIN MOTOR_PWM;
extern DIGITAL_IO_PIN IN1;			extern DIGITAL_IO_PIN IN2;			extern DIGITAL_IO_PIN BLINK;		extern DIGITAL_IO_PIN CLUTCH;
extern USART_IO_PIN USART2_Tx; 		extern USART_IO_PIN USART2_Rx;		extern USART_IO_PIN USART3_Tx; 		extern USART_IO_PIN USART3_Rx;

void ADC_DMA_CONFIG(void)
{
	CREATE_ANALOG_PIN();

	AdcHandle.Instance = ADCx;

	AdcHandle.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV2;
	AdcHandle.Init.Resolution = ADC_RESOLUTION_12B;
	AdcHandle.Init.ScanConvMode = ENABLE;
	AdcHandle.Init.ContinuousConvMode = ENABLE;
	AdcHandle.Init.DiscontinuousConvMode = DISABLE;
	AdcHandle.Init.NbrOfDiscConversion = 0;
	AdcHandle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	AdcHandle.Init.ExternalTrigConv = ADC_EXTERNALTRIGCONV_T1_CC1;
	AdcHandle.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	AdcHandle.Init.NbrOfConversion = ANALOG_PIN_AMOUNT;
	AdcHandle.Init.DMAContinuousRequests = ENABLE;
	AdcHandle.Init.EOCSelection = DISABLE;

	HAL_ADC_Init(&AdcHandle);
	
	ADC_CHANNEL_CONFIG(&AdcHandle, ADCx_CHANNEL_1, 1, ADC_SAMPLETIME_144CYCLES, 0);
	ADC_CHANNEL_CONFIG(&AdcHandle, ADC_CHANNEL_1, 2, ADC_SAMPLETIME_144CYCLES, 0);

	HAL_ADC_Start_DMA(&AdcHandle, (uint32_t*)ADC1ConvertedValue, ANALOG_PIN_AMOUNT);
}

void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
{
	if (hadc == &AdcHandle)
	{
		GPIO_InitTypeDef          GPIO_InitStruct;
		static DMA_HandleTypeDef  hdma_adc;

		ADCx_CHANNEL_GPIO_CLK_ENABLE();
		ADCx_CLK_ENABLE();
		DMAx_CLK_ENABLE(); 

		GPIO_InitStruct.Pin = ANALOG1.PIN | GPIO_PIN_1;
		GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(ANALOG1.PORT, &GPIO_InitStruct);

		hdma_adc.Instance = ADCx_DMA_STREAM;

		hdma_adc.Init.Channel  = ADCx_DMA_CHANNEL;
		hdma_adc.Init.Direction = DMA_PERIPH_TO_MEMORY;
		hdma_adc.Init.PeriphInc = DMA_PINC_DISABLE;
		hdma_adc.Init.MemInc = DMA_MINC_ENABLE;
		hdma_adc.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
		hdma_adc.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
		hdma_adc.Init.Mode = DMA_CIRCULAR;
		hdma_adc.Init.Priority = DMA_PRIORITY_LOW;
		hdma_adc.Init.FIFOMode = DMA_FIFOMODE_DISABLE;         
		hdma_adc.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_HALFFULL;
		hdma_adc.Init.MemBurst = DMA_MBURST_SINGLE;
		hdma_adc.Init.PeriphBurst = DMA_PBURST_SINGLE;

		HAL_DMA_Init(&hdma_adc);

		__HAL_LINKDMA(hadc, DMA_Handle, hdma_adc);

		HAL_NVIC_SetPriority(ADCx_DMA_IRQn, 0, 0);   
		HAL_NVIC_EnableIRQ(ADCx_DMA_IRQn);
	}
	
	if (hadc == &Adc2Handle)
	{
		GPIO_InitTypeDef          GPIO_InitStruct;
		static DMA_HandleTypeDef  hdma_adc;

		__HAL_RCC_GPIOA_CLK_ENABLE();
		__HAL_RCC_ADC1_CLK_ENABLE();
		__HAL_RCC_DMA2_CLK_ENABLE(); 

		GPIO_InitStruct.Pin = GPIO_PIN_1;
		GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		hdma_adc.Instance = DMA2_Stream7;

		hdma_adc.Init.Channel  = DMA_CHANNEL_0;
		hdma_adc.Init.Direction = DMA_PERIPH_TO_MEMORY;
		hdma_adc.Init.PeriphInc = DMA_PINC_DISABLE;
		hdma_adc.Init.MemInc = DMA_MINC_ENABLE;
		hdma_adc.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
		hdma_adc.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
		hdma_adc.Init.Mode = DMA_CIRCULAR;
		hdma_adc.Init.Priority = DMA_PRIORITY_LOW;
		hdma_adc.Init.FIFOMode = DMA_FIFOMODE_DISABLE;         
		hdma_adc.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_HALFFULL;
		hdma_adc.Init.MemBurst = DMA_MBURST_SINGLE;
		hdma_adc.Init.PeriphBurst = DMA_PBURST_SINGLE;

		if (HAL_DMA_Init(&hdma_adc) != HAL_OK)
		{
			while(1);
		}

		__HAL_LINKDMA(hadc, DMA_Handle, hdma_adc);

		HAL_NVIC_SetPriority(DMA2_Stream7_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(DMA2_Stream7_IRQn);
	}
}

void ADC_CHANNEL_CONFIG (ADC_HandleTypeDef *hadc, uint32_t ADC_CHANNEL, uint32_t RANK, uint32_t ADC_SAMPLETIME_xCYCLES, uint32_t OFFSET)
{
	ADC_ChannelConfTypeDef sConfig;
	
	sConfig.Channel = ADC_CHANNEL;
	sConfig.Rank = RANK;
	sConfig.SamplingTime = ADC_SAMPLETIME_xCYCLES;
	sConfig.Offset = OFFSET;

	HAL_ADC_ConfigChannel(hadc, &sConfig);
}

void DIGITAL_OUT_CONFIG(void) {
	CREATE_DIGITAL_PIN();

	GPIO_InitTypeDef GPIO_InitStructure;
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();

	GPIO_InitStructure.Pin = CLUTCH.PIN;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Pull = GPIO_PULLDOWN;
 	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.Pin = IN1.PIN | IN2.PIN;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_InitStructure.Pin = BLINK.PIN;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStructure);
}

void USART2_GPIO_CONFIG (void)
{
	CREATE_USART_PIN();
	GPIO_InitTypeDef GPIO_InitStruct;	// this is for the GPIO pins used as TX and RX
	__HAL_RCC_GPIOD_CLK_ENABLE();
	
	GPIO_InitStruct.Pin = USART2_Tx.PIN | USART2_Rx.PIN;	// Pins 5 (TX) and 6 (RX) are used
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP; 				// the pins are configured as alternate function so the USART peripheral has access to them
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;			// this defines the IO speed and has nothing to do with the baudrate!
	GPIO_InitStruct.Pull = GPIO_PULLUP;						// this activates the pullup resistors on the IO pins
	GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);					// now all the values are passed to the GPIO_Init() function which sets the GPIO registers
}

void USART3_GPIO_CONFIG(void){
	CREATE_USART_PIN();
	GPIO_InitTypeDef GPIO_InitStruct;	// this is for the GPIO pins used as TX and RX
	__HAL_RCC_GPIOC_CLK_ENABLE();
	
	GPIO_InitStruct.Pin = USART3_Tx.PIN | USART3_Rx.PIN ; // Pins 5 (TX) and 6 (RX) are used
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP; 			// the pins are configured as alternate function so the USART peripheral has access to them
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;		// this defines the IO speed and has nothing to do with the baudrate!
	GPIO_InitStruct.Pull = GPIO_PULLUP;			// this activates the pullup resistors on the IO pins
	GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);					// now all the values are passed to the GPIO_Init() function which sets the GPIO register
}

void USART2_CONFIG(uint32_t baudrate)
{
	__HAL_RCC_USART2_CLK_ENABLE();
	USART2_GPIO_CONFIG();

	HAL_NVIC_SetPriority(USART2_IRQn, 0, 1);
	HAL_NVIC_EnableIRQ(USART2_IRQn);

	Uart2Handle.Instance = USART2;

	Uart2Handle.Init.BaudRate 	  = baudrate;
	Uart2Handle.Init.WordLength   = UART_WORDLENGTH_8B;
	Uart2Handle.Init.StopBits     = UART_STOPBITS_1;
	Uart2Handle.Init.Parity       = UART_PARITY_NONE;
	Uart2Handle.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
	Uart2Handle.Init.Mode         = UART_MODE_TX_RX;
	Uart2Handle.Init.OverSampling = UART_OVERSAMPLING_16;

	HAL_UART_Init(&Uart2Handle);

	__HAL_UART_ENABLE_IT(&Uart2Handle, UART_IT_RXNE);

	HAL_UART_Receive_IT(&Uart2Handle, (uint8_t *)USART2_Rx_Buffer, USART2_RX_BUFFER_SIZE);
}

void USART3_CONFIG(uint32_t baudrate)
{
	__HAL_RCC_USART3_CLK_ENABLE();
	USART3_GPIO_CONFIG();
	
	Uart3Handle.Instance = USART3;
	
	Uart3Handle.Init.BaudRate 	  = baudrate;
	Uart3Handle.Init.WordLength   = UART_WORDLENGTH_8B;
	Uart3Handle.Init.StopBits     = UART_STOPBITS_1;
	Uart3Handle.Init.Parity       = UART_PARITY_NONE;
	Uart3Handle.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
	Uart3Handle.Init.Mode         = UART_MODE_TX_RX;
	Uart3Handle.Init.OverSampling = UART_OVERSAMPLING_16;
	
	HAL_UART_Init(&Uart3Handle);
	
	__HAL_RCC_DMA1_CLK_ENABLE();
	static DMA_HandleTypeDef hdma_usart_rx;
	static DMA_HandleTypeDef hdma_usart_tx;
	
	hdma_usart_rx.Instance                 = DMA1_Stream1;
	hdma_usart_rx.Init.Channel             = DMA_CHANNEL_4;
	hdma_usart_rx.Init.Direction           = DMA_PERIPH_TO_MEMORY;
	hdma_usart_rx.Init.PeriphInc           = DMA_PINC_DISABLE;
	hdma_usart_rx.Init.MemInc              = DMA_MINC_ENABLE;
	hdma_usart_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	hdma_usart_rx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
	hdma_usart_rx.Init.Mode                = DMA_CIRCULAR;
	hdma_usart_rx.Init.Priority            = DMA_PRIORITY_VERY_HIGH;
	hdma_usart_rx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
	hdma_usart_rx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
	hdma_usart_rx.Init.MemBurst            = DMA_MBURST_SINGLE;
	hdma_usart_rx.Init.PeriphBurst         = DMA_MBURST_SINGLE;
	
	HAL_DMA_Init(&hdma_usart_rx);
	__HAL_LINKDMA(&Uart3Handle, hdmarx, hdma_usart_rx);
	
	hdma_usart_tx.Instance                 = DMA1_Stream3;
	hdma_usart_tx.Init.Channel             = DMA_CHANNEL_4;
	hdma_usart_tx.Init.Direction           = DMA_MEMORY_TO_PERIPH;
	hdma_usart_tx.Init.PeriphInc           = DMA_PINC_DISABLE;
	hdma_usart_tx.Init.MemInc              = DMA_MINC_ENABLE;
	hdma_usart_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	hdma_usart_tx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
	hdma_usart_tx.Init.Mode                = DMA_NORMAL;
	hdma_usart_tx.Init.Priority            = DMA_PRIORITY_VERY_HIGH;
	hdma_usart_tx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
	hdma_usart_tx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
	hdma_usart_tx.Init.MemBurst            = DMA_MBURST_SINGLE;
	hdma_usart_tx.Init.PeriphBurst         = DMA_MBURST_SINGLE;
	
	HAL_DMA_Init(&hdma_usart_tx);
	__HAL_LINKDMA(&Uart3Handle, hdmatx, hdma_usart_tx);
	
	HAL_NVIC_SetPriority(DMA1_Stream1_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA1_Stream1_IRQn);
	
	HAL_NVIC_SetPriority(DMA1_Stream3_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA1_Stream3_IRQn);
	
	HAL_NVIC_SetPriority(USART3_IRQn, 0, 1);
	HAL_NVIC_EnableIRQ(USART3_IRQn);
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle)
{
	if (UartHandle->Instance == USART2)
	{
	
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
	if (UartHandle->Instance == USART2)
	{
		HAL_UART_Receive_IT(&Uart2Handle, (uint8_t *)USART2_Rx_Buffer, USART2_RX_BUFFER_SIZE);
	}
	
	if (UartHandle->Instance == USART3)
	{
		//while(1);
	}
}

void CAN1_CONFIG(void)
{
	CAN_FilterTypeDef	sFilterConfig;
	GPIO_InitTypeDef	GPIO_InitStruct;

	CREATE_CAN_PIN();
	
	__HAL_RCC_CAN1_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();

	GPIO_InitStruct.Pin = GPIO_PIN_0;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Alternate =  GPIO_AF9_CAN1;

	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = GPIO_PIN_1;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Alternate =  GPIO_AF9_CAN1;

	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	HAL_NVIC_SetPriority(CAN1_RX0_IRQn, 1, 0);
	HAL_NVIC_EnableIRQ(CAN1_RX0_IRQn);

	CanHandle.Instance = CAN1;

	CanHandle.Init.TimeTriggeredMode = DISABLE;
	CanHandle.Init.AutoBusOff = ENABLE;
	CanHandle.Init.AutoWakeUp = ENABLE;
	CanHandle.Init.AutoRetransmission = ENABLE;
	CanHandle.Init.ReceiveFifoLocked = ENABLE;
	CanHandle.Init.TransmitFifoPriority = ENABLE;
	CanHandle.Init.Mode = CAN_MODE_NORMAL;
	CanHandle.Init.SyncJumpWidth = CAN_SJW_1TQ;
	CanHandle.Init.TimeSeg1 = CAN_BS1_11TQ;
	CanHandle.Init.TimeSeg2 = CAN_BS2_2TQ;
	CanHandle.Init.Prescaler = 3;

	if (HAL_CAN_Init(&CanHandle) != HAL_OK)
	{
		while(1);
	}

	sFilterConfig.FilterBank = 0;
	sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
	sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
	sFilterConfig.FilterIdHigh = 0x0000;
	sFilterConfig.FilterIdLow = 0x0000;
	sFilterConfig.FilterMaskIdHigh = 0x0000;
	sFilterConfig.FilterMaskIdLow = 0x0000;
	sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
	sFilterConfig.FilterActivation = ENABLE;
	sFilterConfig.SlaveStartFilterBank = 14;

	if (HAL_CAN_ConfigFilter(&CanHandle, &sFilterConfig) != HAL_OK)
	{
		while(1);
	}

	if (HAL_CAN_Start(&CanHandle) != HAL_OK)
	{
		while(1);
	}

	if (HAL_CAN_ActivateNotification(&CanHandle, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
	{
		while(1);
	}
}

void TIM4_CONFIG(void){ // TIM4 works in 84 MHz
	__HAL_RCC_TIM4_CLK_ENABLE();
	
	Tim4Handle.Instance = TIM4;
	Tim4Handle.Init.Prescaler = 84 - 1; // 1Mhz
	Tim4Handle.Init.CounterMode = TIM_COUNTERMODE_UP;
	Tim4Handle.Init.Period = TIM_PERIOD_DIVIDER- 1; //   4 kHz for PWM
	Tim4Handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	Tim4Handle.Init.RepetitionCounter = 0;
	
	HAL_TIM_Base_Init(&Tim4Handle);
}

void PWM_CONFIG(void) {
	/* Initialization Functions */
	TIM4_CONFIG();
	CREATE_PWM_PIN();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	
	GPIO_InitTypeDef	GPIO_InitStruct;
	GPIO_InitStruct.Pin = MOTOR_PWM.PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Alternate =  GPIO_AF2_TIM4;
	HAL_GPIO_Init(MOTOR_PWM.PORT, &GPIO_InitStruct);
	
	TIM_OC_InitTypeDef outputChannelInit;
	outputChannelInit.OCMode = TIM_OCMODE_PWM1;
	outputChannelInit.Pulse = 0;
	outputChannelInit.OCFastMode = TIM_OCFAST_DISABLE;
	outputChannelInit.OCPolarity = TIM_OCPOLARITY_HIGH;
	HAL_TIM_PWM_ConfigChannel(&Tim4Handle, &outputChannelInit, TIM_CHANNEL_1);
	HAL_TIM_OC_Init(&Tim4Handle);
	HAL_TIM_PWM_Start(&Tim4Handle, TIM_CHANNEL_1);
}
