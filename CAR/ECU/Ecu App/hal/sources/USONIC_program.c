/*****************************************************************************
* @file:    USONIC_program.c
* @author:  Copyright (c) 2023 Gomaa Mohammed.
* @license: GNU GPL version 3 or later.
*			This is free software: you are free to change and redistribute it.  
*			There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Wed, 18 Oct 2023 15:12:09 +0300
* @brief:   Ultrasonic Sensor Driver.
******************************************************************************/


/* ==================================================================== */
/* ========================== include files =========================== */
/* ==================================================================== */ 

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "GPTIM_interface.h"
#include "NVIC_interface.h"
#include "STK_interface.h"
#include "RCC_interface.h"

#include "USONIC_interface.h"
#include "USONIC_private.h"
#include "USONIC_config.h"

/* ==================================================================== */
/* ================= Public Functions Implementation ================== */
/* ==================================================================== */

// Function to initialize ultrasonic module
void USONIC_init(void)
{
    // Enable clocks
    RCC_enableClock(RCC_APB2, RCC_IOPA);
	RCC_enableClock(RCC_APB1, RCC_TIM2);

    // Initialize ultrasonic pins
    GPIO_setPinDirection(ULTRASONIC_TRIG_PORT, ULTRASONIC_TRIG_PIN, GPIO_OUTPUT_10MHZ_PP);
    GPIO_setPinDirection(ULTRASONIC_ECHO_PORT, ULTRASONIC_ECHO_PIN, GPIO_INPUT_FLOATING);

    // Set Timer Callback
    TIM2_setCaptureCompareCallback(CHANNEL1,UltraSonicCallback);

    // Enable timer
    TIM2_initChannel(CHANNEL1,
					 CH_INPUT_TI1,
					 CAPTURE_COMPARE_POL_0,
					 PRELOAD_DISABLE,
					 FAST_DISABLE);
	TIM2_init(INPUT_CAPTURE_MODE, COUNT_UP, 1);

    // Enable Global interrupt
    __enable_irq();


}

// Function to get distance
UltrasonicDistance_type USONIC_getDistance(u32 *Distance)
{
    UltrasonicDistance_type ReturnState = OUT_OF_RANGE_DISTANCE;

    // Reset Parameters
    TriggerFlag = 0;
    EchoFlag = 0;
    TriggerTimerValue = 0;
    EchoTimerValue = 0;
    
	// Set Edge of the timer
    TIM2_changeCaptureComparePolarity(CHANNEL1,CAPTURE_COMPARE_POL_0);

    // enable ICU interrupt
    NVIC_enableInterrupt(NVIC_TIM2);
    TIM2_enableCaptureCompareInterrupt(CHANNEL1);

    // Reload Timer
    TIM2_reloadTimerValue(0);
    TIM2_restartTimer();

    // Make a trigger
    makeTrigger();

    // wait until echo received
    STK_setBusyWait(50000);

    // Deactivate Timer
    NVIC_disableInterrupt(NVIC_TIM2);
    TIM2_disableCaptureCompareInterrupt(CHANNEL1);
    TIM2_stopTimer();

    // Get distance
    if ((TriggerFlag == 1) && (EchoFlag == 1))
    {
        u32 Time = (EchoTimerValue - TriggerTimerValue);
        *Distance = (Time/58);
        if (*Distance > 0 && *Distance <= 400)
        {
            ReturnState = VALID_DISTANCE;
        }
    }
    return ReturnState;
}

/* ==================================================================== */
/* ================ Private Functions Implementation ================== */
/* ==================================================================== */

// Function to generate a trigger
static void makeTrigger(void)
{
    GPIO_setPinValue(ULTRASONIC_TRIG_PORT, ULTRASONIC_TRIG_PIN, GPIO_HIGH);
    STK_setBusyWait(10);
    GPIO_setPinValue(ULTRASONIC_TRIG_PORT, ULTRASONIC_TRIG_PIN, GPIO_LOW);
}

// Logic as a callback
static void UltraSonicCallback(void)
{
    
    if (TriggerFlag == 0 && EchoFlag == 0)
    {
        TriggerTimerValue = TIM2_getCaptureCompareValue(CHANNEL1);
        TIM2_changeCaptureComparePolarity(CHANNEL1,CAPTURE_COMPARE_POL_1);
        TriggerFlag = 1;
    }
    else if (EchoFlag == 0 && TriggerFlag == 1)
    {
        EchoTimerValue = TIM2_getCaptureCompareValue(CHANNEL1);
        TIM2_changeCaptureComparePolarity(CHANNEL1,CAPTURE_COMPARE_POL_0);
        EchoFlag = 1;
    }
}
