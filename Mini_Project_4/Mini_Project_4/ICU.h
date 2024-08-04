 /******************************************************************************
 *
 * Module: ICU
 *
 * File Name: ICU.h
 *
 * Description: header file for the ICU
 *
 * Author: Amr Essam
 *
 *******************************************************************************/

#ifndef ICU_H_
#define ICU_H_

#include "std_types.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/


#define ICU_PORT PORTD
#define ICU_PIN  PD6
#define CONTROL_REGISTER_A TCCR1A
#define CONTROL_REGISTER_B TCCR1B
#define TIMER_INTERRUPT_MASK_REGISTER TIMSK
#define INPUT_CAPTURE_REGISTER ICR1
#define TIMER_COUNTER TCNT1

typedef enum {
	FALLING,RISING
}ICU_EdgeType;


typedef enum {
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024
}ICU_ClockSelect;


typedef struct {

	ICU_EdgeType edge;
	ICU_ClockSelect clock;
}ICU_ConfigType;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description : Function to initialize the ICU driver
 * 	1. Set the required clock.
 * 	2. Set the required edge detection.
 * 	3. Enable the Input Capture Interrupt.
 * 	4. Initialize Timer1 Registers
 */
void ICU_int(void);

/*
 * Description: Function to set the required edge detection.
 */
void ICU_setEdgeDetectionType(const ICU_EdgeType edgeType);

/*
 * Description: Function to set the Call Back function address.
 */
void ICU_SetCallBackFunction(void (* callBack_ptr) (void));

/*
 * Description: Function to get the Timer1 Value when the input is captured
 *              The value stored at Input Capture Register ICR1
 */
uint16 ICU_getInputCaptureValue(void);

/*
 * Description: Function to clear the Timer1 Value to start count from ZERO
 */
void ICU_clearTimerValue(void);

/*
 * Description: Function to disable the Timer1 to stop the ICU Driver
 */
void ICU_DeInit(void);


#endif
