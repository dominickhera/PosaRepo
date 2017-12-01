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
import gc
import os.path
import datetime
# import mysql.connector
from os.path import basename

# dbName = "dhera"
# uName = "dhera"
# passwd = "0943778"

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

# print('9\n')
createCal = callib.createCalendar
createCal.argtypes = [c_char_p,POINTER(POINTER(Calendar))]
createCal.restype = c_int

initCal = callib.manualCalInit

initEvent = callib.manualEventInit
# initEvent.argtypes = [POINTER(POINTER(Calendar)), c_char, c_byte, c_byte]
# initCal.argtypes = [POINTER(POINTER(Calendar)),c_byte , c_float]
# initCal.restype = c_void_p
# versionType = "2.0"

# print("fucker\n")
printErrorCode = callib.printError
printErrorCode.argtypes = [c_void_p]
printErrorCode.restype = c_char_p

printCal = callib.printCalendar

	# Help the Python compiler figure out the types for the function  
printCal.argtypes = [POINTER(Calendar)] #this can also be commented out
printCal.restype = c_char_p
# print('9\n')
printErrorCode = callib.printError
printErrorCode.argtypes = [c_void_p]
printErrorCode.restype = c_char_p     
# print('9\n')

deleteCal = callib.deleteCalendar
deleteCal.argtypes = [POINTER(Calendar)]

calPtr = POINTER(Calendar)()

class createCalendarWindow(object):
	def __init__(self,master):
		top=self.top=Toplevel(master)
		self.L1 = Label(top, text="PRODID").grid(row=0, stick=W)
		self.E1 = Entry(top)
		self.E1.grid(row=0,column=1)
		self.submitButton = Button(top, text="Create Calendar",command=self.cleanUp).grid(row=1,sticky=W)
	def cleanUp(self):
		print(self.E1.get())
		prodidString = bytes(self.E1.get(), encoding='utf-8')
		initCal(byref(calPtr), prodidString)
		self.top.destroy()

class createEventWindow(object):
	def __init__(self,master):
		top=self.top=Toplevel(master)
		self.L2 = Label(top, text="UID").grid(row=0, stick=W)
		# self.L2 = Label(top, text="Second Label").grid(row=1,sticky=W)
		self.E2 = Entry(top)
		self.E2.grid(row=0,column=1)
	
		self.submitButton = Button(top, text="Create Calendar",command=self.cleanUp).grid(row=2,sticky=W)
	def cleanUp(self):
		# print(self.E2.get())
		dateVal = bytes(datetime.datetime.now().strftime('%Y%m%d'), encoding='utf-8')
		timeVal = bytes(datetime.datetime.now().strftime('%H%M%S'), encoding='utf-8')
		# print(dateVal," time val >", timeVal)
		uidString = bytes(self.E2.get(), encoding='utf-8')
		initEvent(byref(calPtr), uidString, dateVal, timeVal)
		self.top.destroy()


