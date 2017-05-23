# PCAN_Test.py

from PCANBasic import *
from time import sleep
from pprint import pprint

PCAN = PCANBasic()	# Initialize an instance of the PCANBasic class

# Initialize the PCAN USB Dongle & Check for Errors
status = PCANBasic.Initialize(PCAN, PCAN_USBBUS1, PCAN_BAUD_125K)
if status > 0:
	print "Error Initializing PCAN USB"
	exit
else:
	print "PCAN USB Initialized"


# Infinite loop of reading CAN messages & keyboard input
while true:
	message = PCANBasic.Read(PCAN, PCAN_USBBUS1)

	if message[1].ID > 1:	# For some reason .Read returns ID of 1 when no messages present...
		print "Received CAN Message"
		print "ID: ",format(message[1].ID, '02x')
		print "DLC: ", message[1].LEN
		print "DATA: "

		for j in range(0, message[1].LEN):
			print "Byte ", j, ": ", message[1].DATA[j]
	else:
		print "No messages"



status = PCANBasic.Uninitialize(PCAN, PCAN_USBBUS1)
if status > 0:
	print "Error Uninitializing PCAN USB"
	exit
else:
	print "PCAN USB Uninitialized"
	exit