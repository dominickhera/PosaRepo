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


	i = 1
	while(i < n):
		if((sieveList[i-1] % (2*i)) == 0):
			# print sieveList[i]

		# i += 1
			k = 2
			while(k < n):
				
				if(k <= n-1 ):
					# print  k
					# print sieveList[k]
					sieveList[k] = 0
					# print "post k is "
					# print sieveList[k]
				# i += 1
				k = i * 2
				i += 1
				# print "hello"
				# print k
		i += 1


	i = 1
	while(i < n):
		if((sieveList[i-1] % (3*i)) == 0):
	# # # 		# print sieveList[i]

	# # # # 	# i += 1
			k = 3
			while(k < n-1):
	# 			# print "k is"
	# 			# print k
				if(k <= n-1 and k is not 3):
					print "k is "
					print k
					print "sieve list at k is"
					print sieveList[k]
					sieveList[k] = 0
	# # 				# print "post k is "
	# # 				# print sieveList[k]
				# i += 1
				k = i * 3
				i += 1
	# 			# print k
		i += 1

	i = 1
	while(i < n):
		if((sieveList[i-1] % (5*i)) == 0):
	# 		# print sieveList[i]

	# 	# i += 1
			k = 5
			while(k < n):
				if(k < n-1 and k is not 5):
					# print k
					# print "is k"
					# print i
					# print "that is i"
	# 				# print "fucker"
					# print "sieve list at k is"
					# print sieveList[k]
					sieveList[k] = 0
					# print "post k is "
					# print sieveList[k]
				# i += 2
				k = i * 5
				i += 1
				# print k
		i += 1

	print "results:"
	for num in range(0, n - 1):
		if (sieveList[num] != 0):
			# print "at num"
			# print num
			# print "is this"
			print sieveList[num]
			