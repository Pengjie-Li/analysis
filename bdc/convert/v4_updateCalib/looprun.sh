#!/bin/bash

runarray=(310 330 340 360 380 450)
n=6

for data in ${runarray[@]};do
{
		sh convert.sh ${data}
		#echo ${data}
}&
done
wait
