/*****************************************************************************
* @file:    PARSER_private.h
* @author:  Copyright (c) 2023 Gomaa Mohammed Gomaa.
* @license: GNU GPL version 3 or later.
*			This is free software: you are free to change and redistribute it.  
*			There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Fri, 20 Oct 2023 14:21:12 +0200
* @brief:   Parser Module
******************************************************************************/
#ifndef  _PARSER_PRIVATE_H
#define  _PARSER_PRIVATE_H
 
/* ==================================================================== */
/* ======================= Private Data Types ========================= */
/* ==================================================================== */

/* Received Status data type */
typedef enum
{
    UNRECIEVED=0,
    RECIEVED
} ReceivedStatus_type;

/* ==================================================================== */
/* =================== Private Variables and Macros =================== */
/* ==================================================================== */

ReceivedStatus_type ReceivedDataIndication = UNRECIEVED;
u8 *DataBuffer = NULL;
static u16 ParsedData[100] = {0};
static u8 DataCount = 0;
static u32 Address = 0x08000000;
static u8 DataAddressFlag;

/* ==================================================================== */
/* =================== Private Functions Declaration ================== */
/* ==================================================================== */

static void parseRecord(u8 *BufData);
static void parseUpperAddress(u8 *BufData);
static void parseData(u8 *BufData);

#endif

