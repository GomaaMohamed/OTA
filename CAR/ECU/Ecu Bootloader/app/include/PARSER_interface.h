/*****************************************************************************
* @file:    PARSER_interface.h
* @author:  Copyright (c) 2023 Gomaa Mohammed Gomaa.
* @license: GNU GPL version 3 or later.
*			This is free software: you are free to change and redistribute it.  
*			There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Fri, 20 Oct 2023 14:21:12 +0200
* @brief:   Parser Module
******************************************************************************/
#ifndef  _PARSER_INTERFACE_H
#define  _PARSER_INTERFACE_H

/* ==================================================================== */
/* ====================Public Functions Declaration =================== */
/* ==================================================================== */

/**
 * @brief---------------------> Initialize parser module
 * @param---------------------> None
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Non-Reentrant       
 */
void PARSER_init(void);


/**
 * @brief---------------------> Set record address
 * @parameter1----------------> (Record) record to be parsed
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Non-Reentrant       
 */
void PARSER_setRecord(u8 *Record);

/**
 * @brief---------------------> Indicate that there is a record
 * @param---------------------> Nine
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Non-Reentrant       
 */
void PARSER_indicateRecievedData(void);

/**
 * @brief---------------------> Task to be called periodically to do the module logic
 * @param---------------------> None
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Non-Reentrant       
 */
void PARSER_update(void);

#endif

