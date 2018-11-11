################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
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
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
DWM_Distance.lss \

FLASH_IMAGE += \
DWM_Distance.hex \

EEPROM_IMAGE += \
DWM_Distance.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: DWM_Distance.elf secondary-outputs

# Tool invocations
DWM_Distance.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,DWM_Distance.map -mmcu=atmega324pa -o "DWM_Distance.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

DWM_Distance.lss: DWM_Distance.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S DWM_Distance.elf  >"DWM_Distance.lss"
	@echo 'Finished building: $@'
	@echo ' '

DWM_Distance.hex: DWM_Distance.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex DWM_Distance.elf  "DWM_Distance.hex"
	@echo 'Finished building: $@'
	@echo ' '

DWM_Distance.eep: DWM_Distance.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex DWM_Distance.elf  "DWM_Distance.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: DWM_Distance.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega324pa DWM_Distance.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) DWM_Distance.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
