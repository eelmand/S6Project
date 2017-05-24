#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "TA_Header_S2017.h"  /* my macros and constants */
#include "timer.h"  // Macros and constants for timer3handler.
#include "spi.h"
#include "elevator.h"
#include <stdlib.h> // For abs() function


// Ultrasonic sensor variables
static unsigned long edge1;   // Time of first edge  in TCNT ticks
static unsigned long edge2;   // Time of second edge in TCNT ticks
static unsigned char edge1ovf;      // Value of overflowCount at first edge
static unsigned char edge2ovf;      // Value of overflowCount at second edge
static unsigned long pulse_width;   // Value of ultrasonic echo pulse width in TCNT ticks
static unsigned char distance;      // Distance measured by ultrasonic sensor in cm

// Motor control variables
static unsigned char gainP = 30;           // Proportional gain - divide this by 10 later
static unsigned char gainI = 5;           // Integral gain - divide this by 1000 later because it will definitely be too big
static signed long errorI = 0;
static signed long error;                       // Calculated error in cm
static unsigned char distance_sp = 100;         // Distance set poit in cm, init to 100cm because that is a cool number
static signed long motor_sp_calc;               // Calculated motor setpoint before clipping
static unsigned char motor_sp_A = 0;            // Actual motor setpoint written to DAC OP A
static unsigned char motor_sp_B = 0;            // Actual motor setpoint written to DAC OP B
static unsigned char enable = 0;                // Enable bit - don't let motor move when this is zero



//;**************************************************************
//;*                 configureElevator(void)
//;*  Configures the timer channels for elevator control
//;**************************************************************   
void configureElevator(void) {

  // Configure TC0 as IC for echo signal
  CLEAR_BITS(TIOS, TIOS_IOS0_MASK); // Enable TC0 as IC
  TCTL4 = TCTL4_INIT;               // Capture on both edges of TC0

  // Configure TC3 as OC for pulse signal
  SET_BITS(TIOS, TIOS_IOS3_MASK);   // Enable TC3 as OC
  FORCE_OC_ACTION_NOW(3, OC_GO_HI); // Set TC3 high to start
  SET_OC_ACTION(3, OC_TOGGLE);      // Set TC3 to toggle port pin
  ULTRA_Pulse = TCNT + (TCNT_uS * 10);      // Delay by 10uS to start

  // Configure TC5 as OC for motor control loop
  SET_BITS(TIOS, TIOS_IOS5_MASK);   // Enable TC5 as OC
  SET_OC_ACTION(5, OC_OFF);         // Don't touch port pin
  MOTOR_Timer = TCNT + (TCNT_mS *30); // Set timer for 30mS

  TIE = (TIOS_IOS0_MASK | TIOS_IOS3_MASK | TIOS_IOS5_MASK);     // Enable interrupts for TC0 and TC3 and TC5
  TFLG1 = (TFLG1_C0F_MASK | TFLG1_C3F_MASK | TFLG1_C5F_MASK);    // Clear the flag in case anything is pending  
}//end of configureElevator


//;**************************************************************
//;*                 get_distance(void)
//;*  Calculates distance in cm and returns value
//;**************************************************************
unsigned char get_distance(void) {
  unsigned char dist;

  DisableInterrupts;
  dist = distance;
  EnableInterrupts;
  return dist;
}//end of get_distance


//;**************************************************************
//;*                 set_distance(unsigned card)
//;*  Set distance target in cm
//;**************************************************************
void set_distance(unsigned char dist) {
  DisableInterrupts;

  // Only update if sp is new  
  if(dist != distance_sp) {      
    distance_sp = dist;
    errorI = 0;
  }

  EnableInterrupts;
}//end of set_distance


//;**************************************************************
//;*                 set_enable(unsigned char)
//;*  Set enable bit
//;**************************************************************
void set_enable(unsigned char ena) {
  DisableInterrupts;
  enable = ena;
  EnableInterrupts;
}//end of set_enable


//;**************************************************************
//;*                 get_enable(void)
//;*  Returns current value of enable bit
//;**************************************************************
unsigned char get_enable(void) {
  unsigned char ena;

  DisableInterrupts;
  ena = enable;
  EnableInterrupts;
  return ena;
}//end of get_enable


//;**************************************************************
//;*                 get_floor(void)
//;*  Returns current floor or '0' for in transit
//;**************************************************************
unsigned char get_floor(void) {
  // Check if we are at a floor or in transit
  if (((F1 - FLOOR_TOL) <= distance) && (distance <= (F1 + FLOOR_TOL))) {
    return 1;
  }
  else if (((F2 - FLOOR_TOL) <= distance) && (distance <= (F2 + FLOOR_TOL))) {
    return 2;
  }
  else if (((F3 - FLOOR_TOL) <= distance) && (distance <= (F3 + FLOOR_TOL))) {
    return 3;
  }

  // Return 0 for 'in transit'
  return 0;
}//end of get_floor


//;**************************************************************
//;*                 timer0Handler()
//;*  Handles IC function for ultrasonic pulse width measurement
//;**************************************************************
interrupt 8 void timer0Handler(void) {

  static unsigned char dist_calc;
  // Rising edge logic (inverted because of schmitt trigger)
  if(!ULTRA_Echo_Pin) {
    edge1 = ULTRA_Echo;
    edge1ovf = get_overflowCount();
  }//end of logic for handling the rising edge
  // Falling edge logic
  else {
    edge2 = ULTRA_Echo;
    edge2ovf = get_overflowCount();
    pulse_width = (edge2 - edge1) + (OVF_Factor * (edge2ovf - edge1ovf));
    dist_calc = ((pulse_width / TCNT_uS) / ULTRA_uS_to_cm);
    
    // Account for reflections on sensor causing bad readings sometimes
    if((dist_calc > 5) && (dist_calc < 150)) {
      distance = dist_calc;
    }
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


//;**************************************************************
//;*                 timer5handler()
//;*  Handles OC function for motor control loop
//;**************************************************************
interrupt 13 void timer5Handler(void) {
  if(enable) {
    // Calculate error in cm
    error = distance_sp - distance;
    errorI += error;

    // PI Control Calculation
    motor_sp_calc = (error * gainP / 10) + (errorI * gainI / 1000);

    // Clip max/min values
    if(motor_sp_calc > 255) {
      motor_sp_calc = 255;
    }
    else if(motor_sp_calc < -255) {
      motor_sp_calc = -255;
    }

    // Logic to determine direction
    if(motor_sp_calc >= 0) {
      motor_sp_A = abs(motor_sp_calc);
      motor_sp_B = 0;
    }
    else {
      motor_sp_A = 0;
      motor_sp_B = abs(motor_sp_calc);
    }
    
    // Write values to DAC channels
    writeDAC(motor_sp_A, DAC_SET_CTRL_A);  
    writeDAC(motor_sp_B, DAC_SET_CTRL_B);
  }
  else {
    // If we are disabled always force 0V on DAC
    writeDAC(0, DAC_SET_CTRL_A);  
    writeDAC(0, DAC_SET_CTRL_B);
  }
  
  // Set timer for 30mS
  MOTOR_Timer = TCNT + (TCNT_mS *30);

}//end of timer5Handler()