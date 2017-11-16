#!/usr/bin/python
from tkinter import filedialog
from tkinter import messagebox
from tkinter import *
import tkinter
import os.path
from os.path import basename
# import tkFileDialog
# import tkMessageBox
import tktable

def donothing():
   filewin = Toplevel(root)
   button = Button(filewin, text="Do nothing button")
   button.pack()

def createCalendar():
	print("lolcats")

def createEvent():
	print("othercats")

def aboutApp():
	messagebox.showinfo("iCalGUI About", "iCalGUI was created by Dominick Hera\nYou can find more of my work on dominickhera.com")

def failSafeExit():
	result = messagebox.askyesno("Exit?", "Are you sure you want to exit?")
	if result == True:
		root.quit()

def openFile():
	filename = filedialog.askopenfilename(initialdir = "/",title = "Select file",filetypes = (("ics files","*.ics"),("all files","*.*")))
	# print(basename(filename))
	root.title("iCalGUI - " + basename(filename))

def saveFile():
	filename = filedialog.asksaveasfilename(initialdir = "/",title = "Select file",filetypes = (("ics files","*.ics"),("all files","*.*")))
	print (filename)
	print(basename(filename))



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

# fileViewPanel = Listbox(root,height=15,yscrollcommand=scrollbar.set)
# fileViewPanel.insert(1, "Python")
# fileViewPanel.insert(2, "Perl")
# fileViewPanel.insert(3, "C")
# fileViewPanel.insert(4, "PHP")
# fileViewPanel.insert(5, "JSP")
# fileViewPanel.insert(6, "Ruby")

# fileViewPanel.pack(side=TOP,fill=BOTH)
# scrollbar.config(command=fileViewPanel.yview)
# Label(root, text="Calendar").grid(column=0)
# Label(root, text="Events").grid(column=1)
# file1 = Listbox(root,height=15)
# file2 = Listbox(root,height=15)

# file1.grid(column=0,rowspan=10)
# file2.grid(column=1,rowspan=10)

scrollbar2 = Scrollbar(root)
scrollbar2.pack(side=RIGHT,fill=Y)

logPanel = Text(root,width=50,height=8,yscrollcommand=scrollbar2.set)
logPanel.insert(INSERT, "1\n2\n3\n4\n5\n6\n7\n8\n")
logPanel.insert(END, "9")
# logPanel.pack(side=BOTTOM)
logPanel.pack()
logPanel.config(state=DISABLED)
logPanel.tag_add("here", "1.0", "1.4")
logPanel.tag_add("start", "1.8", "1.13")
scrollbar2.config(command=logPanel.yview)

clearButton = Button(root, text="Clear", command=donothing)
clearButton.pack(side=BOTTOM)
# clearButton.config(side=BOTTOM)

root.config(menu=menubar)

root.protocol("WM_DELETE_WINDOW", failSafeExit)
root.mainloop()
