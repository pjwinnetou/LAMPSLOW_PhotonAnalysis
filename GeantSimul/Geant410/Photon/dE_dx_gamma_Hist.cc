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
	cout << "**** Gamma Efficiency Draw *****" << endl;

  gStyle -> SetOptStat(0);
  gStyle -> SetTitleYOffset(1.65);
  gStyle -> SetTitleXOffset(1.3);
  gStyle -> SetTitleSize(0.04,"xy");
  gStyle -> SetPadLeftMargin(0.2);
  gStyle -> SetPadRightMargin(0.05);
  gStyle -> SetPadTopMargin(0.20);
  gStyle -> SetPadBottomMargin(0.15);

  double edep1, Depth;
	double nbins1 = 31;
	double low1 = 0;
	double up1 = 31;

	double nbins2 = 110;
	double low2 = 0;
	double up2 = 11;
	


	TFile *readFile = new TFile("./../../data/Gamma_test_CsI4cm.root", "read");
  TTree *hittree = (TTree*) readFile -> Get("Hit");
  TTree *recontree = (TTree*) readFile -> Get("Recon");

  hittree->SetBranchAddress("edep1",&edep1);
  hittree->SetBranchAddress("Depth",&Depth);

  recontree->SetBranchAddress("edep1",&edep1);

	TFile *writeFile = new TFile("./../../analysis/Gamma_test_eDep_CsI3cm.root", "recreate");

	TH1D *hist1 = new TH1D("hist_energyDeposit","E_{dep} vs z (#gamma=10MeV, 3cm);z (mm);dE_{dep}/dz (MeV/mm)",nbins1,low1,up1);
	TH1D *hist2 = new TH1D("edep","E_{dep} (#gamma=10MeV, 3cm);E_{dep} (MeV);(1/N_{event})(dN/dE_{dep})",nbins2,low2,up2);
	
  double totalEntry_Hit = hittree->GetEntries();
  double totalEntry_Recon = recontree->GetEntries();
	hittree -> Draw("Depth>>hist_energyDeposit", "edep1/2126");

  double weight = (nbins2/(up2-low2))/totalEntry_Recon;
  recontree -> SetWeight(weight);
  recontree -> Draw("edep1>>edep");

  hist1 -> SetMinimum(0);
	hist1 -> GetXaxis() -> CenterTitle();
	hist1 -> GetYaxis() -> CenterTitle();
  hist1 -> SetAxisRange(0,0.38,"Y");

  hist2 -> SetMinimum(0);
	hist2 -> GetXaxis() -> CenterTitle();
	hist2 -> GetYaxis() -> CenterTitle();
  hist2 -> SetAxisRange(0,1.2,"Y");
	
  cout << endl;
  cout << endl;
  cout << "===Hit Histogram Information===" << endl;
  cout << "  Total Entries : " << totalEntry_Hit << endl;
  cout << "  Integral : " << hist1 -> Integral("width") << endl;
  cout << "  Mean : " << hist1 -> GetMean() << endl; 

  double NumOfGen = 5000;
  double HitEff = totalEntry_Recon/NumOfGen*100;
  cout << endl;
  cout << endl;
  cout << "===Reconstruction Histogram Information===" << endl;
  cout << "  Total Entries : " << totalEntry_Recon << endl;
  cout << "  Hit Percentage : " << HitEff << endl;
  cout << "  Integral : " << hist2 -> Integral("width") << endl;
  cout << "  Mean : " << hist2 -> GetMean() << endl; 

	//writeFile -> cd();
	
	hist1 -> Write();	
  hist2 -> Write();
 	//cvs->Draw();
	//cvs -> Write();

	delete hist1;
	delete hist2;
	delete writeFile;

	return 0;
}

