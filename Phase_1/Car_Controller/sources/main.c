                                                                 /*	Filename: main.c
	Author: Stanislav Rashevskyi
	Date: May 23, 2017
	Purpose: Testing of car controller
*/

// Includes
#include <stdlib.h>
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "car_controller.h"
#include "TA_Header_S2017.h"  /* my macros and constants */
#include "CAN.h"
//#include "timer.h"
#include "FIFO.h"

// Global variables
unsigned char floorNumber=0;
unsigned char new_floorNumber=0; // no change floor requests by default

unsigned char doorStatus = 1;   // door is closed by default


//**************************************************************
// main()
//**************************************************************
void main(void) {

	link message = NULL;
	link pTemp = NULL;
	unsigned long nodeID;



	/* Setup functions */
  configureCAN(CAR_CONTROLLER);
  //configureTimer();
  CONFIGURE_LEDS;
  InitQueue();
	initCarController();
		
  LED1_ON;
	LED2_OFF;
	
	while (!(CANCTL0&CAN_SYNC));  // Wait for MSCAN to synchronize with the CAN bus
	SET_BITS(CANRFLG, 0xC3);      // Enable CAN Rx Interrupts
	SET_BITS(CANRIER, 0x01);      // Clear CAN Rx flag
	
	
	EnableInterrupts;


for(;;) {
  
    if(IsQueueEmpty()) {
      updateFloorLed(floorNumber);
    	updateDoorLed(doorStatus);
      
    }
    else 
  	{
  	  message = DeQueue(); // Grab a message from the Queue
      nodeID = message->Data.ID; // Get the Node ID of the sender
      		
      if(nodeID == ELEVATOR_CONTROLLER){
  			floorNumber = *(message->Data.DATA) & FLOOR_BITS; // Process floor status
  	    updateController(floorNumber, new_floorNumber, doorStatus);
      }                               
      	    	
  		free(message->Data.DATA); // Free the memory malloc'd for data
  		free(message);            // Free the memory malloc'd for the node structure				   
  	}
	                                                                       
  } /* loop forever */
  
}


//**************************************************************
//ISR for elevator in-car floor requests 
interrupt VectorNumber_Vportp void CALL_FLOOR_ISR(void)
{


  if (new_floorNumber == 0) {
      // we havent selected a floor to go to yet

    	if((PIFP & FLOOR1_BUTTON) == FLOOR1_BUTTON){
    	  	new_floorNumber=1;
    	  	SET_BITS(PIFP, FLOOR1_BUTTON);
    	}
    	else if((PIFP & FLOOR2_BUTTON) == FLOOR2_BUTTON){
    	  	new_floorNumber=2;
    	  	SET_BITS(PIFP, FLOOR2_BUTTON);
    	}
    	else if((PIFP & FLOOR3_BUTTON) == FLOOR3_BUTTON){
    	  	new_floorNumber=3;
    	  	SET_BITS(PIFP, FLOOR3_BUTTON);
    	}

      // check if we requested a different floor from where we are now
    	if(new_floorNumber == floorNumber) 
    	new_floorNumber=0;      // we are already there!
  } 
  else {      
    // we have already selected a floor 
    // clear any intr flags to prevent queued requests
      SET_BITS(PIFP, (FLOOR1_BUTTON|FLOOR2_BUTTON|FLOOR3_BUTTON));    
  
  }
	
	TOGGLE_LEDS;
}

//**************************************************************
//ISR for elevator in-car door open/close requests 
interrupt VectorNumber_Vportj void DOOR_ISR(void)
{
  
  if ((new_floorNumber != 0) && (doorStatus == 1)) {
    // we are moving, cant manage the doors
    
    // clear any intr flags to prevent queued requests
    SET_BITS(PIFJ, (CLOSE_BUTTON|OPEN_BUTTON));

  }
  else {
  
  // you can manage the doors

  	if((PIFJ & CLOSE_BUTTON) == CLOSE_BUTTON){
  	  	doorStatus=1;
  	  	SET_BITS(PIFJ, CLOSE_BUTTON);
  	}
  	else if((PIFJ & OPEN_BUTTON) == OPEN_BUTTON){
  	  	doorStatus=0;
  	  	SET_BITS(PIFJ, OPEN_BUTTON);
  	}

	TOGGLE_LEDS;
	
  }
}
