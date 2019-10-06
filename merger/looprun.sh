#!/bin/bash

runarray=(595 596 597 598 599 600)
#runarray=(310 330 340 360 380 436 450 595 596)
#runarray=(330 340 360 380 436 450 595 596)
n=6

for data in ${runarray[@]};do
{
		sh convert.sh ${data}
		#echo ${data}
}&
done
wait
