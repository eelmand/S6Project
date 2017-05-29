/*	Filename: car_controller.c
	Author: Stanislav Rashevskyi 
	Based of David Eelman's Floor Controller code
	Date: May 23, 2017
	Purpose: 
	 Car controller displays position and sets floors to move elevator to, opens 
	 and closes car doors. Also it is able to receive same commands over CAN.
*/

// Local Includes
#include "car_controller.h"
#include "TA_Header_S2017.h"

unsigned char initCarController(void){
  // Configure ports with LEDs as outputs
	SET_BITS(DDRA, (FLOOR1_LED|FLOOR2_LED|FLOOR3_LED|OPEN_LED|CLOSE_LED));
	
	// Configure port with button to be input
	CLEAR_BITS(DDRP, (FLOOR1_BUTTON|FLOOR2_BUTTON|FLOOR3_BUTTON));
	CLEAR_BITS(DDRJ, (OPEN_BUTTON|CLOSE_BUTTON));


	// Configure the button ports to have a pull down resistor 
	SET_BITS(PERP, (FLOOR1_BUTTON|FLOOR2_BUTTON|FLOOR3_BUTTON));
	SET_BITS(PPSP, (FLOOR1_BUTTON|FLOOR2_BUTTON|FLOOR3_BUTTON));
	SET_BITS(PERJ, (OPEN_BUTTON|CLOSE_BUTTON));
	SET_BITS(PPSJ, (OPEN_BUTTON|CLOSE_BUTTON));
	
            
	//Turn on Interrupts on Port J and Port P
	SET_BITS(PIEP, (FLOOR1_BUTTON|FLOOR2_BUTTON|FLOOR3_BUTTON));	
	SET_BITS(PIEJ, (OPEN_BUTTON|CLOSE_BUTTON));


	//Clear any pending interrupt flags on Port P and J
	//by writing 1 to it
	SET_BITS(PIFP, (FLOOR1_BUTTON|FLOOR2_BUTTON|FLOOR3_BUTTON));	
	SET_BITS(PIFP, (FLOOR1_BUTTON|FLOOR2_BUTTON|FLOOR3_BUTTON));	
	SET_BITS(PIFJ, (OPEN_BUTTON|CLOSE_BUTTON));
	SET_BITS(PIFJ, (OPEN_BUTTON|CLOSE_BUTTON));	


	return 0;
}

unsigned char updateFloorLed(unsigned char floorNumber){
	// Display which floor the elevator is at based on elevator car status message
	if(floorNumber == 1){
		CLEAR_BITS(PORTA, (FLOOR2_LED|FLOOR3_LED));
		SET_BITS(PORTA, FLOOR1_LED);
	}
	else if(floorNumber == 2){
		CLEAR_BITS(PORTA, (FLOOR1_LED|FLOOR3_LED));
		SET_BITS(PORTA, FLOOR2_LED);
	}
	else if(floorNumber == 3){
		CLEAR_BITS(PORTA, (FLOOR1_LED|FLOOR2_LED));
		SET_BITS(PORTA, FLOOR3_LED);
	}
	else{
		return -1;
	}
	return 0;
}

unsigned char updateDoorLed(unsigned char doorStatus){
	// Display whether the car door is open or closed (0 - open, 1 - closed)
	// In future if matters can return whether door was previously open or closed...
	if(doorStatus == 0){  
		CLEAR_BITS(PORTA, CLOSE_LED);
		SET_BITS(PORTA, OPEN_LED);
	}
	else{
  	CLEAR_BITS(PORTA, OPEN_LED);
		SET_BITS(PORTA, CLOSE_LED);
	}
	return 0;
}
