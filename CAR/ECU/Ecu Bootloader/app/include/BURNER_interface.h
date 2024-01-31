/*****************************************************************************
* @file:    BURNER_interface.h
* @author:  Copyright (c) 2023 Gomaa Mohammed Gomaa.
* @license: GNU GPL version 3 or later.
*			This is free software: you are free to change and redistribute it.  
*			There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Fri, 20 Oct 2023 14:21:12 +0200
* @brief:   Bootloader for STM32F103
******************************************************************************/
#ifndef  _BURNER_INTERFACE_H
#define  _BURNER_INTERFACE_H


/* ==================================================================== */
/* ====================== Public Data Types ========================== */
/* ==================================================================== */

/* Received Data data type*/
typedef enum
{
    IDLE_STATE=0,
    WRITE_REQUEST,
    ERASE_REQUEST,
    READ_REQUEST
} BurnerRequest_type;


/* ==================================================================== */
/* =================== Public Functions Declaration =================== */
/* ==================================================================== */

/**
 * @brief---------------------> Initialize burner module
 * @param---------------------> None
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Non-Reentrant       
 */
void BURNER_init(void);

/**
 * @brief---------------------> Send data to burner
 * @parameter1----------------> (Data) refrence to data
 * @parameter2----------------> (Address) address of data
 * @parameter3----------------> (Count) number of half words
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Non-Reentrant       
 */
void BURNER_sendData(u16 *Data, u32 Address, u8 Count);

/**
 * @brief---------------------> Indicate received data
 * @param---------------------> None
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Non-Reentrant       
 */
void BURNER_makeRequest(BurnerRequest_type BurnerRequest);

/**
 * @brief---------------------> Task to be called periodically to do the module logic
 * @param---------------------> None
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Non-Reentrant       
 */
void BURNER_update(void);

#endif

