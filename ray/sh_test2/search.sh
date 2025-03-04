#!/bin/bash
#First you can use grep (-n) to find the number of lines of string.
#Then you can use awk to separate the answer
if [ $# -ne 3 ]; then
    echo "Usage: $0 <input_file> <search_string> <output_file>"
    exit 1
fi
grep -nF "$2" "$1" | cut -d: -f1 > "$3"
