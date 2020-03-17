#!/usr/bin/env bash

readlink="readlink"
if [[ $(uname) == "Darwin" ]]; then
  type greadlink >/dev/null 2>&1 || {
    echo >&2 "You need to install greadlink. (brew install coreutils)"
    echo >&2 "See https://stackoverflow.com/a/4031502"
    exit 1;
  }
  readlink="greadlink"
fi

# 进入脚本目录
cd "$(dirname "$($readlink -f "$0")")/.." || exit 1

usage() {
  printf "Complie and run solution.\n"
  printf "Usage:\n"
  printf "  %s [OPTION]... <COMMAND|number>...\n" $0
  printf "\n"

  printf "OPTION:\n"
  printf "  -m\tEnable memcheck. (use valgrind)\n"
  printf "\n"

  printf "COMMAND:\n"
  printf "  all\tRun all solutions.\n"
  printf "  test\tRun library's test.\n"
  exit 1
}

run() {
  C_INCLUDE_PATH=$C_INCLUDE_PATH:$(pwd)/..
  export C_INCLUDE_PATH
  lib=$(ls c/[a-z]*/*.c |grep -v test.c)

  for file in $1; do
    [ -f "$file" ] || { printf "NO.%d not found.\n" "$id"; exit 1; }

    printf '%s\n' "$file"
    excute=${file%.c}

    if ! gcc -std=c99 -Wall -o "$excute" "$file" $lib -lm; then exit 1; fi
    if ! $valgrind "$excute"; then fail_count=$((fail_count+1)); fi
    rm "$excute"
  done
}

main() {
  if [[ $# -lt 1 ]]; then usage; fi

  for arg in "$@"; do
    if [[ $arg == "-m" ]]; then
      type valgrind >/dev/null 2>&1 || { echo >&2 "You need to install valgrind."; exit 1; }
      valgrind="valgrind";
    fi
  done

  for arg in "$@"; do
    case $arg in
      "all")
        run "c/[0-9]*/*.c"
        ;;
      "test")
        run "c/[a-z]*/*-test.c"
        ;;
      [0-9]*)
        id=$(printf "%02d" "$arg")
        run "c/[0-9]*/$id-*.c"
        ;;
      [-]*)
        ;;
      *)
        usage
    esac
  done

  exit $fail_count
}

main "$@"
