/**
 ===================================================================================================
 Name        : Mini Project 4

 Author      : Amr Essam

 Description : measure the distance using ultrasonic sensor

 Date        : 18/10/2022
 ===================================================================================================
 **/



#include "lcd.h"           /*include the header file of the LCD*/
#include "Ultrasonic.h"    /*include the header file of the UltraSonic Sensor*/
#include <avr/io.h>        /*AVR Library To use the SREG register */
#include <util/delay.h>    /*Delay Library To use Delay Functions */


int main()
{
	/* Variable to store the measured distance*/
	uint16 measuredDistance = 0;

	/* Enable Global Interrupt I-Bit */
	SREG |= (1<<7);

	/* Initialize LCD*/
	LCD_init();

	/*Initialize Ultrasonic*/
	Ultrasonic_init();

	/*Diplay "Distance=    cm" on the LCD */
	LCD_displayString("Distance=     cm");

	/*Infinite loop*/
	while(1)
	{
		measuredDistance = Ultrasonic_readDistance();

		/*move the cursor to the specified place
		 * to display the measured distance*/
		LCD_moveCursor(0,10);

		/* display the Measured distance on the LCD*/
		LCD_intgerToString(measuredDistance+1);


		/*if the distance was three char and then
		 * it is less than 100 the third digit will
		 * not be cleared so this case is handled by
		 * displaying a space after the measued distance*/
		if (measuredDistance<100)
		{
			LCD_displayCharacter(' ');
		}

		_delay_ms(100);
	}

}
