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

extern unsigned char floorNumber;
extern unsigned char new_floorNumber;
extern unsigned char doorStatus;

// Global variables
unsigned char CanTxBuffer[1] = {0x00};
unsigned char count = 0;



//**************************************************************
// Configure ports with LEDs as outputs   
unsigned char initCarController(void){

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
	
	// Configure TC4 as OC for transmitting CAN messages
	SET_OC_ACTION(4, OC_OFF);      // Set TC4 to not touch port pin
	SET_BITS(TIOS, TIOS_IOS4_MASK);   // Enable TC4 as OC
	CAN_TX = TCNT + (TCNT_mS * 10);  // Delay by 10 ms to start

	// Configure TC5 as OC for auto-closing elevator door
	SET_OC_ACTION(5, OC_OFF);      // Set TC5 to not touch port pin
	//SET_BITS(TIOS, TIOS_IOS5_MASK);   // Enable TC5 as OC
	// Don't enable this channel until we need it

	SET_BITS(TIE, TIOS_IOS4_MASK);	// Enable interrupts for TC4
	SET_BITS(TIE, TIOS_IOS5_MASK);	// Enable interrupts for TC5
	TFLG1 = TFLG1_C4F_MASK;    // Clear the flag in case anything is pending  
                     
	return 0;
}

//**************************************************************
// Display which floor the elevator is at based on elevator car status message
unsigned char updateFloorLed(unsigned char floorNumber){
	
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


//**************************************************************
// Display whether the car door is open or closed (0 - open, 1 - closed)
unsigned char updateDoorLed(unsigned char doorStatus){

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

//**************************************************************
// Enables timer channel to auto-close door after some time
void startDoorTimer(void){
	// Kick off timer for auto-closing door
   TC5 = TCNT + (TCNT_mS * 10);  		// Delay by 10 ms to start
   SET_BITS(TIOS, TIOS_IOS5_MASK);   	// Enable TC5 as OC
}


//**************************************************************
// Update controller 
unsigned char updateController(void){//, unsigned char new_floorNumber, unsigned char doorStatus){

  // Check if the elevator arrived to the requested floor and handle
  if ((floorNumber == new_floorNumber) && (floorNumber != 0)) {
   new_floorNumber=0;  // no change floor requests
   doorStatus=0;   // door open

   startDoorTimer();
   
  }
  
  updateFloorLed(floorNumber);
  updateDoorLed(doorStatus);
  
  // update door and requested floor status on CAN 
  CanTxBuffer[0] = ((doorStatus<<2) | new_floorNumber); 
  
 return 0;
}

//**************************************************************
//		timer4Handler()
//	Send a CAN tx message every 500 ms
//---------------------------------------------------------------------
interrupt VectorNumber_Vtimch4 void timer4Handler(void) {
	CAN_TX = TCNT + (TCNT_mS * 10); // Interrupt happens every 10 ms
	if(count++ == 50){ // Send CAN message every 500 ms (50 x 10 ms)
	  
	  TxCAN(ST_ID_200, 0x00, sizeof(CanTxBuffer), CanTxBuffer);
		TOGGLE_LEDS;	
		count = 0;
	}
}

//**************************************************************
//		timer5Handler()
//	Automatically close door after two seconds
//---------------------------------------------------------------------
interrupt VectorNumber_Vtimch5 void timer5Handler(void) {
	static unsigned char i = 0;

	if(i < 200) {
		TC5 = TCNT + (TCNT_mS * 10);	// Delay 10mS
		i += 1;
	}
	else {
		// Close the door
		i = 0;
		doorStatus = 1;
		updateDoorLed(doorStatus);
		(void)TCNT;   //To clear the interrupt flag with fast-clear enabled.
		CLEAR_BITS(TIOS, TIOS_IOS5_MASK);   	// Disable TC5 as OC
	}
}