#!/bin/bash
#NO XF
type1=No_Xf_cut

hadd ./${type1}/results/C/corr_data_C.root ./${type1}/results/C/corr_data_*.root
mv ./${type1}/results/C/corr_data_C.root ./${type1}/results/

hadd ./${type1}/results/Fe/corr_data_Fe.root ./${type1}/results/Fe/corr_data_*.root
mv ./${type1}/results/Fe/corr_data_Fe.root ./${type1}/results/

hadd ./${type1}/results/Pb/corr_data_Pb.root ./${type1}/results/Pb/corr_data_*.root
mv ./${type1}/results/Pb/corr_data_Pb.root ./${type1}/results/

hadd ./${type1}/results/DC/corr_data_DC.root ./${type1}/results/DC/corr_data_*.root
mv ./${type1}/results/DC/corr_data_DC.root ./${type1}/results/

hadd ./${type1}/results/DFe/corr_data_DFe.root ./${type1}/results/DFe/corr_data_*.root
mv ./${type1}/results/DFe/corr_data_DFe.root ./${type1}/results/

hadd ./${type1}/results/DPb/corr_data_DPb.root ./${type1}/results/DPb/corr_data_*.root
mv ./${type1}/results/DPb/corr_data_DPb.root ./${type1}/results/

hadd ./${type1}/results/corr_data_Phi.root ./${type1}/results/corr_data_*.root
rm ./${type1}/results/corr_data_C.root
rm ./${type1}/results/corr_data_Fe.root
rm ./${type1}/results/corr_data_Pb.root
rm ./${type1}/results/corr_data_DC.root
rm ./${type1}/results/corr_data_DFe.root
rm ./${type1}/results/corr_data_DPb.root

#XF
type2=Xf_cut

hadd ./${type2}/results/C/corr_data_C.root ./${type2}/results/C/corr_data_*.root
mv ./${type2}/results/C/corr_data_C.root ./${type2}/results/

hadd ./${type2}/results/Fe/corr_data_Fe.root ./${type2}/results/Fe/corr_data_*.root
mv ./${type2}/results/Fe/corr_data_Fe.root ./${type2}/results/

hadd ./${type2}/results/Pb/corr_data_Pb.root ./${type2}/results/Pb/corr_data_*.root
mv ./${type2}/results/Pb/corr_data_Pb.root ./${type2}/results/

hadd ./${type2}/results/DC/corr_data_DC.root ./${type2}/results/DC/corr_data_*.root
mv ./${type2}/results/DC/corr_data_DC.root ./${type2}/results/

hadd ./${type2}/results/DFe/corr_data_DFe.root ./${type2}/results/DFe/corr_data_*.root
mv ./${type2}/results/DFe/corr_data_DFe.root ./${type2}/results/

hadd ./${type2}/results/DPb/corr_data_DPb.root ./${type2}/results/DPb/corr_data_*.root
mv ./${type2}/results/DPb/corr_data_DPb.root ./${type2}/results/

hadd ./${type2}/results/corr_data_Phi.root ./${type2}/results/corr_data_*.root
rm ./${type2}/results/corr_data_C.root
rm ./${type2}/results/corr_data_Fe.root
rm ./${type2}/results/corr_data_Pb.root
rm ./${type2}/results/corr_data_DC.root
rm ./${type2}/results/corr_data_DFe.root
rm ./${type2}/results/corr_data_DPb.root
