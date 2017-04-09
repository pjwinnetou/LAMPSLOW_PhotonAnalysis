#include <iostream>
#include "TH1.h"
#include "TROOT.h"
#include "TSystem.h"
#include "TF1.h"
#include "TFile.h"
#include "TTree.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TGraphErrors.h"
#include <fstream>
#include "commonUtility.h"
#include "SONGKYO.h"

using namespace std;

void makeHistRoot()
{

  gStyle->SetOptStat(0);

  const int nResol = 5;  
  double Resol[nResol] = {3,5,7,10,12};
  double edep1[nResol] = {0.};
  TFile *rf[nResol];
  TTree *rt[nResol];

  double xbin_s = 0;
  double xbin_e = 860;
  int nbin = 100;
  double neventbin = (xbin_e-xbin_s)/nbin;

  for(int i=0; i<nResol; i++)
  {
    rf[i] = new TFile(Form("Gamma_Cs137_1M_CsI60mm_res%.f.root",Resol[i]),"read");
    rt[i] = (TTree*) rf[i] -> Get("Recon");
    rt[i] -> SetBranchAddress("edep1",&edep1[i]);
  }

  TH1D *h1[nResol];
  for(int i=0;i<nResol;i++)
  {
    h1[i] = new TH1D(Form("hCs137Resol%.f",Resol[i]),Form(";E_{dep} (KeV); Events / (%.3f KeV/c^{2})",neventbin),nbin, xbin_s, xbin_e);
    for(int j=0;j<rt[i]->GetEntries();j++)
    {
      rt[i]->GetEntry(j);
      h1[i]->Fill(edep1[i]*1000);
    }
  }
  
  TFile *wf = new TFile("Cs137_Hist_Resolution.root","recreate");
  wf->cd();
  for(int i=0;i<nResol;i++)
  {
    h1[i]->Write();
  }

}
