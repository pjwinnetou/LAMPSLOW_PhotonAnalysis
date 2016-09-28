#include <TCanvas.h>
#include <TStyle.h>
#include <TFile.h>
#include <TF1.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TMath.h>
#include <TPad.h>
#include <TTree.h>
#include <TLegend.h>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

void EnergyDeposit_Neutron(TTree *tree, TFile *NeutronHistData);

int main()
{

  cout << "Hist Draw" << endl;

  gStyle -> SetOptStat(0);
  gStyle -> SetTitleYOffset(1.75);
  gStyle -> SetTitleXOffset(1.35);
  gStyle -> SetTitleSize(0.04,"xy");
  gStyle -> SetPadLeftMargin(0.16);
  gStyle -> SetPadRightMargin(0.05);
  gStyle -> SetPadTopMargin(0.12);
  gStyle -> SetPadBottomMargin(0.15);

  TFile *rawfile = new TFile("./../../data/Neutron_test.root","read");
  TTree *tree = (TTree*) rawfile -> Get("Recon");

  TFile *NeutronHistData = new TFile("./Hist_Test_Neutron_5MeV_5000.root","recreate");

  //
  EnergyDeposit_Neutron(tree, NeutronHistData);

  return 0;
}

void EnergyDeposit_Neutron(TTree *tree, TFile *NeutronHistData)
{
  const int NumOfEvent = tree->GetEntries();
  int nbin_scint = 180;
  double xlow_scint = 0;
  double xup_scint = 18;
  double weight = (nbin_scint/(xup_scint-xlow_scint))/NumOfEvent;

  int nbin_csi = 80;
  double xlow_csi = 0;
  double xup_csi = 2;

  TCanvas *cvs = new TCanvas("edep","",700,700);
  TH1D *hist1 = new TH1D("hist_edep_Scint","E_{dep}; E_{dep} (MeV);Counts",nbin_scint,xlow_scint,xup_scint);
  TH1D *hist2 = new TH1D("hist_edep_CsI","E_{dep}; E_{dep};Counts",nbin_csi,xlow_csi,xup_csi);

  hist1 -> SetMinimum(0);
  hist1 -> GetXaxis() -> CenterTitle(); 
  hist1 -> GetYaxis() -> CenterTitle(); 

  hist2 -> SetMinimum(0);
  hist2 -> GetXaxis() -> CenterTitle(); 
  hist2 -> GetYaxis() -> CenterTitle(); 
  
  
  cvs -> cd();
  tree -> Draw("edep2>>hist_edep_CsI");

  hist2->Write();
  
  hist2->Draw();
  hist2 -> SetLineColor(1);


  hist2 -> SetLineWidth(2);

//  hist1 -> SetAxisRange(0,10,"Y");


  cout << endl;
  cout << "normal energy deposit Scint : " << hist2 -> Integral("width") << endl;
/*
  cout << endl;
  cout << "Mean energy deposit Silicon : " << hist1 -> GetMean() << endl;
  cout << "Mean energy deposit CsI : " << hist2 -> GetMean() << endl;
  */
  NeutronHistData->cd();

  cvs -> Write();
  cvs -> SaveAs("./../../analysis/Hist_test_neutro.pdf");

  delete cvs;
  delete hist1;
  delete hist2;
}
