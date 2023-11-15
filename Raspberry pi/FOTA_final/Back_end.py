import sys
from PyQt5.QtCore import QObject, pyqtSignal, Qt, QUrl ,pyqtSlot
from PyQt5.QtGui import QGuiApplication
from PyQt5.QtQml import QQmlApplicationEngine
from pickle import TRUE
import pygit2
from github import Github
import os
import serial
from cryptography.fernet import Fernet



class Backend(QObject):
	hello_signal = pyqtSignal()
	#self.progress=0
	def __init__(self):
		super().__init__()

	@pyqtSlot()
	def say_hello(self):
		print("Hello, World!")


	@pyqtSlot(str,str,result=bool)
	def authen(self,user_id,user_pass):    
		if user_id == "ziad" and user_pass =="1234":
		    return True
		else :
		    return False      

	@pyqtSlot(result = bool)
	def update (self):


		g = Github('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')

		user = g.get_user()
		repos = user.get_repos()

		latest_commit = ''
		with open('checkUpdates.txt','r') as file:
		    latest_commit = file.read()
		file.close()

		for repo in repos:
		    # get the latest commit
			if(repo.name == 'Data_update'):
				if( repo.get_commits()[0].sha != latest_commit ):
					os.system(f"sudo rm -r {repo.name}")
					pygit2.clone_repository(url=repo.clone_url,path=f'{repo.name}')
					with open('checkUpdates.txt','w') as file:
						file.write(repo.get_commits()[0].sha)
					file.close()
					return True
				else:
					print("no update")
					return False
	@pyqtSlot(str)
	def send_Uart(self,file_path):
		
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
			print(file_content)
			if(file_content == ":00000001FF\n"):
				print("test")
				break
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
		print('Done')
		
	
	@pyqtSlot(str)
	def Decryption(self,input_file):
	# Provide the Fernet key (replace with the actual key used for encryption)
		key = b'ZMpTIe-1buNOGDFBFSlgLpRQ0GsiifWAPA7-LR2nntM='
		print(input_file)
		# Create a Fernet cipher object with the key
		cipher_suite = Fernet(key)

		# Data to be decrypted
		output_file = "update.txt"

		with open(input_file, 'rb') as sourceFile, open(output_file, 'wb') as destFile:
			for line in sourceFile:
				try:
					# Decrypt the data and write it to the destination file
					decrypted_data = cipher_suite.decrypt(line)
					print(line)
					print(decrypted_data)
					destFile.write(decrypted_data)
				except Exception as e:
					print(f"Error decrypting: {e}")

			print(f"Decryption complete. Decrypted data is saved in '{output_file}'.")
			
	@pyqtSlot()
	def Clean_updates(self):
		with open('checkUpdates.txt','w') as file:
			file.write("")
		file.close()



