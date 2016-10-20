#!/usr/bin/python
import re

userInput = raw_input("input equation\n")

i = -1
numCount = 0;
operandCount = 0;
charCount = 0;

for i in range(len(userInput)):
	if userInput[i] == '1':
		print userInput[i] , " is int "
	elif (userInput[i] == '+') or (userInput[i] == '-') or (userInput[i] == '*') or (userInput[i] == '/'):
		print userInput[i] , " is an operand"
		operandCount = operandCount + 1
		print operandCount , " operands found so far"
	