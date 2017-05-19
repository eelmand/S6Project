#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "TA_Header_S2017.h"
//#include "CAN.h"
//#include "FIFO.h"
#include "lcd.h"
#include "timer.h"
#include "spi.h"

void main(void) {
  CONFIGURE_5VA;
  ENABLE_5VA;
  configureTimer();
  configureLCD();
  configureElevator();
  configureSPI();

	EnableInterrupts;


  for(;;) {
    LCDprintf("Dist: %d\n", get_distance());
    msDelay(100);
  } /* loop forever */
  /* please make sure that you never leave main */
}