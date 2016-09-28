#include <TH1D.h>
#include <TCanvas.h>
#include <fstream>
#include <iostream>
#include <TFile.h>
#include <TTree.h>
#include <TStyle.h>
#include <TMath.h>
#include <sstream>
#include <string>
#include <TLegend.h>

using namespace std;

int main()
{
	cout << "**** Gamma Efficiency Draw in CsI Detector *****" << endl;
  cout << "            CsI Thickness 5cm 4cm 3cm           " << endl;
  cout << "          dE vs dz & energy distribution        " << endl; 
  cout << endl;

  gStyle -> SetOptStat(0);
  gStyle -> SetTitleYOffset(1.73);
  gStyle -> SetTitleXOffset(1.3);
  gStyle -> SetTitleSize(0.04,"xy");
  gStyle -> SetPadLeftMargin(0.2);
  gStyle -> SetPadRightMargin(0.05);
  gStyle -> SetPadTopMargin(0.20);
  gStyle -> SetPadBottomMargin(0.15);

  double edep1, Depth;
	double nbins1_5cm = 51;
	double low1_5cm = 0;
	double up1_5cm = 51;

	double nbins1_4cm = 41;
	double low1_4cm = 0;
	double up1_4cm = 41;

	double nbins1_3cm = 31;
	double low1_3cm = 0;
	double up1_3cm = 31;

	double nbins2 = 110;
	double low2 = 0;
	double up2 = 11;
	

  //read file 
	TFile *readFile5cm = new TFile("./../../data/Gamma_test_CsI5cm.root", "read");
	TFile *readFile4cm = new TFile("./../../data/Gamma_test_CsI4cm.root", "read");
	TFile *readFile3cm = new TFile("./../../data/Gamma_test_CsI3cm.root", "read");
  
  //Get Tree
  TTree *hittree_5cm = (TTree*) readFile5cm -> Get("Hit");
  TTree *recontree_5cm = (TTree*) readFile5cm -> Get("Recon");
  
  TTree *hittree_4cm = (TTree*) readFile4cm -> Get("Hit");
  TTree *recontree_4cm = (TTree*) readFile4cm -> Get("Recon");
  
  TTree *hittree_3cm = (TTree*) readFile3cm -> Get("Hit");
  TTree *recontree_3cm = (TTree*) readFile3cm -> Get("Recon");

  //SetBranchAddress
  hittree_5cm->SetBranchAddress("edep1",&edep1);
  hittree_5cm->SetBranchAddress("Depth",&Depth);

  hittree_4cm->SetBranchAddress("edep1",&edep1);
  hittree_4cm->SetBranchAddress("Depth",&Depth);

  hittree_3cm->SetBranchAddress("edep1",&edep1);
  hittree_3cm->SetBranchAddress("Depth",&Depth);

  recontree_5cm->SetBranchAddress("edep1",&edep1);
  recontree_4cm->SetBranchAddress("edep1",&edep1);
  recontree_3cm->SetBranchAddress("edep1",&edep1);

	TFile *writeFile = new TFile("./../../analysis/Gamma_test_eDep_CsI_all.root", "recreate");

  TCanvas *cvs1 = new TCanvas("edep1","",700,700);
  TCanvas *cvs2 = new TCanvas("edep2","",700,700);
  //Histogram
	TH1D *hist1_5cm = new TH1D("hist_energyDeposit_5cm","E_{dep} vs z (#gamma=10MeV);z (mm);(1/N_{event})(dE_{dep}/dz) (MeV/mm)",nbins1_5cm,low1_5cm,up1_5cm);
	TH1D *hist1_4cm = new TH1D("hist_energyDeposit_4cm","E_{dep} vs z (#gamma=10MeV, 4cm);z (mm);dE_{dep}/dz (MeV/mm)",nbins1_4cm,low1_4cm,up1_4cm);
	TH1D *hist1_3cm = new TH1D("hist_energyDeposit_3cm","E_{dep} vs z (#gamma=10MeV, 3cm);z (mm);dE_{dep}/dz (MeV/mm)",nbins1_3cm,low1_3cm,up1_3cm);

  TH1D *hist2_5cm = new TH1D("edep_5cm","E_{dep} (#gamma=10MeV);E_{dep} (MeV);Counts",nbins2,low2,up2);
  TH1D *hist2_4cm = new TH1D("edep_4cm","E_{dep} (#gamma=10MeV, 4cm);E_{dep} (MeV);dN/dE_{dep}",nbins2,low2,up2);
  TH1D *hist2_3cm = new TH1D("edep_3cm","E_{dep} (#gamma=10MeV, 3cm);E_{dep} (MeV);dN/dE_{dep}",nbins2,low2,up2);
	
  hist1_5cm -> SetMinimum(0);
	hist1_5cm -> GetXaxis() -> CenterTitle();
	hist1_5cm -> GetYaxis() -> CenterTitle();
  hist1_5cm -> SetAxisRange(0,0.4,"Y");

  hist2_5cm -> SetMinimum(0);
	hist2_5cm -> GetXaxis() -> CenterTitle();
	hist2_5cm -> GetYaxis() -> CenterTitle();
  hist2_5cm -> SetAxisRange(0,4500,"Y");
	
  hist1_4cm -> SetMinimum(0);
	hist1_4cm -> GetXaxis() -> CenterTitle();
	hist1_4cm -> GetYaxis() -> CenterTitle();
//  hist1_4cm -> SetAxisRange(0,0.32,"Y");

  hist2_4cm -> SetMinimum(0);
	hist2_4cm -> GetXaxis() -> CenterTitle();
	hist2_4cm -> GetYaxis() -> CenterTitle();
//  hist2_4cm -> SetAxisRange(0,1.4,"Y");
	
  hist1_3cm -> SetMinimum(0);
	hist1_3cm -> GetXaxis() -> CenterTitle();
	hist1_3cm -> GetYaxis() -> CenterTitle();
//  hist1_3cm -> SetAxisRange(0,0.35,"Y");

  hist2_3cm -> SetMinimum(0);
	hist2_3cm -> GetXaxis() -> CenterTitle();
	hist2_3cm -> GetYaxis() -> CenterTitle();
//  hist2_3cm -> SetAxisRange(0,1.2,"Y");
	
  //Entry
  double totalEntry_Hit_5cm = hittree_5cm->GetEntries();
  double totalEntry_Recon_5cm = recontree_5cm->GetEntries();

  double totalEntry_Hit_4cm = hittree_4cm->GetEntries();
  double totalEntry_Recon_4cm = recontree_4cm->GetEntries();

  double totalEntry_Hit_3cm = hittree_3cm->GetEntries();
  double totalEntry_Recon_3cm = recontree_3cm->GetEntries();


  //Weight
  double weight1_5cm = 1./totalEntry_Recon_5cm;
  double weight2_5cm = (nbins2/(up2-low2));
  
  double weight1_4cm = 1./totalEntry_Recon_4cm;
  double weight2_4cm = (nbins2/(up2-low2));
  
  double weight1_3cm = 1./totalEntry_Recon_3cm;
  double weight2_3cm = (nbins2/(up2-low2));
  

  // ******** Draw, Setting & Write *********
  
  //dE vs dz histogram style
  cvs1->cd();
	hittree_5cm -> Draw("Depth>>hist_energyDeposit_5cm","edep1/2982");
	hittree_4cm -> Draw("Depth>>hist_energyDeposit_4cm","edep1/2551");
	hittree_3cm -> Draw("Depth>>hist_energyDeposit_3cm","edep1/2126");

  hist1_5cm -> Draw();
  hist1_4cm -> Draw("same");
  hist1_3cm -> Draw("same");

  hist1_5cm -> SetLineColor(1);
  hist1_4cm -> SetLineColor(2);
  hist1_3cm -> SetLineColor(4);

  hist1_5cm -> SetLineStyle(1);
  hist1_4cm -> SetLineStyle(3);
  hist1_3cm -> SetLineStyle(4);

  hist1_5cm -> SetLineWidth(2.85);
  hist1_4cm -> SetLineWidth(2);
  hist1_3cm -> SetLineWidth(2.3);

  //Legend
  TLegend *legend1 = new TLegend(0.7,0.7,0.9,0.8);
  legend1->SetTextFont(40);
  legend1->SetTextSize(0.02);
  legend1->SetFillColor(0);
  legend1->AddEntry(hist1_5cm, "CsI : 5cm", "l");
  legend1->AddEntry(hist1_4cm, "CsI : 4cm", "l");
  legend1->AddEntry(hist1_3cm, "CsI : 3cm", "l");
  legend1->Draw();



  //Energy distribution histogram style
  cvs2->cd();
  recontree_5cm -> SetWeight(weight2_5cm);
  recontree_5cm -> Draw("edep1>>edep_5cm");

  recontree_4cm -> SetWeight(weight2_4cm);
  recontree_4cm -> Draw("edep1>>edep_4cm");

  recontree_3cm -> SetWeight(weight2_3cm);
  recontree_3cm -> Draw("edep1>>edep_3cm");

  hist2_5cm -> Draw();
  hist2_4cm -> Draw("same");
  hist2_3cm -> Draw("same");

  hist2_5cm -> SetLineColor(1);
  hist2_4cm -> SetLineColor(2);
  hist2_3cm -> SetLineColor(4);

  hist2_5cm -> SetLineStyle(1);
  hist2_4cm -> SetLineStyle(3);
  hist2_3cm -> SetLineStyle(4);

  hist2_5cm -> SetLineWidth(2.9);
  hist2_4cm -> SetLineWidth(3.4);
  hist2_3cm -> SetLineWidth(3.2);

  //Legend
  TLegend *legend2 = new TLegend(0.7,0.7,0.9,0.8);
  legend2->SetTextFont(40);
  legend2->SetTextSize(0.02);
  legend2->SetFillColor(0);
  legend2->AddEntry(hist2_5cm, "CsI : 5cm", "l");
  legend2->AddEntry(hist2_4cm, "CsI : 4cm", "l");
  legend2->AddEntry(hist2_3cm, "CsI : 3cm", "l");
  legend2->Draw();



  // Cout Information
  double NumOfGen = 5000;
  cout << endl;
  cout << endl;
  cout << endl;
  cout << " ******** CsI : 5cm ******** " << endl;
  cout << endl;
  cout << "===Hit Histogram Information===" << endl;
  cout << "  Total Entries : " << totalEntry_Hit_5cm << endl;
  cout << "  Integral - Gamma energy per event (MeV) " << hist1_5cm -> Integral("width") << endl;
  cout << "  Mean (mm) : " << hist1_5cm -> GetMean() << endl; 

  double NumMore8_5cm = recontree_5cm -> GetEntries("edep1>=8");
  double NumMore9_5cm = recontree_5cm -> GetEntries("edep1>=9");
  double More8Eff_5cm = NumMore8_5cm/totalEntry_Recon_5cm*100;
  double More9Eff_5cm = NumMore9_5cm/totalEntry_Recon_5cm*100;
  double HitEff_5cm = totalEntry_Recon_5cm/NumOfGen*100;
  cout << endl;
  cout << "===Reconstruction Histogram Information===" << endl;
  cout << "  # of detected Gammas : " << totalEntry_Recon_5cm << endl;
  cout << "  CsI interaction probability (%) : " << HitEff_5cm << endl;
  cout << "  # of particle >= 8MeV : " << NumMore8_5cm << endl;
  cout << "  # of particle >= 9MeV : " << NumMore9_5cm << endl;
  cout << "  Probability Gamma Energy more than 8MeV (%) : " << More8Eff_5cm << endl;
  cout << "  Probability Gamma Energy more than 9MeV (%) : " << More9Eff_5cm << endl;
  cout << "  Mean Energy of Gamma (MeV) : " << hist2_5cm -> GetMean() << endl; 

  cout << endl;
  cout << endl;
  cout << endl;
  cout << " ******** CsI : 4cm ******** " << endl;
  cout << endl;
  cout << "===Hit Histogram Information===" << endl;
  cout << "  Total Entries : " << totalEntry_Hit_4cm << endl;
  cout << "  Integral - Gamma energy per event (MeV) : " << hist1_4cm -> Integral("width") << endl;
  cout << "  Mean (mm) : " << hist1_4cm -> GetMean() << endl; 

  double NumMore8_4cm = recontree_4cm -> GetEntries("edep1>=8");
  double NumMore9_4cm = recontree_4cm -> GetEntries("edep1>=9");
  double More8Eff_4cm = NumMore8_4cm/totalEntry_Recon_4cm*100;
  double More9Eff_4cm = NumMore9_4cm/totalEntry_Recon_4cm*100;
  double HitEff_4cm = totalEntry_Recon_4cm/NumOfGen*100;
  cout << endl;
  cout << "===Reconstruction Histogram Information===" << endl;
  cout << "  # of detected Gammas : " << totalEntry_Recon_4cm << endl;
  cout << "  CsI interaction probability (%) : " << HitEff_4cm << endl;
  cout << "  # of particle >= 8MeV : " << NumMore8_4cm << endl;
  cout << "  # of particle >= 8MeV : " << NumMore9_4cm << endl;
  cout << "  Probability Gamma Energy more than 8MeV (%) : " << More8Eff_4cm << endl;
  cout << "  Probability Gamma Energy more than 8MeV (%) : " << More9Eff_4cm << endl;
  cout << "  Mean Energy of Gamma (MeV) : " << hist2_4cm -> GetMean() << endl; 

  cout << endl;
  cout << endl;
  cout << endl;
  cout << " ******** CsI : 3cm ******** " << endl;
  cout << endl;
  cout << "===Hit Histogram Information===" << endl;
  cout << "  Total Entries : " << totalEntry_Hit_3cm << endl;
  cout << "  Integral - Gamma energy per event (MeV) : " << hist1_3cm -> Integral("width") << endl;
  cout << "  Mean (mm) : " << hist1_3cm -> GetMean() << endl; 

  double NumMore8_3cm = recontree_3cm -> GetEntries("edep1>=8");
  double NumMore9_3cm = recontree_3cm -> GetEntries("edep1>=9");
  double More8Eff_3cm = NumMore8_3cm/totalEntry_Recon_3cm*100;
  double More9Eff_3cm = NumMore9_3cm/totalEntry_Recon_3cm*100;
  double HitEff_3cm = totalEntry_Recon_3cm/NumOfGen*100;
  cout << endl;
  cout << "===Reconstruction Histogram Information===" << endl;
  cout << "  # of detected Gammas : " << totalEntry_Recon_3cm << endl;
  cout << "  CsI interaction probability (%) : " << HitEff_3cm << endl;
  cout << "  # of particle >= 8MeV : " << NumMore8_3cm << endl;
  cout << "  # of particle >= 9MeV : " << NumMore9_3cm << endl;
  cout << "  Probability Gamma Energy more than 8MeV (%) : " << More8Eff_3cm << endl;
  cout << "  Probability Gamma Energy more than 9MeV (%) : " << More9Eff_3cm << endl;
  cout << "  Mean Energy of Gamma (MeV) : " << hist2_3cm -> GetMean() << endl; 

	writeFile -> cd();
	
	hist1_5cm -> Write();	
	hist1_4cm -> Write();	
	hist1_3cm -> Write();	
  hist2_5cm -> Write();
  hist2_4cm -> Write();
  hist2_3cm -> Write();
	cvs1 -> Write();
	cvs2 -> Write();

  delete cvs1;
  delete cvs2;
	delete hist1_5cm;
	delete hist1_4cm;
	delete hist1_3cm;
	delete hist2_5cm;
	delete hist2_4cm;
	delete hist2_3cm;
	delete writeFile;

	return 0;
}

