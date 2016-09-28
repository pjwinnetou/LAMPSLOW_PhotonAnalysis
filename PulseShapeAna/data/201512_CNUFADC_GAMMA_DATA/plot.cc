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

void TriggPosSelect()
{
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
  
  Int_t TDC[18];
  Int_t ADC[18];

  Double_t mean[4]={0};
  Double_t sigma[4]={0};

  TFile *openFile = new TFile(".root","READ");
  TTree *dataTree = (TTree*) openFile -> Get("data");
  dataTree->SetBranchAddress("",);
  dataTree->SetBranchAddress("",);

  TTree *writeTree = new TTree("data","");
  writeTree->Branch("",&,"/");

  TFile *writeFile = new TFile(".root","recreate");

  TCanvas *cvs = new TCanvas("cvs","",700,700);

  TH1D *h = new TH1D("h","Title;xtitle;ytitle",100,-650,250);
  TF1 *f1 = new TF1("f1","gaus",-103,-20);
 
  const int NEntries = dataTree->GetEntries();
  for(int i=0;i<NEntries;i++)
  {
    dataTree->GetEntry(i);
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
 ->Write(); 

} 

