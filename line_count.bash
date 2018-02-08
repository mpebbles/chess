#!/bin/bash

count=0
for a in $( ls )
do
    if [[ "$a" = *.cpp ]] || [[ "$a" = *.h ]] || [[ "$a" = "Makefile" ]]
    then
         file_lc=$( wc -l < $a )
         count=$(($count+$file_lc))
    fi
done
echo $count
