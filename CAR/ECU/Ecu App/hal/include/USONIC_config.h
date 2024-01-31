/*****************************************************************************
* @file:    USONIC_config.h
* @author:  Copyright (c) 2023 Gomaa Mohammed.
* @license: GNU GPL version 3 or later.
*			This is free software: you are free to change and redistribute it.  
*			There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Wed, 18 Oct 2023 15:12:09 +0300
* @brief:   Ultrasonic Sensor Driver.
******************************************************************************/
#ifndef USONIC_CONFIG_H
#define USONIC_CONFIG_H

/* ==================================================================== */
/* =================== Configurations Selection ======================= */
/* ==================================================================== */

/* ULTRASONIC_TRIG_PORT Configuration */
#define ULTRASONIC_TRIG_PORT GPIOA
#define ULTRASONIC_TRIG_PIN  GPIO_PIN1

#define ULTRASONIC_ECHO_PORT GPIOA
#define ULTRASONIC_ECHO_PIN  GPIO_PIN0

/* Define CPU and Timer Parameters */
#define USONIC_CPU_F         1000000UL
#define USONIC_ICU_PRESCALER 1





#endif

