#!/usr/bin/env python
# loop-directory.py

import os
import sys

#loop_dir = "~/Sync/lectures/rna-bioinformatik/stk-files"
loop_dir = sys.argv[1]

strange_files = []
stats_filterd = 0

for subdir, dirs, files in os.walk(loop_dir):
    stats_filterd += "".join(files).count("filtered")
    for a_file in files:
        name_subdir = os.path.basename(subdir)
        name_file = os.path.basename(a_file)

        if not name_file.startswith('RF') or not name_file.endswith('.stk') or name_file.count('_') < 2:
            strange_files += [name_file]
        else:
            name_parts  = name_file.replace('.stk','').split('_')
            name_part_2 = ' '.join(name_parts[1:len(name_parts)])
            print '{}\t{}\t{}'.format(name_subdir, name_parts[0], name_part_2)
print 'The following files don\'t follow the stk naming scheme: {}'.format(', '.join(strange_files))
print 'stats: filterd {}'.format(stats_filterd - ', '.join(strange_files).count('filtered'))
#        print '{} {} {} {}'.format(name_subdir, name_file, name_parts[1], "".join(name_parts[2:len(name_parts)]))
