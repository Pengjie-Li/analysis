#!/bin/bash

# Be12
run1=331
run2=365

# Be14
#run1=587
#run2=594

#run1=1
#run2=600

n=20


for (( i=1; i<=$n; i++ )); do
{
        for (( j=$run1+$i-1; j<=$run2; j+=$n )); do

                sh convert.sh $j 
                        done
}&
done
wait
