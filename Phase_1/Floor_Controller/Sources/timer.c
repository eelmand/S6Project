/*	Filename: timer.h
	Author: David Eelman
	Date: May 19, 2017
	Purpose: Sets up the timer module for use by the floor controller
*/

#include <hidef.h>  //common defines and macros
#include "derivative.h" // derivative-specific definitions
#include "timer.h"

//**************************************************************
//                 configureTimer(void)
// Configures the timer module with parameters for PWM operation
//**************************************************************   
void configureTimer(void) {
	TSCR1 = TSCR1_INIT; // Turn on timer module
	TSCR2 = TSCR2_INIT; // Set pre-scaler to 6 for a Timer Overflow of 524 ms (1/(8MHz clock / 64 prescaler) * 2^16 counts)
	TFLG2 = TOF_CLR; // Clear the Timer Overflow Flag
}
