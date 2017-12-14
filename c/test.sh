#!/bin/bash

ids=()
for value in $@; do
    if [[ ${value:0:1} == "-" ]]; then
        type valgrind >/dev/null 2>&1 || { echo >&2 "You need to install valgrind."; exit 1; }
        valgrind="valgrind"
    else
      id=$(($value))
      if (( $id != 0 )); then
          ids+=($id)
      fi
    fi
done


if (( ${#ids[@]} == 0 )); then
    echo -e "You must specify numbers. \nAlso you can add '-' to enable memcheck."
    exit 1
fi

lib_dir=("algorithms data-structures tools")
lib=""
for dir in ${lib_dir[@]}; do
    for file in `ls $dir/*.c |grep -v "\-test.c"`; do
        lib="$lib $file"
    done
done

for id in ${ids[@]}; do
    dir="$((id/100))00-$((id/100))99"

    if (( $id < 10 )); then id="0$id"; fi
    file=`ls $dir/*.c |grep "/$id"`
    if [ -z $file ]; then
        # echo "No.$id not found."
        continue
    fi

    excute=${file:0:${#file}-2}
    gcc $file $lib -lm -o $excute
    if [[ !$? ]]; then
        $valgrind $excute
        rm $excute
    fi
done
