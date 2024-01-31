/*****************************************************************************
* @file:    INT_interface.h
* @author:  Copyright (c) 2023 Gomaa Mohammed Gomaa.
* @license: GNU GPL version 3 or later.
*			This is free software: you are free to change and redistribute it.  
*			There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Fri, 20 Oct 2023 14:21:12 +0200
* @brief:   Bootloader for STM32F103
******************************************************************************/
#ifndef _INT_INTERFACE_H
#define _INT_INTERFACE_H

/* ==================================================================== */
/* ======================= Public Data Types ========================== */
/* ==================================================================== */

/* Response Statuse data type */
typedef enum
{
    NOTACK=0,
    ACK
} ResponseStatus_type;

/* ==================================================================== */
/* ==================== Public Functions Declaration ================== */
/* ==================================================================== */

/**
 * @brief---------------------> Initialize interface module
 * @param---------------------> None
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Non-Reentrant       
 */
void INT_init(void);

/**
 * @brief---------------------> Task to be called periodically to do the module logic
 * @param---------------------> None
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Non-Reentrant       
 */
void INT_update(void);

/**
 * @brief---------------------> Set response status to be sent to host
 * @parameter1----------------> (ResponseStatus) response status to be sent
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Non-Reentrant       
 */
void INT_sendAckStatus(ResponseStatus_type ResponseStatus);

#endif

