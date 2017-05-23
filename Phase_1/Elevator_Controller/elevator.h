//;******************************************************************************
//; elevator.h - Header file for operating the elevator
//:
//; Name: Thomas Abdallah
//; Date: 2017-05-23
//;
//;******************************************************************************

// Ultrasonic sensor timer channel configuration
#define ULTRA_Echo TC0					// Timer channel for ultrasonic echo
#define ULTRA_Echo_Pin (PTT & PTT_PTT0_MASK)	// Port pin for ultrasonic echo
#define ULTRA_Pulse TC3					// Timer channel for ultrasonic pulse
#define ULTRA_Pulse_Pin (PTT & PTT_PTT3_MASK)	// Port pin for ultrasonic pulse
#define ULTRA_uS_to_cm 58		// 58uS per centimetre

// Elevator constants and stuff
#define MOTOR_Timer TC5		// Timer channel for Motor control loop
#define F3 122
#define F2 62
#define F1 20
#define FLOOR_TOL 10

// Elevator CAN signal masks
#define enable_bit 0b00000100		// Third LSB for enable/disable
#define floor_bits 0b00000011		// Lower 2 bits for floor number request


// Function prototypes
void configureElevator(void);		// Configure the timer channels for ultrasonic sensor operation
unsigned char get_distance(void);	// Returns distance in cm from ultrasonic sensor
void set_distance(unsigned char dist);	// Set distance targer in cm from ultrasonic sensor
void set_enable(unsigned char ena);	// Set the enable global variable
unsigned char get_enable(void);		// Get the current value of the enable flag
unsigned char get_floor(void);		// Return the current floor