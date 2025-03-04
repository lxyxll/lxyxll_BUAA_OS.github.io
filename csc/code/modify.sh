#!/bin/bash
file=$1
old=$2
new=$3
sed -i "s/$old/$new/g" "$file"
