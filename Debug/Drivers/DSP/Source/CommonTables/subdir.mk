################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/DSP/Source/CommonTables/arm_common_tables.c \
../Drivers/DSP/Source/CommonTables/arm_const_structs.c 

C_DEPS += \
./Drivers/DSP/Source/CommonTables/arm_common_tables.d \
./Drivers/DSP/Source/CommonTables/arm_const_structs.d 

OBJS += \
./Drivers/DSP/Source/CommonTables/arm_common_tables.o \
./Drivers/DSP/Source/CommonTables/arm_const_structs.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/DSP/Source/CommonTables/%.o Drivers/DSP/Source/CommonTables/%.su: ../Drivers/DSP/Source/CommonTables/%.c Drivers/DSP/Source/CommonTables/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -D__FPU_PRESENT=1 -D__FPU_USED=1 -D__TARGET_FPU_VFP -DARM_MATH_CM4 -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/ST/workspace/F4_TCP2Http/Drivers/ESP8266" -I"D:/ST/workspace/F4_TCP2Http/Drivers/DSP" -I"D:/ST/workspace/F4_TCP2Http/Drivers/DSP/include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-DSP-2f-Source-2f-CommonTables

clean-Drivers-2f-DSP-2f-Source-2f-CommonTables:
	-$(RM) ./Drivers/DSP/Source/CommonTables/arm_common_tables.d ./Drivers/DSP/Source/CommonTables/arm_common_tables.o ./Drivers/DSP/Source/CommonTables/arm_common_tables.su ./Drivers/DSP/Source/CommonTables/arm_const_structs.d ./Drivers/DSP/Source/CommonTables/arm_const_structs.o ./Drivers/DSP/Source/CommonTables/arm_const_structs.su

.PHONY: clean-Drivers-2f-DSP-2f-Source-2f-CommonTables
