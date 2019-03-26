################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
posix/PTLS.obj: C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source/ti/posix/freertos/PTLS.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/Noah/Documents/College/ECE453/3DPOV/Firmware/Test_Projects/Test1/freertos_builds_MSP_EXP432P401R_release_ccs" --include_path="C:/FreeRTOSv9.0.0/FreeRTOS/Source/include" --include_path="C:/FreeRTOSv9.0.0/FreeRTOS/Source/portable/CCS/ARM_CM4F" --include_path="C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source/ti/posix/ccs" --include_path="C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source" --include_path="C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source/third_party/CMSIS/Include" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/include" --advice:power=none --define=DeviceFamily_MSP432P401x --define=__MSP432P401R__ -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="posix/$(basename $(<F)).d_raw" --obj_directory="posix" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

posix/aeabi_portable.obj: C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source/ti/posix/freertos/aeabi_portable.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/Noah/Documents/College/ECE453/3DPOV/Firmware/Test_Projects/Test1/freertos_builds_MSP_EXP432P401R_release_ccs" --include_path="C:/FreeRTOSv9.0.0/FreeRTOS/Source/include" --include_path="C:/FreeRTOSv9.0.0/FreeRTOS/Source/portable/CCS/ARM_CM4F" --include_path="C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source/ti/posix/ccs" --include_path="C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source" --include_path="C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source/third_party/CMSIS/Include" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/include" --advice:power=none --define=DeviceFamily_MSP432P401x --define=__MSP432P401R__ -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="posix/$(basename $(<F)).d_raw" --obj_directory="posix" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

posix/clock.obj: C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source/ti/posix/freertos/clock.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/Noah/Documents/College/ECE453/3DPOV/Firmware/Test_Projects/Test1/freertos_builds_MSP_EXP432P401R_release_ccs" --include_path="C:/FreeRTOSv9.0.0/FreeRTOS/Source/include" --include_path="C:/FreeRTOSv9.0.0/FreeRTOS/Source/portable/CCS/ARM_CM4F" --include_path="C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source/ti/posix/ccs" --include_path="C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source" --include_path="C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source/third_party/CMSIS/Include" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/include" --advice:power=none --define=DeviceFamily_MSP432P401x --define=__MSP432P401R__ -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="posix/$(basename $(<F)).d_raw" --obj_directory="posix" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

posix/memory.obj: C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source/ti/posix/freertos/memory.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/Noah/Documents/College/ECE453/3DPOV/Firmware/Test_Projects/Test1/freertos_builds_MSP_EXP432P401R_release_ccs" --include_path="C:/FreeRTOSv9.0.0/FreeRTOS/Source/include" --include_path="C:/FreeRTOSv9.0.0/FreeRTOS/Source/portable/CCS/ARM_CM4F" --include_path="C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source/ti/posix/ccs" --include_path="C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source" --include_path="C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source/third_party/CMSIS/Include" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/include" --advice:power=none --define=DeviceFamily_MSP432P401x --define=__MSP432P401R__ -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="posix/$(basename $(<F)).d_raw" --obj_directory="posix" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

posix/mqueue.obj: C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source/ti/posix/freertos/mqueue.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/Noah/Documents/College/ECE453/3DPOV/Firmware/Test_Projects/Test1/freertos_builds_MSP_EXP432P401R_release_ccs" --include_path="C:/FreeRTOSv9.0.0/FreeRTOS/Source/include" --include_path="C:/FreeRTOSv9.0.0/FreeRTOS/Source/portable/CCS/ARM_CM4F" --include_path="C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source/ti/posix/ccs" --include_path="C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source" --include_path="C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source/third_party/CMSIS/Include" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/include" --advice:power=none --define=DeviceFamily_MSP432P401x --define=__MSP432P401R__ -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="posix/$(basename $(<F)).d_raw" --obj_directory="posix" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

posix/pthread.obj: C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source/ti/posix/freertos/pthread.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/Noah/Documents/College/ECE453/3DPOV/Firmware/Test_Projects/Test1/freertos_builds_MSP_EXP432P401R_release_ccs" --include_path="C:/FreeRTOSv9.0.0/FreeRTOS/Source/include" --include_path="C:/FreeRTOSv9.0.0/FreeRTOS/Source/portable/CCS/ARM_CM4F" --include_path="C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source/ti/posix/ccs" --include_path="C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source" --include_path="C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source/third_party/CMSIS/Include" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/include" --advice:power=none --define=DeviceFamily_MSP432P401x --define=__MSP432P401R__ -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="posix/$(basename $(<F)).d_raw" --obj_directory="posix" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

posix/pthread_barrier.obj: C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source/ti/posix/freertos/pthread_barrier.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/Noah/Documents/College/ECE453/3DPOV/Firmware/Test_Projects/Test1/freertos_builds_MSP_EXP432P401R_release_ccs" --include_path="C:/FreeRTOSv9.0.0/FreeRTOS/Source/include" --include_path="C:/FreeRTOSv9.0.0/FreeRTOS/Source/portable/CCS/ARM_CM4F" --include_path="C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source/ti/posix/ccs" --include_path="C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source" --include_path="C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source/third_party/CMSIS/Include" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/include" --advice:power=none --define=DeviceFamily_MSP432P401x --define=__MSP432P401R__ -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="posix/$(basename $(<F)).d_raw" --obj_directory="posix" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

