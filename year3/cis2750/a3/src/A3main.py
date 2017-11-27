#!/usr/bin/python

# /*

#  * CIS2750 F2017

#  * Assignment 2

#  * Dominick Hera 0943778

#  * This file contains the implementation of the linked List API that also utilises an iterator to traverse through the doubly linked list.

#  * This implementation is based on the List API that I implemented in my Assignment 2 for CIS2520, which I took

#  * in the summer of 2017 with professor Judi McCuaig.  The permission to use my CIS2520 code in CIS2750 was obtained on my behalf by

#  * my current CIS2750 professor, Denis Nikitenko.

#  */

from ctypes	import*
from tkinter import filedialog
from tkinter import messagebox
from tkinter import *
import tkinter
import os.path
from os.path import basename
# import tkFileDialog
# import tkMessageBox

class DateTime(Structure):
	    _fields_ = [
        ("date", c_byte * 9),
        ("time", c_byte * 7),
        ("utc", c_bool)]

class Property(Structure):
	    _fields_ = [
        ("propName", c_byte * 200),
        ("propDescr", c_byte * 200)]

class Alarm(Structure):
	    _fields_ = [
        ("action", c_byte * 200),
        ("trigger", c_byte * 200),
        ("properties", Property)]

class Event(Structure):
	    _fields_ = [
        ("UID", c_char_p * 1000),
        ("creationDateTime", DateTime * 100),
        ("startDateTime", DateTime * 100),
        ("properties", Property * 100),
        ("alarms", Alarm * 100)]

class Calendar(Structure):
    _fields_ = [
        ("version", c_float),
        ("prodID", c_char_p * 1000),
        ("events", Event * 20),
        ("properties", Property * 20)]


calLibPath = './bin/parseLib.so'
callib = CDLL(calLibPath)

listLibPath = './bin/listLib.so'
listLib = CDLL(listLibPath)

createCal = callib.createCalendar
createCal.argtypes = [c_char_p,POINTER(POINTER(Calendar))]
createCal.restype = c_int

printErrorCode = callib.printError
printErrorCode.argtypes = [c_void_p]
printErrorCode.restype = c_char_p

printCal = callib.printCalendar

	# Help the Python compiler figure out the types for the function  
printCal.argtypes = [POINTER(Calendar)] #this can also be commented out
printCal.restype = c_char_p     

def donothing():
   filewin = Toplevel(root)
   button = Button(filewin, text="Do nothing button")
   button.pack()

def printVals(Eo1,Eo2):
	print("height")
	# print()

def createCalendar():
	createCalPrompt = Toplevel(root)
<<<<<<< HEAD
	L1 = Label(createCalPrompt, text="User Name")
	L1.pack()
	Eo1 = Entry(createCalPrompt)
	Eo1.pack()
	L2 = Label(createCalPrompt, text="User Name")
	L2.pack()
	Eo2 = Entry(createCalPrompt)
	Eo2.pack()
	print(Eo1.get())
	print(Eo2.get())
	button = Button(createCalPrompt, text="Do nothing button", command=printVals(Eo1.get(),Eo2.get()))
	button.pack(side = BOTTOM)

def createEvent():
	createEventPrompt = Toplevel(root)
	L1 = Label(createEventPrompt, text="User Name")
	L1.pack()
	E1 = Entry(createEventPrompt)
	E1.pack()
	L2 = Label(createEventPrompt, text="User Name")
	L2.pack()
	E2 = Entry(createEventPrompt)
	E2.pack()
	L3 = Label(createEventPrompt, text="User Name")
	L3.pack()
	E3 = Entry(createEventPrompt)
	E3.pack()
	L4 = Label(createEventPrompt, text="User Name")
	L4.pack()
	E4 = Entry(createEventPrompt)
	E4.pack()
	L5 = Label(createEventPrompt, text="User Name")
	L5.pack()
	E5 = Entry(createEventPrompt)
	E5.pack()
	L6 = Label(createEventPrompt, text="User Name")
	L6.pack()
	E6 = Entry(createEventPrompt)
	E6.pack()
	button = Button(createEventPrompt, text="Do nothing button")
	button.pack(side = BOTTOM)
=======
	TextArea = Text(createCalPrompt)
	ScrollBar = Scrollbar(root)
	ScrollBar.config(command=TextArea.yview)
	TextArea.config(yscrollcommand=ScrollBar.set)
	ScrollBar.pack(side=RIGHT, fill=Y)
	TextArea.pack(side=LEFT, fill=BOTH)
	button = Button(createCalPrompt, text="Do nothing button")
	button.pack()
def createEvent():
   createEventPrompt = Toplevel(root)
   L2 = Label(createEventPrompt, text="User Name")
   L2.pack( side = LEFT)
   E2 = Entry(createEventPrompt)
   E2.pack(side = RIGHT)
   button = Button(createEventPrompt, text="Do nothing button")
   button.pack(side = BOTTOM)
