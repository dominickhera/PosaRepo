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


def aboutApp():
	tkMessageBox.showinfo("iCalGUI About", "iCalGUI was created by Dominick Hera\nYou can find more of my work on dominickhera.com")


root = Tk()
root.title("iCalGUI")
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
createmenu.add_command(label="Create Event", command=donothing)
menubar.add_cascade(label="Create", menu=createmenu)
helpmenu = Menu(menubar, tearoff=0)
helpmenu.add_command(label="About iCalGUI...", command=aboutApp)
menubar.add_cascade(label="Help", menu=helpmenu)

scrollbar = Scrollbar(root)
scrollbar.pack(side=RIGHT,fill=Y)

fileViewPanel = Listbox(root,height=15,yscrollcommand=scrollbar.set)
fileViewPanel.insert(1, "Python")
fileViewPanel.insert(2, "Perl")
fileViewPanel.insert(3, "C")
fileViewPanel.insert(4, "PHP")
fileViewPanel.insert(5, "JSP")
fileViewPanel.insert(6, "Ruby")

fileViewPanel.pack(side=TOP,fill=BOTH)
scrollbar.config(command=fileViewPanel.yview)

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


root.mainloop()
