################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Drivers/ESP8266/MineMain.cpp \
../Drivers/ESP8266/callback.cpp \
../Drivers/ESP8266/esp8266.cpp 

OBJS += \
./Drivers/ESP8266/MineMain.o \
./Drivers/ESP8266/callback.o \
./Drivers/ESP8266/esp8266.o 

CPP_DEPS += \
./Drivers/ESP8266/MineMain.d \
./Drivers/ESP8266/callback.d \
./Drivers/ESP8266/esp8266.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/ESP8266/%.o Drivers/ESP8266/%.su: ../Drivers/ESP8266/%.cpp Drivers/ESP8266/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -D__FPU_PRESENT=1 -D__FPU_USED=1 -D__TARGET_FPU_VFP -DARM_MATH_CM4 -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/ST/workspace/F4_TCP2Http/Drivers/ESP8266" -I"D:/ST/workspace/F4_TCP2Http/Drivers/DSP" -I"D:/ST/workspace/F4_TCP2Http/Drivers/DSP/include" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-ESP8266

clean-Drivers-2f-ESP8266:
	-$(RM) ./Drivers/ESP8266/MineMain.d ./Drivers/ESP8266/MineMain.o ./Drivers/ESP8266/MineMain.su ./Drivers/ESP8266/callback.d ./Drivers/ESP8266/callback.o ./Drivers/ESP8266/callback.su ./Drivers/ESP8266/esp8266.d ./Drivers/ESP8266/esp8266.o ./Drivers/ESP8266/esp8266.su

.PHONY: clean-Drivers-2f-ESP8266

