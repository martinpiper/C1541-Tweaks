#! /bin/bash
OLDCWD=`pwd`
SCRIPT_PATH=`dirname $0`
CHECK_PATH=./src/

cd $SCRIPT_PATH/../../

FILES=`find $CHECK_PATH -type f \( -name \*.c -o -name \*.h -o -name \*.cc -o -name \*.m -o -name Makefile.am \) -print | xargs grep -l ' $'`

cd $OLDCWD

if [ x"$FILES"x != xx ]; then
    echo "error: found dangling spaces in the following files:"
    for n in $FILES; do
        echo $n
    done
    exit -1
fi
