/*	Filename: floor_controller.c
	Author: David Eelman
	Date: May 25, 2017
	Purpose: Header file for floor_controller.c
*/

// Includes
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "TA_Header_S2017.h"
#include "timer.h"
#include "CAN.h"

// Floor Controller Number
#define CONTROLLER_FLOOR  1

// Elevator CAN signal masks
#define ENABLE_BIT		0b00000100 // Third LSB for enable/disable
#define FLOOR_BITS 		0b00000011 // Lower 2 bits for floor number request
#define DOOR_STATUS_BIT 0b00000100 // Third LSB for door open/closed
#define NO_CALL_REQUEST 0b00000000 // Lowest bit indicates no elevator call request
#define CALL_REQUEST 	0b00000001 // Lowest bit indicates elevator call request
#define CAN_TX TC4 // Timer channel 4 will control CAN TX

// Bit patterns for floor LEDs & elevator call button + LED
#define FLOOR1_LED  0b00000001 // Port T0
#define FLOOR2_LED  0b00000010 // Port T1
#define FLOOR3_LED  0b00000100 // Port T2
#define CALL_LED	0b00001000 // Port T3
#define CALL_BUTTON	0b01000000 // Port T6

// Function Prototypes
unsigned char initFloorController(void);
unsigned char updateController(unsigned char floorNumber, unsigned char doorStatus);
unsigned char callElevator(void);