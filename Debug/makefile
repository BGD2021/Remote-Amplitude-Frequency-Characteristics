################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include Drivers/ESP8266/subdir.mk
-include Drivers/DSP/Source/TransformFunctions/subdir.mk
-include Drivers/DSP/Source/SupportFunctions/subdir.mk
-include Drivers/DSP/Source/StatisticsFunctions/subdir.mk
-include Drivers/DSP/Source/MatrixFunctions/subdir.mk
-include Drivers/DSP/Source/FilteringFunctions/subdir.mk
-include Drivers/DSP/Source/FastMathFunctions/subdir.mk
-include Drivers/DSP/Source/ControllerFunctions/subdir.mk
-include Drivers/DSP/Source/ComplexMathFunctions/subdir.mk
-include Drivers/DSP/Source/CommonTables/subdir.mk
-include Drivers/DSP/Source/BasicMathFunctions/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := F4_TCP2Http
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
F4_TCP2Http.elf \

MAP_FILES += \
F4_TCP2Http.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
F4_TCP2Http.list \


# All Target
all: main-build

# Main-build Target
main-build: F4_TCP2Http.elf secondary-outputs

# Tool invocations
F4_TCP2Http.elf F4_TCP2Http.map: $(OBJS) $(USER_OBJS) D:\ST\workspace\F4_TCP2Http\STM32F407ZGTX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-g++ -o "F4_TCP2Http.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"D:\ST\workspace\F4_TCP2Http\STM32F407ZGTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="F4_TCP2Http.map" -Wl,--gc-sections -static "D:\ST\workspace\F4_TCP2Http\Drivers\DSP\libarm_cortexM4lf_math.a" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -lstdc++ -lsupc++ -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

F4_TCP2Http.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "F4_TCP2Http.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) F4_TCP2Http.elf F4_TCP2Http.list F4_TCP2Http.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
