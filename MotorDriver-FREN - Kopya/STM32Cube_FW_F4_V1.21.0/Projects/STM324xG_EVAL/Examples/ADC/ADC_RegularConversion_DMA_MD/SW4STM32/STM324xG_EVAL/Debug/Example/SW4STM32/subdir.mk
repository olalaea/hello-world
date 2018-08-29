################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Projects/STM324xG_EVAL/Examples/ADC/ADC_RegularConversion_DMA_Test/SW4STM32/startup_stm32f407xx.s 

OBJS += \
./Example/SW4STM32/startup_stm32f407xx.o 


# Each subdirectory must supply rules for building sources it contributes
Example/SW4STM32/startup_stm32f407xx.o: C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Projects/STM324xG_EVAL/Examples/ADC/ADC_RegularConversion_DMA_Test/SW4STM32/startup_stm32f407xx.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Assembler'
	@echo $(PWD)
	arm-none-eabi-as -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -g -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


