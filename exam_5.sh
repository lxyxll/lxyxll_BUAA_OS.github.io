#!/bin/bash
a=0
while [ $a -le 20 ]
do
	sed "s/REPLACE/"$a"/g" origin/code/$a.c > result/code/$a.c
	a=$((a+1))
done
