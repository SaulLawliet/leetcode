#!/bin/bash

readlink="readlink"
if [[ `uname` == "Darwin" ]]; then
    type greadlink >/dev/null 2>&1 || {
        echo >&2 "You need to install greadlink. (brew install coreutils)"
        echo >&2 "See https://stackoverflow.com/a/4031502"
        exit 1;
    }
    readlink="greadlink"
fi

usage() {
    echo "You must specify numbers."
    echo "Or use '-t' to run library's test."
    echo ""
    echo "Also you can add '-' to enable memcheck."
    exit 1
}

cd $(dirname $($readlink -f $0))

open_test=0
ids=()
for value in $@; do
    case $value in
        "-t")
            open_test=1 # run library's test
            ;;
        "-")
            type valgrind >/dev/null 2>&1 || { echo >&2 "You need to install valgrind."; exit 1; }
            valgrind="valgrind";
            ;;
        [0-9]*)
            ids+=$value
            ;;
        *)
            usage
    esac
done


if (( !$open_test && ${#ids[@]} == 0 )); then
    usage
fi


export C_INCLUDE_PATH=$C_INCLUDE_PATH:`pwd`

lib_dir=`ls -d */ |grep -v "^[0-9]"`
lib=""
for dir in ${lib_dir[@]}; do
    for file in `ls ${dir}*.c 2>/dev/null |grep -v "\-test.c"` ; do
        lib="$lib $file"
    done
done

run() {
    excute=${file:0:${#file}-2}
    gcc $file $lib -lm -o $excute
    if [[ !$? ]]; then
        $valgrind $excute
        rm $excute
    fi
}

if (( $open_test)); then
    files=`ls */* |grep "\-test.c"`
    for file in ${files[@]}; do
        echo $file
        run
    done
else
    for id in ${ids[@]}; do
        dir="$((id/100))00-$((id/100))99"

        if (( $id < 10 )); then id="0$id"; fi
        file=`ls $dir/*.c |grep "/$id"`
        if [ -z $file ]; then
            # echo "No.$id not found."
            continue
        fi
        run
    done
fi
