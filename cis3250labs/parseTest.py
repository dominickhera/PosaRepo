#!/usr/bin/python
import re

userInput = raw_input("input equation\n")

numCount = 0
operandCount = 0
entryBracketCount = 0
exitBracketCount = 0
charCount = 0
endOfLine = len(userInput) - 1
for i in range(len(userInput)):
	if (re.search('[a-zA-Z]+', userInput[i])):
		charCount = charCount + 1
	elif (re.search('[0-9]+', userInput[i])):
		numCount = numCount + 1
	elif (re.search('[[\+|\-|\*|\/]+', userInput[i])):
		operandCount = operandCount + 1
		# print endOfLine
		if(re.search('[[\+|\-|\*|\/]+', userInput[endOfLine])):
			print "invalid expression"
			exit(0)
		else:
			if(re.search('[a-zA-Z]+', userInput[i + 1])):
				continue
			elif(re.search('[\d]+', userInput[i + 1])):
				continue
			else:
				print 'invalid expression'
				exit(0)
	elif (re.search('[(]+', userInput[i])):
		entryBracketCount = entryBracketCount + 1
	elif (re.search('[)]+', userInput[i])):
		exitBracketCount = exitBracketCount + 1

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