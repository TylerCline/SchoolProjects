#!/bin/sh

# This script compiles and executes each program [f] in `ls *.gpy`,
# testing output against expected output in [f.expected].

for f in `ls *.gpy`; do
    ../grumpy.native -i $f;
    if [ $? -eq 0 ]; then 
	echo "*** $f passed ***"
    else 
	echo "*** $f FAILED ***"
    fi
done
