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
#include "CAN.h"
#include "timer.h"
#include "FIFO.h"

// Global variables
unsigned char txbuff[1] = {0x00};

//**************************************************************
// main()
//**************************************************************
void main(void) {
	unsigned char * message;
	unsigned char floorNumber;
	link pTemp = NULL;
	
  	if(CONTROLLER_FLOOR == 1){
		configureCAN(FLOOR_CONTROLLER_1);
	}
	else if(CONTROLLER_FLOOR == 2){
		configureCAN(FLOOR_CONTROLLER_2);
	}
	else if(CONTROLLER_FLOOR == 3){
		configureCAN(FLOOR_CONTROLLER_3);
	}
		  
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
			pTemp = DeQueue();  // Grab a message from the Queue
      		
			message = pTemp->Data.DATA; // Get a pointer to the data of the message

			if((*message & 0x04) != 0){ // Determine if elevator status enabled
				floorNumber = (*message & 0x03); // Collect the floor position reported by elevator controller
				// Check if the current floor is the one this controller is on
	      updateFloorLed(floorNumber); // Update LEDs 
	      if (floorNumber == CONTROLLER_FLOOR){
		      txbuff[0] = 0x00; // No longer need to request car
		      CLEAR_BITS(PTT, CALL_LED);
	      }	
			}
			else{
				// What behaviour should we have when the elevator is disabled? Thinking flashing LEDs
			}

			free(pTemp->Data.DATA); // Free the memory malloc'd for data
			free(pTemp);            // Free the memory malloc'd for the node structure				   
		}
		
		if((PTIT & CALL_BUTTON) == 0){ // If the elevator call button pressed
			SET_BITS(PTT, CALL_LED); // Turn on elevator call LED
			txbuff[0] = 0x01; // Request car
		}		
	}
}

//**************************************************************
//    TX_CAN()
// Interrupt handler for transmitting CAN status message
//**************************************************************
interrupt VectorNumber_Vtimovf void TX_CAN(void){	
	if(CONTROLLER_FLOOR == 1){
	  TxCAN(ST_ID_201, 0x00, sizeof(txbuff), txbuff);
	}
	else if(CONTROLLER_FLOOR == 2){
	  TxCAN(ST_ID_202, 0x00, sizeof(txbuff), txbuff);
	}
	else if(CONTROLLER_FLOOR == 3){
	  TxCAN(ST_ID_203, 0x00, sizeof(txbuff), txbuff); 
	}
	TFLG2 = TOF_CLR;
	TOGGLE_LEDS;
}