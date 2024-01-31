/*****************************************************************************
* @file:    USONIC_private.h
* @author:  Copyright (c) 2023 Gomaa Mohammed.
* @license: GNU GPL version 3 or later.
*			This is free software: you are free to change and redistribute it.  
*			There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Wed, 18 Oct 2023 15:12:09 +0300
* @brief:   Ultrasonic Sensor Driver.
*************************************************************************/
#ifndef USONIC_PRIVATE_H
#define USONIC_PRIVATE_H

/* ==================================================================== */
/* =================== Private Variables and Macros =================== */
/* ==================================================================== */

u32 TriggerTimerValue;
u32 EchoTimerValue;

u8 TriggerFlag;
u8 EchoFlag;

/* ==================================================================== */
/* ==================== Private Functions Declaration ================= */
/* ==================================================================== */

static void makeTrigger(void);
static void UltraSonicCallback(void);

#endif

