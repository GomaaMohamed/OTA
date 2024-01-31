/*****************************************************************************
* @file:    INT_private.h
* @author:  Copyright (c) 2023 Gomaa Mohammed Gomaa.
* @license: GNU GPL version 3 or later.
*			This is free software: you are free to change and redistribute it.  
*			There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Fri, 20 Oct 2023 14:21:12 +0200
* @brief:   Bootloader for STM32F103
******************************************************************************/
#ifndef _INT_PRIVATE_H
#define _INT_PRIVATE_H

/* ==================================================================== */
/* ====================== Private Data Types ========================== */
/* ==================================================================== */

/* Pointr to function data type */
typedef void (*Function_type)(void);

/* ==================================================================== */
/* =================== Private Variables and Macros =================== */
/* ==================================================================== */

static volatile ResponseStatus_type ResponseStatus ;
Function_type AddressToCall;
volatile u8  RecCounter;
volatile u8 JumpFlag;
static u8 FirstRecordFlag;
u8 RecBuffer[100];

/* ==================================================================== */
/* ==================== Pivate Functions Declaration ================== */
/* ==================================================================== */

/* Private Functions Prototypes go here */
void jumpToApp(void);
void checkTime(void);

#endif

