#!/bin/bash

runarray=(310 320 330 340 380 700)
n=6

for data in ${runarray[@]};do
{
                sh convert.sh ${data}
                #echo ${data}
}&
done
wait

