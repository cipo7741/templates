#!/bin/bash
# update-kiwix-bookmarks.sh
# 2016-01-08 by me

PASSED=$1
OLDID=d1093a74-db1e-2d54-d5c0-4155130df64f
NEWID=8c696cf3-9c3f-5ea8-9e08-9e35312a8ae0
TFILE="/tmp/out.tmp.$$"

for f in $PASSED*.xml
do
    if [ -f $f -a -r $f ]; then
        cat $f | sed "s/$OLDID/$NEWID/g" > $TFILE && mv $TFILE "$f"
#        tail -n +2 $f > $TFILE && mv $TFILE "$f"
#        cat $f | sed 's/\.000000//g' > $TFILE && mv $TFILE "$f"
    else
        echo "Error: Cannot read $f"
    fi
done

