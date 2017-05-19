#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "TA_Header_S2017.h"  /* my macros and constants */
#include "timer.h"  // Macros and constants for timer3handler.

// Global variables
static unsigned char overflowCount = 0; //To handle timer wrapping for IC functionality

static unsigned long edge1;   // Time of first edge  in TCNT ticks
static unsigned long edge2;   // Time of second edge in TCNT ticks
static unsigned char edge1ovf;      // Value of overflowCount at first edge
static unsigned char edge2ovf;      // Value of overflowCount at second edge
static unsigned long pulse_width;   // Value of ultrasonic echo pulse width in TCNT ticks


//;**************************************************************
//;*                 configureTimer(void)
//;*  Configures the timer module with parameters for PWM operation
//;**************************************************************   
void configureTimer(void) {
  TSCR1 = TSCR1_INIT; // Turn on timer module and enable fast-clear and freeze in debug
  TSCR2 = TSCR2_INIT; // Set pre-scaler to 4 for finest resolution @50Hz PWM frequency, overflow interrupt enabled
}//end of configureTimer


//;**************************************************************
//;*                 configureUltra(void)
//;*  Configures the timer channels for ultrasonic sensor operation
//;**************************************************************   
void configureUltra(void) {

  // Configure TC0 as IC for echo signal
  CLEAR_BITS(TIOS, TIOS_IOS0_MASK); // Enable TC0 as IC
  TCTL4 = TCTL4_INIT;               // Capture on both edges of TC0

  // Configure TC3 as OC for pulse signal
  SET_BITS(TIOS, TIOS_IOS3_MASK);   // Enable TC3 as OC
  FORCE_OC_ACTION_NOW(3, OC_GO_HI); // Set TC3 high to start
  SET_OC_ACTION(3, OC_TOGGLE);      // Set TC3 to toggle port pin
  ULTRA_Pulse = TCNT + (TCNT_uS * 10);      // Delay by 10uS to start

  TIE = (TIOS_IOS0_MASK | TIOS_IOS1_MASK);     // Enable interrupts for TC0 and TC1
  TFLG1 = (TFLG1_C0F_MASK | TFLG1_C3F_MASK);    // Clear the flag in case anything is pending

  TIE = (TIOS_IOS0_MASK | TIOS_IOS3_MASK);     // Enable interrupts for TC0 and TC3
  TFLG1 = (TFLG1_C0F_MASK | TFLG1_C3F_MASK);    // Clear the flag in case anything is pending  
}//end of configureUltra


//;**************************************************************
//;*                 get_distance(void)
//;*  Calculates distance in cm and returns value
//;**************************************************************
unsigned char get_distance(void) {
  unsigned char dist;

  DisableInterrupts;
  dist = ((pulse_width / TCNT_uS) / ULTRA_uS_to_cm);
  EnableInterrupts;
  return dist;
}//end of get_distance


//;**************************************************************
//;*                 msDelay(time)
//;*  Delay program execution by time mS (busy wait)
//;*  Delays on TC7
//;**************************************************************
void msDelay(unsigned char time) {
  // 1 TCNT tick = 0.5uS so 2000 TCNT ticks = 1mS
  volatile unsigned char count;

  SET_OC_ACTION(7,OC_OFF);     // Set TC7 to not touch the port pin
  TC7 = TCNT + TCNT_mS; // Set first OC event timer (for 1mS)
  TIOS |= TIOS_IOS7_MASK; // Enable TC7 as OC

  for(count = 0; count < time; count ++)
  {
    while(!(TFLG1 & TFLG1_C7F_MASK)); // Wait for the OC event
    TC7 += TCNT_mS;
  }

  TIOS &= LOW(~TIOS_IOS7_MASK);  // Turn off OC on TC7

}//end of msDelay


//;**************************************************************
//;*                 usDelay(time)
//;*  Delay program execution by time uS (busy wait)
//;*  Delays on TC7
//;**************************************************************
void usDelay(unsigned char time) {
  // 1 TCNT tick = 0.5uS so 2 TCNT ticks = 1uS
  volatile unsigned char count;

  SET_OC_ACTION(7,OC_OFF);     // Set TC7 to not touch the port pin
  TC7 = TCNT + TCNT_uS; // Set first OC event timer (for 1mS)
  TIOS |= TIOS_IOS7_MASK; // Enable TC7 as OC

  for(count = 0; count < time; count ++)
  {
    while(!(TFLG1 & TFLG1_C7F_MASK)); // Wait for the OC event
    TC7 += TCNT_uS;
  }

  TIOS &= LOW(~TIOS_IOS7_MASK);  // Turn off OC on TC7

}//end of usDelay


//;**************************************************************
//;*                 timerOverflowHandler()
//;*  Increments global variable to track timer overflow events
//;**************************************************************
interrupt 16 void timerOverflowHandler(void) {
  overflowCount ++; //Increment the overflow counter
  (void)TCNT;   //To clear the interrupt flag with fast-clear enabled.
}//end of timerOverflowHandler()


//;**************************************************************
//;*                 timer0Handler()
//;*  Handles IC function for ultrasonic pulse width measurement
//;**************************************************************
interrupt 8 void timer0Handler(void) {
  // Rising edge logic (inverted because of schmitt trigger)
  if(!ULTRA_Echo_Pin) {
    edge1 = ULTRA_Echo;
    edge1ovf = overflowCount;
  }//end of logic for handling the rising edge
  // Falling edge logic
  else {
    edge2 = ULTRA_Echo;
    edge2ovf = overflowCount;
    pulse_width = (edge2 - edge1) + (OVF_Factor * (edge2ovf - edge1ovf));
  }//end of logic for handling the falling edge
}//end of timer0Handler()


//;**************************************************************
//;*                 timer3handler()
//;*  Handles OC function for ultrasonic pulse generation
//;**************************************************************
interrupt 11 void timer3Handler(void) {
  // Start of pulse
  if(ULTRA_Pulse_Pin) {
    ULTRA_Pulse = TCNT + (TCNT_uS * 10);      // Delay by 10uS to start
  }
  else {
    ULTRA_Pulse = TCNT + (TCNT_mS * 20);      // Delay by 20ms
  }
}//end of timer3Handler()