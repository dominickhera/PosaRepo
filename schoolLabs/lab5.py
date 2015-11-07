#!/usr/bin/python

for i in range (1,6):
   for j in range (1,6):
      print  j * i, '   ',
      if (j*i < 10):
	  print '    ',
      else:
	  print '   ',
   print ' '
