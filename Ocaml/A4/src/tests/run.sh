#!/bin/sh
# This script compiles and executes each program [f] in `ls *.gpy`,
# testing type-annotated output against expected output in [f.expected].

## First, we compile programs we expect to typecheck:

for f in `ls test*.gpy`; do
    ../grumpy.native -i $f --dump-tycheck
    if [ ! $? -eq 0 ]; then
	echo "*** $f FAILED ***"		
    else 
	cmp -s $f.expected $f.tychecked
	if [ $? -eq 0 ]; then 
	    echo "$f passed"
	else 
	    echo "*** $f FAILED ***"
	fi
    fi
done

## Next, we compile programs we expect *NOT* to typecheck:

for f in `ls fail*.gpy`; do
    ../grumpy.native -i $f --dump-tycheck >/dev/null 2>&1
    if [ $? -eq 0 ]; then 
	echo "*** $f FAILED ***"
    else 
	echo "$f passed"
    fi
done

