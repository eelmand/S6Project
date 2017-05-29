/*	Filename: main.c
	Author: David Eelman
	Date: May 17, 2017
	Purpose: Testing of floor controller
*/

// Includes
#include <stdlib.h>
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "floor_controller.h"
#include "TA_Header_S2017.h"  /* my macros and constants */
#include "timer.h"
#include "FIFO.h"

//**************************************************************
// main()
//**************************************************************
void main(void) {
	unsigned char floorNumber = 0;
	unsigned char doorStatus = 1;
	unsigned long nodeID;
	link message = NULL;
	
	// Based on the floor this controller is at, set appropriate filters
  	if(CONTROLLER_FLOOR == 1){
		configureCAN(FLOOR_CONTROLLER_1);
	}
	else if(CONTROLLER_FLOOR == 2){
		configureCAN(FLOOR_CONTROLLER_2);
	}
	else if(CONTROLLER_FLOOR == 3){
		configureCAN(FLOOR_CONTROLLER_3);
	}
	
	// Setup functions	  
	configureTimer();
	CONFIGURE_LEDS;
	InitQueue();
	initFloorController();
	LED1_ON;
	LED2_OFF;

	while (!(CANCTL0&CAN_SYNC));  // Wait for MSCAN to synchronize with the CAN bus
	SET_BITS(CANRFLG, 0xC3);      // Enable CAN Rx Interrupts
	SET_BITS(CANRIER, 0x01);      // Clear CAN Rx flag

	EnableInterrupts;
	
	for (;;) {
		if(IsQueueEmpty()) 
		{
			// Do nothing
		} 
		else 
		{
			message = DeQueue(); // Grab a message from the Queue
      		nodeID = message->Data.ID; // Get the Node ID of the sender
      		if(nodeID == CAR_CONTROLLER){
      			doorStatus = message->Data.ID & DOOR_STATUS_BIT;
      		}
      		else if(nodeID == ELEVATOR_CONTROLLER){
      			floorNumber = *(message->Data.DATA) & FLOOR_BITS; // Process floor status
				updateController(floorNumber, doorStatus);
      		}
			free(message->Data.DATA); // Free the memory malloc'd for data
			free(message);            // Free the memory malloc'd for the node structure				   
		}
		if((PTIT & CALL_BUTTON) == 0){ // If the elevator call button pressed
			callElevator();
		}		
	}
}