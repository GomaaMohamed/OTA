/*****************************************************************************
* @file:    BURNER_program.c
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

#include "FPEC_interface.h"
#include "INT_interface.h"

#include "BURNER_interface.h"
#include "BURNER_private.h"
#include "BURNER_config.h"

/* ==================================================================== */
/* ================= Public Functions Implementation ================== */
/* ==================================================================== */

// Function to initialize the module
void BURNER_init(void)
{
    DataToBeFlashed = NULL;
    AddressOfData = APP_SART_ADDRESS;
    CountOfData = 0;
    BurnerRequestState = IDLE_STATE;
    FirstRecordFlag = 1;
}

// Function to be called from the other modules to send the data that will be flashed
void BURNER_sendData(u16 *Data,u32 Address,u8 Count)
{
    DataToBeFlashed = Data;
    AddressOfData = Address;
    CountOfData = Count;
}

// Function to be called from the other modules to set the event of the recieved data
void BURNER_makeRequest(BurnerRequest_type BurnerRequest)
{
    BurnerRequestState = BurnerRequest;
}

// Task to be called periodicly to do the logic of the module
void BURNER_update(void)
{
    // Check the recieved record event
    if (BurnerRequestState == WRITE_REQUEST)
    {
        // Check if the recived record is the first record or not
        if (FirstRecordFlag == 1)
        {
            // Erase Application Area
            FPEC_eraseNumberOfPages(APP_START_PAGE,APP_NUMBER_OF_PAGES);
            // Reset first record flag
            FirstRecordFlag = 0;
        }
        // Flash the recieved data
        FPEC_writeFlash(AddressOfData,DataToBeFlashed,CountOfData);
        // Verify the flashed data
        u8 Verify = writeVerification(AddressOfData,CountOfData);
        while(Verify != 1)
        {
            FPEC_writeFlash(AddressOfData,DataToBeFlashed,CountOfData);
            Verify = writeVerification(AddressOfData,CountOfData);
        }
        // Send an Ack event to INTERFACE Module 
        INT_sendAckStatus(ACK);
        // Reset the recieved data event
        BurnerRequestState = IDLE_STATE;
    }
    else if (BurnerRequestState == ERASE_REQUEST)
    {
        // Erase Application Area
        FPEC_eraseNumberOfPages(APP_START_PAGE,APP_NUMBER_OF_PAGES);
        // Reset the recieved data event
        BurnerRequestState = IDLE_STATE;
    }
    
}

/* ==================================================================== */
/* =============== private functions definition ======================= */
/* ==================================================================== */

// Function to read the flashed data and verify it 
static u8 writeVerification(u32 Address,u8 HalfWordCount)
{
    // Variable to hold the state 
    u8 WriteVerificationFlag = 0;
    // Loop on all the flashed half words
    for (u8 i = 0; i < HalfWordCount; i++)
    {   // Check the equality with the actual data
        if (*(((u16*)Address)+i)==DataToBeFlashed[i])
        {  
            // Set write verification flag
            WriteVerificationFlag = 1;
        }
        else{
            // Reset write verification flag
            WriteVerificationFlag = 0;
            break;
        }
    }
    // Return write verification flag
    return WriteVerificationFlag;
}
