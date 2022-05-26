#!/bin/bash

#SBATCH --time=00:20:00
#SBATCH --output=./out_log/%x.txt
#SBATCH --error=./err_log/%x.txt
#SBATCH --mail-type=FAIL
#SBATCH --mail-user=emolinac92@gmail.com

#INPUT VARIABLES
target=$1
Q2_BIN=$2
NU_BIN=$3
ZH_BIN=$4
results_location=$5
binning_name=$6

STARTTIME=$(date +"%s")

cp MACRO_acc_corrected.cpp $TMPDIR

cd $TMPDIR
root -q -l "MACRO_acc_corrected.cpp(${Q2_BIN},${NU_BIN},${ZH_BIN},\"${target}\",\"${binning_name}\")"

if [ -e "results.root" ]
then
    mv results.root ${results_location}corr_data_${target}_${Q2_BIN}${NU_BIN}${ZH_BIN}.root
elif [ ! -e "results.root" ]
then
    echo The result file does not exist
fi

ENDTIME=$(date +"%s")

echo Elapsed time was $((${ENDTIME} - ${STARTTIME})) seconds
