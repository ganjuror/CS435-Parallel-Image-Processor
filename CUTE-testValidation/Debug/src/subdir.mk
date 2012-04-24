################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Test.cpp \
../src/iteration2main.cpp 

OBJS += \
./src/Test.o \
./src/iteration2main.o 

CPP_DEPS += \
./src/Test.d \
./src/iteration2main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/ganjuror/docs/School/CompSci/CS435-SoftwareEngineering/project/CS435-Parallel-Image-Processor/CUTE-testValidation/cute" -I"/home/ganjuror/docs/School/CompSci/CS435-SoftwareEngineering/project/CS435-Parallel-Image-Processor/CUTE-testValidation/boost" -I/usr/include/ImageMagick -O2 -g -Wall -c -fmessage-length=0 -fopenmp `Magick++-config --cppflags --cxxflags --ldflags --libs` -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


