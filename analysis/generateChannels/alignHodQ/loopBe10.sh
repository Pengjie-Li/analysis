#!/bin/bash

# Be14
#run1=366
#run2=455

run1=300
run2=310
n=10


for (( i=1; i<=$n; i++ )); do
{
        for (( j=$run1+$i-1; j<=$run2; j+=$n )); do

                sh convert.sh $j 
                        done
}&
done
wait
