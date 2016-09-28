#include <TTree.h>
#include <TFile.h>
#include <TPad.h>
#include <TMath.h>
#include <TH1D.h>
#include <TH2F.h>
#include <TF1.h>
#include <TLegend.h>
#include <TStyle.h>
#include <TROOT.h>
#include <TSystem.h>
#include <TCanvas.h>
#include <TChain.h>
#include <fstream>
#include <iostream>

#include "var.h"
using namespace std;

void ana.cc()
{
  data md;
  
  gStyle->SetPalette(1);
  gStyle->SetOptFit(kTRUE);
  gStyle->SetOptStat(0);
  gStyle->SetTextSize(0.01908148);
  gStyle->SetTitleFontSize(0.03);
  gStyle->SetTitleXSize(0.04);
  gStyle->SetTitleXOffset(1.3);
  gStyle->SetTitleYSize(0.04);
  gStyle->SetTitleYOffset(2.2);
  gStyle->SetPadBottomMargin(0.18);
  gStyle->SetPadTopMargin(0.05);
  gStyle->SetPadLeftMargin(0.2);
  gStyle->SetPadRightMargin(0.1);
  
  TString sfile = "filename.root"; 
  TString outputfile; 

  TFile *openFile = new TFile(Form("%s",sfile.Data())"READ");
  TTree *finaltr = (TTree*) openFile -> Get("finaldata");
  TTree *sorttr = (TTree*) openFile -> Get("sortdata"); 

  finaltr->SetBranchAddress("eventID",&md.eventID);
  finaltr->SetBranchAddress("num_ArrayEvent_SM",&md.num_ArrayEvent_SM);
  finaltr->SetBranchAddress("SMfADC_ch1",md.SMfADC_ch1);
  finaltr->SetBranchAddress("SMfADC_ch2",md.SMfADC_ch2);
  finaltr->SetBranchAddress("SMfADC_ch3",md.SMfADC_ch3);
  finaltr->SetBranchAddress("SMfADC_ch4",md.SMfADC_ch4);
  finaltr->SetBranchAddress("err_ch1",md.err_ch1);
  finaltr->SetBranchAddress("err_ch2",md.err_ch2);
  finaltr->SetBranchAddress("err_ch3",md.err_ch3);
  finaltr->SetBranchAddress("err_ch4",md.err_ch4);

  sorttr->SetBranchAddress("eventID",&md.eventID);
  sorttr->SetBranchAddress("num_ArrayEvent",&md.num_ArrayEvent);
  sorttr->SetBranchAddress("SMfADC_ch1",md.SMfADC_ch1);
  sorttr->SetBranchAddress("SMfADC_ch2",md.SMfADC_ch2);
  sorttr->SetBranchAddress("SMfADC_ch3",md.SMfADC_ch3);
  sorttr->SetBranchAddress("SMfADC_ch4",md.SMfADC_ch4);
  
  TTree *writeTree = new TTree("data","");
  writeTree->Branch("eventID",&md.eventId,"eventID/I");
  writeTree->Branch("pedestal",&pedestal,"pedestal/F");
  writeTree->Branch("pedrms",&pedrms,"pedrms/F");
  writeTree->Branch("Psum",&QSum,"Qsum/F");
  writeTree->Branch("Pint",&QInt,"Qint/F");
  writeTree->Branch("Pfheight",&Pfheight,"Pfheight/F");
  writeTree->Branch("Pfheight_x",&Pfheight_x,"Pfheight_x/F");
  writeTree->Branch("Pheight",&Pheight,"Pheight/F");
  writeTree->Branch("Ptail",&Ptail,"Ptail/F");
  writeTree->Branch("chisq",&chisq,"chisq/F");
  writeTree->Branch("chisqprob",&chisqprob,"chisqprob/F");
  writeTree->Branch("NDF",&NDF,"NDF/F");
  writeTree->Branch("tau_r",&tau_r,"tau_r/F");
  writeTree->Branch("tau_s",&tau_s,"tau_s/F");
  writeTree->Branch("tau_f",&tau_f,"tau_f/F");
  writeTree->Branch("ratio",&ratio,"ratio/F");
  writeTree->Branch("t0",&t0,"t0/F");
  writeTree->Branch("IntStartVal",&IntStartVal,"IntStartVal/F");
  writeTree->Branch("IntEndVal",&IntEndVal,"IntEndVal/F");


  TFile *writeFile = new TFile(".root","recreate");

  TCanvas *cvs = new TCanvas("cvs","",700,700);

  TH1D *h = new TH1D("h","Title;xtitle;ytitle",600, 0,12000);
  TF1* FitFunction = new TF1("fFit","[0]*(1/[2]*TMath::Exp(-(x-[1])/[2])+[4]/[3]*TMath::Exp(-(x-[1])/[3])-(1/[2]+[4]/[3])*TMath::Exp(-(x-[1])/[5]))");

  // event loop start
  const int NEntries = dataTree->GetEntries();
  for(int i=0;i<NEntries;i++)
  {
    finaltr->GetEntry(i);
   
    // channel loop start 
    for(int j=0;j<md.num_ArrayEvent_SM)
    {
      // pedestal calculation
      for(int k=0; k<md.num_ArrayEvent_SM/16; k++)
      {
        if(j<16*(k+1) && j>=16*k)
        {
          SumPed += md.SMfADC_ch1[j];
          ped_confirm[k] = SumPed/(j+1-16*k);
        



    writeTree->Fill();
  }

  //Scint1
  c1->cd();
  dataTree->Draw(">>h1");
  h1->Fit("f1","R");
  mean[0] = f1->GetParameter(1); 
  sigma[0] = f1->GetParameter(2);
  h1->Draw();
  f1->Draw("same");

 writeFile->cd();

}







