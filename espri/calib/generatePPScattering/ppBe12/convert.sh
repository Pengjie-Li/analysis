#!/bin/bash

runnum=$1
cd /media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/macros/espri/calib/generatePPScattering/ppBe12
./ppBe12  $runnum
cd -
