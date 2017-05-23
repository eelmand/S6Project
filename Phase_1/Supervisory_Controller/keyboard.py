# Check for input every 100mS
# Process input if received
# Display elevator status otherwise

import sys
import select
import time
import os

floor = 1
enable = 0

# files monitored for input
read_list = [sys.stdin]

# select() timeout for input in seconds
timeout = 0.1

def treat_input(linein):
	print "Processing input" # Read input from 

def update_elevator_status():
	os.system('clear')
	print("Elevator Status")
	print "Floor: ", floor
	print "Enable: ", enable

def main():
  global read_list
  # while still waiting for input on at least one file
  while read_list:
    ready = select.select(read_list, [], [], timeout)[0]
    
    # Check for Keyboard Input
    if not ready:
      update_elevator_status()
    else:
      for file in ready:
        line = file.readline()
        if not line: # EOF, remove file from input list
          read_list.remove(file)
        elif line.rstrip(): # optional: skipping empty lines
          treat_input(line)

try:
    main()
except KeyboardInterrupt:
  pass