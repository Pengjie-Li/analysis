#!/bin/bash

version=v2
#runarray=(310 330 340 360 380 436 450 595 596)
# runarray=(330 340 360 380 436 450 595 596)
n=6

for data in ${runarray[@]};do
{
		mv ./rootfiles/run0${data}_analysed.root  ./rootfiles/run0${data}_analysed.root_${version}
		#echo mv ./rootfiles/run0${data}_analysed.root  ./rootfiles/run0${data}_analysed.root_${version}
}&
done
wait
