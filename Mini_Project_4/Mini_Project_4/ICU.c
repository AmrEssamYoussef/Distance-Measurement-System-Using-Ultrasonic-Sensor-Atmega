/************************************************************************
 *  Module: ICU
 *
 *  File Name: ICU.c
 *
 *  Description: Source file for the AVR ICU driver
 *
 *  Author: Amr Essam
 *
 *
 ***********************************************************************/

#include "ICU.h"
#include "common_macros.h" /* To use the macros like SET_BIT */
#include <avr/io.h> /* To use ICU/Timer1 Registers */
#include <avr/interrupt.h> /* For ICU ISR */


/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;


/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

ISR(TIMER1_CAPT_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/*Will call the call back function*/
		(*g_callBackPtr)();
	}
}


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/


void ICU_init(const ICU_ConfigType * Config_Ptr)
{
	/* Configure ICP1/PD6 as i/p pin */
	CLEAR_BIT(ICU_PORT,ICU_PIN);

	SET_BIT(CONTROL_REGISTER_A,FOC1B);

	SET_BIT(CONTROL_REGISTER_A,FOC1A);

	/*
     * insert the required edge type in ICES1 bit in CONTROL_REGISTER_B Register
	 */
	CONTROL_REGISTER_B = (CONTROL_REGISTER_B & ~(1<<6)) | (Config_Ptr->edge<<6);

	/*
	 * insert the required clock value in the first three bits (CS10, CS11 and CS12)
	 * of CONTROL_REGISTER_B Register
	 */
    CONTROL_REGISTER_B = (CONTROL_REGISTER_B & ~(7)) | (Config_Ptr->clock);


    /* Initial Value for Timer1 */
	TIMER_COUNTER=0;

	/* Initial Value for the input capture register */
	INPUT_CAPTURE_REGISTER=0;

	/* Enable the Input Capture interrupt to generate an interrupt when edge is detected on ICP1/PD6 pin */
	SET_BIT(TIMER_INTERRUPT_MASK_REGISTER,TICIE1);
}


void ICU_setEdgeDetectionType(const ICU_EdgeType a_edgeType)
{
	/*
	 * insert the required edge type in ICES1 bit in CONTROL_REGISTER_B(TCCR1B) Register
	 */
	CONTROL_REGISTER_B = (CONTROL_REGISTER_B & ~(1<<6)) | (a_edgeType<<6);
}

void ICU_SetCallBackFunction(void (* a_callBackPtr) (void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr=a_callBackPtr;
}

uint16 ICU_getInputCaptureValue(void)
{
	return INPUT_CAPTURE_REGISTER;
}

void ICU_clearTimerValue(void)
{
	TIMER_COUNTER=0;
}

void ICU_DeInit(void)
{
	CONTROL_REGISTER_A=0;
	CONTROL_REGISTER_B=0;
	TIMER_COUNTER=0;
	INPUT_CAPTURE_REGISTER=0;
	CLEAR_BIT(TIMER_INTERRUPT_MASK_REGISTER,TICIE1);
}