posix/pthread_cond.obj: C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source/ti/posix/freertos/pthread_cond.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/Noah/Documents/College/ECE453/3DPOV/Firmware/Test_Projects/Test1/freertos_builds_MSP_EXP432P401R_release_ccs" --include_path="C:/FreeRTOSv9.0.0/FreeRTOS/Source/include" --include_path="C:/FreeRTOSv9.0.0/FreeRTOS/Source/portable/CCS/ARM_CM4F" --include_path="C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source/ti/posix/ccs" --include_path="C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source" --include_path="C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source/third_party/CMSIS/Include" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/include" --advice:power=none --define=DeviceFamily_MSP432P401x --define=__MSP432P401R__ -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="posix/$(basename $(<F)).d_raw" --obj_directory="posix" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

posix/pthread_mutex.obj: C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source/ti/posix/freertos/pthread_mutex.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/Noah/Documents/College/ECE453/3DPOV/Firmware/Test_Projects/Test1/freertos_builds_MSP_EXP432P401R_release_ccs" --include_path="C:/FreeRTOSv9.0.0/FreeRTOS/Source/include" --include_path="C:/FreeRTOSv9.0.0/FreeRTOS/Source/portable/CCS/ARM_CM4F" --include_path="C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source/ti/posix/ccs" --include_path="C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source" --include_path="C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source/third_party/CMSIS/Include" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/include" --advice:power=none --define=DeviceFamily_MSP432P401x --define=__MSP432P401R__ -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="posix/$(basename $(<F)).d_raw" --obj_directory="posix" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

posix/pthread_rwlock.obj: C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source/ti/posix/freertos/pthread_rwlock.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/Noah/Documents/College/ECE453/3DPOV/Firmware/Test_Projects/Test1/freertos_builds_MSP_EXP432P401R_release_ccs" --include_path="C:/FreeRTOSv9.0.0/FreeRTOS/Source/include" --include_path="C:/FreeRTOSv9.0.0/FreeRTOS/Source/portable/CCS/ARM_CM4F" --include_path="C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source/ti/posix/ccs" --include_path="C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source" --include_path="C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source/third_party/CMSIS/Include" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/include" --advice:power=none --define=DeviceFamily_MSP432P401x --define=__MSP432P401R__ -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="posix/$(basename $(<F)).d_raw" --obj_directory="posix" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

posix/sched.obj: C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source/ti/posix/freertos/sched.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/Noah/Documents/College/ECE453/3DPOV/Firmware/Test_Projects/Test1/freertos_builds_MSP_EXP432P401R_release_ccs" --include_path="C:/FreeRTOSv9.0.0/FreeRTOS/Source/include" --include_path="C:/FreeRTOSv9.0.0/FreeRTOS/Source/portable/CCS/ARM_CM4F" --include_path="C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source/ti/posix/ccs" --include_path="C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source" --include_path="C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source/third_party/CMSIS/Include" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/include" --advice:power=none --define=DeviceFamily_MSP432P401x --define=__MSP432P401R__ -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="posix/$(basename $(<F)).d_raw" --obj_directory="posix" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

posix/semaphore.obj: C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source/ti/posix/freertos/semaphore.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/Noah/Documents/College/ECE453/3DPOV/Firmware/Test_Projects/Test1/freertos_builds_MSP_EXP432P401R_release_ccs" --include_path="C:/FreeRTOSv9.0.0/FreeRTOS/Source/include" --include_path="C:/FreeRTOSv9.0.0/FreeRTOS/Source/portable/CCS/ARM_CM4F" --include_path="C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source/ti/posix/ccs" --include_path="C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source" --include_path="C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source/third_party/CMSIS/Include" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/include" --advice:power=none --define=DeviceFamily_MSP432P401x --define=__MSP432P401R__ -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="posix/$(basename $(<F)).d_raw" --obj_directory="posix" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

posix/sleep.obj: C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source/ti/posix/freertos/sleep.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/Noah/Documents/College/ECE453/3DPOV/Firmware/Test_Projects/Test1/freertos_builds_MSP_EXP432P401R_release_ccs" --include_path="C:/FreeRTOSv9.0.0/FreeRTOS/Source/include" --include_path="C:/FreeRTOSv9.0.0/FreeRTOS/Source/portable/CCS/ARM_CM4F" --include_path="C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source/ti/posix/ccs" --include_path="C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source" --include_path="C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source/third_party/CMSIS/Include" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/include" --advice:power=none --define=DeviceFamily_MSP432P401x --define=__MSP432P401R__ -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="posix/$(basename $(<F)).d_raw" --obj_directory="posix" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

posix/timer.obj: C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source/ti/posix/freertos/timer.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/Noah/Documents/College/ECE453/3DPOV/Firmware/Test_Projects/Test1/freertos_builds_MSP_EXP432P401R_release_ccs" --include_path="C:/FreeRTOSv9.0.0/FreeRTOS/Source/include" --include_path="C:/FreeRTOSv9.0.0/FreeRTOS/Source/portable/CCS/ARM_CM4F" --include_path="C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source/ti/posix/ccs" --include_path="C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source" --include_path="C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source/third_party/CMSIS/Include" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/include" --advice:power=none --define=DeviceFamily_MSP432P401x --define=__MSP432P401R__ -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="posix/$(basename $(<F)).d_raw" --obj_directory="posix" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


