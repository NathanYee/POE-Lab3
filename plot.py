import serial
import time
import csv

# Creating a serial object
ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=2)

# Sleep for 1 second to wait for the serial to init
time.sleep(1)

sleft = []
sright = []
mleft = []
mright = []

for d in range(0,800):
	try:
		val = int(ser.readline().strip())
	except:
		val = 0
	finally:
		if d%4 == 0:
			sleft.append(val)
		elif d%4 == 1:
			sright.append(val)
		elif d%4 == 2:
			mleft.append(val)
		elif d%4 == 3:
			mright.append(val)


csvfile =  open('data.csv', 'wb')
w = csv.writer(csvfile, delimiter=' ',
                    quotechar='|', quoting=csv.QUOTE_MINIMAL)
w.writerow(sleft)
w.writerow(sright)
w.writerow(mleft)
w.writerow(mright)
csvfile.close()

# Close the serial port
ser.close()