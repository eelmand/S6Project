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
#include "timer.h"
#include "FIFO.h"

// Global variables
unsigned char txbuff[1] = {0x00};
unsigned char floorNumber = 1;

//**************************************************************
// main()
//**************************************************************
void main(void) {
	unsigned char * message;
	unsigned char doorOpen;
	link pTemp = NULL;
	
	configureCAN(CAR_CONTROLLER);
		  
	configureTimer();
//	CONFIGURE_LEDS;
//	InitQueue();
	initCarController();
	
	
  LED1_ON;
	LED2_OFF;
	
	floorNumber=1;
	doorOpen=1;

	EnableInterrupts;


for(;;) {
  
	updateFloorLed(floorNumber);
	updateDoorLed(doorOpen);
	
	
  _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
  
	
}


// NEED TO SIMPLIFY this interrupt
//ISR for elevator in-car floor requests 
interrupt VectorNumber_Vportp void CALL_FLOOR_ISR(void)
{

	if((PIFP & FLOOR1_BUTTON) == FLOOR1_BUTTON){
	  	floorNumber=1;
	  	SET_BITS(PIFP, FLOOR1_BUTTON);
	}
	else if((PIFP & FLOOR2_BUTTON) == FLOOR2_BUTTON){
	  	floorNumber=2;
	  	SET_BITS(PIFP, FLOOR2_BUTTON);
	}
	else if((PIFP & FLOOR3_BUTTON) == FLOOR3_BUTTON){
	  	floorNumber=3;
	  	SET_BITS(PIFP, FLOOR3_BUTTON);
	}

	TOGGLE_LEDS;
}