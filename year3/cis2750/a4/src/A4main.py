#!/usr/bin/python

# /*

#  * CIS2750 F2017

#  * Assignment 4

#  * Dominick Hera 0943778

#  * This file contains the implementation of the linked List API that also utilises an iterator to traverse through the doubly linked list.

#  * This implementation is based on the List API that I implemented in my Assignment 2 for CIS2520, which I took

#  * in the summer of 2017 with professor Judi McCuaig.  The permission to use my CIS2520 code in CIS2750 was obtained on my behalf by

#  * my current CIS2750 professor, Denis Nikitenko.

#  */

from ctypes	import*
from tkinter import filedialog
import tkinter.simpledialog
from tkinter import messagebox
from tkinter import *
import tkinter
import os.path
import datetime
from os.path import basename

class Calendar(Structure):
    _fields_ = [
        ("version", c_float),
        ("prodID", c_byte * 1000),
        ("events", c_void_p),
        ("properties", c_void_p)]


calLibPath = './bin/parseLib.so'
callib = CDLL(calLibPath)

listLibPath = './bin/listLib.so'
listLib = CDLL(listLibPath)

createCal = callib.createCalendar
createCal.argtypes = [c_char_p,POINTER(POINTER(Calendar))]
createCal.restype = c_int


# print("fucker\n")
printErrorCode = callib.printError
printErrorCode.argtypes = [c_void_p]
printErrorCode.restype = c_char_p

printCal = callib.printCalendar

	# Help the Python compiler figure out the types for the function  
# printCal.argtypes = [POINTER(Calendar)] #this can also be commented out
# printCal.restype = c_char_p     


class createCalendarWindow(object):
	def __init__(self,master):
		top=self.top=Toplevel(master)
		self.L1 = Label(top, text="UID").grid(row=0, stick=W)
		self.E1 = Entry(top)
		self.E1.grid(row=0,column=1)
		self.submitButton = Button(top, text="Create Calendar",command=self.cleanUp).grid(row=1,sticky=W)
	def cleanUp(self):
		print(self.E1.get())
		self.top.destroy()

class createEventWindow(object):
	def __init__(self,master):
		top=self.top=Toplevel(master)
		self.L2 = Label(top, text="UID").grid(row=0, stick=W)
		# self.L2 = Label(top, text="Second Label").grid(row=1,sticky=W)
		self.E2 = Entry(top)
		self.E2.grid(row=0,column=1)
		# self.E2 = Entry(top).grid(row=1,column=1)
		self.submitButton = Button(top, text="Create Calendar",command=self.cleanUp).grid(row=2,sticky=W)
	def cleanUp(self):
		# print(self.E2.get())
		self.top.destroy()


