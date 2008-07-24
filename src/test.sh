#!/bin/sh
if [ $# -gt 1 ]
then
    echo "test.sh [-v]" > /dev/stderr
    exit 1
fi

if [ $# -eq 0 ]
then
    ./test
    exit $?
fi

if [ $1 == "-v" ]
then
    valgrind --tool=memcheck --leak-check=full --show-reachable=yes -q ./test
else
    echo "test.sh [-v]" > /dev/stderr
    exit 1
fi
