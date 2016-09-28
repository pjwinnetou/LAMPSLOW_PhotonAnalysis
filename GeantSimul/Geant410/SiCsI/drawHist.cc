// Root header
#include <TCanvas.h>
#include <TStyle.h>
#include <TFile.h>
#include <TMath.h>
#include <TTree.h>
#include <TCut.h>
#include <TPad.h>
#include <TH1D.h>
#include <TF1.h>

// c/c++ header
#include <string>

void energyDeg(TTree *labTree, TFile *histData); //Fixed

const int nEvent = 2010;

int main()
{
  std::cout << std::endl << std::endl;
  std::cout << "Drawing histograms..." << std::endl;

  gStyle -> SetOptStat(0);
  gStyle -> SetTitleYOffset(1.5);
  gStyle -> SetTitleXOffset(1.1);
  gStyle -> SetTitleSize(0.05,"xy");
  gStyle -> SetPadLeftMargin(0.16);
  gStyle -> SetPadRightMargin(0.05);
  gStyle -> SetPadTopMargin(0.13);
  gStyle -> SetPadBottomMargin(0.12);

  TFile *amdData = new TFile("dE_E_Hist.root","read");
  TTree *labTree = (TTree*) amdData -> Get("Energy");

  TFile *histData = new TFile("hist.root","recreate");

  energyDeg(labTree, histData);

  return 0;
}
void energyDeg(TTree *labTree, TFile *histData)
{

  int entries = labTree -> GetEntries();
  int    nbinsx = 100;
  double xlow   = 0;
  double xup    = 1000;
  double weight = (nbinsx/(xup - xlow))/entries;

  TCanvas *cvs = new TCanvas("theta_deg","",800,800);

  TH1D *hist = new TH1D("hist_theta_deg","E_{Kin};E_{Kin} (MeV);(1/N_{event})(dN/dE_{Kin})",nbinsx, xlow, xup);

        hist -> GetXaxis() -> CenterTitle();
        hist -> GetYaxis() -> CenterTitle();

  labTree -> SetWeight(weight);
  cvs -> cd();
  labTree -> Draw("etot>>hist_theta_deg");
  histData -> cd();
    cvs -> Write();


  delete cvs;

  delete hist;
}
