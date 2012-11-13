################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/TicTacToeControl.cpp \
../src/TicTacToeWindow.cpp \
../src/TicTaeToeSearch.cpp 

OBJS += \
./src/TicTacToeControl.o \
./src/TicTacToeWindow.o \
./src/TicTaeToeSearch.o 

CPP_DEPS += \
./src/TicTacToeControl.d \
./src/TicTacToeWindow.d \
./src/TicTaeToeSearch.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 `pkg-config gtkmm-3.0 --cflags --libs` -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


