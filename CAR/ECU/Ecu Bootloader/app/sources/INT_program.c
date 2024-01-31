/*****************************************************************************
* @file:    INT_program.c
* @author:  Copyright (c) 2023 Gomaa Mohammed Gomaa.
* @license: GNU GPL version 3 or later.
*			This is free software: you are free to change and redistribute it.  
*			There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Fri, 20 Oct 2023 14:21:12 +0200
* @brief:   Bootloader for STM32F103
******************************************************************************/

/* ==================================================================== */
/* ========================== Include Files =========================== */
/* ==================================================================== */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "STK_interface.h"
#include "USART_interface.h"
#include "PARSER_interface.h"
#include "BURNER_interface.h"
#include "NVIC_interface.h"
#include "CHECK_interface.h"

#include "INT_interface.h"
#include "INT_private.h"
#include "INT_config.h"

/* ==================================================================== */
/* ================= Public Functions Implementation ================== */
/* ==================================================================== */

// Function to initialize the module
void INT_init(void)
{
    // Initialize UART
    USART_init();

    // Initialize system timer
    STK_init();

    // Set the period that the bootloader will wait before jumbing to the application
    STK_setSingleInterval(JUMP_TIMEOUT,checkTime);

    // Data initialization of the module
    ResponseStatus = NOTACK;
    AddressToCall = 0;
    RecCounter = 0;
    JumpFlag = 0;
    FirstRecordFlag = 1;
}

// Task to be called periodicly to do the logic of the module
void INT_update(void)
{
    // ACTION1: Listen over uart and recieve data
	UartRecievedState_type RecStatus = USART_receiveCharacter( &(RecBuffer[RecCounter]) );
    // Check if there are recieved data or not
	if (RecStatus == RECEIVED_OK)
	{   
        // Stop timer
		STK_stopInterval();
        // Check if a full recored was recieved or not
		if(RecBuffer[RecCounter] == '\n')
		{
            // Send the recieved record to the PARSER Module
            PARSER_setRecord(RecBuffer);
            // Send a recieved record indication
            PARSER_indicateRecievedData();
        }
		else
		{
            // Increase the index counter of the data buffer
		    RecCounter++ ;
		}
        // Start timer stop timer
		STK_setSingleInterval(JUMP_TIMEOUT,checkTime);
	}

    // ACTION2: If the record was successfully flashed send ack message over UART
    if(ResponseStatus == ACK)
    {
        USART_transmitCharacter('C');
        RecCounter = 0;
        ResponseStatus = NOTACK;
    }
        
    // ACTION3: Jumb to application at specific condition
    if (JumpFlag == 1)
    {   
        JumpFlag = 0;
        RecCounter = 0;
        FirstRecordFlag = 1;
        jumpToApp();
    }
}

// Function to be called from the other modules to set OK event
void INT_sendAckStatus(ResponseStatus_type StatusValue)
{
    ResponseStatus = StatusValue;
}

/* ==================================================================== */
/* =============== Private Functions Definition ======================= */
/* ==================================================================== */

// Function to jump to the Application
void jumpToApp(void)
{   
    // Disable all interrupts and faults
	asm("CPSID i");
    asm("CPSID f");
    // Jump to application code
    AddressToCall = *(Function_type *)(JUMP_ADDRESS);      
    AddressToCall();
}

// Function to be called if timeout without recieving any thing over UART
void checkTime(void)
{
    JumpFlag = 1;
}
