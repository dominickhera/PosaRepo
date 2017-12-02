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
import mysql.connector
from os.path import basename

# dbName = "dhera"
# uName = "dhera"
# passwd = "0943778"

# def grabDatabase():
# 	global conn
# 	if (len(sys.argv) < 1):
# 		userName = sys.argv[1]
# 		if userName:
# 			dbName = userName
# 			uName = userName
# 			try:
# 				conn = mysql.connector.connect(host="dursley.socs.uoguelph.ca",database=dbName,user=uName,password="")
# 			except mysql.connector.Error as err:
# 				print("Something went wrong: {}".format(err))
# 				exit()
# 		else:
# 			dbName = "dhera"
# 			uName = "dhera"
# 			passwd = "0943778"
# 			try:
# 				conn = mysql.connector.connect(host="dursley.socs.uoguelph.ca",database=dbName,user=uName,password=passwd)
# 				cursor = conn.cursor()
# 			except mysql.connector.Error as err:
# 				print("Something went wrong: {}".format(err))
# 				exit()
	

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

writeCal = callib.writeCalendar
writeCal.argtypes = [c_char_p,POINTER(Calendar)]
writeCal.restype = c_int

getCalEventCount = callib.getEventListSize
getCalEventCount.argtypes = [POINTER(Calendar)]
getCalEventCount.restype = c_int

getListLength = listLib.getLength

createIter = listLib.createIterator

nextElem = listLib.nextElement
# getListLength.argtypes[]
# getListLength.restype = c_int

initCal = callib.manualCalInit

initEvent = callib.manualEventInit
initEvent.argtypes = [POINTER(POINTER(Calendar)), c_char_p, c_char_p, c_char_p]
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

mainFileName = " "
# conn = None

class queryWindow(object):
	def __init__(self,master):
		top=self.top=Toplevel(master)
		self.label1 = Label(top, text="Query")
		self.label2 = Label(top, text="Results")
		self.Listbox1 = Listbox(top, height=15)
		self.Listbox2 = Listbox(top, height=15)
		self.label1.grid(row=0,column=0)
		self.label2.grid(row=0,column=3)
		self.Listbox1.grid(row=1, column=0, rowspan = 15, columnspan = 2)
		self.Listbox2.grid(row=1 ,column=3, rowspan = 15, columnspan = 2)
		self.helpButton = Button(top, text="Help", command=self.helpLog)
		self.helpButton.grid(row=17,column=0)
		self.clearButton = Button(top, text="Help", command=self.clearQueryLog)
		self.clearButton.grid(row=18,column=0)
	def helpLog(self):
		print("hiya")
	def clearQueryLog(self):
		print("fudge")
	def cleanUp(self):
		self.top.destroy()

class createCalendarWindow(object):
	def __init__(self,master):
		top=self.top=Toplevel(master)
		self.L1 = Label(top, text="PRODID").grid(row=0, stick=W)
		self.E1 = Entry(top)
		self.E1.grid(row=0,column=1)
		self.submitButton = Button(top, text="Create Calendar",command=self.cleanUp).grid(row=1,sticky=W)
	def cleanUp(self):
		# print(self.E1.get())
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
		# calLength = getCalEventCount(calPtr)
		# for num in range(calLength):
			# main.self.Listbox1.insert(num, num)
		# testCal = calPtr.contents
		# stuff = cast(testCal.events, c_void_p)
		# # print('',testCal.evenlength)
		# print("list length", getListLength(stuff))
		# print("the amount of events are", testCal.events.length)
		self.top.destroy()


