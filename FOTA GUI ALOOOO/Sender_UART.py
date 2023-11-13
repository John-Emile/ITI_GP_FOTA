import serial
import os 
def send_Uart(file_path):
	file_content = 1

	received_data=1
	# Create a Serial object
	ser = serial.Serial("/dev/ttyS0",baudrate=115200,parity=serial.PARITY_NONE,stopbits=serial.STOPBITS_ONE,bytesize=serial.EIGHTBITS)  

	if ser.isOpen() == False:
		ser.Open()
	while True:
		# Data to send
		file=open(file_path,'r')
		while file_content:

			file_content = file.readline()
			# Send the file content as a string
			ser.write(file_content.encode())
			print("zi")
			while received_data != "ok":
				received_data = ser.read(2).decode()
				print(f"Data is {received_data}")
			received_data=1
			


	# Close the serial connection when done
	ser.close()
send_Uart("main.py")	