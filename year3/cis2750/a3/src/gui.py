#!/usr/bin/python

from Tkinter import *
import tkMessageBox
import sys

# playerTurn = 0
# boxCount = [0,0,0,0,0,0,0,0,0]
def donothing():
   filewin = Toplevel(root)
   button = Button(filewin, text="Do nothing button")
   button.pack()


def sosPlsWork(root):
	print("whoops")


root = Tk()
root.title("iCalGui")
root.geometry('400x400')

menubar = Menu(root)
filemenu = Menu(menubar, tearoff=0)
filemenu.add_command(label="Open", command=donothing, accelerator="Ctrl+O")
filemenu.add_command(label="Save", command=donothing, accelerator="Ctrl+S")
filemenu.add_command(label="Save as...", command=donothing)
filemenu.add_separator()
filemenu.add_command(label="Exit", command=root.quit, accelerator="Ctrl+X")
menubar.add_cascade(label="File", menu=filemenu)
filemenu.bind_all("<Control-x>", quit)
filemenu.bind_all("<Control-s>", donothing)
createmenu = Menu(menubar, tearoff=0)
createmenu.add_command(label="Create Calendar", command=donothing)

# createmenu.add_separator()

createmenu.add_command(label="Create Event", command=donothing)
# editmenu.add_command(label="Copy", command=donothing)
# editmenu.add_command(label="Paste", command=donothing)
# editmenu.add_command(label="Delete", command=donothing)
# editmenu.add_command(label="Select All", command=donothing)

menubar.add_cascade(label="Create", menu=createmenu)
helpmenu = Menu(menubar, tearoff=0)
# helpmenu.add_command(label="Help Index", command=donothing)
helpmenu.add_command(label="About iCalGui...", command=donothing)
menubar.add_cascade(label="Help", menu=helpmenu)

root.config(menu=menubar)


root.mainloop()
