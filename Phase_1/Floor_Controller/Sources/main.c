/*	Filename: main.c
	Author: David Eelman
	Date: May 17, 2017
	Purpose: Testing of floor controller
*/

#include <stdlib.h>
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "floor_controller.h"
#include "TA_Header_S2017.h"  /* my macros and constants */
#include "CAN.h"
#include "timer.h"
#include "FIFO.h"

//******************************************************************************
// main()
//******************************************************************************
void main(void) {
	unsigned char txbuff[2] = {0x00};
	unsigned char * message;
	unsigned char floorNumber;
	link pTemp = NULL;
	
	configureCAN();
	configureTimer();
	CONFIGURE_LEDS;
	InitQueue();
	init_floor_controller();
	LED1_ON;
	LED2_OFF;

	while (!(CANCTL0&CAN_SYNC));  // Wait for MSCAN to synchronize with the CAN bus
	SET_BITS(CANRFLG, 0xC3);      // Enable CAN Rx Interrupts
	SET_BITS(CANRIER, 0x01);      // Clear CAN Rx flag

	EnableInterrupts;

	for (;;) {
		TxCAN(ST_ID_100, 0x00, sizeof(txbuff)-1, txbuff);
		msDelay(250);
		
		if(IsQueueEmpty()) 
		{
			// Do nothing
		} 
		else 
		{
			pTemp = DeQueue();  // Grab a message from the Queue
      		
			message = pTemp->Data.DATA;

			if((*message & 0x04) != 0){ // Elevator Status
				floorNumber = (*message & 0x03); // Elevator Floor Position
				update_floor_led(floorNumber);
			}
			else{
				// What behaviour should we have when the elevator is disabled? Thinking flashing LEDs
			}

			free(pTemp->Data.DATA); // Free the memory malloc'd for data
			free(pTemp);            // Free the memory malloc'd for the node structure				   
		}
		
		if((PTIT & CALL_BUTTON) == 0){ // If the elevator call button pressed
			call_elevator();
			txbuff[0] = 0x01; // Request car
		}		
		TOGGLE_LEDS;
	}
}