class main(object):
	def __init__(self,master):
		self.master=master
		# print('10\n')
		self.menubar = Menu(root)
		# print('11\n')
		self.filemenu = Menu(self.menubar, tearoff=0)
		# print('12\n')
		self.filemenu.add_command(label="Open", accelerator="Ctrl+O", command=self.openFile)
		# print('13\n')
		self.filemenu.add_command(label="Save",  accelerator="Ctrl+S")
		# print('14\n')
		self.filemenu.add_command(label="Save as...", command=self.saveFile)
		self.filemenu.add_command(label="Delete Current Cal", command=self.deleteCal)
		self.filemenu.add_command(label="print Current Cal", command=self.printCal)
		# print('15\n')
		self.filemenu.add_separator()
		# print('16\n')
		self.filemenu.add_command(label="Exit", command=self.failSafeExit, accelerator="Ctrl+X")
		# print('17\n')
		self.menubar.add_cascade(label="File", menu=self.filemenu)
		# print('18\n')
		self.filemenu.bind_all("<Control-X>", self.failSafeExit)
		# print('19\n')
		self.filemenu.bind_all("<Control-s>", self.donothing)
		# print('20\n')
		self.createmenu = Menu(self.menubar, tearoff=0)
		# print('21\n')
		self.createmenu.add_command(label="Create Calendar", command=self.createCalEvent)
		# print('22\n')
		self.createmenu.add_command(label="Create Event", command=self.createEventEvent)
		# print('23\n')
		self.menubar.add_cascade(label="Create", menu=self.createmenu)
		# print('24\n')
		self.databaseMenu = Menu(self.menubar, tearoff=0)
		# print('25\n')
		self.databaseMenu.add_command(label="Store All Events", command=self.aboutApp)
		# print('26\n')
		self.databaseMenu.add_command(label="Store Current Event", command=self.aboutApp)
		# print('27\n')
		self.databaseMenu.add_command(label="Clear All Data", command=self.aboutApp)
		# print('28\n')
		self.databaseMenu.add_command(label="Display DB Status", command=self.aboutApp)
		# print('29\n')
		self.databaseMenu.add_command(label="Execute Query", command=self.aboutApp)
		# print('30\n')
		self.menubar.add_cascade(label="Database", menu=self.databaseMenu)
		# print('31\n')
		self.helpmenu = Menu(self.menubar, tearoff=0)
		# print('32\n')
		self.helpmenu.add_command(label="About iCalGUI...", command=self.aboutApp)
		# print('33\n')
		self.menubar.add_cascade(label="Help", menu=self.helpmenu)
		# print('34\n')
		self.scrollbar = Scrollbar(root)
		# print('35\n')
		self.scrollbar.pack(side=RIGHT,fill=Y)
		# print('36\n')
		self.fileViewPanel = Listbox(root,height=15,yscrollcommand=self.scrollbar.set)
		# print('37\n')
		self.fileViewPanel.pack(side=TOP,fill=BOTH)
		# print('38\n')
		self.scrollbar.config(command=self.fileViewPanel.yview)
		# print('39\n')
		self.scrollbar2 = Scrollbar(root)
		# print('40\n')
		self.scrollbar2.pack(side=RIGHT,fill=Y)
		# print('41\n')
		self.logPanel = Text(root,width=50,height=8,yscrollcommand=self.scrollbar2.set)
		# print('42\n')
		self.logPanel.pack()
		# print('43\n')
		self.logPanel.config(state=DISABLED)
		# print('44\n')
		self.logPanel.tag_add("here", "1.0", "1.4")
		# print('45\n')
		self.logPanel.tag_add("start", "1.8", "1.13")
		# print('46\n')
		self.scrollbar2.config(command=self.logPanel.yview)
		# print('47\n')
		self.clearButton = Button(root, text="Clear", command=self.clearLog)
		# print('48\n')
		self.clearButton.pack(side=BOTTOM)
		# print('49\n')
		self.master.config(menu=self.menubar)
		# print('50\n')
		self.master.protocol("WM_DELETE_WINDOW", self.failSafeExit)
		# print('51\n')
	def createCalEvent(self):
		self.w=createCalendarWindow(self.master)
		self.master.wait_window(self.w.top)

	def createEventEvent(self):
		self.w=createEventWindow(self.master)
		self.master.wait_window(self.w.top)
		# print(self.createEventWindow.E2.get())

	def entryValue(self):
		return self.w.value

	def aboutApp(self):
		messagebox.showinfo("iCalGUI About", "iCalGUI was created by Dominick Hera\nYou can find more of my work on dominickhera.com")

	def openFile(self):
		filename = filedialog.askopenfilename(initialdir = "./assets/",title = "Select file",filetypes = (("ics files","*.ics"),("all files","*.*")))
		print('1\n')
		# if filename:
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
			# createCal.argtypes = [c_char_p,POINTER(POINTER(Calendar))]
			# createCal.restype = c_int

		# calPtr = POINTER(Calendar)()
		print('1\n')

		# calPtr = initCal()
		returnVal = createCal(fStr,byref(calPtr))
		print('2\n')
			#call the library function createCalendar() using our alias createCal
		# print('returned = ', returnVal)
		print('3\n')

		# calStr = printCal(calPtr)
		# calPrint = calStr.decode('utf-8')
		# print(calPrint)
			# calPrint = calStr.decode('utf-8').splitlines()
			# print(calPrint[2])


			# calLength = len(calPrint) - 1
			# for num in range(calLength):
			# 	self.fileViewPanel.insert(num, calPrint[num])
			# printErrorCode = callib.printError
			# printErrorCode.argtypes = [c_void_p]
			# printErrorCode.restype = c_char_p
		errorCodeThing = cast(returnVal, c_void_p)
		# print('4\n')
		errorStr = printErrorCode(errorCodeThing)
		# print('5\n')
		self.logPanel.config(state=NORMAL)
		# print('6\n')
		print(errorStr.decode('utf-8'))
		self.logPanel.insert(INSERT, errorStr.decode("utf-8"))
		# print('7\n')
		self.logPanel.pack()
		# print('8\n')
		self.logPanel.config(state=DISABLED)
		# print('9\n')

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
			deleteCal(calPtr)
			# gc.collect(calPtr)
			root.quit()
	def deleteCal(self):
		# deleteCal = callib.deleteCalendar
		# deleteCal.argtypes = [POINTER(Calendar)]
		# calDelPtr = POINTER(Calendar)()
		# gc.collect(calPtr)
		deleteCal(calPtr)
		# gc.collect(calPtr)
	def printCal(self):
		if calPtr:
			calStr = printCal(calPtr)
			calPrint = calStr.decode('utf-8')
			print(calPrint)

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
	print('boop')
	# root.config(menu=menubar)
	# root.protocol("WM_DELETE_WINDOW", failSafeExit)
	root.mainloop()