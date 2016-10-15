import serial
import time

# Creating a serial object
ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=2)

# Sleep for 2 seconds to wait for the serial to init
time.sleep(2)

con = 'y'
while con == 'y':
	b0 = input('Enter the Left Motor Speed: ')
	b1 = input('Enter the Right Motor Speed: ')

	# Take the value of the threshhold and split it into 2 bytes
	threshhold = input('Enter the IR threshhold: ')
	b2 = threshhold%256
	b3 = threshhold/256

	# Write those bytes to the arduino
	ser.write(bytearray([b0, b1, b2, b3]))
	con = raw_input('Continue? (y/n): ')

# Close the serial port
ser.close()