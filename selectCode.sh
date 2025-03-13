#!/bin/bash
rm -rf testfile.c
ln -s testfile.c codeSet/$1.c
gcc -Iinclude testfile.c -o test.out
