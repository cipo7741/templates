#!/usr/bin/env python
# main_content.py

import sys
from HTMLParser import HTMLParser

class MyHTMLParser(HTMLParser):
    c = 0
    d = 0
    def handle_starttag(self, tag, attrs):
        self.c = self.c + 1
    def handle_endtag(self, tag):
        self.c = self.c + 1
    def handle_data(self, data):
        if (self.c == self.d and data.strip()):
            print data.strip()
        self.d = self.c

# instantiate the parser and fed it some HTML
parser = MyHTMLParser()

file=open(sys.argv[1],'r')
row = file.readlines()
for line in row:
	parser.feed(line)
