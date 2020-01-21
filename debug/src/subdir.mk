################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Controller.cpp \
../src/Model.cpp \
../src/Player.cpp \
../src/Tile.cpp \
../src/Unit.cpp \
../src/Util.cpp \
../src/View.cpp \
../src/exceptions.cpp \
../src/main.cpp 

OBJS += \
./src/Controller.o \
./src/Model.o \
./src/Player.o \
./src/Tile.o \
./src/Unit.o \
./src/Util.o \
./src/View.o \
./src/exceptions.o \
./src/main.o 

CPP_DEPS += \
./src/Controller.d \
./src/Model.d \
./src/Player.d \
./src/Tile.d \
./src/Unit.d \
./src/Util.d \
./src/View.d \
./src/exceptions.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


