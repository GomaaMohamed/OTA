/*****************************************************************************
* @file:    PARSER_program.c
* @author:  Copyright (c) 2023 Gomaa Mohammed Gomaa.
* @license: GNU GPL version 3 or later.
*			This is free software: you are free to change and redistribute it.  
*			There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Fri, 20 Oct 2023 14:21:12 +0200
* @brief:   Parser Module
******************************************************************************/

/* ==================================================================== */
/* ========================== Include Files =========================== */
/* ==================================================================== */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "CHECK_interface.h"

#include "PARSER_interface.h"
#include "PARSER_private.h"
#include "PARSER_config.h"

#include "BURNER_interface.h"
#include "INT_interface.h"

/* ==================================================================== */
/* ================= Public Functions Implementation ================== */
/* ==================================================================== */

// Function to initialize the module
void PARSER_init(void)
{
    // Data initialization of the module
    ReceivedDataIndication = UNRECIEVED;
    DataBuffer =NULL;
    DataCount = 0;
    Address = 0x08000000;
	DataAddressFlag = 0;
}

// Function to be called from the other modules to send the data that will be parsed
void PARSER_setRecord(u8 *Record)
{
    DataBuffer = Record;
}

// Function to be called from the other modules to set the event of the recieved data
void PARSER_indicateRecievedData(void)
{
    ReceivedDataIndication = RECIEVED;
}

// Task to be called periodicly to do the logic of the module
void PARSER_update(void)
{
	// Check that there is a record must be parsed
    if (ReceivedDataIndication == RECIEVED)
    {
        // check the Record
		u8 CheckSum = checkHex(DataBuffer);
		if (CheckSum == 1)
		{
			// Analyse the Record
			parseRecord(DataBuffer);
       		if (DataAddressFlag == 1)
       	    {
        		// Send the Data Record to Burner to flash it
        		BURNER_sendData(ParsedData,Address,DataCount);
        		// indicate the burner with the record
				BURNER_makeRequest(WRITE_REQUEST);
				DataAddressFlag = 0;
			}
			else
			{
				// Send Ack
				INT_sendAckStatus(ACK);
			}
			
		}
		
		// set the UNRECIEVED state
        ReceivedDataIndication = UNRECIEVED;
    }
    
}

/* ==================================================================== */
/* =============== Private Functions Implementation =================== */
/* ==================================================================== */

// Function to parse the data record(remove the extra data and set the endianess)
static void parseData(u8* BufData)
{
	// Auxilary variables
	u8 DigitLow,DigitHigh,CC,i;
	u8 DataDigit0,DataDigit1,DataDigit2,DataDigit3;
	u8 DataCounter = 0;
	// Get character count 
	DigitHigh = AsciToHex (BufData[1]);
	DigitLow  = AsciToHex (BufData[2]);
	CC        = (DigitHigh<<4) | DigitLow ;
	// Get the address 
	DataDigit0 = AsciToHex (BufData[3]);
	DataDigit1 = AsciToHex (BufData[4]);
	DataDigit2 = AsciToHex (BufData[5]);
	DataDigit3 = AsciToHex (BufData[6]);
	// Clear low part of address 
	Address = Address & 0xFFFF0000;
	// Set low part
	Address = Address | (DataDigit3) | (DataDigit2 << 4) | (DataDigit1 << 8) | (DataDigit0<<12);
    // Loop on all the recieved data, set the endianess and store it in a new buffer 
	for (i=0;i<CC/2; i++)
	{  
		// Get current data
		DataDigit0 = AsciToHex (BufData[4*i+9 ]);
		DataDigit1 = AsciToHex (BufData[4*i+10]);
		DataDigit2 = AsciToHex (BufData[4*i+11]);
		DataDigit3 = AsciToHex (BufData[4*i+12]);
	    // Set the endianess and store the data
		ParsedData[DataCounter] = (DataDigit3 << 8) | (DataDigit2 << 12) | (DataDigit1) | (DataDigit0<<4);
		DataCounter++;
	}
	// Set the number of half words
	DataCount = CC/2;
}

// Function to parse the address record
static void parseUpperAddress(u8* BufData)
{
	// Auxilary variables
	u8 DataDigit0,DataDigit1,DataDigit2,DataDigit3;
	// Get address 
	DataDigit0 = AsciToHex (BufData[9]);
	DataDigit1 = AsciToHex (BufData[10]);
	DataDigit2 = AsciToHex (BufData[11]);
	DataDigit3 = AsciToHex (BufData[12]);
	// Clear high part of address 
	Address = Address & (u32)0x0000FFFF;
	// Set the address
	Address = Address | (u32)((u32)(DataDigit0 << 28) | (u32)(DataDigit1 << 24) | (u32)(DataDigit2 << 20) | (u32)(DataDigit3 << 16));
}

// Function to parse the record based on its type
static void parseRecord(u8* BufData)
{
	switch (BufData[8])
	{
	case '0': 
        parseData(BufData);
        DataAddressFlag = 1;
        break;
    case '4': 
        parseUpperAddress(BufData);
    	DataAddressFlag = 0;
    	break;
    }
}







