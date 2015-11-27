#!/usr/bin/python

a = []
i = 0

while i != 3:
      usrInput = raw_input('enter name: ')
      a.append(usrInput)
      i += 1

a.sort()
print a

