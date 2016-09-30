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
using namespace std;

// How to run : root -l MakeHist.C\(0\) for Cs137
// How to run : root -l MakeHist.C\(1\) for Noise

void MakeHist(int iCat_ = 0) // 0 : Cs137, 1 : Noise
{
  gStyle->SetPalette(1);
  gStyle->SetOptFit(kTRUE);
  gStyle->SetOptStat(0);
  gStyle->SetTextSize(0.01908148);
  gStyle->SetTitleFontSize(0.03);
  gStyle->SetTitleXSize(0.04);
  gStyle->SetTitleXOffset(1.3);
  gStyle->SetTitleYSize(0.04);
  gStyle->SetTitleYOffset(1.2);
  gStyle->SetPadBottomMargin(0.13);
  gStyle->SetPadTopMargin(0.05);
  gStyle->SetPadLeftMargin(0.13);
  gStyle->SetPadRightMargin(0.1);

  Int_t eventID;

  Int_t TDC[18];
  Float_t IntEndVal, Pheight, Pint, tau_r, tau_s, tau_f, A, ratio, t0, NDF, chisqprob, Pfheight, Pfheight_x;
  Double_t chisq;
  Double_t pedestal, RMS;
  Double_t mean[4]={0};
  Double_t sigma[4]={0};

  Int_t NBin_sp = 200;

  if(iCat_ == 0) cout<<"This is Cs137 Data !!!!"<<endl;
  if(iCat_ == 1) cout<<"This is Noise !!!!"<<endl;

  TFile *fl;
  if(iCat_ == 0) fl = new TFile("fitted_Cs137_2100_60_100000_1_front_32_ss.root","READ");
  if(iCat_ == 1) fl = new TFile("fitted_noise_2100_60_100000_Cs_32_ss.root","READ");
  TFile *writeFile;
  if(iCat_ == 0) writeFile = new TFile("Cs137_Ana_Sgn_Front.root","RECREATE");
  if(iCat_ == 1) writeFile = new TFile("Cs137_Ana_Noise.root","RECREATE");

  TH2F *hPintChi2 = new TH2F("hPintChi2",";Pint;Chi2",2000,0.0,2000,1000,0.0,100);
  TH2F *hPintChi2NDF = new TH2F("hPintChi2NDF",";Pint;Chi2/NDF",2000,0.0,2000,1000,0.0,2.0);
  TH2F *hPintRMS = new TH2F("hPintRMS",";Pint;RMS",2000,0.0,2000,1000,0.0,1.0);
  TH2F *hPintChi2Prob = new TH2F("hPintChi2Prob",";Pint;Chi2Prob",2000,0.0,2000,1000,0.0,1.0);
  TH2F *hPintPheightX = new TH2F("hPintPheightX",";Pint;Pfheight_x",2000,0.0,2000,1000,0.0,100);
  TH2F *hPintPheight = new TH2F("hPintPheight",";Pint;Pfheight",2000,0.0,2000,1000,0.0,200);
  TH2F *hPintEndValPheight = new TH2F("hPintEndValPheight",";Pint;IntEndVal-Pfheight_x",2000,0.0,2000,1000,0.0,100);
  TH2F *hPintT0 = new TH2F("hPintT0",";Pint;T0",2000,0.0,2000,1200,0.0,60);
  TH2F *hPintA = new TH2F("hPintA",";Pint;A",2000,0.0,2000,2000,0.0,2000);
  TH2F *hPintTauF = new TH2F("hPintTauF",";Pint;tau_f",2000,0.0,2000,8000,0.0,8000);
  TH2F *hPintTauF2 = new TH2F("hPintTauF2",";Pint;tau_f",2000,0.0,2000,1000,0.0,100);
  TH2F *hPintTauF3 = new TH2F("hPintTauF3",";Pint;tau_f",2000,0.0,2000,1200,0.0,30);
  TH2F *hPintTauR = new TH2F("hPintTauR",";Pint;tau_r",2000,0.0,2000,300,0.0,3);
  TH2F *hPintTauR2 = new TH2F("hPintTauR2",";Pint;tau_r",2000,0.0,2000,300,0.0,20);
  TH2F *hPintTauS = new TH2F("hPintTauS",";Pint;tau_s",2000,0.0,2000,1000,0.0,40);
  TH2F *hPintRatio = new TH2F("hPintRatio",";Pint;ratio",2000,0.0,2000,100,0.0,10);

  TH2F *hChi2NDFRMS = new TH2F("hChi2NDFRMS",";Chi2NDF;RMS",2000,0.0,10.0,1000,0.0,1.0);
  TH2F *hChi2NDFChi2Prob = new TH2F("hChi2NDFChi2Prob",";Chi2NDF;Chi2Prob",2000,0.0,10.0,1000,0.0,1.0);
  TH2F *hChi2NDFPheightX = new TH2F("hChi2NDFPheightX",";Chi2NDF;Pfheight_x",2000,0.0,10.0,1000,0.0,100);
  TH2F *hChi2NDFPheight = new TH2F("hChi2NDFPheight",";Chi2NDF;Pfheight",2000,0.0,10.0,1000,0.0,200);
  TH2F *hChi2NDFEndValPheight = new TH2F("hChi2NDFEndValPheight",";Chi2NDF;IntEndVal-Pfheight_x",2000,0.0,10.0,1000,0.0,100);
  TH2F *hChi2NDFT0 = new TH2F("hChi2NDFT0",";Chi2NDF;T0",2000,0.0,10.0,1200,0.0,60);
  TH2F *hChi2NDFA = new TH2F("hChi2NDFA",";Chi2NDF;A",2000,0.0,10.0,2000,0.0,1000.0);
  TH2F *hChi2NDFTauF = new TH2F("hChi2NDFTauF",";Chi2NDF;tau_f",2000,0.0,10.0,8000,0.0,8000);
  TH2F *hChi2NDFTauF2 = new TH2F("hChi2NDFTauF2",";Chi2NDF;tau_f",2000,0.0,10.0,1000,0.0,100);
  TH2F *hChi2NDFTauR = new TH2F("hChi2NDFTauR",";Chi2NDF;tau_r",2000,0.0,10.0,300,0.0,3);
  TH2F *hChi2NDFTauS = new TH2F("hChi2NDFTauS",";Chi2NDF;tau_s",2000,0.0,10.0,8000,0.0,1000);
  TH2F *hChi2NDFRatio = new TH2F("hChi2NDFRatio",";Chi2NDF;ratio",2000,0.0,10.0,100,0.0,10);


  TTree* chain = (TTree *) fl->Get("tr");
  //TTree* chain = (TTree *) fl->Get("data");
  chain->SetBranchAddress("eventID",&eventID);  
  chain->SetBranchAddress("pedestal",&pedestal); // pedestal
  chain->SetBranchAddress("Pheight",&Pheight); // Pfheight
  chain->SetBranchAddress("Pint",&Pint); // Pint
  chain->SetBranchAddress("RMS",&RMS); // RMS
  chain->SetBranchAddress("tau_r",&tau_r); 
  chain->SetBranchAddress("tau_s",&tau_s);
  chain->SetBranchAddress("tau_f",&tau_f);
  chain->SetBranchAddress("A",&A);
  chain->SetBranchAddress("ratio",&ratio); // ratio
  chain->SetBranchAddress("t0",&t0);
  chain->SetBranchAddress("NDF",&NDF);
  chain->SetBranchAddress("chisq",&chisq);
  chain->SetBranchAddress("chisqprob",&chisqprob);
  chain->SetBranchAddress("Pfheight",&Pfheight); //
  chain->SetBranchAddress("Pfheight_x",&Pfheight_x); //
  chain->SetBranchAddress("IntEndVal",&IntEndVal); // IntEndVal

  TTree *writeTree = new TTree("data","");

  writeTree->Branch("eventID",&eventID);  
  writeTree->Branch("pedestal",&pedestal); // pedestal
  writeTree->Branch("Pheight",&Pheight); // Pfheight
  writeTree->Branch("Pint",&Pint); // Pint
  writeTree->Branch("RMS",&RMS); // RMS
  writeTree->Branch("tau_r",&tau_r); 
  writeTree->Branch("tau_s",&tau_s);
  writeTree->Branch("tau_f",&tau_f);
  writeTree->Branch("A",&A);
  writeTree->Branch("ratio",&ratio); // ratio
  writeTree->Branch("t0",&t0);
  writeTree->Branch("NDF",&NDF);
  writeTree->Branch("chisq",&chisq);
  writeTree->Branch("chisqprob",&chisqprob);
  writeTree->Branch("Pfheight",&Pfheight); //
  writeTree->Branch("Pfheight_x",&Pfheight_x); //
  writeTree->Branch("IntEndVal",&IntEndVal); // IntEndVal



  const int NEntries = chain->GetEntries();
  for(int i=0;i<NEntries;i++)
  {
    chain->GetEntry(i);
    writeTree->Fill();

    hPintChi2->Fill(Pint,chisq);
    hPintChi2NDF->Fill(Pint,chisq/NDF);
    hPintRMS->Fill(Pint,RMS);
    hPintChi2Prob->Fill(Pint,chisqprob);
    hPintPheightX->Fill(Pint,Pfheight_x);
    hPintPheight->Fill(Pint,Pfheight);
    hPintEndValPheight->Fill(Pint,IntEndVal-Pfheight_x);
    hPintT0->Fill(Pint,t0);
    hPintA->Fill(Pint,A);
    hPintTauF->Fill(Pint,tau_f);
    hPintTauF2->Fill(Pint,tau_f);
    hPintTauF3->Fill(Pint,tau_f);
    hPintTauR->Fill(Pint,tau_r);
    hPintTauR2->Fill(Pint,tau_r);
    hPintTauS->Fill(Pint,tau_s);
    hPintRatio->Fill(Pint,ratio);

    hChi2NDFRMS->Fill(chisq/NDF,RMS);
    hChi2NDFChi2Prob->Fill(chisq/NDF,chisqprob);
    hChi2NDFPheightX->Fill(chisq/NDF,Pfheight_x);
    hChi2NDFPheight->Fill(chisq/NDF,Pfheight);
    hChi2NDFEndValPheight->Fill(chisq/NDF,IntEndVal-Pfheight_x);
    hChi2NDFT0->Fill(chisq/NDF,t0);
    hChi2NDFA->Fill(chisq/NDF,A);
    hChi2NDFTauF->Fill(chisq/NDF,tau_f);
    hChi2NDFTauF2->Fill(chisq/NDF,tau_f);
    hChi2NDFTauR->Fill(chisq/NDF,tau_r);
    hChi2NDFTauS->Fill(chisq/NDF,tau_s);
    hChi2NDFRatio->Fill(chisq/NDF,ratio);


  }

  writeFile->cd();
  hPintChi2->Write();
  hPintChi2NDF->Write();
  hPintRMS->Write();
  hPintChi2Prob->Write();
  hPintPheightX->Write();
  hPintPheight->Write();
  hPintEndValPheight->Write();
  hPintT0->Write();
  hPintA->Write();
  hPintTauF->Write();
  hPintTauF2->Write();
  hPintTauF3->Write();
  hPintTauR->Write();
  hPintTauR2->Write();
  hPintTauS->Write();
  hPintRatio->Write();

  hChi2NDFRMS->Write();
  hChi2NDFChi2Prob->Write();
  hChi2NDFPheightX->Write();
  hChi2NDFPheight->Write();
  hChi2NDFEndValPheight->Write();
  hChi2NDFT0->Write();
  hChi2NDFA->Write();
  hChi2NDFTauF->Write();
  hChi2NDFTauF2->Write();
  hChi2NDFTauR->Write();
  hChi2NDFTauS->Write();
  hChi2NDFRatio->Write();

  writeTree->Write(); 
} 

