#!/bin/bash

runnum=$1
cd /media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/macros/bdc/convert
echo "Converting" $runnum
./ConvertDC  $runnum
cd -