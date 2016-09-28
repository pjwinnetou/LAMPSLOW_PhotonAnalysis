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

const int NumOfEvent = 1000;
void EnergyDeposit_SiCsI(TTree *tree, TFile *SiCsIHistData);

int main()
{

  cout << "Hist Draw" << endl;

  gStyle -> SetOptStat(0);
  gStyle -> SetTitleYOffset(1.35);
  gStyle -> SetTitleXOffset(1.3);
  gStyle -> SetTitleSize(0.04,"xy");
  gStyle -> SetPadLeftMargin(0.16);
  gStyle -> SetPadRightMargin(0.05);
  gStyle -> SetPadTopMargin(0.12);
  gStyle -> SetPadBottomMargin(0.15);

  TFile *rawfile = new TFile("./test_center_SiCsI_ring5.root","read");
  TTree *tree = (TTree*) rawfile -> Get("dE_E");

  TFile *SiCsIHistData = new TFile("./Center_SiCsI_ring2_proton.root","recreate");

  EnergyDeposit_SiCsI(tree,SiCsIHistData);

  return 0;
}

void EnergyDeposit_SiCsI(TTree *tree, TFile *SiCsIHistData)
{
  int nbin = 100;
  double xlow = 0;
  double xup = 10.5;
  double weight = (nbin/(xup-xlow))/NumOfEvent;

  TCanvas *cvs = new TCanvas("edep_Si","",700,700);
  TH1D *hist1 = new TH1D("hist_edep_Si","E_{dep}; E_{dep} (MeV);(1/N_{event})(dN/dE_{dep})",nbin,xlow,xup);
  TH1D *hist2 = new TH1D("hist_edep_CsI","E_{dep}; E_{dep};(1/N_{event})(dN/dE_{dep})",nbin,xlow,xup);
  TH1D *hist3 = new TH1D("hist_edep_tot","E_{dep}; E_{dep};(1/N_{event})(dN/dE_{dep})",nbin,xlow,xup);

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
  tree -> SetWeight(weight);
  tree -> Draw("edep1>>hist_edep_Si");
  tree -> Draw("edep2>>hist_edep_CsI");
  tree -> Draw("etot>>hist_edep_tot");


  hist1->Write();
  hist2->Write();
  hist3->Write();

  hist1->Draw();
  hist2->Draw("same");
  hist3->Draw("same");

  hist1 -> SetLineColor(2);
  hist2 -> SetLineColor(4);
  hist3 -> SetLineColor(3);

  hist1 -> SetAxisRange(0,10,"Y");

  TLegend *legend = new TLegend(0.6,0.7,0.8,0.8);
  legend->SetTextFont(40);
  legend->SetTextSize(0.03);
  legend->AddEntry(hist1, "Si : 0.83122", "l");
  legend->AddEntry(hist2, "CsI : 9.1688", "l");
  legend->AddEntry(hist3, "Total : 10", "l");
  legend->Draw();


  cout << endl;
  cout << "normal energy deposit Silicon : " << hist1 -> Integral("width") << endl;
  cout << "normal energy deposit CsI : " << hist2 -> Integral("width") << endl;
  cout << "normal energy deposit Total : " << hist3 -> Integral("width") << endl;

  cout << endl;
  cout << "Mean energy deposit Silicon : " << hist1 -> GetMean() << endl;
  cout << "Mean energy deposit CsI : " << hist2 -> GetMean() << endl;
  cout << "Mean energy deposit Total : " << hist3 -> GetMean() << endl;
  
  SiCsIHistData->cd();

  cvs -> Write();
  cvs -> SaveAs("./../../analysis/CenterSiCsI_proton_ring2.pdf");

  delete cvs;
  delete hist1;
  delete hist2;
  delete hist3;
}
