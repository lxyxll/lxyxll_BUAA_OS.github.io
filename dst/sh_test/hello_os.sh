#!/bin/bash

if [ $# -ne 2 ]; then
	echo "Usage:$0 <input> <output>"
	exit 1
fi
sed -n '8p;32p;128p;512p;1024p' "$1" > "$2"
