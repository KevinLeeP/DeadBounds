################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
ADC.o: C:/Users/kevin/Desktop/S2026/ECE\ 319K/ValvanoWare/inc/ADC.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/Users/kevin/Desktop/S2026/ECE 319K/ValvanoWare/CrystalfontzLCD" -I"C:/Users/kevin/Desktop/S2026/ECE 319K/ValvanoWare/CrystalfontzLCD/Debug" -I"C:/ti/mspm0_sdk_2_09_00_01/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_09_00_01/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"ADC.d_raw" -MT"ADC.o" -I"C:/Users/kevin/Desktop/S2026/ECE 319K/ValvanoWare/CrystalfontzLCD/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Clock.o: C:/Users/kevin/Desktop/S2026/ECE\ 319K/ValvanoWare/inc/Clock.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/Users/kevin/Desktop/S2026/ECE 319K/ValvanoWare/CrystalfontzLCD" -I"C:/Users/kevin/Desktop/S2026/ECE 319K/ValvanoWare/CrystalfontzLCD/Debug" -I"C:/ti/mspm0_sdk_2_09_00_01/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_09_00_01/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"Clock.d_raw" -MT"Clock.o" -I"C:/Users/kevin/Desktop/S2026/ECE 319K/ValvanoWare/CrystalfontzLCD/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

LCD.o: C:/Users/kevin/Desktop/S2026/ECE\ 319K/ValvanoWare/inc/LCD.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/Users/kevin/Desktop/S2026/ECE 319K/ValvanoWare/CrystalfontzLCD" -I"C:/Users/kevin/Desktop/S2026/ECE 319K/ValvanoWare/CrystalfontzLCD/Debug" -I"C:/ti/mspm0_sdk_2_09_00_01/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_09_00_01/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"LCD.d_raw" -MT"LCD.o" -I"C:/Users/kevin/Desktop/S2026/ECE 319K/ValvanoWare/CrystalfontzLCD/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

%.o: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/Users/kevin/Desktop/S2026/ECE 319K/ValvanoWare/CrystalfontzLCD" -I"C:/Users/kevin/Desktop/S2026/ECE 319K/ValvanoWare/CrystalfontzLCD/Debug" -I"C:/ti/mspm0_sdk_2_09_00_01/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_09_00_01/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -I"C:/Users/kevin/Desktop/S2026/ECE 319K/ValvanoWare/CrystalfontzLCD/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

LaunchPad.o: C:/Users/kevin/Desktop/S2026/ECE\ 319K/ValvanoWare/inc/LaunchPad.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/Users/kevin/Desktop/S2026/ECE 319K/ValvanoWare/CrystalfontzLCD" -I"C:/Users/kevin/Desktop/S2026/ECE 319K/ValvanoWare/CrystalfontzLCD/Debug" -I"C:/ti/mspm0_sdk_2_09_00_01/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_09_00_01/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"LaunchPad.d_raw" -MT"LaunchPad.o" -I"C:/Users/kevin/Desktop/S2026/ECE 319K/ValvanoWare/CrystalfontzLCD/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

SPI.o: C:/Users/kevin/Desktop/S2026/ECE\ 319K/ValvanoWare/inc/SPI.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/Users/kevin/Desktop/S2026/ECE 319K/ValvanoWare/CrystalfontzLCD" -I"C:/Users/kevin/Desktop/S2026/ECE 319K/ValvanoWare/CrystalfontzLCD/Debug" -I"C:/ti/mspm0_sdk_2_09_00_01/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_09_00_01/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"SPI.d_raw" -MT"SPI.o" -I"C:/Users/kevin/Desktop/S2026/ECE 319K/ValvanoWare/CrystalfontzLCD/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


