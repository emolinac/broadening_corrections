/*GLOBAL VARIABLES*/
TString simul_loc = "/work/emolina/";
TString data_loc  = "/work/emolina/";

const Int_t N_Phi = 12;

void target_setting(TString& simul_target, TString& data_target, TCut& VC_data, TString target);
void rec_histo_process(TH1F* h);
void acc_histo_process(TH1F* h);

Int_t empty_histo(TH1F* h);

void MACRO_acc_corrected(Int_t Q2_bin_selected, Int_t Nu_bin_selected, Int_t Zh_bin_selected, TString target,
			   TString binning_name)
{
  TString simul_target, data_target;
  TCut VC_data;

  /*Target setting*/
  target_setting(simul_target, data_target, VC_data, target);

  TFile* fsimul   = new TFile(simul_loc+simul_target+"1_simul.root","READ");
  TFile* fdata    = new TFile(data_loc+data_target+"_data_Npion.root","READ");
  TFile* fbinning = new TFile(binning_name,"READ");
  
  gROOT->cd();

  /*Get the tuples*/
  TNtuple* ntuple_thrown = (TNtuple*) fsimul->Get("ntuple_thrown");
  TNtuple* ntuple_accept = (TNtuple*) fsimul->Get("ntuple_accept");
  TNtuple* ntuple_data   = (TNtuple*) fdata->Get("ntuple_data");
  TNtuple* limits_tuple  = (TNtuple*) fbinning->Get("limits_tuple");

  /*FAIL-SAFE*/
  if(ntuple_thrown==NULL||ntuple_accept==NULL||ntuple_data==NULL||limits_tuple==NULL){
    std::cout<<"ERROR! One of the tuples could not be loaded!"<<std::endl;
    return;
  }

  /*Setting the tuples than need to be read*/
  Float_t Q2_bin_min, Q2_bin_max,Nu_bin_min, Nu_bin_max,Zh_bin_min, Zh_bin_max,Pt2_bin_min, Pt2_bin_max,Phi_bin_min, Phi_bin_max;
  Float_t Q2_bin, Nu_bin, Zh_bin, Pt2_bin, Phi_bin;
  limits_tuple->SetBranchAddress("Q2_min",&Q2_bin_min);
  limits_tuple->SetBranchAddress("Q2_max",&Q2_bin_max);
  limits_tuple->SetBranchAddress("Nu_min",&Nu_bin_min);
  limits_tuple->SetBranchAddress("Nu_max",&Nu_bin_max);
  limits_tuple->SetBranchAddress("Zh_min",&Zh_bin_min);
  limits_tuple->SetBranchAddress("Zh_max",&Zh_bin_max);
  limits_tuple->SetBranchAddress("Pt2_min",&Pt2_bin_min);
  limits_tuple->SetBranchAddress("Pt2_max",&Pt2_bin_max);
  limits_tuple->SetBranchAddress("Phi_min",&Phi_bin_min);
  limits_tuple->SetBranchAddress("Phi_max",&Phi_bin_max);
  limits_tuple->SetBranchAddress("Q2_bin",&Q2_bin);
  limits_tuple->SetBranchAddress("Nu_bin",&Nu_bin);
  limits_tuple->SetBranchAddress("Zh_bin",&Zh_bin);
  limits_tuple->SetBranchAddress("Pt2_bin",&Pt2_bin);
  limits_tuple->SetBranchAddress("Phi_bin",&Phi_bin);

  Double_t limits_entries     = limits_tuple->GetEntries();

  /*Set the lists according to the bin being used*/
  std::cout<<"Q2 bin selected "<<Q2_bin_selected<<" Nu bin selected "<<Nu_bin_selected<<std::endl;

  Float_t Q2_min_event = 0;
  Float_t Q2_max_event = 0;
  Float_t Nu_min_event = 0;
  Float_t Nu_max_event = 0;
  Float_t Zh_min_event = 0;
  Float_t Zh_max_event = 0;

  for(Int_t acc_entry = 0 ; acc_entry < limits_entries ; acc_entry++)
    {
      limits_tuple->GetEntry(acc_entry);
      if(Q2_bin==Q2_bin_selected&&Nu_bin==Nu_bin_selected&&Zh_bin==Zh_bin_selected)
	{
	  Q2_min_event = Q2_bin_min;
	  Q2_max_event = Q2_bin_max;
	  Nu_min_event = Nu_bin_min;
	  Nu_max_event = Nu_bin_max;
	  Zh_min_event = Zh_bin_min;
	  Zh_max_event = Zh_bin_max;

	  break;
	}
    } 

  std::cout<<Q2_min_event<<" < Q2 < "<<Q2_max_event<<std::endl;
  std::cout<<Nu_min_event<<" < Nu < "<<Nu_max_event<<std::endl;
  std::cout<<Zh_min_event<<" < Zh < "<<Zh_max_event<<std::endl;

  TCut Q2_cut     = Form("Q2>%f&&Q2<%f",Q2_min_event,Q2_max_event);
  TCut Nu_cut     = Form("Nu>%f&&Nu<%f",Nu_min_event,Nu_max_event);
  TCut Zh_cut     = Form("Zh>%f&&Zh<%f",Zh_min_event,Zh_max_event);
  TCut YC_cut     = "TMath::Abs(YC)<1.4";
  TCut deltaZ_cut = "TMath::Abs(deltaZ)<3.";

  TCut cuts_simul   = Q2_cut&&Nu_cut&&Zh_cut&&deltaZ_cut;
  TCut cuts_data    = Q2_cut&&Nu_cut&&Zh_cut&&deltaZ_cut&&YC_cut&&VC_data;

  std::cout<<"SIMUL CUTS = "<<cuts_simul<<std::endl;
  std::cout<<"DATA  CUTS = "<<cuts_data<<std::endl;

  ntuple_thrown->Draw(">>list_thr",cuts_simul);
  ntuple_accept->Draw(">>list_acc",cuts_simul&&YC_cut);
  ntuple_data->Draw(">>list_dat",cuts_data);

  TEventList* evnt_thr = (TEventList*) gDirectory->Get("list_thr");
  TEventList* evnt_acc = (TEventList*) gDirectory->Get("list_acc");
  TEventList* evnt_dat = (TEventList*) gDirectory->Get("list_dat");

  ntuple_thrown->SetEventList(evnt_thr);
  ntuple_accept->SetEventList(evnt_acc);
  ntuple_data->SetEventList(evnt_dat);

  /*Start loop with binning tuple*/
  TH1F* hdata      = new TH1F("hdata","",N_Phi,-180,180);
  TH1F* haccept    = new TH1F("haccept","",N_Phi,-180,180);
  TH1F* hthrown    = new TH1F("hthrown","",N_Phi,-180,180);
  TH1F* hratio     = new TH1F("hratio","",N_Phi,-180,180);
  TH1F* hdata_corr = new TH1F("hdata_corr","",N_Phi,-180,180);
  
  hdata->Sumw2();
  haccept->Sumw2();
  hthrown->Sumw2();

  TFile* ftarget  = new TFile("results.root","RECREATE");
  gROOT->cd();

  for(Int_t entry = 0 ; entry < limits_tuple->GetEntries() ; entry++){
    limits_tuple->GetEntry(entry);
    if(Q2_bin==Q2_bin_selected&&Nu_bin==Nu_bin_selected&&Zh_bin==Zh_bin_selected&&Phi_bin==0){

      TCut loop_cut = Form("Pt2>%f&&Pt2<%f",Pt2_bin_min,Pt2_bin_max);

      std::cout<<"LOOP CUT = "<<loop_cut<<std::endl;

      /*Filling of histograms*/
      ntuple_data->Project("hdata","PhiPQ",loop_cut);
      if(empty_histo(hdata)==1){continue;}
      ntuple_thrown->Project("hthrown","PhiPQ",loop_cut);
      ntuple_accept->Project("haccept","PhiPQ",loop_cut);

      /*Setting Naccept>1*/
      rec_histo_process(haccept);

      /*Obtaining Acc factors*/
      hratio->Divide(haccept,hthrown,1,1,"B");

      /*Setting acc<1*/
      acc_histo_process(hratio);

      /*Obtaining Acc Corr Data*/
      hdata_corr->Divide(hdata,hratio,1,1);

      ftarget->cd();
      hratio->Write(Form("accfactor_"+target+"_%i%i%i%i",Q2_bin_selected,Nu_bin_selected,Zh_bin_selected,(Int_t)Pt2_bin));
      hdata->Write(Form("data_"+target+"_%i%i%i%i",Q2_bin_selected,Nu_bin_selected,Zh_bin_selected,(Int_t)Pt2_bin));
      hdata_corr->Write(Form("corr_data_"+target+"_%i%i%i%i",Q2_bin_selected,Nu_bin_selected,Zh_bin_selected,(Int_t)Pt2_bin));
      gROOT->cd();

      hdata->Reset();
      haccept->Reset();
      hthrown->Reset();
      hratio->Reset();
      hdata_corr->Reset();
    }
  }
}

