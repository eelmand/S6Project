/*	Filename: car_controller.h
	Author: Stanislav Rashevskyi 
	Based of David Eelman's Floor Controller code
	Date: May 23, 2017
	Purpose: Header file for car_controller.c
*/

// Includes
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "timer.h"
#include "CAN.h"

// Bit patterns for floor LEDs, floor buttons, car open and close door buttons + 2 LEDs
#define FLOOR3_LED  0b00000001 // Port A0
#define FLOOR2_LED  0b00000010 // Port A1
#define FLOOR1_LED  0b00000100 // Port A2

#define FLOOR3_BUTTON 0b00001000 // Port P3
#define FLOOR2_BUTTON 0b00010000 // Port P4
#define FLOOR1_BUTTON 0b00100000 // Port P5

#define OPEN_LED	0b01000000 // Port A6
#define CLOSE_LED	0b10000000 // Port A7

#define OPEN_BUTTON	 0b01000000 // built-in SW1 (Port J6)
#define CLOSE_BUTTON 0b10000000 // built-in SW2 (Port J7)


// Configure PS2 and PS3 as outputs to drive LEDs on my board
#define OPEN_LED_ON (SET_BITS(PTS, LED1))
#define LED2_ON (SET_BITS(PTS, LED2))
#define LED1_OFF (CLEAR_BITS(PTS, LED1))
#define LED2_OFF (CLEAR_BITS(PTS, LED2))


// Elevator CAN signal masks
#define ENABLE_BIT		0b00000100 // Third LSB for enable/disable
#define FLOOR_BITS 		0b00000011 // Lower 2 bits for floor number request
#define DOOR_STATUS_BIT 0b00000100 // Third LSB for door open/closed
#define CAN_TX TC4 // Timer channel 4 will control CAN TX


// Function Prototypes
unsigned char initCarController(void);
unsigned char updateFloorLed(unsigned char floorNumber);
unsigned char updateDoorLed(unsigned char doorStatus);
//unsigned char updateController(unsigned char floorNumber, unsigned char new_floorNumber, unsigned char doorStatus);
unsigned char updateController(void);
void startDoorTimer(void);