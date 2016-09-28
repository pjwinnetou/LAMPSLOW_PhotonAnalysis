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

void EnergyDeposit_Neutron(TTree *tree, TTree *treepure, TFile *NeutronHistData);

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

  TFile *rawpurefile = new TFile("./../../data/Neutron_test_pure.root","read");
  TTree *treepure = (TTree*) rawpurefile -> Get("Recon");

  TFile *NeutronHistData = new TFile("./Hist_Test_Neutron_5MeV_5000.root","recreate");

  //
  EnergyDeposit_Neutron(tree, treepure, NeutronHistData);

  return 0;
}

void EnergyDeposit_Neutron(TTree *tree, TTree *treepure, TFile *NeutronHistData)
{
  const int NumOfEvent = tree->GetEntries();
  const int NumOfEventPure = treepure->GetEntries();
  int nbin_scint = 50;
  double xlow_scint = 0;
  double xup_scint = 5;
  double weight = (nbin_scint/(xup_scint-xlow_scint))/NumOfEvent;

  int nbin_csi = 80;
  double xlow_csi = 0;
  double xup_csi = 2;

  TCanvas *cvs = new TCanvas("edep","",700,700);
  TH1D *hist1 = new TH1D("hist_edep_Scint","E_{dep}; E_{dep} (MeV);Counts",nbin_scint,xlow_scint,xup_scint);
  TH1D *hist2 = new TH1D("hist_edep_CsI","E_{dep}; E_{dep};Counts",nbin_csi,xlow_csi,xup_csi);
  TH1D *hist3 = new TH1D("hist_edep_Scint_pure","E_{dep}; E_{dep} (MeV);Counts",nbin_scint,xlow_scint,xup_scint);

  hist1 -> SetMinimum(0);
  hist1 -> GetXaxis() -> CenterTitle(); 
  hist1 -> GetYaxis() -> CenterTitle(); 

  hist2 -> SetMinimum(0);
  hist2 -> GetXaxis() -> CenterTitle(); 
  hist2 -> GetYaxis() -> CenterTitle(); 
  
  hist3 -> SetMinimum(0);
  hist3 -> GetXaxis() -> CenterTitle(); 
  hist3 -> GetYaxis() -> CenterTitle(); 
  
  
  cvs -> cd();
  tree -> Draw("edep3>>hist_edep_Scint");
  treepure -> Draw("edep3>>hist_edep_Scint_pure");

  hist1->Write();
  hist2->Write();
  hist3->Write();
  
  double hist1Max = hist1->GetMaximum();
  double hist3Max = hist3->GetMaximum();
  double ratio = hist1Max/hist3Max*100.;

  cout << "max : " << hist1Max << endl;
  cout << "max : " << hist3Max << endl;
  cout << "ratio : " << ratio << endl;

  hist3->Draw();
  hist1->Draw("same");
  hist1 -> SetLineColor(2);
  hist3 -> SetLineColor(1);

  hist1 -> SetLineStyle(2);

  hist1 -> SetLineWidth(2.85);
  hist3 -> SetLineWidth(2);

//  hist1 -> SetAxisRange(0,10,"Y");

  TLegend *legend = new TLegend(0.7,0.7,0.9,0.8);
  legend->SetTextFont(40);
  legend->SetTextSize(0.02);
  legend->SetFillColor(0);
  legend->AddEntry(hist3, "Without SiCsI", "l");
  legend->AddEntry(hist1, "With SiCsI", "l");
  legend->Draw();


  cout << endl;
  cout << "normal energy deposit Scint : " << hist1 -> Integral("width") << endl;
  cout << "normal energy deposit CsI : " << hist3 -> Integral("width") << endl;
/*
  cout << endl;
  cout << "Mean energy deposit Silicon : " << hist1 -> GetMean() << endl;
  cout << "Mean energy deposit CsI : " << hist2 -> GetMean() << endl;
  */
  NeutronHistData->cd();

  cvs -> Write();
  cvs -> SaveAs("./../../analysis/Hist_test_neutron_5MeV_5000.pdf");

  delete cvs;
  delete hist1;
  delete hist2;
  delete hist3;
}