class main(object):
	def __init__(self,master):
		# global conn
		self.master=master
		self.menubar = Menu(root)
		self.filemenu = Menu(self.menubar, tearoff=0)
		self.filemenu.add_command(label="Open", accelerator="Ctrl+O", command=self.openFile)
		self.filemenu.add_command(label="Save",  accelerator="Ctrl+S", command=self.saveFile)
		self.filemenu.add_command(label="Save as...", command=self.saveAsFile)
		self.filemenu.add_command(label="Delete Current Cal", command=self.deleteCal)
		self.filemenu.add_command(label="Print Current Cal", command=self.printCal)
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
		self.databaseMenu.add_command(label="Display DB Status", command=self.displayDBStatus)
		self.databaseMenu.add_command(label="Execute Query", command=self.aboutApp)
		self.menubar.add_cascade(label="Database", menu=self.databaseMenu)
		self.helpmenu = Menu(self.menubar, tearoff=0)
		self.helpmenu.add_command(label="About iCalGUI...", command=self.aboutApp)
		self.menubar.add_cascade(label="Help", menu=self.helpmenu)
		# self.scrollbar = Scrollbar(root)
		# self.scrollbar.pack(side=RIGHT,fill=Y)
		
		# self.fileViewPanel = Listbox(root,height=15,yscrollcommand=self.scrollbar.set)
		# self.fileViewPanel.pack(side=TOP,fill=BOTH)

		self.label1 = Label(root, text="Evt No.")
		self.label2 = Label(root, text="Props")
		self.label3 = Label(root, text="Alarms")
		self.label4 = Label(root, text="Summary")
		self.Listbox1 = Listbox(root, height=15)
		self.Listbox2 = Listbox(root, height=15)
		self.Listbox3 = Listbox(root, height=15)
		self.Listbox4 = Listbox(root, height=15)
		self.label1.grid(row=0,column=0)
		self.label2.grid(row=0,column=3)
		self.label3.grid(row=0,column=5)
		self.label4.grid(row=0,column=7)
		self.Listbox1.grid(row=1, column=0, rowspan = 15, columnspan = 2)
		self.Listbox2.grid(row=1 ,column=3, rowspan = 15, columnspan = 2)
		self.Listbox3.grid(row=1 ,column=5, rowspan = 15, columnspan = 2)
		self.Listbox4.grid(row=1 ,column=7, rowspan = 15, columnspan = 2)
		

		# self.scrollbar.config(command=self.fileViewPanel.yview)
		self.scrollbar2 = Scrollbar(root)
		self.scrollbar2.grid()
		# self.scrollbar2.pack(side=RIGHT,fill=Y)
		self.logPanel = Text(root,width=100,height=8,yscrollcommand=self.scrollbar2.set)
		# self.logPanel = Text(root,yscrollcommand=self.scrollbar2.set)
		self.logPanel.grid(row=16,column=0, rowspan=1, columnspan=50)
		# self.logPanel.pack()
		self.logPanel.config(state=DISABLED)
		self.logPanel.tag_add("here", "1.0", "1.4")
		self.logPanel.tag_add("start", "1.8", "1.13")
		self.scrollbar2.config(command=self.logPanel.yview)
		self.clearButton = Button(root, text="Clear", command=self.clearLog)
		self.clearButton.grid(row=17,column=0)
		# self.clearButton.pack(side=BOTTOM)
		self.master.config(menu=self.menubar)
		if (len(sys.argv) < 1):
		userName = sys.argv[1]
		if userName:
			dbName = userName
			uName = userName
			try:
				conn = mysql.connector.connect(host="dursley.socs.uoguelph.ca",database=dbName,user=uName,password="")
			except mysql.connector.Error as err:
				print("Something went wrong: {}".format(err))
				exit()
		else:
			dbName = "dhera"
			uName = "dhera"
			passwd = "0943778"
			try:
				conn = mysql.connector.connect(host="dursley.socs.uoguelph.ca",database=dbName,user=uName,password=passwd)
				cursor = conn.cursor()
			except mysql.connector.Error as err:
				print("Something went wrong: {}".format(err))
				exit()
		cursor = conn.cursor()
		self.master.protocol("WM_DELETE_WINDOW", self.failSafeExit)
	def createCalEvent(self):
		self.w=createCalendarWindow(self.master)
		self.master.wait_window(self.w.top)

	def createEventEvent(self):
		self.w=createEventWindow(self.master)
		self.master.wait_window(self.w.top)
		calLength = getCalEventCount(calPtr)
		self.Listbox1.delete(0,END)
		for num in range(calLength):
			self.Listbox1.insert(num, num + 1)
		# print(self.createEventWindow.E2.get())

	def entryValue(self):
		return self.w.value

	def aboutApp(self):
		messagebox.showinfo("iCalGUI About", "iCalGUI was created by Dominick Hera\nYou can find more of my work on dominickhera.com")

	def openFile(self):
		global mainFileName
		filename = filedialog.askopenfilename(initialdir = "./assets/",title = "Select file",filetypes = (("ics files","*.ics"),("all files","*.*")))
		# print('1\n')
		if filename:
			mainFileName = filename
			# print("filename is ",mainFileName)
			root.title("iCalGUI - " + basename(filename))
				# openFileName = basename(filename)

			# filename = './assets/test2.ics'
			fStr = filename.encode('utf-8')



			returnVal = createCal(fStr,byref(calPtr))
			# print('2\n')
				#call the library function createCalendar() using our alias createCal
			# print('returned = ', returnVal)
			# print('3\n')

			calStr = printCal(calPtr)
			# calPrint = calStr.decode('utf-8')
			# print(calPrint)
			calPrint = calStr.decode('utf-8').splitlines()
				# print(calPrint[2])


			calLength = getCalEventCount(calPtr)
			self.Listbox1.delete(0,END)
			for num in range(calLength):
				self.Listbox1.insert(num, num + 1)
			printErrorCode = callib.printError
			printErrorCode.argtypes = [c_void_p]
			printErrorCode.restype = c_char_p
			errorCodeThing = cast(returnVal, c_void_p)
			# print('4\n')
			errorStr = printErrorCode(errorCodeThing)
			# print('5\n')
			self.logPanel.config(state=NORMAL)
			# print('6\n')
			print(errorStr.decode('utf-8'))
			self.logPanel.insert(INSERT, errorStr.decode("utf-8"))
			# print('7\n')
			self.logPanel.grid(row=16,column=0, rowspan=1, columnspan=50)
			# self.logPanel.pack()
			# print('8\n')
			self.logPanel.config(state=DISABLED)
		# print('9\n')

		# printErrorCodeintoLog(errorCodeThing) 
	def saveFile(self):
		global mainFileName
		if mainFileName:
			fStr = mainFileName.encode('utf-8')
			# print('1\n')
			writeReturnVal = writeCal(fStr, calPtr)
			# print('2\n')
			print('returned = ', writeReturnVal)
			errorCodeThing = cast(writeReturnVal, c_void_p)
			# # print('4\n')
			errorStr = printErrorCode(errorCodeThing)
			# # print('5\n')
			self.logPanel.config(state=NORMAL)
			# # print('6\n')
			print(errorStr.decode('utf-8'))
			self.logPanel.insert(INSERT, errorStr.decode("utf-8"))
			# # print('7\n')
			self.logPanel.grid(row=16,column=0, rowspan=1, columnspan=50)
			# self.logPanel.pack()
			# # print('8\n')
			self.logPanel.config(state=DISABLED)

	def saveAsFile(self):
		initFilename = filedialog.asksaveasfilename(initialdir = "./assets/outputFiles/",title = "Select location",filetypes = (("ics files","*.ics"),("all files","*.*")))
		filename = initFilename
		global mainFileName
		mainFileName = filename
		print(basename(filename))

		fStr = initFilename.encode('utf-8')
		# print('1\n')
		writeReturnVal = writeCal(fStr, calPtr)
		# print('2\n')
		print('returned = ', writeReturnVal)
		errorCodeThing = cast(writeReturnVal, c_void_p)
		# # print('4\n')
		errorStr = printErrorCode(errorCodeThing)
		# # print('5\n')
		self.logPanel.config(state=NORMAL)
		# # print('6\n')
		print(errorStr.decode('utf-8'))
		self.logPanel.insert(INSERT, errorStr.decode("utf-8"))
		# # print('7\n')
		self.logPanel.grid(row=16,column=0, rowspan=1, columnspan=50)
		# self.logPanel.pack()
		# # print('8\n')
		self.logPanel.config(state=DISABLED)



	def clearLog(self):
		self.logPanel.config(state=NORMAL)
		self.logPanel.delete(1.0,END)
		self.logPanel.grid(row=16,column=0, rowspan=1, columnspan=50)
		# self.logPanel.pack()
		self.logPanel.config(state=DISABLED)

	def failSafeExit(self):
		global mainFileName
		result = messagebox.askyesno("Exit?", "Are you sure you want to exit?")
		if result == True:
			# deleteCal = callib.deleteCalendar
			# deleteCal.argtypes = [POINTER(Calendar)]
			# calDelPtr = POINTER(Calendar)()
			deleteCal(calPtr)
			if mainFileName != " ":
				self.saveFile()
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

	def displayDBStatus(self):
		# global conn
		self.logPanel.config(state=NORMAL)
		organizerCount = self.cursor.execute("SELECT COUNT(*) FROM organizers")
		eventCount = self.cursor.execute("SELECT COUNT(*) FROM event")
		self.logPanel.insert(INSERT, "Database has ", organizerCount, " organizers and ",eventCount," events.\n")
		self.logPanel.grid(row=16,column=0, rowspan=1, columnspan=50)
		self.logPanel.config(state=DISABLED)

	def clearAllData(self):
		# global conn
		self.cursor.execute("DELETE FROM organizers")
		self.cursor.execute("DELETE FROM event")
		self.displayDBStatus()

	def executeQuery(self):
		self.w=queryWindow(self.master)
		self.displayDBStatus()

	def storeAllEvents(self):
		self.displayDBStatus()

	def storeCurrentEvent(self):
		self.displayDBStatus()

	def donothing(self):
   		filewin = Toplevel(root)
   		button = Button(filewin, text="Do nothing button")
   		button.pack()

if __name__ == "__main__":
	root = Tk()
	root.title("iCalGUI")
	# grabDatabase()
	# cursor = conn.cursor()
	# root.geometry('730x425')
	# menubar = Menu(root)
	# print(sys.argv[1])
	m=main(root)
	# print('boop')
	# root.config(menu=menubar)
	# root.protocol("WM_DELETE_WINDOW", failSafeExit)
	root.mainloop()
