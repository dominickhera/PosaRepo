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
	if (re.search('[\s*a-z\s*A-Z]+', userInput[i])):
		charCount = charCount + 1
		print operandCount, " 1"
	elif (re.search('[\s*0-9]+', userInput[i])):
		numCount = numCount + 1
		print operandCount, " 2"
	elif (re.search('[\*]', userInput[i])):
		print 'TRUE'
	# 	operandCount = operandCount + 1
	# 	print operandCount, " 3.5"
	# elif (re.search('[\s*\+|\s*\-|\s*\/]+', userInput[i])):
	elif (re.search('[+-/*]+', userInput[i])):
		operandCount = operandCount + 1
		print operandCount, " 3"
		# if(re.search('[\s*\+|\s*\-|\s*\/]+', userInput[endOfLine])):
		if(re.search('[+-/*]+', userInput[endOfLine])):
			print "invalid expression"
			print "1"
			exit(0)
		else:
			if((re.search('[\s*a-zA-Z]+', userInput[i - 1])) or (re.search('[\s*\d]+', userInput[i - 1]))):
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
			elif (re.search('[\(]+', userInput[i + 1])):
				continue
			elif (re.search('[\)]+', userInput[i + 1])):
				continue 
			else: 
				print 'invalid expression'
				print '4'
				exit(0)
	elif (re.search('[\(]+', userInput[i])):
		entryBracketCount = entryBracketCount + 1
		print operandCount, " 4"
	elif (re.search('[\)]+', userInput[i])):
		exitBracketCount = exitBracketCount + 1
		print operandCount, " 5"
		if(re.search('[\)]+', userInput[endOfLine])):
			continue
		else:
			if(re.search('[\(]+', userInput[i + 1])):
				print 'invalid expression'
				print '5'
				exit(0)

print operandCount, " 6"
if (entryBracketCount != exitBracketCount):
	print "invalid expression"
	print '6'
	exit(0)
elif operandCount == 0:
	print operandCount
	print "invalid expression"
	print '7'
	exit(0)
elif ((numCount == 0) and (charCount == 0)):
	print "invalid expression"
	print '8'
	exit(0)
else:
	print "valid expression"
