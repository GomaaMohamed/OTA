#Home of the Work Space
#Edit the path of the project here
HOME := /home/gomaa/embedded/08-ARMCortex-M/bootloader
CC = arm-none-eabi-gcc
AS = arm-none-eabi-as 
LD = arm-none-eabi-ld 
BIN = arm-none-eabi-objcopy
STL = st-flash
CFLAGS = -mthumb -mcpu=cortex-m3


#Directories that will be searched for Headers
INCLUDES +=  -I $(HOME)/mcal/include \
             -I $(HOME)/hal/include \
			 -I $(HOME)/app/include \
			 -I $(HOME)/lib/include 
 
#Source Files of the Project
SRCS += $(wildcard $(HOME)/*.c) \
        $(wildcard $(HOME)/mcal/sources/*.c) \
		$(wildcard $(HOME)/hal/sources/*.c) \
		$(wildcard $(HOME)/app/sources/*.c) \
		$(wildcard $(HOME)/lib/sources/*.c)  
       
compile :  
	@$(CC) $(CFLAGS) -c $(SRCS) -g $(INCLUDES)

clean :
	@rm -f *.o *.s *.i  *.asm 
	
	
