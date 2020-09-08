################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32L4xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/view/subdir.mk
-include Core/Src/util/subdir.mk
-include Core/Src/ssd1306/subdir.mk
-include Core/Src/sen0237a/subdir.mk
-include Core/Src/sen0189/subdir.mk
-include Core/Src/sen0169/subdir.mk
-include Core/Src/sen0165/subdir.mk
-include Core/Src/sen0161/subdir.mk
-include Core/Src/mqtt_client/subdir.mk
-include Core/Src/esp8266/subdir.mk
-include Core/Src/ds18b20/subdir.mk
-include Core/Src/dma/subdir.mk
-include Core/Src/configuration/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
ESP8266MQTT.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
ESP8266MQTT.list \

OBJCOPY_BIN += \
ESP8266MQTT.bin \


# All Target
all: ESP8266MQTT.elf secondary-outputs

# Tool invocations
ESP8266MQTT.elf: $(OBJS) $(USER_OBJS) C:\Users\hugog\STM32CubeIDE\workspace_1.3.0\ESP8266MQTT\STM32L433RCTX_FLASH.ld
	arm-none-eabi-gcc -o "ESP8266MQTT.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\hugog\STM32CubeIDE\workspace_1.3.0\ESP8266MQTT\STM32L433RCTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="ESP8266MQTT.map" -Wl,--gc-sections -static  -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -u _printf_float -u _scanf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

ESP8266MQTT.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "ESP8266MQTT.list"
	@echo 'Finished building: $@'
	@echo ' '

ESP8266MQTT.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "ESP8266MQTT.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
