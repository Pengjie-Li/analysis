#!/bin/bash

# Be14
#run1=366
#run2=455

run1=331
run2=365
n=30


for (( i=1; i<=$n; i++ )); do
{
        for (( j=$run1+$i-1; j<=$run2; j+=$n )); do

                sh convert.sh $j 
                        done
}&
done
wait
