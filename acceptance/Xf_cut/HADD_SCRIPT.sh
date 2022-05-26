#!/bin/bash

hadd ./results/C/corr_data_C.root ./results/C/corr_data_C_*.root

hadd ./results/Fe/corr_data_Fe.root ./results/Fe/corr_data_Fe_*.root

hadd ./results/Pb/corr_data_Pb.root ./results/Pb/corr_data_Pb_*.root

hadd ./results/DC/corr_data_DC.root ./results/DC/corr_data_DC_*.root

hadd ./results/DFe/corr_data_DFe.root ./results/DFe/corr_data_DFe_*.root

hadd ./results/DPb/corr_data_DPb.root ./results/DPb/corr_data_DPb_*.root
