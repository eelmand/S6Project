/*	Filename: floor_controller.c
	Author: David Eelman
	Date: May 25, 2017
	Purpose: The floor controller exists on each floor the elevator is to service. The controller
		includes features to call the elevator and display the current floor the elevator is servicing.
*/

// Local Includes
#include "floor_controller.h"

// Global variables
unsigned char CanTxBuffer[1] = {0x00};
unsigned char count = 0;

//---------------------------------------------------------------------
//		initFloorController()
//	Configures the ports for LEDS + push button and configures timer channel for transmitting CAN messages
//---------------------------------------------------------------------
unsigned char initFloorController(void){
	// Configure ports with LEDs as outputs
	SET_BITS(DDRT, (FLOOR1_LED|FLOOR2_LED|FLOOR3_LED|CALL_LED));
	
	// Configure port with button to be input
	CLEAR_BITS(DDRT, CALL_BUTTON);
	
	// Configure the call button port to have a pull up resistor
	SET_BITS(PERT, CALL_BUTTON);
	CLEAR_BITS(PPST, CALL_BUTTON);

	// Configure TC4 as OC for transmitting CAN messages
	SET_OC_ACTION(4, OC_OFF);      // Set TC4 to not touch port pin
	SET_BITS(TIOS, TIOS_IOS4_MASK);   // Enable TC4 as OC
	CAN_TX = TCNT + (TCNT_mS * 10);  // Delay by 10 ms to start

	TIE = TIOS_IOS4_MASK;     // Enable interrupts for TC4
	TFLG1 = TFLG1_C4F_MASK;    // Clear the flag in case anything is pending  
	return 0;
}

//---------------------------------------------------------------------
//		updateController(unsigned char floorNumber, unsigned char doorStatus)
//	Updates the floor/elevator call LEDS and handles if we're at our floor
//---------------------------------------------------------------------
unsigned char updateController(unsigned char floorNumber, unsigned char doorStatus){
	// Check if the elevator is at our floor and handle
	if ((floorNumber == CONTROLLER_FLOOR) && (doorStatus == 0)){
		CanTxBuffer[0] = NO_CALL_REQUEST; // No longer need to request car
		CLEAR_BITS(PTT, CALL_LED);
	}	

	// Display which floor the elevator is at based on elevator car status message
	if(floorNumber == 1 ){
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

//---------------------------------------------------------------------
//		callElevator()
//	Illumintate call elevator LED and transmit a request for the elevator
//---------------------------------------------------------------------
unsigned char callElevator(void){
	SET_BITS(PTT, CALL_LED); // Turn on elevator call LED
	CanTxBuffer[0] = CALL_REQUEST; // Request car
	return 0;
}

//---------------------------------------------------------------------
//		timer4Handler()
//	Send a CAN tx message every 500 ms
//---------------------------------------------------------------------
interrupt VectorNumber_Vtimch4 void timer4Handler(void) {
	CAN_TX = TCNT + (TCNT_mS * 10); // Interrupt happens every 10 ms
	if(count++ == 50){ // Send CAN message every 500 ms (50 x 10 ms)
		if(CONTROLLER_FLOOR == 1){
			TxCAN(ST_ID_201, 0x00, sizeof(CanTxBuffer), CanTxBuffer);
		}
		else if(CONTROLLER_FLOOR == 2){
			TxCAN(ST_ID_202, 0x00, sizeof(CanTxBuffer), CanTxBuffer);
		}
		else if(CONTROLLER_FLOOR == 3){
			TxCAN(ST_ID_203, 0x00, sizeof(CanTxBuffer), CanTxBuffer); 
		}
		TOGGLE_LEDS;	
		count = 0;
	}
}