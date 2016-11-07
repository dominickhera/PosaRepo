#!/usr/bin/python

for i in range (1,6):
   for j in range (1,6):
      print i*j, '   ',
      if (i*j < 10):
         print '    ',
      else:
          print '   ',
   print ' '
