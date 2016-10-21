#!/usr/bin/python
import re

userInput = raw_input("input equation\n")

# i = 0
numCount = 0
operandCount = 0
entryBracketCount = 0
exitBracketCount = 0
charCount = 0

print (len(userInput))
for i in range(len(userInput)):
	if (re.search('[a-zA-Z]+', userInput[i])):
		charCount = charCount + 1
	elif (re.search('[0-9]+', userInput[i])):
		# print userInput[i]
		numCount = numCount + 1
	elif (re.search('[[\+|\-|\*|\/]+', userInput[i])):
		operandCount = operandCount + 1
		# if userInput[i + 1] == len(userInput):
		# if len(userInput) == userInput[i]:
		# 	print "invalid expression"
		# 	exit(0)
		# else:
			# if(re.search('[^a-zA-Z0-9]+', userInput[i + 1])):
				# print 'next char is not a number'
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