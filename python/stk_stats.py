#!/usr/bin/env python
# stk-stats.py

import re
import os
import sys

loop_dir = sys.argv[1]

def get_stats(filename):
    stats = [0,0,0]
    f_in = open(filename, "r")
    for line_f in f_in:
        #print line_f.strip()
        if re.match(r'^[A-Z]{3}', line_f):
            #print "bat:{}".format(line_f.strip())
            stats[0] += 1
        elif re.match(r'^#=GS\s[A-Z]{3}', line_f):
            #print "com:{}".format(line_f.strip())
            stats[1] += 1
        elif re.match(r'^([a-zA-Z]+_)*[a-zA-Z]+[.][0-9]+\s.*$', line_f):
            #print "ref:{}".format(line_f.strip())
            stats[2] += 1
    return stats

print "RF\t#refs\t#bats\t#thrown\tnote\tdir"

for dirs, subdirs, files in os.walk(loop_dir):
    for a_file in files:
        if a_file.endswith('.stk'):
            a_file_name = os.path.basename(a_file)
            result = re.match(r'(RF[0-9]{5}_.*)_filtered(.*)', a_file_name)
            reason = "fine"
            if result is not None:
                reason = result.group(2).replace("_", " ").strip().replace(".stk", "")
            if not reason:
                reason = "fine"
            stats = get_stats(dirs + "/" + a_file)
            thrown = stats[1] - stats[0]
            print "{}\t{}\t{}\t{}\t\'{}\'\t{}".format(result.group(1), stats[2], stats[1], thrown, reason, dirs)
            #print reason

# regex for seqences of references
#^([a-zA-Z]+_)*[a-zA-Z]+[.][0-9]+\s.*$
#^([a-zA-Z]+_)*[a-zA-Z]+[.][0-9]+\s+[ATCGUNatcgun-]{5,}$
#^([a-zA-Z]+_)*[a-zA-Z]+[.][0-9]+\s+[ATCGUWSMKRYBDHVNZatcguwsmkrybdhvnz-]{5,}$
