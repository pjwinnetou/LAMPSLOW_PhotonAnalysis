#include <iostream>
#include <sstream>
#include "TF1.h"
#include "TH1D.h"
#include "TFile.h"
#include "TMath.h"
#include "TTree.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TCanvas.h"
#include "TStyle.h"

using namespace std;

void fitstudy()
{
  
  gStyle->SetPalette(1);
  gStyle->SetOptFit(kTRUE);
  gStyle->SetOptFit(11111111);
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
  
  float t0 = 14;
  float A = 5000;
  
  double tau_r1 = 0.7665;
  double tau_s1 = 65.87;
  double tau_f1 = 13.12;
  double R1 = 0.012;
  
  double tau_r2 = 0.7665;
  double tau_s2 = 65.87;
  double tau_f2 = 13.12;
  double R2 = 0.52;

  TF1 *FitFunction1 = new TF1("fFit1","[0]*(1/[2]*TMath::Exp(-(x-[1])/[2])+[4]/[3]*TMath::Exp(-(x-[1])/[3])-(1/[2]+[4]/[3])*TMath::Exp(-(x-[1])/[5]))");
  FitFunction1 -> SetRange(t0-1,80);
  FitFunction1 -> SetParName(0,"A");
  FitFunction1 -> SetParName(1,"t_{0}");
  FitFunction1 -> SetParName(2,"#tau_{f}");
  FitFunction1 -> SetParName(3,"#tau_{s}");
  FitFunction1 -> SetParName(4,"R");
  FitFunction1 -> SetParName(5,"#tau_{r}");
  FitFunction1 -> SetParameters(A,t0,tau_f1,tau_s1,R1,tau_r1);

  TF1 *FitFunction2 = new TF1("fFit2","[0]*(1/[2]*TMath::Exp(-(x-[1])/[2])+[4]/[3]*TMath::Exp(-(x-[1])/[3])-(1/[2]+[4]/[3])*TMath::Exp(-(x-[1])/[5]))");
  FitFunction2 -> SetRange(t0-1,80);
  FitFunction2 -> SetParName(0,"A");
  FitFunction2 -> SetParName(1,"t_{0}");
  FitFunction2 -> SetParName(2,"#tau_{f}");
  FitFunction2 -> SetParName(3,"#tau_{s}");
  FitFunction2 -> SetParName(4,"R");
  FitFunction2 -> SetParName(5,"#tau_{r}");
  FitFunction2 -> SetParameters(A,t0,tau_f2,tau_s2,R2,tau_r2);

  TCanvas *c1 = new TCanvas("c1","",600,600);
  c1->cd();
  c1->DrawFrame(0,-5,200,1000,"Fitting function;80 (ns);ADC");
  FitFunction1 -> Draw("same");
  FitFunction1 -> SetLineColor(1);
  FitFunction2 -> Draw("same");
  FitFunction2 -> SetLineColor(2);

  TLegend *l1 = new TLegend(0.7,0.7,0.9,0.9);
  l1 -> SetTextFont(40);
  l1 -> SetFillColor(0);
  l1 -> SetTextSize(0.027);
  l1 -> AddEntry(FitFunction1,Form("R :%f",R1),"l");
  l1 -> AddEntry(FitFunction2,Form("R :%f",R2),"l");
  l1 -> Draw("same");
  
  c1->SaveAs("fittingstudy.png");
}
