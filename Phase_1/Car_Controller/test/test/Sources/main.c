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
unsigned char floorNumber;
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
	
  EnableInterrupts;


for(;;) {
  
  updateFloorLed(floorNumber);
	updateDoorLed(doorStatus);
	
	                                                                       
  _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
  
	
}


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

//ISR for elevator in-car door open/close requests 
interrupt VectorNumber_Vportj void DOOR_ISR(void)
{

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
