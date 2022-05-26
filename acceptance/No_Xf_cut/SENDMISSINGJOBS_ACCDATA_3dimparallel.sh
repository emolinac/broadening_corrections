#!/bin/bash

#PROGRAM TO SEND PARALLEL JOBS

#____________________ACC+DATA PARALLEL______________________#
echo Input C Fe Pb DC DFe DPb
read target

#FINAL LOCATION
results_location=$(pwd)/results/${target}/
results_folder=$(pwd)/results/
mother_directory=$(pwd)
err_loc=$(pwd)/err_log/
out_loc=$(pwd)/out_log/

#_____________________CREATION OF NON-CREATED FOLDERS___________________________#
if [ ! -d "$results_folder" ]
then
    echo Results folderdirectory does not exist! Creating one...
    mkdir ${results_folder}
fi
if [ ! -d "$results_location" ]
then
    echo Results directory does not exist! Creating one...
    mkdir ${results_location}
fi
if [ ! -d "$err_loc" ]
then
    echo Err directory not found! Creating one...
    mkdir ${err_loc}
fi

if [ ! -d "$out_loc" ]
then
    echo Out directory not found! Creating one...
    mkdir ${out_loc}
fi

echo Mother directory = $mother_directory

#VARIABLES
N_Q2=3
N_NU=0
N_ZH=10
NU_BINS_ARRAY=(3 3 3)

if [ -d "$results_location" ]
then
    for(( i = 0 ; i < ${N_Q2} ; i++ ))
    do
	NU_BINS=${NU_BINS_ARRAY[$i]}
	for(( j = 0 ; j < ${NU_BINS} ; j++))
	do
	    for(( k = 0 ; k < ${N_ZH} ; k++))
	    do
		if [ ! -e "${results_location}corr_data_${target}_${i}${j}${k}.root" ]
		then
		    echo The result file $i $j $k does not exist. Sending JOB!
		    sbatch -J ACCRCDAT_${target}_${i}${j}${k} JOB_ACCRCDATA.sh $target $i $j $k ${results_location}
		fi
	    done
	done
    done
elif [ ! -d "$results_location" ]
then
    echo One of the adresses does not exist PLEASE CHECK
fi

# if [ -d "$results_location" ]
# then
#     for(( i = 1 ; i < 2 ; i++ ))
#     do
# 	for(( j = 0 ; j < 1 ; j++))
# 	do
# 	    for(( k = 0 ; k < 5 ; k++))
# 	    do
# 		sbatch -J ACCRCDAT_${target}_${i}${j}${k} JOB_ACCRCDATA.sh $target $i $j $k ${results_location}
# 	    done
# 	done
#     done
# elif [ ! -d "$results_location" ]
# then
#     echo One of the adresses does not exist PLEASE CHECK
# fi
