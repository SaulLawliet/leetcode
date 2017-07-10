#!/bin/bash

# type valgrind >/dev/null 2>&1 || { echo >&2 "You need to install valgrind."; exit 1; }
type valgrind >/dev/null 2>&1
if (( $? == 0 )); then valgrind="valgrind"; fi

function usage() {
    echo "You must specify a number."
    exit 1
}

if (( $# != 1 ));then
    usage
fi

lib_dir=("algorithms data-structures tools")
lib=""
for dir in ${lib_dir[@]}; do
    for file in `ls $dir/*.c |grep -v "\-test.c"`; do
        lib="$lib $file"
    done
done

n="$(($@))"
dir="$((n/100))00-$((n/100))99"

file=$n
if (($n < 10)); then file="0$n"; fi

file=`ls $dir/*.c |grep "/$file"`
if [ -z $file ]; then
    echo "No.$n not found."
    exit 1
fi

excute=${file:0:${#file}-2}

# echo "gcc $file $lib -o $excute && valgrind $excute && rm $excute"
gcc $file $lib -lm -o $excute && $valgrind $excute && rm $excute

