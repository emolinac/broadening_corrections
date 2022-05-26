//This binning program is very specific, if you want to change a single thing you have to inspec it closely!
TString ffinal_loc = "/user/e/emolina/Pt_broadening/binning/";

/*ZH VARIABALES*/
Double_t Zh_min = 0.;
Double_t Zh_max = 1.;
const Int_t N_Zh = 8;
Double_t delta_Zh = (Zh_max-Zh_min)/N_Zh;

/*PT2 VARIABALES*/
Double_t Pt2_min = 0.;
Double_t Pt2_max = 3.;
const Int_t N_Pt2 = 25;
Double_t delta_Pt2 = (Pt2_max-Pt2_min)/N_Pt2;

//PhiPQ uses full range->NOt necessary in the cuts of other variables bin limits calculation
Double_t Phi_min = -180;
Double_t Phi_max = 180;
const Int_t N_Phi = 12;
Double_t delta_Phi = (Phi_max-Phi_min)/N_Phi;

const Int_t N_Q2 = 3;
const Int_t N_Nu = 3;

Double_t Q2_binning[4]   = {1,1.3,1.8,4};
Double_t Nu_binning[4]   = {2.2,3.2,3.7,4.26}; 
Double_t Zh_binning[9]   = {0,0.1,0.2,0.3,0.4,0.5,0.6,0.8,1};

TString ffinal_name = Form("binning_%i%i%i%i%i_Zh_fancy.root",N_Q2,N_Nu,N_Zh,N_Pt2,N_Phi);

void MACRO_custom_binning_Zh_fancy()
{
  TFile* ffinal = new TFile(ffinal_loc+ffinal_name,"RECREATE");
  TNtuple* limits_tuple = new TNtuple("limits_tuple","limits_tuple","Q2_bin:Nu_bin:Zh_bin:Pt2_bin:Phi_bin:Q2_min:Q2_max:Nu_min:Nu_max:Zh_min:Zh_max:Pt2_min:Pt2_max:Phi_min:Phi_max");

  for(Int_t i = 0 ; i < N_Q2 ; i++)
    {
      for(Int_t j = 0 ; j < N_Nu ; j++)
	{
	  for(Int_t k = 0 ; k < N_Zh ; k++)
	    {
	      for(Int_t l = 0 ; l < N_Pt2 ; l++)
		{
		  for(Int_t m = 0 ; m < N_Phi ; m++)
		    {
		      Double_t Q2_bin_min = Q2_binning[i];
		      Double_t Q2_bin_max = Q2_binning[i+1];

		      Double_t Nu_bin_min = Nu_binning[j];
		      Double_t Nu_bin_max = Nu_binning[j+1];

		      Double_t Zh_bin_min = Zh_binning[k];
		      Double_t Zh_bin_max = Zh_binning[k+1];

		      Double_t Pt2_bin_min = Pt2_min + l*delta_Pt2;
		      Double_t Pt2_bin_max = Pt2_min + (l+1)*delta_Pt2;

		      Double_t Phi_bin_min = Phi_min + m*delta_Phi;
		      Double_t Phi_bin_max = Phi_min + (m+1)*delta_Phi;

		      limits_tuple->Fill(i,j,k,l,m,Q2_bin_min,Q2_bin_max,Nu_bin_min,Nu_bin_max,Zh_bin_min,Zh_bin_max,Pt2_bin_min,Pt2_bin_max,Phi_bin_min,Phi_bin_max);
		    }
		}
	    }
	}
    }

  ffinal->cd();
  limits_tuple->Write();
}
