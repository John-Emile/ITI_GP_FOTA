import tkinter as tk
from tkinter import *
from tkinter import filedialog
import os
import git
from Fernet import *

def browse_file():
    file_path = filedialog.askopenfilename(title="Select a file")
    File_Entry.delete(0, tk.END)  # Clear the current content
    File_Entry.insert(0, file_path)
			
def update():
	try:
		#Encryption(File_Entry.get())
		os.system('git config --global user.email "abdelrahmanelneshwy77@gmail.com')
		os.system('git add .')
		os.system(f'git commit -m \'{comment_Entry.get()}\' ')
		os.system('git push origin main')
		File_Entry.delete(0, tk.END)
		comment_Entry.delete(0, tk.END)
	except:
		print("wrong path")

	
    


# Create the main application window
iti_window =tk.Tk()
iti_window.geometry("900x480")
iti_window.title("ITI")
# ----------------------------------------------------------canves------------------------------------------------------#
canves1 =Canvas(iti_window, width=900, height=480,background="Gray")
canves1.pack()

image = PhotoImage(file=".//iti-logo.png")
desired_width = 200
desired_height = 200

# Resize the image using the subsample method
image = image.subsample(image.width() // desired_width, image.height() // desired_height)
ITI_label = tk.Label(canves1, 
     image=image
     )
ITI_label.place(x=600,y=50)
# Create and place labels and entry fields for username and password

update_button = tk.Button(canves1,
	  text="update ",
	  font=("Arial", 20, "bold"),
	  command=update,
	  background="yellow",
	  foreground="black"
	  )
update_button.place(x=200,y = 400)

browse_button = tk.Button(canves1, 
			text="Browse",
			command=browse_file,
			font=("Arial", 20, "bold"),
			background="yellow",
	  		foreground="black"
			 )
browse_button.place(x=400,y = 400)

File_label = tk.Label(canves1, 
	text="File Path",
	font=("Arial", 20, "bold"),
	background="Orange",
	foreground="white",
	borderwidth=10)
File_label.place(x=60,y=100)
File_Entry = tk.Entry(canves1,
     	     font=("Arial", 15, "bold"),
     	     width=30,
     	     borderwidth=10
     	     )
File_Entry.place(x=220,y = 107)


comment_label = tk.Label(canves1, 
	text="comment",
	font=("Arial", 20, "bold"),
	background="Orange",
	foreground="white",
	borderwidth=10)
comment_label.place(x=60,y=200)
comment_Entry = tk.Entry(canves1,
    		font=("Arial", 15, "bold"),
      		width=30,
      		borderwidth=10
    		)
comment_Entry.place(x=220,y = 207)

# Run the main event loop
iti_window.mainloop()


