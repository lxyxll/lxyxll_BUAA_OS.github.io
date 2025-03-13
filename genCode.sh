#!/bin/bash
mkdir codeSet
for file in $(ls code/) 
do
	sed "1i\#include"include/libsy.h"" $file | sed 's/getInt/getint/g' | codeSet/$file.c
done
