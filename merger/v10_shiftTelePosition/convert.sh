#!/bin/bash

runnum=$1
cd /media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/macros/merger
./Merger  $runnum
cd -
