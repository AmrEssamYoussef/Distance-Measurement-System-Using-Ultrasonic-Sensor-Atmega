/******************************************************************************
 *
 * Module: Ultrasonic
 *
 * File Name: Ultrasonic.c
 *
 * Description: Source file for the Ultrasonic
 *
 * Author: Amr Essam
 *
 ***
 ***/

#include "Ultrasonic.h"
#include "ICU.h"
#include "gpio.h"
#include <util/delay.h>

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

uint8  g_edgeCount = 0;
uint16 g_timeMeasured = 0;
uint16 g_Distance=0;


/* Structure of Type ICU_ConfigType to configure the ICU according to the
 * edge (RISING or FALLING) and the prescaler )
 */
ICU_ConfigType Icu_config ={RISING,F_CPU_8};


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/


void Ultrasonic_init(void)
{
	/*Configure and initialize the ICU */
	ICU_init(&Icu_config);

    /*Set the call back*/
	ICU_SetCallBackFunction(Ultrasonic_edgeProcessing);

	/*Setup the direction for the trigger pin as output pin through the GPIO driver*/
	GPIO_setupPinDirection(ULTRASONIC_TRIGGER_PORT, ULTRASONIC_TRIGGER_PIN ,PIN_OUTPUT);

}


void Ultrasonic_trigger(void)
{
	/* Send the trigger pulse to the ultrasonic*/
	GPIO_writePin(ULTRASONIC_TRIGGER_PORT,ULTRASONIC_TRIGGER_PIN , LOGIC_HIGH);

	/*Wait 10us*/
	_delay_us(10);

	/*Stop the trigger pulse*/
	GPIO_writePin(ULTRASONIC_TRIGGER_PORT,ULTRASONIC_TRIGGER_PIN , LOGIC_LOW);
}


uint16 Ultrasonic_readDistance(void)
{
	/* Send the trigger pulse*/
	Ultrasonic_trigger();

	/*To get the Distance*/
	g_Distance = g_timeMeasured / 58 ;

	return g_Distance;
}


void Ultrasonic_edgeProcessing(void)
{
	g_edgeCount++;
	if(g_edgeCount == 1)
	{
		/*Clear the Timer Counter Register and start
		 * from the beginning */
		ICU_clearTimerValue();

		/* Detect falling edge */
		ICU_setEdgeDetectionType(FALLING);
	}
	else if(g_edgeCount == 2)
	{
		/* Store the High time value */
		g_timeMeasured = ICU_getInputCaptureValue();

		/* Detect rising edge */
		ICU_setEdgeDetectionType(RISING);

		g_edgeCount = 0;
	}

}
