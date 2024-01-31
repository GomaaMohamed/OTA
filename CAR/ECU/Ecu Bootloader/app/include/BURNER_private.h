/*****************************************************************************
* @file:    BURNER_private.h
* @author:  Copyright (c) 2023 Gomaa Mohammed Gomaa.
* @license: GNU GPL version 3 or later.
*			This is free software: you are free to change and redistribute it.  
*			There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Fri, 20 Oct 2023 14:21:12 +0200
* @brief:   Bootloader for STM32F103
******************************************************************************/
#ifndef  _BURNER_PRIVATE_H
#define  _BURNER_PRIVATE_H
 
/* ==================================================================== */
/* =================== Private Variables and Macros =================== */
/* ==================================================================== */
/* Definition of private datatypes go here */
static u16 *DataToBeFlashed;
static u32 AddressOfData;
static u8 CountOfData;
static u8 FirstRecordFlag;

BurnerRequest_type BurnerRequestState;


/* ==================================================================== */
/* =================== Private Functions Declaration ================== */
/* ==================================================================== */

static u8 writeVerification(u32 Address, u8 HalfWordCount);

#endif
