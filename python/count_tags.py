#!/usr/bin/env python
# count_tags.py

import sys
from HTMLParser import HTMLParser

class MyHTMLParser(HTMLParser):
    c = 0
    def handle_starttag(self, tag, attrs):
        self.c = self.c + 1
        print self.c
    def handle_endtag(self, tag):
        self.c = self.c + 1
        print self.c
    def handle_data(self, data):
        print self.c

parser = MyHTMLParser()
a = str(sys.argv[1])
file=open(a,'r') 
row = file.readlines()
for line in row:
    parser.feed(line)
