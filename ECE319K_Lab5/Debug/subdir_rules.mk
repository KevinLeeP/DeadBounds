################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Clock.o: C:/Users/kevin/Desktop/S2026/ECE\ 319K/ValvanoWare/inc/Clock.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/Users/kevin/Desktop/S2026/ECE 319K/ValvanoWare/ECE319K_Lab5" -I"C:/Users/kevin/Desktop/S2026/ECE 319K/ValvanoWare/ECE319K_Lab5/Debug" -I"C:/ti/mspm0_sdk_2_09_00_01/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_09_00_01/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"Clock.d_raw" -MT"Clock.o" -I"C:/Users/kevin/Desktop/S2026/ECE 319K/ValvanoWare/ECE319K_Lab5/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

DAC5.o: C:/Users/kevin/Desktop/S2026/ECE\ 319K/ValvanoWare/inc/DAC5.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/Users/kevin/Desktop/S2026/ECE 319K/ValvanoWare/ECE319K_Lab5" -I"C:/Users/kevin/Desktop/S2026/ECE 319K/ValvanoWare/ECE319K_Lab5/Debug" -I"C:/ti/mspm0_sdk_2_09_00_01/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_09_00_01/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"DAC5.d_raw" -MT"DAC5.o" -I"C:/Users/kevin/Desktop/S2026/ECE 319K/ValvanoWare/ECE319K_Lab5/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Dump.o: C:/Users/kevin/Desktop/S2026/ECE\ 319K/ValvanoWare/inc/Dump.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/Users/kevin/Desktop/S2026/ECE 319K/ValvanoWare/ECE319K_Lab5" -I"C:/Users/kevin/Desktop/S2026/ECE 319K/ValvanoWare/ECE319K_Lab5/Debug" -I"C:/ti/mspm0_sdk_2_09_00_01/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_09_00_01/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"Dump.d_raw" -MT"Dump.o" -I"C:/Users/kevin/Desktop/S2026/ECE 319K/ValvanoWare/ECE319K_Lab5/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

%.o: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/Users/kevin/Desktop/S2026/ECE 319K/ValvanoWare/ECE319K_Lab5" -I"C:/Users/kevin/Desktop/S2026/ECE 319K/ValvanoWare/ECE319K_Lab5/Debug" -I"C:/ti/mspm0_sdk_2_09_00_01/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_09_00_01/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -I"C:/Users/kevin/Desktop/S2026/ECE 319K/ValvanoWare/ECE319K_Lab5/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

FIFO.o: C:/Users/kevin/Desktop/S2026/ECE\ 319K/ValvanoWare/inc/FIFO.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/Users/kevin/Desktop/S2026/ECE 319K/ValvanoWare/ECE319K_Lab5" -I"C:/Users/kevin/Desktop/S2026/ECE 319K/ValvanoWare/ECE319K_Lab5/Debug" -I"C:/ti/mspm0_sdk_2_09_00_01/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_09_00_01/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"FIFO.d_raw" -MT"FIFO.o" -I"C:/Users/kevin/Desktop/S2026/ECE 319K/ValvanoWare/ECE319K_Lab5/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Key.o: C:/Users/kevin/Desktop/S2026/ECE\ 319K/ValvanoWare/inc/Key.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/Users/kevin/Desktop/S2026/ECE 319K/ValvanoWare/ECE319K_Lab5" -I"C:/Users/kevin/Desktop/S2026/ECE 319K/ValvanoWare/ECE319K_Lab5/Debug" -I"C:/ti/mspm0_sdk_2_09_00_01/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_09_00_01/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"Key.d_raw" -MT"Key.o" -I"C:/Users/kevin/Desktop/S2026/ECE 319K/ValvanoWare/ECE319K_Lab5/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

LaunchPad.o: C:/Users/kevin/Desktop/S2026/ECE\ 319K/ValvanoWare/inc/LaunchPad.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/Users/kevin/Desktop/S2026/ECE 319K/ValvanoWare/ECE319K_Lab5" -I"C:/Users/kevin/Desktop/S2026/ECE 319K/ValvanoWare/ECE319K_Lab5/Debug" -I"C:/ti/mspm0_sdk_2_09_00_01/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_09_00_01/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"LaunchPad.d_raw" -MT"LaunchPad.o" -I"C:/Users/kevin/Desktop/S2026/ECE 319K/ValvanoWare/ECE319K_Lab5/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Timer.o: C:/Users/kevin/Desktop/S2026/ECE\ 319K/ValvanoWare/inc/Timer.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/Users/kevin/Desktop/S2026/ECE 319K/ValvanoWare/ECE319K_Lab5" -I"C:/Users/kevin/Desktop/S2026/ECE 319K/ValvanoWare/ECE319K_Lab5/Debug" -I"C:/ti/mspm0_sdk_2_09_00_01/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_09_00_01/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"Timer.d_raw" -MT"Timer.o" -I"C:/Users/kevin/Desktop/S2026/ECE 319K/ValvanoWare/ECE319K_Lab5/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

UART.o: C:/Users/kevin/Desktop/S2026/ECE\ 319K/ValvanoWare/inc/UART.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/Users/kevin/Desktop/S2026/ECE 319K/ValvanoWare/ECE319K_Lab5" -I"C:/Users/kevin/Desktop/S2026/ECE 319K/ValvanoWare/ECE319K_Lab5/Debug" -I"C:/ti/mspm0_sdk_2_09_00_01/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_09_00_01/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"UART.d_raw" -MT"UART.o" -I"C:/Users/kevin/Desktop/S2026/ECE 319K/ValvanoWare/ECE319K_Lab5/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

UARTints.o: C:/Users/kevin/Desktop/S2026/ECE\ 319K/ValvanoWare/inc/UARTints.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/Users/kevin/Desktop/S2026/ECE 319K/ValvanoWare/ECE319K_Lab5" -I"C:/Users/kevin/Desktop/S2026/ECE 319K/ValvanoWare/ECE319K_Lab5/Debug" -I"C:/ti/mspm0_sdk_2_09_00_01/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_09_00_01/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"UARTints.d_raw" -MT"UARTints.o" -I"C:/Users/kevin/Desktop/S2026/ECE 319K/ValvanoWare/ECE319K_Lab5/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


