import serial
import os 
def send_Uart(file_path):
	file_content = 1

	received_data=1
	# Create a Serial object
	ser = serial.Serial("/dev/ttyS0",baudrate=115200,parity=serial.PARITY_NONE,stopbits=serial.STOPBITS_ONE,bytesize=serial.EIGHTBITS)  

	if ser.isOpen() == False:
		ser.Open()
	
	file=open(file_path,'r')
	while file_content :
		print('wait')
		file_content = file.readline()
		if(file_content == '\n'):
			break
		print(file_content)
		print('Then')
		# Send the file content as a string
		ser.write(file_content.encode())
		while received_data != "ok":
			try:
				print('TTTTTTTTTT')
				received_data = ser.read(2).decode()
			except UnicodeDecodeError as e:
				print(f"UnicodeDecodeError: {e}")
				
			# Handle or log the error as needed
			if(received_data != "ok"):
				print(file_content)
				ser.write(file_content.encode())
			print(f"Data is {received_data}")
			
		received_data=1
			
	# Close the serial connection when done
	ser.close()
	

send_Uart("update.txt")
print('Done')
