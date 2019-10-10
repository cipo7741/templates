#!/bin/bash

PASSED=$1
TFILE="/tmp/out.tmp.$$"

for f in $PASSED*
do
    if [ -f $f -a -r $f ]; then
        cat $f | sed 's/ /, /g' > $TFILE && mv $TFILE "$f"
#        tail -n +2 $f > $TFILE && mv $TFILE "$f"
#        cat $f | sed 's/\.000000//g' > $TFILE && mv $TFILE "$f"
    else
        echo "Error: Cannot read $f"
    fi
done
