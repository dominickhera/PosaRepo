#!/usr/bin/python

from __future__ import division
from Tkinter import *

import tkMessageBox
import sys

firstNameList = []
lastNameList = []
idList = []
parseList = []
i = 0

def load():
	fpt = open('student.txt', 'r')
	dataFile = fpt.read()

	myList = dataFile.split('\n')

	for index in range(len(myList)):
		parseList = myList[index].split(' ')
		firstNameList.append(parseList[0])
		lastNameList.append(parseList[1])
		idList.append(parseList[2])

	global i 
	i = len(myList) - 1
	global maxAmount
	maxAmount = len(myList) - 1
	entryBox1.delete(0, END)
	entryBox1.insert(END, firstNameList[i])
	entryBox2.delete(0, END)
	entryBox2.insert(END, lastNameList[i])
	entryBox3.delete(0, END)
	entryBox3.insert(END, idList[i])

def jumpToBeginning():
	x = 0
	global i
	i = x
	entryBox1.delete(0, END)
	entryBox1.insert(END, firstNameList[i])
	entryBox2.delete(0, END)
	entryBox2.insert(END, lastNameList[i])
	entryBox3.delete(0, END)
	entryBox3.insert(END, idList[i])

def jumpToEnd():
	global i
	i = maxAmount
	entryBox1.delete(0, END)
	entryBox1.insert(END, firstNameList[i])
	entryBox2.delete(0, END)
	entryBox2.insert(END, lastNameList[i])
	entryBox3.delete(0, END)
	entryBox3.insert(END, idList[i])

def next():

	x = i + 1
	global maxAmount
	if (x <= maxAmount):
		global i
		i = x
	else:
		x = 0
		i = 0
	entryBox1.delete(0, END)
	entryBox1.insert(END, firstNameList[i])
	entryBox2.delete(0, END)
	entryBox2.insert(END, lastNameList[i])
	entryBox3.delete(0, END)
	entryBox3.insert(END, idList[i])


def back():
	x = i - 1
	if (x <= -1):
		x = maxAmount - 1
		global i 
		i = x
	else:
		global i
		i = x 

	entryBox1.delete(0, END)
	entryBox1.insert(END, firstNameList[i])
	entryBox2.delete(0, END)
	entryBox2.insert(END, lastNameList[i])
	entryBox3.delete(0, END)
	entryBox3.insert(END, idList[i])

root = Tk()

label_text = StringVar()
labelTest = Label(root, textvariable = label_text, width = 60)
labelTest.pack()
label_text.set("Student Info")

entryBox1 = Entry(root)
entryBox1.pack()

entryBox2 = Entry(root)
entryBox2.pack()

entryBox3 = Entry(root)
entryBox3.pack()

bDisplayMessage4 = Button(root, text ="load", command = load)
bDisplayMessage4.pack()

bDisplayMessage = Button(root, text ="<<", command = jumpToBeginning)
bDisplayMessage.pack()

bDisplayMessage1 = Button(root, text ="<", command = back)
bDisplayMessage1.pack()

bDisplayMessage2 = Button(root, text =">", command = next)
bDisplayMessage2.pack()

bDisplayMessage3 = Button(root, text =">>", command = jumpToEnd)
bDisplayMessage3.pack()

root.mainloop()
