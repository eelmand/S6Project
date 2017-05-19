//;******************************************************************************
//; timer.h - Header file for operating the RC servo on timer 3 (PT3)
//:
//; Name: Thomas Abdallah
//; Date: 2016-03-31
//;
//;******************************************************************************

// Action values for OC function
#define OC_OFF		0x00
#define OC_TOGGLE	0x01
#define OC_GO_LO	0x02
#define OC_GO_HI	0x03


// Timer configuration parameters
#define TSCR1_INIT 0b10110000	// Turn on timer module and enable fast-clear and freeze in debug
//#define TSCR2_INIT 0b00000010	// Set pre-scaler to 4 for finest resolution @50Hz PWM frequency
#define TSCR2_INIT 0b10000010	// Set pre-scaler to 4 for finest resolution @50Hz PWM frequency, overflow interrupt enabled
#define TCTL4_INIT 0b00000011	// Capture on both edges of TC0

// Define TCTL_1_2 as a single 16 bit register made up of TCTL1 and TCTL2 together
#define TCTL_1_2 (*(volatile word * const) &TCTL1)

#define TCNT_mS 2000			// Number of TCNT ticks for 1mS with prescaler of 4
#define TCNT_uS 2 				// Number of TCNT ticks for 1uS with prescaler of 4

// Ultrasonic sensor timer channel configuration
#define ULTRA_Echo TC0					// Timer channel for ultrasonic echo
#define ULTRA_Echo_Pin (PTT & PTT_PTT0_MASK)	// Port pin for ultrasonic echo
#define ULTRA_Pulse TC3					// Timer channel for ultrasonic pulse
#define ULTRA_Pulse_Pin (PTT & PTT_PTT3_MASK)	// Port pin for ultrasonic pulse
#define ULTRA_uS_to_cm 58		// 58uS per centimetre
#define OVF_Factor 65536l	//2^16

// Function prototypes
void configureTimer(void);			// Configure the timer module at startup
void configureUltra(void);			// Configure the timer channels for ultrasonic sensor operation
void msDelay(unsigned char time);	// Delay by time ms using OC polling
void usDelay(unsigned char time);	// Delay by time us using OC polling
unsigned char get_distance(void);	// Returns distance in cm from ultrasonic sensor