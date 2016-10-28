#!/usr/bin/python

from __future__ import division
from Tkinter import *

import math
import tkMessageBox

def calculate():
	xVar = input("input x variable: ")
	deltaE = input("input your delta E variable (predefined error value): ")



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


root = Tk()

entryBox1 = Entry(root)
entryBox1.pack()

bDisplayMessage = Button(root, text ="calculate", command = calculate)
bDisplayMessage.pack()

root.mainloop()