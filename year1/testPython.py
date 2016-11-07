#!/usr/bin/python

a = [1,2,3]
b = []

for i in a:
    usrInput = raw_input('enter name: ')
    b.append(usrInput)

b.sort()
print b
