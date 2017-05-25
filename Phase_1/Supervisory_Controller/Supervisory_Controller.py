# Supervisory_Controller.py

# Code for keyboard input from https://repolinux.wordpress.com/2012/10/09/non-blocking-read-from-stdin-in-python/

from PCANBasic import *
from time import sleep
from pprint import pprint
import sys
import select
import os
from tabulate import tabulate

PCAN = PCANBasic() 		# Initialize an instance of the PCANBasic class
read_list = [sys.stdin] # Files monitored for input


##############################################################################################
## CAN protocol definition
## Refer to: https://github.com/eelmand/S6Project/blob/master/Project%20Plan/Shared_CAN_Protocol_Proposal.xlsx
##############################################################################################

# CAN message ID's
ID_sc = 0x100 			# CAN message ID for Supervisory Controller
ID_ec = 0x101			# CAN message ID for Elevator controller
ID_cc = 0x200			# CAN message ID for elevator Car Controller
ID_f1 = 0x201			# CAN message ID for Floor Controller 1
ID_f2 = 0x202			# CAN message ID for Floor Controller 2
ID_f3 = 0x203			# CAN message ID for Floor Controller 3

# CAN signal masks
mask_sc_enable = 		0b00000100	# Bit mask for sc_enable signal
mask_sc_sc_floor_cmd =	0b00000011	# Bit mask for sc_sc_floor_cmd signal
mask_ec_state =			0b00000100	# Bit mask for ec_state signal
mask_ec_car_pos = 		0b00000011 	# Bit mask for ec_car_pos signal
mask_cc_door_state = 	0b00000100	# Bit mask for cc_door_state signal
mask_cc_floor_req = 	0b00000011	# Bit mask for cc_floor_req signal
mask_f1_call_req = 		0b00000001	# Bit mask for f1_call_req signal
mask_f2_call_req = 		0b00000001	# Bit mask for f2_call_req signal
mask_f3_call_req = 		0b00000001	# Bit mask for f3_call_req signal

# CAN signal value tables
sig_sc_enable = ["Cmd Disable Elevator", "Cmd Enable Elevator"]
sig_sc_floor_cmd = ["Cmd Don't Care", "Cmd Floor 1", "Cmd Floor 2", "Cmd Floor 3"]
sig_ec_state = ["Elevator Disabled", "Elevator Enabled"]
sig_ec_car_pos = ["In Transit", "Floor 1", "Floor 2", "Floor 3"]
sig_cc_door_state = ["Door Open", "Door Closed"]
sig_cc_floor_req = ["No Request", "Req Floor 1", "Req Floor 2", "Req Floor 3"]
sig_f1_call_req = ["No Request", "Car Requested"]
sig_f2_call_req = ["No Request", "Car Requested"]
sig_f3_call_req = ["No Request", "Car Requested"]

##############################################################################################
## Global data storage
## Maybe improve this later
##############################################################################################

# Supervisory Controller Data
sc_enable = 0 					# Enable bit value to be sent to EC
sc_floor_cmd = 0 				# Floor number to be sent to EC

# Elevator Controller Data
ec_state = -1 					# Enable bit value reported from EC
ec_car_pos = -1 				# Floor number reported from EC

# Floor Controller Data
f1_call_req = 0 				# Value of request bit from Floor Controller 1
f2_call_req = 0 				# Value of request bit from Floor Controller 2
f3_call_req = 0 				# Value of request bit from Floor Controller 3

# Car Controller Data
cc_floor_req = 0 				# Floor number requested from Car Controller
cc_door_state = 0 				# Door state reported from Car Controller, init to 0 (open)

# Remote Interface Data
remote_floor_req = 0 			# Floor number requested from Remote Operator


##############################################################################################
## Functions/methods
##############################################################################################

##
## Init_PCAN()
## Initialize the PCAN USB Dongle & Check for Errors
## Resets Tx & Rx queues
##
def Init_PCAN(device):
	status = PCANBasic.Initialize(device, PCAN_USBBUS1, PCAN_BAUD_125K)
	PCANBasic.Reset(device, PCAN_USBBUS1)
	if status > 0:
		print "Error Initializing PCAN USB"
		exit
	else:
		print "PCAN USB Initialized"	

## end of method


##
## Uninit_PCAN()
## Uninitialize the PCAN USB Dongle & check for errors
##
def Uninit_PCAN(device):
	status = PCANBasic.Uninitialize(device, PCAN_USBBUS1)
	if status > 0:
		print "Error Uninitializing PCAN USB"
		exit
	else:
		print "PCAN USB Uninitialized"
		exit	
## end of method			


##
## process_input()
## Debug mode - allow user to set parameters and stuff
## Basically a playground for now
##
def process_input():
	print "Elevator Command Input"
	global sc_floor_cmd
	global sc_enable

	sc_floor_cmd = input("Enter floor number:")
	sc_enable = input("Enter enable value:")			
## end of method


