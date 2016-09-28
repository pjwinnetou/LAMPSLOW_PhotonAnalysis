#include <iostream>
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
#include <TGraphErrors.h>
using namespace std;

void FADC_TriggerRate()
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
  gStyle->SetEndErrorSize(0);
  
  TFile *f = new TFile("TriggerRate.root","recreate");
  TGraphErrors *g1 = new TGraphErrors();
  
  const int nP = 5;
  const int nMeasured = 3;
  double nMeasuredEntries = 100000;
  Double_t fg_rate[nP] = {0.};
  fg_rate[0] = 0.5;
  fg_rate[1] = 1.;
  fg_rate[2] = 5.;
  fg_rate[3] = 10.;
  fg_rate[4] = 15.;

  Double_t fadc_rawrate[nP][nMeasured] = {371,371,371, 369,367,369, 369,370,371, 371,370,375, 361,371,371};

  Double_t fadc_rawrate_avg[nP] = {0.};
  Double_t fadc_rawrate_avg_err[nP] = {0.};
  Double_t fadc_rawrate_avg_errR[nP] = {0.};

  for(int i=0;i<nP;i++)
  {
    for(int j=0; j<nMeasured; j++)
    {
      fadc_rawrate_avg[i] += fadc_rawrate[i][j];
    }

    fadc_rawrate_avg[i] = fadc_rawrate_avg[i]/(double)nMeasured; //until here it is the average time not Hz!!
  }
  
  Double_t fadc_rawrate_max[nP]; 
  Double_t fadc_rawrate_min[nP]; 
  Double_t fadc_all_max, fadc_all_min;

  for(int i=0; i<nP; i++)
  {
    fadc_rawrate_max[i] = fadc_rawrate_avg[i];
    fadc_rawrate_min[i] = fadc_rawrate_avg[i];
    for(int j=0; j<nMeasured; j++)
    {
      if(fadc_rawrate_max[i] < fadc_rawrate[i][j]) fadc_rawrate_max[i] = fadc_rawrate[i][j];
      if(fadc_rawrate_min[i] > fadc_rawrate[i][j]) fadc_rawrate_min[i] = fadc_rawrate[i][j];
    }

    fadc_rawrate_max[i] = (double)nMeasuredEntries/fadc_rawrate_max[i]; 
    fadc_rawrate_min[i] = (double)nMeasuredEntries/fadc_rawrate_min[i];  
    fadc_rawrate_avg[i] = (double)nMeasuredEntries/fadc_rawrate_avg[i]; //get the average Hz

    if(i==0) fadc_all_max = fadc_rawrate_avg[i]; fadc_all_min = fadc_rawrate_avg[i];

    fadc_rawrate_avg_errR[i] = TMath::Abs(fadc_rawrate_max[i] - fadc_rawrate_min[i])/2.;
    fadc_rawrate_avg_err[i] = fadc_rawrate_avg_errR[i]/TMath::Sqrt(nMeasured);

    cout << " error : " << fadc_rawrate_avg_err[i] << endl;
    
    g1->SetPoint(i, fg_rate[i], fadc_rawrate_avg[i]);
    g1->SetPointError(i,0,fadc_rawrate_avg_err[i]);
    
    if(fadc_all_max < fadc_rawrate_avg[i]) fadc_all_max = fadc_rawrate_avg[i];
    if(fadc_all_min > fadc_rawrate_avg[i]) fadc_all_min = fadc_rawrate_avg[i];
  }

  g1->SetTitle("FADC 400MHz rate");
  g1->SetMarkerStyle(25);
  g1->SetMarkerColor(kRed-7);
  g1->GetHistogram()->GetXaxis()->SetTitle("Input Rate (Function Generator) (kHz) ");
  g1->GetHistogram()->GetXaxis()->CenterTitle();
  g1->GetHistogram()->GetXaxis()->SetLimits(0,20);
  g1->GetHistogram()->GetXaxis()->SetRangeUser(0,20);
  g1->GetHistogram()->GetYaxis()->SetTitle("FADC Readout Rate (kHz) ");
  g1->GetHistogram()->GetYaxis()->CenterTitle();
  g1->GetHistogram()->GetYaxis()->SetLimits(0,400);
  g1->GetHistogram()->GetYaxis()->SetRangeUser(fadc_all_min*0.9, fadc_all_max*1.1);

  g1->Draw("AP");

  TF1 *fFit = new TF1("fFit","[0]",0,20);
  g1->Fit(fFit);

  f->cd();
  g1->Write();
  f->Close();
}  



