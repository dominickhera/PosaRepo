#!/usr/bin/python
import array

if __name__ == "__main__":
	print "Enter the upper limit of prime numbers to calculate: "
	userInput = raw_input()
	n = int(userInput.strip())
	print "the user entered " + userInput
	sieveList = []
	for num in range(2,n+1):
		sieveList.append(num)

	# for num in range(2,n-1):
		
	# 	# print sieveList[num]
	# 	# print "hiya"
	# 	if((sieveList[num] % 2*num) == 0):
	# 		# print num
	# 		for num2 in range (1, n-1):
				
	# 			if(num2 * 2 < n):
	# 				# print sieveList[num2*2]
	# 				sieveList[num2*2] = 0
	# 				# print "changed"
	# 				# print sieveList[num2*2]
	# 				# print "to that ^"
	# 				# print num2*2


	i = 2
	while(i < n - 1):
		if((sieveList[i] % (2*i)) == 0):
			# print sieveList[i]

		# i += 1
			k = 2
			while(k <= n-1):
				
				if(k < n-1):
					sieveList[k] = 0
				
				k = i * 2
				i += 1
				# print k
		i += 1


	i = 2
	while(i < n - 1):
		if((sieveList[i] % (3*i)) == 0):
			# print sieveList[i]

		# i += 1
			k = 3
			while(k <= n-1):
				print k
				if(k < n-1 and k is not 3):
					sieveList[k] = 0
				# i += 1
				k = i * 3
				i += 1
				# print k
		i += 1

	i = 2
	while(i < n - 1):
		if((sieveList[i] % (5*i)) == 0):
			# print sieveList[i]

		# i += 1
			k = 5
			while(k < n-1):
				# print k
				# print "lol"
				if(k < n-1 and k is not 5):
					# print "fucker"
					sieveList[k] = 0
				# i += 1
				k = i * 5
				i += 1
				# print k
		i += 1
	# for num in range(2,n - 1):
	# 	# print sieveList[num]
	# 	if((sieveList[num] % 3*num) == 0):
			
	# 		for num2 in range (num*3, n-1):
	# 			print num2 * 3
	# 			# if(num2 * 3 < n -1):
	# 				# print sieveList[num2*3]
	# 				# sieveList[num2*3] = 0
	# # 				# print sieveList[num2*3]

	# for num in range(0,n - 1):
	# # 	# print sieveList[num]
	# 	if((sieveList[num] % 5*num) == 0):
			
	# 		for num2  in range (4, n-1):
	# 			if(num2 * 5 < n):
	# 				sieveList[num2*5] = 0

	print "results:"
	for num in range(0, n - 1):
		if (sieveList[num] != 0):
			print sieveList[num]
			