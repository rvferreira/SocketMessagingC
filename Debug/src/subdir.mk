################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/SocketMessagingC.c \
../src/client.c \
../src/TCPClient.c \
../src/message.c \
../src/server.c \
../src/utils.c 
 

OBJS += \
./src/SocketMessagingC.o \
./src/client.o \
./src/TCPClient.o \
./src/message.o \
./src/server.o \
./src/utils.o 

C_DEPS += \
./src/SocketMessagingC.d \
./src/client.d \
./src/TCPClient.d \
./src/message.d \
./src/server.d \
./src/utils.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


