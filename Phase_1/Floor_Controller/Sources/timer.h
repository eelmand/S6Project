/*	Filename: timer.h
	Author: David Eelman
	Date: May 19, 2017
	Purpose: Header file for timer.c
*/

// Timer configuration parameters
#define TSCR1_INIT 0b10000000	// Turn on timer module
#define TSCR2_INIT 0b10000110	// Set pre-scaler to 6 for 

// Function prototypes
void configureTimer(void);