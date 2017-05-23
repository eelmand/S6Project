#include "TA_Header_S2017.h"  /* my macros and constants */

#define CAN_INIT 0x01
#define CAN_START 0x00
#define CAN_SYNC 0x10
#define CAN_RxACK 0x01		// Write to CANRFLG to acknowledge the interrupt and release the buffer
#define CAN_LOOPBACK 0xE0	// Enable module in loopback mode with bus clock
#define CAN_NORMAL 0xC0		// Enable module in normal mode with bus clock
#define BTR0_125K 0x07
#define BTR1_125K 0x23
#define CAN_FILTER_16b 0x10		// Define four 16-bit filters

// Acceptance filter definitions
#define ACC_CODE_ID100 0x2000
#define ACC_CODE_ID100_HIGH ((ACC_CODE_ID100 & 0xFF00)>>8)
#define ACC_CODE_ID100_LOW (ACC_CODE_ID100 & 0x00FF)

#define ACC_CODE_ID101 0x2020
#define ACC_CODE_ID101_HIGH ((ACC_CODE_ID101 & 0xFF00)>>8)
#define ACC_CODE_ID101_LOW (ACC_CODE_ID101 & 0x00FF)

#define ACC_CODE_ID200 0x4000
#define ACC_CODE_ID200_HIGH ((ACC_CODE_ID200 & 0xFF00)>>8)
#define ACC_CODE_ID200_LOW (ACC_CODE_ID200 & 0x00FF)

#define ACC_CODE_ID201 0x4020
#define ACC_CODE_ID201_HIGH ((ACC_CODE_ID201 & 0xFF00)>>8)
#define ACC_CODE_ID201_LOW (ACC_CODE_ID201 & 0x00FF)

#define ACC_CODE_ID202 0x4040
#define ACC_CODE_ID202_HIGH ((ACC_CODE_ID202 & 0xFF00)>>8)
#define ACC_CODE_ID202_LOW (ACC_CODE_ID202 & 0x00FF)

#define ACC_CODE_ID203 0x4060
#define ACC_CODE_ID203_HIGH ((ACC_CODE_ID203 & 0xFF00)>>8)
#define ACC_CODE_ID203_LOW (ACC_CODE_ID203 & 0x00FF)

// Mask code definitions
#define MASK_CODE_ST_ID 0x0007
#define MASK_CODE_ST_ID_HIGH ((MASK_CODE_ST_ID & 0xFF00)>>8)
#define MASK_CODE_ST_ID_LOW (MASK_CODE_ST_ID & 0xFF)

// CAN module errors
#define CAN_ERR_NONE 0x00
#define CAN_ERR_BUFFER_FULL 0x01

// Node IDs
#define SUPERVISORY_CONTROLLER 0x100
#define ELEVATOR_CONTROLLER 0x101
#define CAR_CONTROLLER 0x200
#define FLOOR_CONTROLLER_1 0x201
#define FLOOR_CONTROLLER_2 0x202
#define FLOOR_CONTROLLER_3 0x203

// ID definition
#define ST_ID_100 0x20000000
#define ST_ID_101 0x20200000
#define ST_ID_200 0x40000000
#define ST_ID_201 0x40200000
#define ST_ID_202 0x40400000
#define ST_ID_203 0x40600000

// Function to initialize CAN module
void configureCAN(unsigned int nodeID);

// Function to send CAN message
unsigned char TxCAN(unsigned long id, unsigned char priority, unsigned char length, unsigned char *txdata);