void target_setting(TString& simul_target, TString& data_target, TCut& VC_data, TString target)
{
  if(target(0,1)=="D"){
    std::cout<<"Choosed LIQUID target of "<<target<<" configuration"<<std::endl;
    /*Target Names*/
    simul_target = "D";
    data_target  = target(1,2);

    /*VC setting*/
    // USING TM VC
    VC_data   = "VC_TM==1.";
  }
  else{
    std::cout<<"Choosed SOLID target of "<<target<<" configuration"<<std::endl;
    /*Target Names*/
    simul_target = target;
    data_target = target;

    /*VC setting*/
    // USING TM VC
    VC_data   = "VC_TM==2.";
  }
}

Int_t empty_histo(TH1F* h)
{
  //return 1 means that the histo is empty!
  Int_t empty = 0;
  for(Int_t bin = 1 ; bin <= h->GetNbinsX() ; bin++)
    {
      if(h->GetBinContent(bin)==0){empty++;}
    }
  if(empty==h->GetNbinsX()){return 1;}
  else{return 0;}
}

void rec_histo_process(TH1F* h)
{
  /*Here is applied the condition that Naccept>1*/
  for(Int_t bin = 1 ; bin <= h->GetNbinsX() ; bin++){
    if(h->GetBinContent(bin)==1){
      h->SetBinContent(bin,0);
      h->SetBinError(bin,0);
    }
  }
}

void acc_histo_process(TH1F* h)
{
  /*Here is applied the condition that acc<1*/
  for(Int_t bin = 1 ; bin <= h->GetNbinsX() ; bin++){
    if(h->GetBinContent(bin)>=1){
      h->SetBinContent(bin,0);
      h->SetBinError(bin,0);
    }
  }
}

