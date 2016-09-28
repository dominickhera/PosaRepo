#!/usr/bin/python

firstNameList = []
lastNameList = []
idList = []
userOption = 0

while (userOption != 6):
	print "(1) Print all students\n(2) Add a student to the list\n(3) Print the information of next student on the list.\n(4) Print the information of previous student on the list.\n(5) Save the entire list of students\n(6) Quit\n"
	userOption = input("choose a number:\n> ")

	if (userOption > 6):
		print "\nplease enter a number between 1 - 6\n"

	if (userOption == 1):
		print "\nyou selected option 1\n"
	if (userOption == 2):
		firstNameEntry = input("enter student first name:\n> ")
		firstNameList.append(firstNameEntry)
	if (userOption == 3):
		print "\nyou selected option 3\n"
	if (userOption == 4):
		print "\nyou selected option 4\n"
	if (userOption == 5):
		print "\nyou selected option 5\n"
	if (userOption == 6):
		print "\ngoodbye\n"