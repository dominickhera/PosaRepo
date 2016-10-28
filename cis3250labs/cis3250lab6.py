#!/usr/bin/python

from __future__ import division
from Tkinter import *

import math
import tkMessageBox

def calculate():
	initXVar = entryBox1.get()
	initDeltaE = entryBox2.get()
	xVar = (float(initXVar))
	deltaE = (float(initDeltaE))

	newX = xVar * (math.pi/180)
	c = math.sin(newX)


	y = 0
	k = 1
	n = 0

	while ((math.fabs(c - y)) > deltaE):
		if (y % 2 == 0):
			y = y + (newX**k)/(math.factorial(k))
		else:
			y = y - (newX**k)/(math.factorial(k))
		n = n + 1
		k = k + 2
	
	cLine = "c = ", c
	cText.set(cLine)
	
	yLine = "y = ", y
	yText.set(yLine)

	nLine = "n = ", n
	nText.set(nLine)

	cyLine = "|c - y| = ", (math.fabs(c - y))
	cyText.set(cyLine)


root = Tk()

label_text = StringVar()
labelTest = Label(root, textvariable = label_text, width = 60)
labelTest.pack()
label_text.set("x var")

entryBox1 = Entry(root)
entryBox1.pack()

label_text2 = StringVar()
labelTest2 = Label(root, textvariable = label_text2, width = 60)
labelTest2.pack()
label_text2.set("delta E var")

entryBox2 = Entry(root)
entryBox2.pack()

bDisplayMessage = Button(root, text ="calculate", command = calculate)
bDisplayMessage.pack()

cText = StringVar()
cTest = Label(root, textvariable = cText, width = 60)
cTest.pack()
cText.set(" ")

yText = StringVar()
yTest = Label(root, textvariable = yText, width = 60)
yTest.pack()
yText.set(" ")

nText = StringVar()
nTest = Label(root, textvariable = nText, width = 60)
nTest.pack()
nText.set(" ")

cyText = StringVar()
cyTest = Label(root, textvariable = cyText, width = 60)
cyTest.pack()
cyText.set(" ")

root.mainloop()


