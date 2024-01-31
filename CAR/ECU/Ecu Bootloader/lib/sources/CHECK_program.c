/*****************************************************************************
* @file:    CHECK_program.c
* @author:  Copyright (c) 2023 Gomaa Mohammed Gomaa.
* @license: GNU GPL version 3 or later.
*			This is free software: you are free to change and redistribute it.  
*			There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Fri, 20 Oct 2023 14:21:12 +0200
* @brief:   Check Module
******************************************************************************/

/* ==================================================================== */
/* ========================== Include Files =========================== */
/* ==================================================================== */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "CHECK_interface.h"
#include "CHECK_private.h"
#include "CHECK_config.h"

/* ==================================================================== */
/* ================= Public Functions Implementation ================== */
/* ==================================================================== */

// Function to calculates length of a string
u8 stringLength(u8 String[]){
    // variable to hold the length
    u8 Length = 0;
    // loop on the string until reach the null charachter \0(end of the string)
    while (String[Length] != '\0')
    {   // increment the length
        Length++;
    }
    // return the length of the passed string
    return Length;
}

// Function to compare the simirarity of two strings
u8 stringCompare(u8 string1[],u8 string2[]){
    // Claculate the length of the two strings
    u8 Length1 = stringLength(string1);
    u8 Length2 = stringLength(string2);
    // Flag to check
    u8 CompareFlag = 0;
    // If the length of the two strings the same continue 
    if (Length1 == Length2)
    {
        // Loop on the two strings
        for (u8 i = 0; i < Length1; i++)
        {   // If all charachters of the two strings is identical compareFlag = 1
            if (string1[i]==string2[i])
            {
                CompareFlag = 1;
            }
            // Else if one of the charachters is not identical compareFlag = 0 and break
            else{
                CompareFlag = 0;
                break;
            }
        }
        
    }
    // Return the state of the two strings
    return CompareFlag;
}

// Function to convert any charchter and number in ascii to hexadecimal
u8 AsciToHex(u8 Asci)
{
    // Variable to hold the converted value
	u8 Result;
    // Check if it is a number from 0 to 9
	if ( (Asci >= 48) && (Asci <= 57) )
	{   // subtracte the offset of ascii
		Result = Asci - 48;
	}
    // Else if it is a character from A to Z
	else
	{   // subtracte the offset of ascii
		Result = Asci - 55;
	}
    // Return the converted value
	return Result;
}

// Function to check if the hex record is correct or not
u8 checkHex(u8 HexRecord[]){
    // Flag to hold the state
    u8 CheckFlag = 0;
    // Variable to hold the incremental value of the checksum
    u8  CheckSum = 0;
    // Apply the algorithm on the address and data records only
    if (HexRecord[8] == '0' || HexRecord[8] == '1' || HexRecord[8] == '4' || HexRecord[8] == '5')
    {
        // Calculate the length of the ihex record
        u8 Len1 = AsciToHex(HexRecord[1]);
        u8 Len0 = AsciToHex(HexRecord[2]);
        u8 Length = ((Len1 << 4) | (Len0))*2 + 0xB;
        // Take the incremental summation of all bytes of the ihex recors
        for (int i=1; i < Length-3; i+=2)
        {   // Adjust every two digits in one byte
            u8 Digit1 = AsciToHex(HexRecord[i]);
            u8 Digit0 = AsciToHex(HexRecord[i + 1]);
            u8 Temp = (Digit1 << 4) | (Digit0);
            CheckSum += Temp;
        }
        // Make the 2'nd complement on the summation
        CheckSum = (~CheckSum) + 1;
        // Extract the checksum from the ihex record
        u8 Digit1 = AsciToHex(HexRecord[Length-2]);
        u8 Digit0 = AsciToHex(HexRecord[Length-1]);
        u8 Temp = (Digit1 << 4) | (Digit0);
        // Compare the calculated checksum and the extrcated one
        if (CheckSum == Temp)
        {
            CheckFlag = 1;
        }
        }
        // return the state
        return CheckFlag;
}

// Function to convert any number to binary coded decimal form
void convertDecimalToBcd(u32 DecimalNumber,u8 BcdDigits[],u8 NumberOfDigits) 
{
    // Auxilary variables
    u32 Remainder;
    u8 i = 0;

    // put buffer = 0
    for (i = 0; i < NumberOfDigits; i++)
    {
        BcdDigits[i] = 0;
    }
    i = 0;
    // Convert
    while (DecimalNumber != 0)
    {
        Remainder = DecimalNumber % 10;
        BcdDigits[i] = Remainder;
        DecimalNumber /= 10;
        i++;
    }
}

// Function to convert any number to binary coded decimal form
void convertHexToAsci(u32 HexNumber,u8 AsciDigits[],u8 NumberOfDigits) 
{
    // Auxilary variables
    u32 Remainder;
    u8 i = 0;

    // put buffer = 0
    for (i = 0; i < NumberOfDigits; i++)
    {
        AsciDigits[i] = 0;
    }
    i = NumberOfDigits-1;
    // Convert
    while (HexNumber != 0)
    {
        Remainder = HexNumber % 0x10;
        AsciDigits[i] = Remainder;
        HexNumber /= 0x10;
        i--;
    }
    // put buffer = 0
    for (i = 0; i < NumberOfDigits; i++)
    {
        if (AsciDigits[i] >= 0 && AsciDigits[i] <= 9)
        {
            AsciDigits[i] += 48;
        }
        else
        {
            AsciDigits[i] += 55;
        }
    }
}






