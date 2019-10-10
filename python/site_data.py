#!/usr/bin/env python
# document_slope_curves.py

import sys
from HTMLParser import HTMLParser

class MyHTMLParser(HTMLParser):
    def handle_data(self, data):
        print data

parser = MyHTMLParser()

file=open(sys.argv[1],'r')
row = file.readlines()
for line in row:
	parser.feed(line)
