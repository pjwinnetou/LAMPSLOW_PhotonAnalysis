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

void plot_weight()
{
  gStyle->SetOptStat(0);

  TFile *f1[2];
  f1[0] = new TFile("Gamma_Cobalt1170_1M_CsI60mm_res8.root","read");
  f1[1] = new TFile("Gamma_Cobalt1330_1M_CsI60mm_res8.root","read");

  double edep1[2];
  TTree *rt[2];
  for(int i=0;i<2;i++){
    rt[i] = (TTree*) f1[i] -> Get("Recon");
    rt[i] -> SetBranchAddress("edep1",&edep1[i]);
  }
  double xbin_s = 0;
  double xbin_e = 1600;
  int nbin = 130;
  double neventbin = (xbin_e-xbin_s)/nbin;

  TH1D *h1[2];
  h1[0] = new TH1D("h1",Form(";E_{dep} (KeV); Events / (%.3f KeV/c^{2})",neventbin),nbin, xbin_s, xbin_e);
  h1[1] = new TH1D("h2",Form(";E_{dep} (KeV); Events / (%.3f KeV/c^{2})",neventbin),nbin, xbin_s, xbin_e);

  for(int i=0;i<2;i++)
  { 
    h1[i]->GetXaxis()->CenterTitle();
    h1[i]->GetYaxis()->CenterTitle();
    h1[i]->GetXaxis()->SetTitleOffset(1.3);
    h1[i]->GetYaxis()->SetTitleOffset(1.9);
    h1[i]->GetXaxis()->SetTitleSize(0.05);
    h1[i]->GetYaxis()->SetTitleSize(0.05);
    h1[i]->GetXaxis()->SetLabelSize(0.04);
    h1[i]->GetYaxis()->SetLabelSize(0.04);
    h1[i]->SetMarkerStyle(20);
    h1[i]->SetMarkerColor(kBlue+3);
    h1[i]->SetMarkerSize(1.0);
    for(int j=0;j<rt[i]->GetEntries();j++)
    {
      rt[i]->GetEntry(j);
      h1[i]->Fill(edep1[i]*1000);
    }
  }
  

  TCanvas *c1;
 
  double ypos = 0.77;
  double ypos_diff = 0.059;
  double xpos = 0.25;
  double text_size = 20;
  TString sperc = "%";
  TLegend *leg; 
    c1 = new TCanvas("c1","",600,600);
    leg = new TLegend(xpos,ypos+0.04,xpos+0.05,ypos+0.09);
    SetLegendStyle(leg);
    leg->SetTextSize(0.038);

    c1->cd();
    gPad->SetLeftMargin(0.205);
    gPad->SetBottomMargin(0.17);
    gPad->SetRightMargin(0.06);
    gPad->SetTopMargin(0.06);
    h1[0]->Scale(0.7);
    h1[0]->Draw("P");
    h1[1]->Draw("P same");
    leg->AddEntry(h1[0]," Geant4 MC","lp");
    leg->Draw("same");
    drawText("Source : ^{60}Co",xpos,ypos,1,text_size);
    drawText("E_{#gamma} = 1170 & 1330 KeV",xpos,ypos-ypos_diff,1,text_size);
    drawText(Form("FWHM = 8%s",sperc.Data()),xpos,ypos-ypos_diff*2,1,text_size);
    c1->SaveAs("Spectrum_Cobalt_Res8.pdf"); 
  

}
