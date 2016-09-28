#!/bin/bash
# nevt_min : starting event number 
# nevt_max : ending event number
# nevt_max = -1 : loop until the end 
nevt_min='0'
nevt_max='-1'

#channel selection chselect = 1-4
chselect='1'

outputDir='FitAnaResult'
DATE="$(date +"%y%m%d%H%M")"

mkdir -p $outputDir
cp var.h var_$DATE.h
cp anafitt.C anafitt_$DATE.C
mv var_$DATE.h $outputDir
mv anafitt_$DATE.C $outputDir


# anafitt.cc(int nevt_min = 0, int nevt_max = 20, int chselect = 1, TString inputfile = "filename")

root -l -b <<EOF
.L anafitt.C++
.q
EOF

echo Start Condor
./condor_root.sh $outputDir 'anafitt.C+('$nevt_min','$nevt_max','$chselect')'
