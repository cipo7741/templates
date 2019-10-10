#!/usr/bin/env python
# simple_plot.py
# http://matplotlib.org/examples/pylab_examples/simple_plot.html

from pylab import *

import sys
import csv
import re

#f = open(sys.argv[2],'w')

#prev = 0
count = 0
x = []
y = []
with open(sys.argv[1], 'rb') as f:
    for line in f:
        values = line.split(',')
        x.append(values[0])
        y.append(values[1])

plot(x, y)

xlabel('generation')
ylabel('distance to optimum')
title('Evol Alg')
grid(True)
savefig("test.png")
show()
