################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/API/Src/mpu9265_SPI.c \
../Drivers/API/Src/port.c 

OBJS += \
./Drivers/API/Src/mpu9265_SPI.o \
./Drivers/API/Src/port.o 

C_DEPS += \
./Drivers/API/Src/mpu9265_SPI.d \
./Drivers/API/Src/port.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/API/Src/%.o Drivers/API/Src/%.su Drivers/API/Src/%.cyclo: ../Drivers/API/Src/%.c Drivers/API/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/UBA/CESE/ProgMicro/PdM_workspace-main/mpu9265_SPI/Drivers/API/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-API-2f-Src

clean-Drivers-2f-API-2f-Src:
	-$(RM) ./Drivers/API/Src/mpu9265_SPI.cyclo ./Drivers/API/Src/mpu9265_SPI.d ./Drivers/API/Src/mpu9265_SPI.o ./Drivers/API/Src/mpu9265_SPI.su ./Drivers/API/Src/port.cyclo ./Drivers/API/Src/port.d ./Drivers/API/Src/port.o ./Drivers/API/Src/port.su

.PHONY: clean-Drivers-2f-API-2f-Src

