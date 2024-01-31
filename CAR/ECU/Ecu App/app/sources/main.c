#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "RCC_interface.h"
#include "STK_interface.h"
#include "GPIO_interface.h"
#include "USART_interface.h"

typedef void (*Function_type)(void);
Function_type AddressToCall;
u8 Buffer[10];
u8 Counter = 0;

int main(void)
{
	RCC_initSysClock();
	STK_init();
	USART_init();
	RCC_enableClock(RCC_APB2, RCC_IOPA);
	GPIO_setPinDirection(GPIOA, GPIO_PIN0, GPIO_OUTPUT_10MHZ_PP);
	GPIO_setPinValue(GPIOA, GPIO_PIN0, GPIO_HIGH);
	while (1)
	{
		// Handle reset request
		if(USART_receiveCharacter( &Buffer[Counter] )== RECEIVED_OK)
		{
			if (Buffer[Counter] == '\n')
			{
				if (Buffer[0] == '0'&& Buffer[1] == 'x' && Buffer[2] == '3' && Buffer[3] == '7')
				{
					// Respond with a positive response
					GPIO_setPinValue(GPIOA, GPIO_PIN0, GPIO_LOW);
					USART_transmitCharacter('C');
					// Make a reset
					// Disable all interrupts and faults
					asm("CPSID i");
    				asm("CPSID f");
    				// Jump to application code
    				AddressToCall = *(Function_type *)(0x08000004);      
    				AddressToCall();
				}
				else if (Buffer[0] == '0'&& Buffer[1] == 'x' && Buffer[2] == '5' && Buffer[3] == '9')
				{
					// Read DTCs
					
					// Respond with the DTCs
					GPIO_setPinValue(GPIOA, GPIO_PIN0, GPIO_LOW);
					USART_transmitCharacter('C');
				}
				else if (Buffer[0] == '0'&& Buffer[1] == 'x' && Buffer[2] == '1' && Buffer[3] == '4')
				{
					// Clear DTCs
					
					// Respond with Positive response
					GPIO_setPinValue(GPIOA, GPIO_PIN0, GPIO_LOW);
					USART_transmitCharacter('C');
				}
				else 
				{
					// Respond with a time out 
				}	
				Counter = 0;
			}
			else
			{
				Counter++;
			}
		}
	}
	return 0;
}


