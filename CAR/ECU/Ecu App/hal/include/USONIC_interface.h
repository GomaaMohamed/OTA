/*****************************************************************************
* @file:    USONIC_interface.h
* @author:  Copyright (c) 2023 Gomaa Mohammed.
* @license: GNU GPL version 3 or later.
*			This is free software: you are free to change and redistribute it.  
*			There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Wed, 18 Oct 2023 15:12:09 +0300
* @brief:   Ultrasonic Sensor Driver.
******************************************************************************/
#ifndef USONIC_INTERFACE_H
#define USONIC_INTERFACE_H

/* ==================================================================== */
/* ======================= Public Data Types ========================== */
/* ==================================================================== */

typedef enum
{
    VALID_DISTANCE=1,
    OUT_OF_RANGE_DISTANCE=0
}UltrasonicDistance_type;

/* ==================================================================== */
/* ==================== Public Functions Declaration ================== */
/* ==================================================================== */

/**
 * @brief---------------------> Initialize ultrasonic module 
 * @param---------------------> None
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant
 */
void USONIC_init(void);

/**
 * @brief---------------------> Get distance from object 
 * @param---------------------> Distance
 * @return--------------------> Distance state
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant
 */
UltrasonicDistance_type USONIC_getDistance(u32 *Distance);



#endif

