#!/usr/bin/python

from Tkinter import *
import tkMessageBox 
import re
  
root = Tk()

e = Entry(root)
e.pack()

e.focus_set()

def grabData():
    # print e.get()
    userInput = e.get()
    # print testInput
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

		elif (re.search('[\s*\+|\s*\-|\s*\*|\s*\/]+', userInput[i])):
			operandCount = operandCount + 1
			if(re.search('[\s*\+|\s*\-|\s*\*|\s*\/]+', userInput[endOfLine])):
				print "invalid expression"
				print "1"
				exit(0)
			else:
				if((re.search('[\s*a-zA-Z]+', userInput[i - 2])) or (re.search('[\s*\d]+', userInput[i - 2]))):
					continue
				else:
					print 'invalid expression'
					print '2'
					exit(0)
				if(re.search('[\s*\d]+', userInput[i - 1])):
					continue
				else:
					print 'invalid expression'
					print '3'
					exit(0)

				if(re.search('[\s*a-zA-Z]+', userInput[i + 1])):
					continue
				elif(re.search('[\s*\d]+', userInput[i + 1])):
					continue
				elif (re.search('[\s*(]+', userInput[i + 1])):
					continue
				elif (re.search('[\s*)]+', userInput[i + 1])):
					continue 
				else: 
					print 'invalid expression'
					print '4'
					exit(0)
		elif (re.search('[\s*(]+', userInput[i])):
			entryBracketCount = entryBracketCount + 1

		elif (re.search('[\s*)]+', userInput[i])):
			exitBracketCount = exitBracketCount + 1
			if(re.search('[\s*)]+', userInput[endOfLine])):
				continue
			else:
				if(re.search('[\s*(]+', userInput[i + 1])):
					print 'invalid expression'
					print '5'
					exit(0)

	if (entryBracketCount != exitBracketCount):
		print "invalid expression"
		exit(0)
	elif operandCount == 0:
		print "invalid expression"
		exit(0)
	elif ((numCount == 0) and (charCount == 0)):
		print "invalid expression"
		exit(0)
	else:
		print "valid expression"


b = Button(root, text="Validate", width=60, command=grabData)
b.pack()

root.mainloop()
# e = Entry(root, width=50)
# e.pack()

# text = e.get()


# text = content.get()
# content.set(text)                  
# def helloMessage(): 
#     tkMessageBox.showinfo( "Hello ...", "You clicked on display message button!")

# root = Tk() 

# bDisplayMessage = Button(root, text ="Validate", command = helloMessage)

# bDisplayMessage.pack()
# root.mainloop()