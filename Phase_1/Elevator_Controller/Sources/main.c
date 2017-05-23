#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <stdlib.h>       // For free() function
#include "TA_Header_S2017.h"
#include "CAN.h"
#include "FIFO.h"
#include "lcd.h"
#include "timer.h"
#include "spi.h"
#include "elevator.h"

static link message = NULL;
static unsigned char enable_req = 0;
static unsigned char floor_req = 0;
static unsigned char TxData = 0;

void main(void) {
  CONFIGURE_5VA;
  ENABLE_5VA;
  configureTimer();
  configureLCD();
  configureElevator();
  configureSPI();
  configureCAN(ELEVATOR_CONTROLLER);
  CONFIGURE_LEDS;
  LED1_ON;
  LED2_OFF;
  
  writeDAC(0, DAC_SET_CTRL_A);  // Don't let motor move at startup
  writeDAC(0, DAC_SET_CTRL_B);  // Don't let motor move at startup

  while (!(CANCTL0&CAN_SYNC));  // Wait for MSCAN to synchronize with the CAN bus
	SET_BITS(CANRFLG, 0xC3);      // Enable CAN Rx Interrupts
	SET_BITS(CANRIER, 0x01);      // Clear CAN Rx flag

	EnableInterrupts;

  for(;;) {
    // Display debug data on LCD
    LCDprintf("Ena: %u Req: %u\nFloor: %u", enable_req, floor_req, get_floor());
    
    // Check for new CAN messages & process if requried
    if(IsQueueEmpty()) 
    {
      // Do Nothing
    } else {
      message = DeQueue();  // Get a message from the FIFO
     
      // Process enable bit & floor request
      enable_req = *(message->Data.DATA) & enable_bit;
      floor_req = *(message->Data.DATA) & floor_bits;
      
      if(floor_req == 0) {
        // Do nothing
      } 
      else if (floor_req == 1) {
        set_distance(F1);
      } 
      else if (floor_req == 2) {
        set_distance(F2);
      } 
      else if (floor_req == 3) {
        set_distance(F3);
      }       

      set_enable(enable_req);
      
      free(message->Data.DATA); // Free the message data
      free(message);            // Free the message structure
      TOGGLE_LEDS;    
    }
  
    // Transmit status message
    TxData = (get_enable() | get_floor());
    TxCAN(ST_ID_101, 0x00, 0x01, &TxData);
    
    msDelay(100);
    
  } /* loop forever */
  /* please make sure that you never leave main */
}