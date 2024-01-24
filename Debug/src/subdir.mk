################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/SensorPorting.cpp \
../src/platform.cpp \
../src/vl53l5cx_api.cpp 

OBJS += \
./src/SensorPorting.o \
./src/platform.o \
./src/vl53l5cx_api.o 

CPP_DEPS += \
./src/SensorPorting.d \
./src/platform.d \
./src/vl53l5cx_api.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	aarch64-tdx-linux-g++ -I/opt/tdx-xwayland/6.5.0/sysroots/cortexa72-cortexa53-tdx-linux/usr/include -I/opt/tdx-xwayland/6.5.0/sysroots/cortexa72-cortexa53-tdx-linux/usr/lib/glib-2.0/include -I/opt/tdx-xwayland/6.5.0/sysroots/cortexa72-cortexa53-tdx-linux/usr/include/glib-2.0 -O0 -g3 -Wall -c -fmessage-length=0 --sysroot=/opt/tdx-xwayland/6.5.0/sysroots/cortexa72-cortexa53-tdx-linux `/opt/tdx-xwayland/6.5.0/sysroots/x86_64-tdxsdk-linux/usr/bin/pkg-config --libs glib-2.0` -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


