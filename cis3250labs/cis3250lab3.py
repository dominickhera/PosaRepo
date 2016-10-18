#!/usr/bin/python

from Tkinter import *
import tkMessageBox 
                    
root = Tk() 

canavasThing = Canvas(root, height = 400, width = 400)

def drawCircle():
	oval = canavasThing.create_oval(300,300,100,100, fill="yellow")

def drawLine():
	line = canavasThing.create_line(0,100, 399, 100, fill="red")
	line2 = canavasThing.create_line(0,200, 399, 200, fill="red")
	line3 = canavasThing.create_line(0,300, 399, 300, fill="red")
	line4 = canavasThing.create_line(100,0, 100, 399, fill="red")
	line5 = canavasThing.create_line(200,0, 200, 399, fill="red")
	line6 = canavasThing.create_line(300,0, 300, 399, fill="red")

bDisplayMessage = Button(root, text ="Divide Canvas Area", command = drawLine)
bDisplayMessage1 = Button(root, text ="Draw Circle", command = drawCircle)

canavasThing.pack()
bDisplayMessage.pack()
bDisplayMessage1.pack()
root.mainloop()