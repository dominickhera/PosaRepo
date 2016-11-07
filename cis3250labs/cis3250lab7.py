#!/usr/bin/python

from __future__ import division
from Tkinter import *

import math
import tkMessageBox
import sys


root = Tk() 

canavasThing = Canvas(root, height = 750, width = 1500)

initVelocity = sys.argv[1]
print initVelocity
initAngle = sys.argv[2]
print initAngle
velocity = (float(initVelocity))
angle = (float(initAngle))
g = 9.8

newAngle = (angle * math.pi)/180
T = (((2 * velocity) * (math.sin(newAngle)))/ g)

t = 0
h = 0
x = 0

while (t <= T):
	
	h = -((.5 * g) * (t**2)) + (velocity * t * math.sin(newAngle))
	x = velocity * t * math.cos(newAngle)

	t = t + .1
	oval = canavasThing.create_oval(x,749 - h,x,749 - h, fill="black")

canavasThing.pack()
root.mainloop()