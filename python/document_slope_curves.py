#!/usr/bin/env python
# document_slope_curves.py

import sys
from HTMLParser import HTMLParser
from pylab import *

class MyHTMLParser(HTMLParser):
    c = 0
    tag_count = []
    def handle_starttag(self, tag, attrs):
        self.c = self.c + 1
        self.tag_count.append(self.c)
    def handle_endtag(self, tag):
        self.c = self.c + 1
        self.tag_count.append(self.c)
    def handle_data(self, data):
        self.tag_count.append(self.c)

# instantiate the parser and fed it some HTML
parser = MyHTMLParser()

file=open(sys.argv[1],'r')
row = file.readlines()
for line in row:
	parser.feed(line)

plot(parser.tag_count)
xlabel('token')
ylabel('tags')
title('document slope curve for %s' % sys.argv[1])
grid(True)
savefig("test.png")
show()
