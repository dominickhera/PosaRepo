#!/usr/bin/python
import array
import time

if __name__ == "__main__":
	print "Enter the upper limit of prime numbers to calculate: "
	userInput = raw_input()
	n = int(userInput.strip())
	# print "the user entered " + userInput

	startTime = time.time()
	sieveList = []
	for num in range(2,n+2):
		sieveList.append(num)

	i = 0
	while(i < n - 1):
		if((sieveList[i] % (2*(i+1))) == 0):
			k = 0
			while(k < n - 1):
				
				if(k <= n-1 and sieveList[k-2] is not 2):
					sieveList[k-2] = 0
				k = i * 2
				i += 1
		i += 1


	i = 0
	while(i < n - 1):
		if((sieveList[i] % (3*(i + 1))) == 0):
			k = 0
			while(k < n-1):
				if(k <= n-1 and sieveList[k-2 is not 3]):
					sieveList[k-2] = 0
				k = i * 3
				i += 1
		i += 1

	i = 0
	while(i < n - 1):
		if((sieveList[i] % (5*(i + 1))) == 0):
			k = 0
			while(k < n-1):
				if(k < n-1 and sieveList[k-2 is not 5]):
					sieveList[k-2] = 0
				k = i * 5
				i += 1
		i += 1

	fileOutput = open('primeNumberPythonOutput.txt', 'w')
	fileOutput.write("results:\n")
	for num in range(0, n - 3):
		if (sieveList[num] != 0):
			fileOutput.write("%s\n" % sieveList[num])


	fileOutput.close()
	print ("execution time: %s seconds" % (time.time() - startTime))
			