##
## update_display()
## Show elevator status and command
##
def update_display():
	global sc_floor_cmd
	global sc_enable
	global ec_car_pos
	global ec_state
	
	os.system('clear')	# Clear screen

	# Print data nicely https://stackoverflow.com/questions/9535954/printing-lists-as-tabular-data
	header = ["Signal", "Value"]
	data_sc_enable = ['SC_ENABLE', sig_sc_enable[sc_enable]]
	data_sc_floor_cmd = ['SC_FLOOR_CMD', sig_sc_floor_cmd[sc_floor_cmd]]
	data_ec_state = ['EC_STATE', sig_ec_state[ec_state]]
	data_ec_car_pos = ['EC_CAR_POS', sig_ec_car_pos[ec_car_pos]]
	data_f1_call_req = ['F1_CALL_REQ', sig_f1_call_req[f1_call_req]]
	data_f2_call_req = ['F2_CALL_REQ', sig_f2_call_req[f2_call_req]]
	data_f3_call_req = ['F3_CALL_REQ', sig_f3_call_req[f3_call_req]]
	data_cc_floor_req = ['CC_FLOOR_REQ', sig_cc_floor_req[cc_floor_req]]
	data_cc_door_state = ['CC_DOOR_STATE', sig_cc_door_state[cc_door_state]]

	data_table = [data_sc_enable, data_sc_floor_cmd, data_ec_state, data_ec_car_pos, 
					data_f1_call_req, data_f2_call_req, data_f3_call_req, 
					data_cc_floor_req, data_cc_door_state]

	print tabulate(data_table, headers=header)

	# Add note at bottom to enter debug mode
	print ""
	print "Press 'Enter' for debug mode"
## end of method


##
## Rx_CAN(device)
## Receive any pending CAN messages and populate global variables as necessary
##
def Rx_CAN(device):
	global ec_car_pos
	global ec_state
	global f1_call_req
	global f2_call_req
	global f3_call_req
	global cc_floor_req
	global cc_door_state

	# Do-while loop of reading messages until there aren't any more
	message = PCANBasic.Read(PCAN, PCAN_USBBUS1)
	while message[1].ID > 1:					
		# Process EC Status Message
		if message[1].ID == ID_ec:
			ec_car_pos = message[1].DATA[0] & mask_ec_car_pos
			ec_state = ((message[1].DATA[0] & mask_ec_state) >> 2)	# Any good way to dynamically shift bits based on bit number??? Think about this later
		
		# Process F1 Status Message
		elif message[1].ID == ID_f1:
			f1_call_req = message[1].DATA[0] & mask_f1_call_req

		# Process F2 Status Message
		elif message[1].ID == ID_f2:
			f2_call_req = message[1].DATA[0] & mask_f2_call_req

		# Process F3 Status Message
		elif message[1].ID == ID_f3:
			f3_call_req = message[1].DATA[0] & mask_f3_call_req

		# Process CC Status Message
		elif message[1].ID == ID_cc:
			cc_floor_req = message[1].DATA[0] & mask_cc_floor_req
			cc_door_state = ((message[1].DATA[0] & mask_cc_door_state) >> 2) # Any good way to dynamically shift bits based on bit number??? Think about this later

		# Read next message
		message = PCANBasic.Read(PCAN, PCAN_USBBUS1)		
## end of method


## 
## Tx_EC_Cmd(device)
## Transmit the command message to the elevator controller
##
def Tx_EC_Cmd(device):
	global sc_floor_cmd
	global sc_enable
	message = TPCANMsg()

	message.ID = ID_sc
	message.MSGTYPE = PCAN_MESSAGE_STANDARD
	message.LEN = 1
	message.DATA[0] = (sc_floor_cmd | (sc_enable << 2)) # Any good way to dynamically shift bits based on bit number??? Think about this later

	# Send the message and check if it was successful
	status = PCANBasic.Write(device, PCAN_USBBUS1, message)
	if status > 0:
		print "Error transmitting CAN message"
		exit()
## end of method


## 
## main()
##
def main():
	# Initialize device
	Init_PCAN(PCAN)

	# Infinite loop of reading CAN messages & keyboard input
	while 1:
		# Wait for keyboard input, or do other stuff
		while sys.stdin in select.select([sys.stdin], [], [], 0)[0]:
			line = sys.stdin.readline()
			if line:
				process_input()
			else: 
				print('eof')
				exit(0)
		else:
			Rx_CAN(PCAN)
	  		update_display()
	  		Tx_EC_Cmd(PCAN)
	  		sleep(0.5)  
## end of method


try:
	main()
except KeyboardInterrupt:
	print " "
	Uninit_PCAN(PCAN)



## Place to store cool shit
def playground(device):
	PCAN = device
	message = PCANBasic.Read(PCAN, PCAN_USBBUS1)

	if message[1].ID > 1:	# For some reason .Read returns ID of 1 when no messages present...
		print "Received CAN Message"
		print "ID: ",format(message[1].ID, '02x')
		print "DLC: ", message[1].LEN
		print "DATA: "

		for j in range(0, message[1].LEN):
			print "Byte ", j, ": ", message[1].DATA[j]