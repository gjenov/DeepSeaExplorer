################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/Users/standard/ti/ccs1250/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=none -me -Ooff --include_path="C:/Users/standard/eec172/lab2/i2c/i2c_demo" --include_path="C:/Users/standard/ti/ccs1250/cc3200-sdk/" --include_path="C:/Users/standard/ti/ccs1250/cc3200-sdk/driverlib/" --include_path="C:/Users/standard/ti/ccs1250/cc3200-sdk/inc/" --include_path="C:/Users/standard/ti/ccs1250/cc3200-sdk/example/common/" --include_path="C:/Users/standard/ti/ccs1250/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --define=ccs --define=cc3200 --define=NON_NETWORK -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

i2c_if.obj: C:/Users/standard/ti/ccs1250/cc3200-sdk/example/common/i2c_if.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/Users/standard/ti/ccs1250/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=none -me -Ooff --include_path="C:/Users/standard/eec172/lab2/i2c/i2c_demo" --include_path="C:/Users/standard/ti/ccs1250/cc3200-sdk/" --include_path="C:/Users/standard/ti/ccs1250/cc3200-sdk/driverlib/" --include_path="C:/Users/standard/ti/ccs1250/cc3200-sdk/inc/" --include_path="C:/Users/standard/ti/ccs1250/cc3200-sdk/example/common/" --include_path="C:/Users/standard/ti/ccs1250/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --define=ccs --define=cc3200 --define=NON_NETWORK -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

startup_ccs.obj: C:/Users/standard/ti/ccs1250/cc3200-sdk/example/common/startup_ccs.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/Users/standard/ti/ccs1250/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=none -me -Ooff --include_path="C:/Users/standard/eec172/lab2/i2c/i2c_demo" --include_path="C:/Users/standard/ti/ccs1250/cc3200-sdk/" --include_path="C:/Users/standard/ti/ccs1250/cc3200-sdk/driverlib/" --include_path="C:/Users/standard/ti/ccs1250/cc3200-sdk/inc/" --include_path="C:/Users/standard/ti/ccs1250/cc3200-sdk/example/common/" --include_path="C:/Users/standard/ti/ccs1250/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --define=ccs --define=cc3200 --define=NON_NETWORK -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

uart_if.obj: C:/Users/standard/ti/ccs1250/cc3200-sdk/example/common/uart_if.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/Users/standard/ti/ccs1250/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=none -me -Ooff --include_path="C:/Users/standard/eec172/lab2/i2c/i2c_demo" --include_path="C:/Users/standard/ti/ccs1250/cc3200-sdk/" --include_path="C:/Users/standard/ti/ccs1250/cc3200-sdk/driverlib/" --include_path="C:/Users/standard/ti/ccs1250/cc3200-sdk/inc/" --include_path="C:/Users/standard/ti/ccs1250/cc3200-sdk/example/common/" --include_path="C:/Users/standard/ti/ccs1250/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --define=ccs --define=cc3200 --define=NON_NETWORK -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


