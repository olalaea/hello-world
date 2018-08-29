################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c \
C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_adc.c \
C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_adc_ex.c \
C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c \
C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c \
C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c \
C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c.c \
C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c \
C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sram.c \
C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.c \
C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_fsmc.c \
../Drivers/STM32F4xx_HAL_Driver/stm32f4xx_ll_usart.c 

OBJS += \
./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal.o \
./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_adc.o \
./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_adc_ex.o \
./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_cortex.o \
./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_dma.o \
./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_gpio.o \
./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_i2c.o \
./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_rcc.o \
./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_sram.o \
./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_uart.o \
./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_ll_fsmc.o \
./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_ll_usart.o 

C_DEPS += \
./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal.d \
./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_adc.d \
./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_adc_ex.d \
./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_cortex.d \
./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_dma.d \
./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_gpio.d \
./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_i2c.d \
./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_rcc.d \
./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_sram.d \
./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_uart.d \
./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_ll_fsmc.d \
./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_ll_usart.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal.o: C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DUSE_HAL_DRIVER -DSTM32F407xx -DUSE_STM324xG_EVAL -I"C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Projects/STM324xG_EVAL/Examples/ADC/ADC_RegularConversion_DMA_Test/Inc" -I"C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/BSP/STM324xG_EVAL" -I"C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/CMSIS/Include"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -Wno-unused-variable -Wno-pointer-sign -Wno-main -Wno-format -Wno-address -Wno-unused-but-set-variable -Wno-strict-aliasing -Wno-parentheses -Wno-missing-braces -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_adc.o: C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_adc.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DUSE_HAL_DRIVER -DSTM32F407xx -DUSE_STM324xG_EVAL -I"C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Projects/STM324xG_EVAL/Examples/ADC/ADC_RegularConversion_DMA_Test/Inc" -I"C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/BSP/STM324xG_EVAL" -I"C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/CMSIS/Include"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -Wno-unused-variable -Wno-pointer-sign -Wno-main -Wno-format -Wno-address -Wno-unused-but-set-variable -Wno-strict-aliasing -Wno-parentheses -Wno-missing-braces -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_adc_ex.o: C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_adc_ex.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DUSE_HAL_DRIVER -DSTM32F407xx -DUSE_STM324xG_EVAL -I"C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Projects/STM324xG_EVAL/Examples/ADC/ADC_RegularConversion_DMA_Test/Inc" -I"C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/BSP/STM324xG_EVAL" -I"C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/CMSIS/Include"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -Wno-unused-variable -Wno-pointer-sign -Wno-main -Wno-format -Wno-address -Wno-unused-but-set-variable -Wno-strict-aliasing -Wno-parentheses -Wno-missing-braces -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_cortex.o: C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DUSE_HAL_DRIVER -DSTM32F407xx -DUSE_STM324xG_EVAL -I"C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Projects/STM324xG_EVAL/Examples/ADC/ADC_RegularConversion_DMA_Test/Inc" -I"C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/BSP/STM324xG_EVAL" -I"C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/CMSIS/Include"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -Wno-unused-variable -Wno-pointer-sign -Wno-main -Wno-format -Wno-address -Wno-unused-but-set-variable -Wno-strict-aliasing -Wno-parentheses -Wno-missing-braces -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_dma.o: C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DUSE_HAL_DRIVER -DSTM32F407xx -DUSE_STM324xG_EVAL -I"C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Projects/STM324xG_EVAL/Examples/ADC/ADC_RegularConversion_DMA_Test/Inc" -I"C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/BSP/STM324xG_EVAL" -I"C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/CMSIS/Include"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -Wno-unused-variable -Wno-pointer-sign -Wno-main -Wno-format -Wno-address -Wno-unused-but-set-variable -Wno-strict-aliasing -Wno-parentheses -Wno-missing-braces -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_gpio.o: C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DUSE_HAL_DRIVER -DSTM32F407xx -DUSE_STM324xG_EVAL -I"C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Projects/STM324xG_EVAL/Examples/ADC/ADC_RegularConversion_DMA_Test/Inc" -I"C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/BSP/STM324xG_EVAL" -I"C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/CMSIS/Include"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -Wno-unused-variable -Wno-pointer-sign -Wno-main -Wno-format -Wno-address -Wno-unused-but-set-variable -Wno-strict-aliasing -Wno-parentheses -Wno-missing-braces -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_i2c.o: C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DUSE_HAL_DRIVER -DSTM32F407xx -DUSE_STM324xG_EVAL -I"C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Projects/STM324xG_EVAL/Examples/ADC/ADC_RegularConversion_DMA_Test/Inc" -I"C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/BSP/STM324xG_EVAL" -I"C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/CMSIS/Include"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -Wno-unused-variable -Wno-pointer-sign -Wno-main -Wno-format -Wno-address -Wno-unused-but-set-variable -Wno-strict-aliasing -Wno-parentheses -Wno-missing-braces -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_rcc.o: C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DUSE_HAL_DRIVER -DSTM32F407xx -DUSE_STM324xG_EVAL -I"C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Projects/STM324xG_EVAL/Examples/ADC/ADC_RegularConversion_DMA_Test/Inc" -I"C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/BSP/STM324xG_EVAL" -I"C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/CMSIS/Include"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -Wno-unused-variable -Wno-pointer-sign -Wno-main -Wno-format -Wno-address -Wno-unused-but-set-variable -Wno-strict-aliasing -Wno-parentheses -Wno-missing-braces -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_sram.o: C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sram.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DUSE_HAL_DRIVER -DSTM32F407xx -DUSE_STM324xG_EVAL -I"C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Projects/STM324xG_EVAL/Examples/ADC/ADC_RegularConversion_DMA_Test/Inc" -I"C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/BSP/STM324xG_EVAL" -I"C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/CMSIS/Include"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -Wno-unused-variable -Wno-pointer-sign -Wno-main -Wno-format -Wno-address -Wno-unused-but-set-variable -Wno-strict-aliasing -Wno-parentheses -Wno-missing-braces -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_uart.o: C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DUSE_HAL_DRIVER -DSTM32F407xx -DUSE_STM324xG_EVAL -I"C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Projects/STM324xG_EVAL/Examples/ADC/ADC_RegularConversion_DMA_Test/Inc" -I"C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/BSP/STM324xG_EVAL" -I"C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/CMSIS/Include"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -Wno-unused-variable -Wno-pointer-sign -Wno-main -Wno-format -Wno-address -Wno-unused-but-set-variable -Wno-strict-aliasing -Wno-parentheses -Wno-missing-braces -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Drivers/STM32F4xx_HAL_Driver/stm32f4xx_ll_fsmc.o: C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_fsmc.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DUSE_HAL_DRIVER -DSTM32F407xx -DUSE_STM324xG_EVAL -I"C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Projects/STM324xG_EVAL/Examples/ADC/ADC_RegularConversion_DMA_Test/Inc" -I"C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/BSP/STM324xG_EVAL" -I"C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/CMSIS/Include"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -Wno-unused-variable -Wno-pointer-sign -Wno-main -Wno-format -Wno-address -Wno-unused-but-set-variable -Wno-strict-aliasing -Wno-parentheses -Wno-missing-braces -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Drivers/STM32F4xx_HAL_Driver/%.o: ../Drivers/STM32F4xx_HAL_Driver/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DUSE_HAL_DRIVER -DSTM32F407xx -DUSE_STM324xG_EVAL -I"C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Projects/STM324xG_EVAL/Examples/ADC/ADC_RegularConversion_DMA_Test/Inc" -I"C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/BSP/STM324xG_EVAL" -I"C:/Users/Ugur/Desktop/STM32Cube_FW_F4_V1.21.0/Drivers/CMSIS/Include"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -Wno-unused-variable -Wno-pointer-sign -Wno-main -Wno-format -Wno-address -Wno-unused-but-set-variable -Wno-strict-aliasing -Wno-parentheses -Wno-missing-braces -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


