################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
ADC1.o: C:/Users/charl/OneDrive/Documents/DeadBoundsCode/DeadBounds/inc/ADC1.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/Users/charl/OneDrive/Documents/DeadBoundsCode/DeadBounds/ECE319K_Lab9" -I"C:/Users/charl/OneDrive/Documents/DeadBoundsCode/DeadBounds/ECE319K_Lab9/Debug" -I"C:/ti/mspm0_sdk_2_09_00_01/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_09_00_01/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -I"C:/Users/charl/OneDrive/Documents/DeadBoundsCode/DeadBounds/ECE319K_Lab9/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

%.o: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/Users/charl/OneDrive/Documents/DeadBoundsCode/DeadBounds/ECE319K_Lab9" -I"C:/Users/charl/OneDrive/Documents/DeadBoundsCode/DeadBounds/ECE319K_Lab9/Debug" -I"C:/ti/mspm0_sdk_2_09_00_01/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_09_00_01/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -I"C:/Users/charl/OneDrive/Documents/DeadBoundsCode/DeadBounds/ECE319K_Lab9/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Animations.o: ../Animations.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/Users/charl/OneDrive/Documents/DeadBoundsCode/DeadBounds/ECE319K_Lab9" -I"C:/Users/charl/OneDrive/Documents/DeadBoundsCode/DeadBounds/ECE319K_Lab9/Debug" -I"C:/ti/mspm0_sdk_2_09_00_01/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_09_00_01/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(basename\ $(<F)).o" -I"C:/Users/charl/OneDrive/Documents/DeadBoundsCode/DeadBounds/ECE319K_Lab9/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Arabic.o: C:/Users/charl/OneDrive/Documents/DeadBoundsCode/DeadBounds/inc/Arabic.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/Users/charl/OneDrive/Documents/DeadBoundsCode/DeadBounds/ECE319K_Lab9" -I"C:/Users/charl/OneDrive/Documents/DeadBoundsCode/DeadBounds/ECE319K_Lab9/Debug" -I"C:/ti/mspm0_sdk_2_09_00_01/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_09_00_01/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -I"C:/Users/charl/OneDrive/Documents/DeadBoundsCode/DeadBounds/ECE319K_Lab9/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Clock.o: C:/Users/charl/OneDrive/Documents/DeadBoundsCode/DeadBounds/inc/Clock.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/Users/charl/OneDrive/Documents/DeadBoundsCode/DeadBounds/ECE319K_Lab9" -I"C:/Users/charl/OneDrive/Documents/DeadBoundsCode/DeadBounds/ECE319K_Lab9/Debug" -I"C:/ti/mspm0_sdk_2_09_00_01/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_09_00_01/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -I"C:/Users/charl/OneDrive/Documents/DeadBoundsCode/DeadBounds/ECE319K_Lab9/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

DAC5.o: C:/Users/charl/OneDrive/Documents/DeadBoundsCode/DeadBounds/inc/DAC5.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/Users/charl/OneDrive/Documents/DeadBoundsCode/DeadBounds/ECE319K_Lab9" -I"C:/Users/charl/OneDrive/Documents/DeadBoundsCode/DeadBounds/ECE319K_Lab9/Debug" -I"C:/ti/mspm0_sdk_2_09_00_01/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_09_00_01/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -I"C:/Users/charl/OneDrive/Documents/DeadBoundsCode/DeadBounds/ECE319K_Lab9/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Lab9Main.o: ../Lab9Main.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/Users/charl/OneDrive/Documents/DeadBoundsCode/DeadBounds/ECE319K_Lab9" -I"C:/Users/charl/OneDrive/Documents/DeadBoundsCode/DeadBounds/ECE319K_Lab9/Debug" -I"C:/ti/mspm0_sdk_2_09_00_01/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_09_00_01/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(basename\ $(<F)).o" -I"C:/Users/charl/OneDrive/Documents/DeadBoundsCode/DeadBounds/ECE319K_Lab9/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

LaunchPad.o: C:/Users/charl/OneDrive/Documents/DeadBoundsCode/DeadBounds/inc/LaunchPad.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/Users/charl/OneDrive/Documents/DeadBoundsCode/DeadBounds/ECE319K_Lab9" -I"C:/Users/charl/OneDrive/Documents/DeadBoundsCode/DeadBounds/ECE319K_Lab9/Debug" -I"C:/ti/mspm0_sdk_2_09_00_01/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_09_00_01/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -I"C:/Users/charl/OneDrive/Documents/DeadBoundsCode/DeadBounds/ECE319K_Lab9/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

SPI.o: C:/Users/charl/OneDrive/Documents/DeadBoundsCode/DeadBounds/inc/SPI.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/Users/charl/OneDrive/Documents/DeadBoundsCode/DeadBounds/ECE319K_Lab9" -I"C:/Users/charl/OneDrive/Documents/DeadBoundsCode/DeadBounds/ECE319K_Lab9/Debug" -I"C:/ti/mspm0_sdk_2_09_00_01/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_09_00_01/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -I"C:/Users/charl/OneDrive/Documents/DeadBoundsCode/DeadBounds/ECE319K_Lab9/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

ST7735.o: C:/Users/charl/OneDrive/Documents/DeadBoundsCode/DeadBounds/inc/ST7735.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/Users/charl/OneDrive/Documents/DeadBoundsCode/DeadBounds/ECE319K_Lab9" -I"C:/Users/charl/OneDrive/Documents/DeadBoundsCode/DeadBounds/ECE319K_Lab9/Debug" -I"C:/ti/mspm0_sdk_2_09_00_01/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_09_00_01/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -I"C:/Users/charl/OneDrive/Documents/DeadBoundsCode/DeadBounds/ECE319K_Lab9/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

TExaS.o: C:/Users/charl/OneDrive/Documents/DeadBoundsCode/DeadBounds/inc/TExaS.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/Users/charl/OneDrive/Documents/DeadBoundsCode/DeadBounds/ECE319K_Lab9" -I"C:/Users/charl/OneDrive/Documents/DeadBoundsCode/DeadBounds/ECE319K_Lab9/Debug" -I"C:/ti/mspm0_sdk_2_09_00_01/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_09_00_01/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -I"C:/Users/charl/OneDrive/Documents/DeadBoundsCode/DeadBounds/ECE319K_Lab9/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Timer.o: C:/Users/charl/OneDrive/Documents/DeadBoundsCode/DeadBounds/inc/Timer.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/Users/charl/OneDrive/Documents/DeadBoundsCode/DeadBounds/ECE319K_Lab9" -I"C:/Users/charl/OneDrive/Documents/DeadBoundsCode/DeadBounds/ECE319K_Lab9/Debug" -I"C:/ti/mspm0_sdk_2_09_00_01/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_09_00_01/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -I"C:/Users/charl/OneDrive/Documents/DeadBoundsCode/DeadBounds/ECE319K_Lab9/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

render3D.o: ../render3D.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/Users/charl/OneDrive/Documents/DeadBoundsCode/DeadBounds/ECE319K_Lab9" -I"C:/Users/charl/OneDrive/Documents/DeadBoundsCode/DeadBounds/ECE319K_Lab9/Debug" -I"C:/ti/mspm0_sdk_2_09_00_01/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_09_00_01/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(basename\ $(<F)).o" -I"C:/Users/charl/OneDrive/Documents/DeadBoundsCode/DeadBounds/ECE319K_Lab9/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


