#!/bin/bash

folder=$1
rm -rf $folder/klee-out-*

count=0
time {
for filename in $folder/*.c; do
    echo $filename
    make -j 4 -- "klee_build/${filename%.c}.bc"
    [ -f "$filename" ] || break
    echo ""
    echo "GOING TO ANALYSE : $filename"
    echo ""
    echo "" >> klee_output.log
    echo "GOING TO ANALYSE : $filename" >> klee_output.log
    klee -libc=klee "klee_build/${filename%.c}.bc" >> klee_output.log 2>&1
    cat klee-out-$count/info | grep walltimer
    count=$((count+1))
done
}

rm -rf *.bc *.log klee-last klee-out-*
