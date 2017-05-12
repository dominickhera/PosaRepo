#!/usr/bin/python

numbers = ["1", "2", "3"]
testNum = 0


for i in range(len(numbers)):
    testNum = testNum + int(numbers[i])
    print testNum
