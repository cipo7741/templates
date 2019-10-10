#!/usr/bin/env python
# loop-directory.py

import os
import sys

loop_dir = sys.argv[1]

for subdir, dirs, files in os.walk(loop_dir):
    for a_file in files:
        print os.path.basename(a_file)
