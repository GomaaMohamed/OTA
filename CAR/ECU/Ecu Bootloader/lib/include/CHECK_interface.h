/*****************************************************************************
* @file:    CHECK_interface.h
* @author:  Copyright (c) 2023 Gomaa Mohammed Gomaa.
* @license: GNU GPL version 3 or later.
*			This is free software: you are free to change and redistribute it.  
*			There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Fri, 20 Oct 2023 14:21:12 +0200
* @brief:   Check Module
******************************************************************************/
#ifndef  _CHECK_INTERFACE_H
#define  _CHECK_INTERFACE_H
 

/* ==================================================================== */
/* =================== Public Function Declaration ==================== */
/* ==================================================================== */

/**
 * @brief---------------------> Calculates length(number of charachters) of a string
 * @parameter1----------------> (String) the string that its length will be calculated
 * @return--------------------> String length
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant       
 */
u8 stringLength(u8 string[]);

/**
 * @brief---------------------> Compare the simirity of two strings
 * @parameter1----------------> (String1) the first string that will be compared
 * @parameter2----------------> (String2) the second string that will be compared
 * @return--------------------> 1 if the two strings are similar and 0 if not
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant       
 */
u8 stringCompare(u8 string1[], u8 string2[]);

/**
 * @brief---------------------> Convert any digit from asci code to a hex number
 * @parameter1----------------> (Asci) the digit that will be converted
 * @return--------------------> the converted digit in the form of hexadecimal
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant       
 */
u8 AsciToHex(u8 Asci);

/**
 * @brief---------------------> Apply the CRC check on any recod in form of ihex and check it
 * @parameter1----------------> (HexRecord) the ihex record that will be checked
 * @return--------------------> 1 if the record is correct else it return 0
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant       
 */
u8 checkHex(u8 HexRecord[]);

/**
 * @brief---------------------> Convert any decimal number to BCD form
 * @parameter1----------------> (DecimalNumber) the number that will be converted
 * @parameter2----------------> (BcdDigits) buffer to hold the converted number
 * @parameter3----------------> (NumberOfDidits) number of digits of the converted number
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant       
 */
void convertDecimalToBcd(u32 DecimalNumber, u8 BcdDigits[],u8 NumberOfDigits);

/**
 * @brief---------------------> Convert any hex number to Asci form
 * @parameter1----------------> (HexNumber) the number that will be converted
 * @parameter2----------------> (AsciDigits) buffer to hold the converted number
 * @parameter3----------------> (NumberOfDidits) number of digits of the converted number
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant       
 */
void convertHexToAsci(u32 HexNumber, u8 AsciDigits[],u8 NumberOfDigits);

#endif

