#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "TA_Header_S2017.h"  /* my macros and constants */
#include <stdlib.h>
#include "CAN.h"
#include "timer.h"
#include "FIFO.h"

void main(void) {
	unsigned char txbuff[] = 0x42;
	link pTemp = NULL;

  	configureCAN();
  	configureTimer();
  	CONFIGURE_LEDS;
  	InitQueue();
  	LED1_ON;
  	LED2_OFF;

	while (!(CANCTL0&CAN_SYNC));  // Wait for MSCAN to synchronize with the CAN bus
	SET_BITS(CANRFLG, 0xC3);      // Enable CAN Rx Interrupts
	SET_BITS(CANRIER, 0x01);      // Clear CAN Rx flag

	EnableInterrupts;

	for (;;) {
		errorflag = TxCAN(ST_ID_100, 0x00, sizeof(txbuff)-1, txbuff);
		msDelay(250);
		
		if(IsQueueEmpty()) 
		{
		  // Do nothing
		} 
		else 
		{
		  pTemp = DeQueue();  // Grab a message from the Queue
      
		  free(pTemp->Data.DATA); // Free the memory malloc'd for data
		  free(pTemp);            // Free the memory malloc'd for the node structure				   
		}


		TOGGLE_LEDS;
	}
}