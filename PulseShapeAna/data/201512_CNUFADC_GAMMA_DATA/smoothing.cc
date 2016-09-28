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
#include <TSpectrum.h>
#include <fstream>
#include <iostream>
using namespace std;

void smoothing()
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
  
  Int_t i;
  Int_t nbins = 4096;
  Double_t xmin = 0;
  Double_t xmax = 10240;
  Double_t * source = new Double_t[nbins];
  TH1F *h1 = new TH1F("h1","Smoothed spectrum for m=3",nbins,xmin,xmax);
  TH1F *h2 = new TH1F("h2","Raw Signal",nbins,xmin,xmax);
  TFile *f = new TFile("Co60_2310_385_1.root");
  h2 = (TH1F*) f -> Get("hoscd1;1");

  for(i=0;i<nbins;i++)
  {
    h2->SetBinContent(i+1,869-h2->GetBinContent(i+1));
  }

  for(i=0; i<nbins; i++)
  {
    source[i] = h2->GetBinContent(i+1);
  }
  TCanvas *Smooth1 = new TCanvas("Smooth1","Smooth1",0,0,700,700);
  
  TSpectrum *s = new TSpectrum();
  s->SmoothMarkov(source,nbins,4);

  for(i=0;i<nbins;i++) h1->SetBinContent(i+1,source[i]);
  h1->SetAxisRange(0,10240);
  Smooth1->cd();
  h1->Draw("L");

  TCanvas *c1 = new TCanvas("c1","",0,0,700,700);
  c1->cd();
  h2->Draw();

} 

