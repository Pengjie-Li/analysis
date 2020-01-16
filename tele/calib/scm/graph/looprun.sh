#!/bin/bash

#runarray=(310 320 330 340 380 700)
runarray=(595 596 597 598 599 600)
n=6

for data in ${runarray[@]};do
{
                sh convert.sh ${data}
                #echo ${data}
}&
done
wait

