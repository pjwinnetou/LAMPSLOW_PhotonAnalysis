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

void plot()
{
  double Resol[4] = {8,5,7,10};
  gStyle->SetOptStat(0);
  TFile *rf = new TFile("Cobalt_Hist_Resolution.root","read");
    cout << "sadasda" << endl;

  TH1D *h1[4];
  h1[0] = (TH1D*) rf->Get("hCobaltResol8");

  for(int i=0;i<1;i++)
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
  }


  TCanvas *c1[4];
 
  double ypos = 0.77;
  double ypos_diff = 0.059;
  double xpos = 0.25;
  double text_size = 20;
  TString sperc = "%";
  TLegend *leg[4]; 
  for(int i=0;i<1;i++)
  {
    c1[i] = new TCanvas(Form("c%d",i),"",600,600);
    leg[i] = new TLegend(xpos,ypos+0.04,xpos+0.05,ypos+0.09);
    SetLegendStyle(leg[i]);
    leg[i]->SetTextSize(0.038);

    c1[i]->cd();
    gPad->SetLeftMargin(0.205);
    gPad->SetBottomMargin(0.17);
    gPad->SetRightMargin(0.06);
    gPad->SetTopMargin(0.06);
    h1[i]->Draw("P");
    leg[i]->AddEntry(h1[i]," Geant4 MC","lp");
    leg[i]->Draw("same");
    drawText("Source : ^{60}Co",xpos,ypos,1,text_size);
    drawText("E_{#gamma} = 1170 & 1330 KeV",xpos,ypos-ypos_diff,1,text_size);
    drawText(Form("FWHM = %.f%s",Resol[i],sperc.Data()),xpos,ypos-ypos_diff*2,1,text_size);
    c1[i]->SaveAs(Form("Spectrum_Cobalt_Res%.f.pdf",Resol[i])); 
  }

}
