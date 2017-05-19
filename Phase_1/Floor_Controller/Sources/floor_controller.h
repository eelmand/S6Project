/*	Filename: floor_controller.c
	Author: David Eelman
	Date: May 19, 2017
	Purpose: Header file for floor_controller.c
*/

// Includes
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

// Floor Controller Number
#define CONTROLLER_FLOOR  1

// Bit patterns for floor LEDs & elevator call button + LED
#define FLOOR1_LED  0b00000001 // Port T0
#define FLOOR2_LED  0b00000010 // Port T1
#define FLOOR3_LED  0b00000100 // Port T2
#define CALL_LED	0b00001000 // Port T3
#define CALL_BUTTON	0b10000000 // Port T7

// Function Prototypes
unsigned char initFloorController(void);
unsigned char updateFloorLed(unsigned char floorNumber);