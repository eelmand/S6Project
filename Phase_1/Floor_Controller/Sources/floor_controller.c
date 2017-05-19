/*	Filename: floor_controller.c
	Author: David Eelman
	Date: May 16, 2017
	Purpose: The floor controller exists on each floor the elevator is to service. The controller
		includes features to call the elevator and display the current floor the elevator is servicing.
*/

// Local Includes
#include "floor_controller.h"
#include "TA_Header_S2017.h"

unsigned char init_floor_controller(){
	// Configure ports with LEDs as outputs
	SET_BITS(DDRT, (FLOOR1_LED|FLOOR2_LED|FLOOR3_LED|CALL_LED));
	// Configure port with button to be input
	CLEAR_BITS(DDRT, CALL_BUTTON);
	// Configure the call button port to have a pull up resistor
	SET_BITS(PERT, CALL_BUTTON);
	CLEAR_BITS(PPST, CALL_BUTTON);
}

unsigned char update_floor_led(unsigned char floorNumber){
	// Check if the current floor is the one this controller is on
	if (floorNumber == CONTROLLER_FLOOR){
		CLEAR_BITS(PTT, CALL_LED);
	}
	else{
		// Do nothing
	}

	// Display which floor the elevator is at based on elevator car status message
	if(floorNumber == 1){
		CLEAR_BITS(PTT, (FLOOR2_LED|FLOOR3_LED));
		SET_BITS(PTT, FLOOR1_LED);
	}
	else if(floorNumber == 2){
		CLEAR_BITS(PTT, (FLOOR1_LED|FLOOR3_LED));
		SET_BITS(PTT, FLOOR2_LED);
	}
	else if(floorNumber == 3){
		CLEAR_BITS(PTT, (FLOOR1_LED|FLOOR2_LED));
		SET_BITS(PTT, FLOOR3_LED);
	}
	else{
		return -1;
	}
	return 0;
}

unsigned char call_elevator(){
	SET_BITS(PTT, CALL_LED); 
	// Generate a call elevator CAN message
}