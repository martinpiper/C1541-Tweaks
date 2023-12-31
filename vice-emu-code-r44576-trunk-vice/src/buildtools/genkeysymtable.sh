#!/bin/sh
#
# Process `vhkkeysyms.h` to generate a sorted table of key names with their
# symbolic values.
#
# Usage: genkeysymtable.sh <path-to-vhkkeysysm.h> <output-file>
#
# This script is called from src/arch/shared/hotkeys/Makefile.am


# Print usage message
usage()
{
    echo "Usage: $(basename $0) <path-to-vhkkeysyms.h> <output-file>"
    echo ""
    echo "For example: $(basename $0) src/arch/shared/hotkeys/vhkkeysyms.h \\"
    echo "                               src/arch/shared/hotkeys/keysymtable.h"
}


# Check command line arguments
if [ "$1" = "-h" -o "$1" = "--help" ]; then
    # help requested
    usage
    exit 0
fi
if [ "$#" -ne 2 ]; then
    # error, need two arguments
    echo "Error: need input and output file arguments."
    usage
    exit 1
fi

# Check for input file existence
if [ ! -f $INFILE ]; then
    echo "Error: could not locate input file \"$INFILE\"."
    exit 1
fi


INFILE=$1
OUTFILE=$2
MYDIR=$(dirname $0)

# Output header: comment and start of array definition
echo "/* This file is generated by $(basename $0), do not edit. */" > $OUTFILE
echo "static const vhk_key_t keys[] = {" >> $OUTFILE

# Run awk script to generate array initializers
#
# We need LC_ALL=C for `sort` to make sure we sort in the correct order for
# strcmp(3) to work while doing a bsearch(3) on the table.
awk -f $MYDIR/genkeysymtable.awk < $INFILE | LC_ALL=C sort >> $OUTFILE

# Output footer: close array definition
# Unfortunately we have a trailing comma in the initializer list; should a
# compiler start complaining we'll have to fix that somehow.
echo "};" >> $OUTFILE
