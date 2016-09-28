#!/usr/bin/python

firstNameList = []
lastNameList = []
idList = []
userOption = 0
listCount = 0
i = 0

while (userOption != 6):
	print "(1) Print all students\n(2) Add a student to the list\n(3) Print the information of next student on the list.\n(4) Print the information of previous student on the list.\n(5) Save the entire list of students\n(6) Quit\n"
	userOption = input("choose a number:\n> ")

	if (userOption > 6):
		print "\nplease enter a number between 1 - 6\n"

	if (userOption == 1):
		print "\nyou selected option 1\n"
		for x in firstNameList:
			# print "%s %s - %d\n" % (firstNameList[x], lastNameList[x], idList[x])
			print firstNameList
			print lastNameList
			print idList
	if (userOption == 2):
		firstNameEntry = raw_input("enter student first name:\n> ")
		firstNameList.append(firstNameEntry)
		print firstNameList
		lastNameEntry = raw_input("enter student last name:\n> ")
		lastNameList.append(lastNameEntry)
		print lastNameList
		idEntry = raw_input("enter student id number:\n> ")
		# if (isinstance(idEntry, int)):
			# print(isinstance(idEntry, int))
		idList.append(idEntry)
		print idList
		listCount = listCount + 1
		print listCount
		# else:
		# 	print "not a var fam"
		# 	while ((isinstance(idEntry, int) == 0)):
		# 		idEntry = raw_input("enter student id number:\n> ")
		# 	idList.append(idEntry)
		# 	print idList
		# 	listCount = listCount + 1
		# 	print listCount
	if (userOption == 3):
		print "\nyou selected option 3\n"
	if (userOption == 4):
		print "\nyou selected option 4\n"
	if (userOption == 5):
		print "\nyou selected option 5\n"
	if (userOption == 6):
		print "\ngoodbye\n"