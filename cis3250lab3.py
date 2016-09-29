#!/usr/bin/python

firstNameList = []
lastNameList = []
idList = []
theFile = open('student.txt', 'w')
userOption = 0
listCount = 0
viewCount = 0
i = 0

while (userOption != 6):
	print "(1) Print all students\n(2) Add a student to the list\n(3) Print the information of next student on the list.\n(4) Print the information of previous student on the list.\n(5) Save the entire list of students\n(6) Quit\n"
	userOption = input("choose a number:\n> ")

	if (userOption > 6):
		print "\nplease enter a number between 1 - 6\n"

	if (userOption == 1):
		i = 0
		print "\nyou selected option 1\n"
		for x in firstNameList:
			print "%s %s - %s" % (firstNameList[i], lastNameList[i], idList[i])
			i = i + 1
		print "\n"

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
		# print "\nyou selected option 3\n"
		if (viewCount + 1 > listCount):
			viewCount = 0
			print "%s %s - %s\n" % (firstNameList[viewCount], lastNameList[viewCount], idList[viewCount])
		else:
			viewCount = listCount + 1
			print "%s %s - %s\n" % (firstNameList[viewCount], lastNameList[viewCount], idList[viewCount])
	if (userOption == 4):
		# print "\nyou selected option 4\n"
		viewCount = (listCount - 1)
		print "%s %s - %s\n" % (firstNameList[viewCount], lastNameList[viewCount], idList[viewCount])
	if (userOption == 5):
		i = 0
		# print "\nyou selected option 5\n"
		theFile.write("First Name  Last Name  - Student ID\n")
		for x in firstNameList:
			theFile.write("%s %s - %s" % (firstNameList[i], lastNameList[i], idList[i]))
			i = i + 1

	if (userOption == 6):
		print "\ngoodbye\n"