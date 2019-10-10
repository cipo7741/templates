#!/bin/bash
a=/tmp/xx/file.tar.gz
xpath=${a%/*} 
xbase=${a##*/}
xfext=${xbase##*.}
xpref=${xbase%.*}
echo;echo path=${xpath};echo pref=${xpref};echo ext=${xfext}

path=/tmp/xx
pref=file.tar
ext=gz
