#!/usr/bin/python

from Tkinter import *
import tkMessageBox 
import re

def validate():
	userInput = entryBox.get()

	numCount = 0
	operandCount = 0
	entryBracketCount = 0
	exitBracketCount = 0
	charCount = 0
	endOfLine = len(userInput) - 1

	for i in range(len(userInput)):
		if (re.search('[\s*a-z\s*A-Z]+', userInput[i])):
			charCount = charCount + 1
		elif (re.search('[\s*0-9]+', userInput[i])):
			numCount = numCount + 1
		elif (re.search('[\s*\+|\s*\-|\s*\/]+', userInput[i])):
			operandCount = operandCount + 1
			if(re.search('[\s*\+|\s*\-|\s*\/]+', userInput[endOfLine])):
				tkMessageBox.showinfo("Hey pal", "invalid expression")
			else:
				if((re.search('[\s*a-zA-Z]+', userInput[i - 1])) or (re.search('[\s*\d]+', userInput[i - 1]))):
					continue
				else:
					tkMessageBox.showinfo("Hey pal", "invalid expression")

				if(re.search('[\s*\d]+', userInput[i - 1])):
					continue
				else:
					tkMessageBox.showinfo("Hey pal", "invalid expression")

				if(re.search('[\s*a-zA-Z]+', userInput[i + 1])):
					continue
				elif(re.search('[\s*\d]+', userInput[i + 1])):
					continue
				elif (re.search('[\(]+', userInput[i + 1])):
					continue
				elif (re.search('[\)]+', userInput[i + 1])):
					continue 
				else: 
					tkMessageBox.showinfo("Hey pal", "invalid expression")
		elif(re.search('[\(]+', userInput[i])):
			entryBracketCount = entryBracketCount + 1
		elif(re.search('[\)]+', userInput[i])):
			exitBracketCount = exitBracketCount + 1
			if(re.search('[\)]+', userInput[endOfLine])):
				continue
			else:
				if(re.search('[\(]+', userInput[i + 1])):
					kMessageBox.showinfo("Hey pal", "invalid expression")

	if (entryBracketCount != exitBracketCount):
		tkMessageBox.showinfo("Hey pal", "invalid expression")
	elif operandCount == 0:
		tkMessageBox.showinfo("Hey pal", "invalid expression")
	elif ((numCount == 0) and (charCount == 0)):
		tkMessageBox.showinfo("Hey pal", "invalid expression")
	else:
		tkMessageBox.showinfo("Hey pal", "valid expression ")



root = Tk()

entryBox = Entry(root, width=80)
entryBox.pack()

bDisplayMessage = Button(root, text ="validate", command = validate)
bDisplayMessage.pack()

root.mainloop()