class main(object):
	def __init__(self,master):
		self.master=master
		self.menubar = Menu(root)
		self.filemenu = Menu(self.menubar, tearoff=0)
		self.filemenu.add_command(label="Open", accelerator="Ctrl+O", command=self.openFile)
		self.filemenu.add_command(label="Save",  accelerator="Ctrl+S")
		self.filemenu.add_command(label="Save as...", command=self.saveFile)
		self.filemenu.add_separator()
		self.filemenu.add_command(label="Exit", command=self.failSafeExit, accelerator="Ctrl+X")
		self.menubar.add_cascade(label="File", menu=self.filemenu)
		self.filemenu.bind_all("<Control-X>", self.failSafeExit)
		self.filemenu.bind_all("<Control-s>", self.donothing)
		self.createmenu = Menu(self.menubar, tearoff=0)
		self.createmenu.add_command(label="Create Calendar", command=self.createCalEvent)
		self.createmenu.add_command(label="Create Event", command=self.createEventEvent)
		self.menubar.add_cascade(label="Create", menu=self.createmenu)
		self.databaseMenu = Menu(self.menubar, tearoff=0)
		self.databaseMenu.add_command(label="Store All Events", command=self.aboutApp)
		self.databaseMenu.add_command(label="Store Current Event", command=self.aboutApp)
		self.databaseMenu.add_command(label="Clear All Data", command=self.aboutApp)
		self.databaseMenu.add_command(label="Display DB Status", command=self.aboutApp)
		self.databaseMenu.add_command(label="Execute Query", command=self.aboutApp)
		self.menubar.add_cascade(label="Database", menu=self.databaseMenu)
		self.helpmenu = Menu(self.menubar, tearoff=0)
		self.helpmenu.add_command(label="About iCalGUI...", command=self.aboutApp)
		self.menubar.add_cascade(label="Help", menu=self.helpmenu)
		self.scrollbar = Scrollbar(root)
		self.scrollbar.pack(side=RIGHT,fill=Y)
		self.fileViewPanel = Listbox(root,height=15,yscrollcommand=self.scrollbar.set)
		self.fileViewPanel.pack(side=TOP,fill=BOTH)
		self.scrollbar.config(command=self.fileViewPanel.yview)
		self.scrollbar2 = Scrollbar(root)
		self.scrollbar2.pack(side=RIGHT,fill=Y)
		self.logPanel = Text(root,width=50,height=8,yscrollcommand=self.scrollbar2.set)
		self.logPanel.pack()
		self.logPanel.config(state=DISABLED)
		self.logPanel.tag_add("here", "1.0", "1.4")
		self.logPanel.tag_add("start", "1.8", "1.13")
		self.scrollbar2.config(command=self.logPanel.yview)
		self.clearButton = Button(root, text="Clear", command=self.clearLog)
		self.clearButton.pack(side=BOTTOM)
		self.master.config(menu=self.menubar)
		self.master.protocol("WM_DELETE_WINDOW", self.failSafeExit)

	def createCalEvent(self):
		self.w=createCalendarWindow(self.master)
		self.master.wait_window(self.w.top)

	def createEventEvent(self):
		self.w=createEventWindow(self.master)
		self.master.wait_window(self.w.top)
		print(self.createEventWindow.E2.get())

	def entryValue(self):
		return self.w.value

	def aboutApp(self):
		messagebox.showinfo("iCalGUI About", "iCalGUI was created by Dominick Hera\nYou can find more of my work on dominickhera.com")

	def openFile(self):
		filename = filedialog.askopenfilename(initialdir = "./assets/",title = "Select file",filetypes = (("ics files","*.ics"),("all files","*.*")))
		if filename:
			root.title("iCalGUI - " + basename(filename))
			# openFileName = basename(filename)

		# filename = './assets/test2.ics'
			fStr = filename.encode('utf-8')

		# createCal = callib.createCalendar
		# createCal.argtypes = [c_char_p,POINTER(POINTER(Calendar))]
		# createCal.restype = c_int

		# printCal = callib.printCalendar

		# # Help the Python compiler figure out the types for the function  
		# printCal.argtypes = [POINTER(Calendar)] #this can also be commented out
		# printCal.restype = c_char_p             #this CANNOT be commented out! Otherwise Python will decide that printCal returns an int!

		# create a variable that will store the pointer to the calendar
		# if we don't do this, Python will be unhappy


			# createCal = callib.createCalendar
			createCal.argtypes = [c_char_p,POINTER(POINTER(Calendar))]
			createCal.restype = c_int

			calPtr = POINTER(Calendar)()

			returnVal = createCal(fStr,byref(calPtr))
			#call the library function createCalendar() using our alias createCal
			print('returned = ', returnVal)

			calStr = printCal(calPtr)
			calPrint = calStr.decode('utf-8')
			print(calPrint)
			# calPrint = calStr.decode('utf-8').splitlines()
			# print(calPrint[2])


			# calLength = len(calPrint) - 1
			# for num in range(calLength):
			# 	self.fileViewPanel.insert(num, calPrint[num])
			# printErrorCode = callib.printError
			# printErrorCode.argtypes = [c_void_p]
			# printErrorCode.restype = c_char_p
			# errorCodeThing = cast(returnVal, c_void_p)
			# errorStr = printErrorCode(errorCodeThing)
			# self.logPanel.config(state=NORMAL)
			# print(errorStr.decode('utf-8'))
			# self.logPanel.insert(INSERT, errorStr.decode("utf-8"))
			# self.logPanel.pack()
			# self.logPanel.config(state=DISABLED)

		# printErrorCodeintoLog(errorCodeThing) 

	def saveFile(self):
		initFilename = filedialog.asksaveasfilename(initialdir = "/",title = "Select file",filetypes = (("ics files","*.ics"),("all files","*.*")))
		filename = initFilename + ".ics"
		print(basename(filename))


	def clearLog(self):
		self.logPanel.config(state=NORMAL)
		self.logPanel.delete(1.0,END)
		self.logPanel.pack()
		self.logPanel.config(state=DISABLED)

	def failSafeExit(self):
		result = messagebox.askyesno("Exit?", "Are you sure you want to exit?")
		if result == True:
			# deleteCal = callib.deleteCalendar
			# deleteCal.argtypes = [POINTER(Calendar)]
			# calDelPtr = POINTER(Calendar)()
			# deleteCal(calDelPtr)
			root.quit()

	def donothing(self):
   		filewin = Toplevel(root)
   		button = Button(filewin, text="Do nothing button")
   		button.pack()

if __name__ == "__main__":
	root = Tk()
	root.title("iCalGUI")
	root.geometry('400x425')
	# menubar = Menu(root)
	m=main(root)
	# root.config(menu=menubar)
	# root.protocol("WM_DELETE_WINDOW", failSafeExit)
	root.mainloop()