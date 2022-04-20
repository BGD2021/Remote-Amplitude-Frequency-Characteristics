################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Startup/startup_stm32f407zgtx.s 

S_DEPS += \
./Core/Startup/startup_stm32f407zgtx.d 

OBJS += \
./Core/Startup/startup_stm32f407zgtx.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Startup/%.o: ../Core/Startup/%.s Core/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -D__FPU_PRESENT=1 -D__FPU_USED=1 -D__TARGET_FPU_VFP -DARM_MATH_CM4 -c -I"D:/ST/workspace/F4_TCP2Http/Drivers/ESP8266" -I"D:/ST/workspace/F4_TCP2Http/Drivers/DSP" -I"D:/ST/workspace/F4_TCP2Http/Drivers/DSP/include" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Core-2f-Startup

clean-Core-2f-Startup:
	-$(RM) ./Core/Startup/startup_stm32f407zgtx.d ./Core/Startup/startup_stm32f407zgtx.o

.PHONY: clean-Core-2f-Startup

