#!/usr/bin/python

from __future__ import print_function
import sys


n = int(raw_input().strip())
staircase = ["".join(["#" for row in xrange(width + 1)]) for width in xrange(n)]
padded = map(lambda stair: "".join([" " for _ in xrange(n - len(stair))]) + stair, staircase)
[print(stair) for stair in padded]
