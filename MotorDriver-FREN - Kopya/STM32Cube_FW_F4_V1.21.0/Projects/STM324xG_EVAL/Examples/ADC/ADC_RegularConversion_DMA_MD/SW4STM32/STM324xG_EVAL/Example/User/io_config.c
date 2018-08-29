#include "config.h"
#include "io_config.h"
#include "io_pin.h"

uint16_t ADC1ConvertedValue[ANALOG_PIN_AMOUNT];

/* ADC handler declaration */
ADC_HandleTypeDef AdcHandle;
UART_HandleTypeDef Uart2Handle;
UART_HandleTypeDef Uart3Handle;
uint8_t USART2_Rx_Buffer[USART2_RX_BUFFER_SIZE];
uint8_t USART3_Rx_Buffer[USART3_RX_BUFFER_SIZE];
uint32_t USART2_Rx_Index = 0;

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
	
	ADC_CHANNEL_CONFIG(ADCx_CHANNEL_1, 1, ADC_SAMPLETIME_144CYCLES, 0);
	ADC_CHANNEL_CONFIG(ADCx_CHANNEL_2, 2, ADC_SAMPLETIME_144CYCLES, 0);
	ADC_CHANNEL_CONFIG(ADCx_CHANNEL_3, 3, ADC_SAMPLETIME_144CYCLES, 0);

	HAL_ADC_Start_DMA(&AdcHandle, (uint32_t*)ADC1ConvertedValue, ANALOG_PIN_AMOUNT);
}

void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
{
  GPIO_InitTypeDef          GPIO_InitStruct;
  static DMA_HandleTypeDef  hdma_adc;
  
  ADCx_CHANNEL_GPIO_CLK_ENABLE();
  ADCx_CLK_ENABLE();
  DMAx_CLK_ENABLE(); 
  
  GPIO_InitStruct.Pin = ANALOG1.PIN | ANALOG2.PIN | ANALOG3.PIN;
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

void HAL_ADC_MspDeInit(ADC_HandleTypeDef *hadc)
{
  static DMA_HandleTypeDef  hdma_adc;
  
  ADCx_FORCE_RESET();
  ADCx_RELEASE_RESET();

  HAL_GPIO_DeInit(ANALOG1.PORT, ANALOG1.PIN);
  HAL_GPIO_DeInit(ANALOG1.PORT, ANALOG2.PIN);
  HAL_GPIO_DeInit(ANALOG1.PORT, ANALOG3.PIN);
  
  HAL_DMA_DeInit(&hdma_adc); 

  HAL_NVIC_DisableIRQ(ADCx_DMA_IRQn);
}

void ADC_CHANNEL_CONFIG (uint32_t ADC_CHANNEL, uint32_t RANK, uint32_t ADC_SAMPLETIME_xCYCLES, uint32_t OFFSET)
{
	ADC_ChannelConfTypeDef sConfig;
	
	sConfig.Channel = ADC_CHANNEL;
	sConfig.Rank = RANK;
	sConfig.SamplingTime = ADC_SAMPLETIME_xCYCLES;
	sConfig.Offset = OFFSET;

	HAL_ADC_ConfigChannel(&AdcHandle, &sConfig);
}

void DIGITAL_IN_CONFIG(void) {
	CREATE_DIGITAL_IN_PIN();

	GPIO_InitTypeDef GPIO_InitStructure;
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();

	GPIO_InitStructure.Pin = DIGITAL_IN4.PIN  | DIGITAL_IN5.PIN| DIGITAL_IN6.PIN | DIGITAL_IN7.PIN |DIGITAL_IN8.PIN | DIGITAL_IN9.PIN |DIGITAL_IN10.PIN | DIGITAL_IN11.PIN  | DIGITAL_IN12.PIN; // GPIOE All Pins;
	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
	GPIO_InitStructure.Pull = GPIO_PULLDOWN;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_InitStructure.Pin = DIGITAL_IN1.PIN | DIGITAL_IN2.PIN |DIGITAL_IN3.PIN | DIGITAL_IN13.PIN | DIGITAL_IN14.PIN;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.Pin = DIGITAL_IN15.PIN| DIGITAL_IN16.PIN;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void DIGITAL_OUT_CONFIG(void) {
	CREATE_DIGITAL_OUT_PIN();

	GPIO_InitTypeDef GPIO_InitStructure;
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();

	GPIO_InitStructure.Pin = DIGITAL_OUT1.PIN | DIGITAL_OUT2.PIN | DIGITAL_OUT3.PIN;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Pull = GPIO_PULLDOWN;
 	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.Pin = DIGITAL_OUT4.PIN | DIGITAL_OUT5.PIN;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_InitStructure.Pin = BLINK.PIN;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStructure);
}

void USART2_GPIO_CONFIG (void)
{
	CREATE_USART2_PIN();
	GPIO_InitTypeDef GPIO_InitStruct;	// this is for the GPIO pins used as TX and RX
	__HAL_RCC_GPIOD_CLK_ENABLE();
	
	GPIO_InitStruct.Pin = USART2_Tx.PIN | USART2_Rx.PIN ; // Pins 5 (TX) and 6 (RX) are used
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP; 			// the pins are configured as alternate function so the USART peripheral has access to them
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;		// this defines the IO speed and has nothing to do with the baudrate!
	GPIO_InitStruct.Pull = GPIO_PULLUP;			// this activates the pullup resistors on the IO pins
	GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);					// now all the values are passed to the GPIO_Init() function which sets the GPIO registers
}

void USART3_GPIO_CONFIG(void){
	CREATE_USART3_PIN();
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
	
	Uart2Handle.Init.BaudRate 		= baudrate;
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
	
	Uart3Handle.Init.BaudRate 		= baudrate;
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
	__HAL_DMA_ENABLE_IT(&hdma_usart_rx, DMA_IT_TC);
	__HAL_DMA_ENABLE_IT(&hdma_usart_rx, DMA_IT_TE);
  
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
	__HAL_DMA_ENABLE_IT(&hdma_usart_tx, DMA_IT_TC);
	__HAL_DMA_ENABLE_IT(&hdma_usart_tx, DMA_IT_TE);
	
	HAL_DMA_Init(&hdma_usart_tx);
  __HAL_LINKDMA(&Uart3Handle, hdmatx, hdma_usart_tx);
  
  HAL_NVIC_SetPriority(DMA1_Stream1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream1_IRQn);
  
  HAL_NVIC_SetPriority(DMA1_Stream3_IRQn, 0, 1);
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