>>>>>>> 212e8c62e989549988bda11bbebf3dfbccf338e3

def aboutApp():
	messagebox.showinfo("iCalGUI About", "iCalGUI was created by Dominick Hera\nYou can find more of my work on dominickhera.com")

def openFile():
	filename = filedialog.askopenfilename(initialdir = "/",title = "Select file",filetypes = (("ics files","*.ics"),("all files","*.*")))
	# if filename == True:
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
	calPtr = POINTER(Calendar)()

	returnVal = createCal(fStr,byref(calPtr))
	#call the library function createCalendar() using our alias createCal
	print('returned = ', returnVal)

	calStr = printCal(calPtr)
	calPrint = calStr.decode('utf-8').splitlines()
	# print(calPrint[2])
	calLength = len(calPrint)
	for num in range(calLength):
		fileViewPanel.insert(num, calPrint[num])
	# printErrorCode = callib.printError
	# printErrorCode.argtypes = [c_void_p]
	# printErrorCode.restype = c_char_p
	errorCodeThing = cast(returnVal, c_void_p)
	errorStr = printErrorCode(errorCodeThing)
	logPanel.config(state=NORMAL)
	print(errorStr.decode('utf-8'))
	logPanel.insert(INSERT, errorStr.decode("utf-8"))
	logPanel.pack()
	logPanel.config(state=DISABLED)
	# printErrorCodeintoLog(errorCodeThing) 


def saveFile():
	initFilename = filedialog.asksaveasfilename(initialdir = "/",title = "Select file",filetypes = (("ics files","*.ics"),("all files","*.*")))
	filename = initFilename + ".ics"
	print(basename(filename))


def clearLog():
	logPanel.config(state=NORMAL)
	logPanel.delete(1.0,END)
	logPanel.pack()
	logPanel.config(state=DISABLED)

def failSafeExit():
	result = messagebox.askyesno("Exit?", "Are you sure you want to exit?")
	if result == True:
		deleteCal = callib.deleteCalendar
		deleteCal.argtypes = [POINTER(Calendar)]
		calDelPtr = POINTER(Calendar)()
		deleteCal(calDelPtr)
		root.quit()


root = Tk()
root.title("iCalGUI")
root.geometry('400x425')

menubar = Menu(root)
filemenu = Menu(menubar, tearoff=0)
filemenu.add_command(label="Open", command=openFile, accelerator="Ctrl+O")
filemenu.add_command(label="Save", command=donothing, accelerator="Ctrl+S")
filemenu.add_command(label="Save as...", command=saveFile)
filemenu.add_separator()
filemenu.add_command(label="Exit", command=failSafeExit, accelerator="Ctrl+X")
menubar.add_cascade(label="File", menu=filemenu)
filemenu.bind_all("<Control-x>", failSafeExit)
filemenu.bind_all("<Control-s>", donothing)
createmenu = Menu(menubar, tearoff=0)
createmenu.add_command(label="Create Calendar", command=createCalendar)
createmenu.add_command(label="Create Event", command=createEvent)
menubar.add_cascade(label="Create", menu=createmenu)
helpmenu = Menu(menubar, tearoff=0)
helpmenu.add_command(label="About iCalGUI...", command=aboutApp)
menubar.add_cascade(label="Help", menu=helpmenu)

scrollbar = Scrollbar(root)
scrollbar.pack(side=RIGHT,fill=Y)

# fileViewPanel = tktable.Table(root, rows=5,cols=5,height=15,yscrollcommand=scrollbar.set)

fileViewPanel = Listbox(root,height=15,yscrollcommand=scrollbar.set)

fileViewPanel.pack(side=TOP,fill=BOTH)
scrollbar.config(command=fileViewPanel.yview)
# Label(root, text="Calendar").grid(column=0)
# Label(root, text="Events").grid(column=1)
# file1 = Listbox(root,height=15)
# file2 = Listbox(root,height=15)

# file1.grid(column=0,rowspan=10)
# file2.grid(column=1,rowspan=10)

scrollbar2 = Scrollbar(root)
scrollbar2.pack(side=RIGHT,fill=Y)

logPanel = Text(root,width=50,height=8,yscrollcommand=scrollbar2.set)
# logPanel.insert(INSERT, "1\n2\n3\n4\n5\n6\n7\n8\n")
# logPanel.insert(END, "9")
# logPanel.pack(side=BOTTOM)
logPanel.pack()
logPanel.config(state=DISABLED)
logPanel.tag_add("here", "1.0", "1.4")
logPanel.tag_add("start", "1.8", "1.13")
scrollbar2.config(command=logPanel.yview)

clearButton = Button(root, text="Clear", command=clearLog)
clearButton.pack(side=BOTTOM)
# clearButton.config(side=BOTTOM)

root.config(menu=menubar)

root.protocol("WM_DELETE_WINDOW", failSafeExit)
root.mainloop()
