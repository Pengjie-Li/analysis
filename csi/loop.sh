#!/bin/bash

## Be10 run
#first=310 # first suffix 
#last=316 # last suffix



# Be12 run
first=336 # first suffix 
last=339 # last suffix



## Be14 run
#first=436 # first suffix 
#last=440 # last suffix



# alpha run
#first=595 # first suffix 
#last=600 # last suffix

n=5 # nb of parallel processing


for (( i=1; i<=$n; i++ )); do
    {
        for (( j=$first+$i-1; j<=$last; j+=$n )); do
		#echo "./beam"  $j
		./beam  $j
        done
    }&
done
