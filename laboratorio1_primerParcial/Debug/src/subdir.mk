################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/cliente.c \
../src/compra.c \
../src/funcionesComunes.c \
../src/gets.c \
../src/informes.c \
../src/laboratorio1_primerParcial.c \
../src/menues.c \
../src/validations.c 

OBJS += \
./src/cliente.o \
./src/compra.o \
./src/funcionesComunes.o \
./src/gets.o \
./src/informes.o \
./src/laboratorio1_primerParcial.o \
./src/menues.o \
./src/validations.o 

C_DEPS += \
./src/cliente.d \
./src/compra.d \
./src/funcionesComunes.d \
./src/gets.d \
./src/informes.d \
./src/laboratorio1_primerParcial.d \
./src/menues.d \
./src/validations.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


