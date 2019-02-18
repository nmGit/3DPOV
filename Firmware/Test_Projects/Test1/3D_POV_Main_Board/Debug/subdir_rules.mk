################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/Noah/Documents/College/ECE453/3DPOV/Firmware/Test_Projects/Test1/3D_POV_Main_Board/SimpleLink" --include_path="C:/Users/Noah/Documents/College/ECE453/3DPOV/Firmware/Test_Projects/Test1/3D_POV_Main_Board/source/platform/include" --include_path="C:/Users/Noah/Documents/College/ECE453/3DPOV/Firmware/Test_Projects/Test1/3D_POV_Main_Board/source/communication/include" --include_path="C:/Users/Noah/Documents/College/ECE453/3DPOV/Firmware/Test_Projects/Test1/3D_POV_Main_Board" --include_path="C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source" --include_path="C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source/third_party/CMSIS/Include" --include_path="C:/ti/simplelink_msp432p4_sdk_2_40_00_10/source/ti/posix/ccs" --include_path="C:/FreeRTOSv9.0.0/FreeRTOS/Source/include" --include_path="C:/FreeRTOSv9.0.0/FreeRTOS/Source/portable/CCS/ARM_CM4F" --include_path="C:/Users/Noah/Documents/College/ECE453/3DPOV/Firmware/Test_Projects/Test1/freertos_builds_MSP_EXP432P401R_release_ccs" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/include" --advice:power=none -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


