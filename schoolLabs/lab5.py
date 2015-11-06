#!/usr/bin/python

for i in range (1,6):
   for j in range (i, i * 6, i):
      print '{:^4}'.format(j), '    ',
   print '\n'
