#!/bin/bash
if [ $# -eq 0 ]
	then
	cat stderr.txt
elif [ $# -eq 1 ]
       then 
       sed -n '$1,$p' stderr.txt
elif [ $# -eq 2 ]
       then
       sed -n '$1,$2p' stderr.txt
fi
