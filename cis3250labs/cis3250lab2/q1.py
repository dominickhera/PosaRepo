#!/usr/bin/python
import string

f = open("./infile", "r")
content=f.read()
print  content
print "-----------"

f.seek(0)

for line in f:
	splitLine = line.split(':')
	# print splitLine
	for splitLine in splitLine:
		newLine = string.strip(splitLine)
		print newLine
print "-----------"

# f.seek(0)

# for line in f:
# 	line.split(':')
# 	newLine = line.strip()
# 	print newLine
# print "\n"

f.close()