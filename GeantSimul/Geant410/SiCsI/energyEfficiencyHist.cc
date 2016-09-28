#include <TCanvas.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TF1.h>
#include <TFile.h>
#include <TMath.h>
#include <TTree.h>
#include <TLegend.h>
#include <TStyle.h>
#include <string>
#include <iostream>

void EKAnalysis(TTree *pidTree,TTree *amdTree, TFile *histData);
using namespace std;

int main()
{
	gStyle -> SetOptStat(0);
	gStyle -> SetOptTitle(0);
	gStyle -> SetTitleYOffset(2.1);
	gStyle -> SetTitleXOffset(1.5);
	gStyle -> SetTitleSize(0.038, "xy");
	gStyle -> SetPadLeftMargin(0.20);
	gStyle -> SetPadRightMargin(0.1);
	gStyle -> SetPadTopMargin(0.14);
	gStyle -> SetPadBottomMargin(0.23);

	TFile *simulationData = new TFile("dE_E_real.root", "read");
	TTree *pidTree = (TTree*) simulationData -> Get("dE_E");
	
	TFile *amdData = new TFile("./AMD_trackSelect.root", "read");
	TTree *amdTree = (TTree*) amdData -> Get("dE_E");

	TFile *histData = new TFile("./energyEfficiency.root","recreate");
	


	EKAnalysis(pidTree,amdTree,histData);
//
	return 0;
}

void EKAnalysis(TTree *pidTree,TTree *amdTree, TFile *histData)
{
	int nbins = 80;
	double xlow = 0;
	double xup = 130;
	double xupamd = 130;
	double weight;
  
  int nprotonS = 5238;
  int ndeuteronS = 1339;
  int ntritonS = 700;
  int nhelium4S = 621;
  int nhelium3S = 56;
  int nhelium6S = 36;


	TCanvas *cvs_proton = new TCanvas("KinE_protonIso","",700,700);
		cvs_proton -> SetLogy(1);
	TCanvas *cvs_helium = new TCanvas("KinE_heliumIso","",700,700);
	//	cvs_helium -> SetLogy(1);

	TH1D *hist_proton = new TH1D("hist_KinE_proton","E_{Kin} (MeV) ;E_{Kin} (MeV);(dN/dE_{Kin})",nbins,xlow,xup);
	TH1D *hist_deuteron = new TH1D("hist_KinE_deuteron","",nbins,xlow,xup);
	TH1D *hist_triton = new TH1D("hist_KinE_triton","",nbins,xlow,xup);
	TH1D *hist_helium4 = new TH1D("hist_KinE_helium4","E_{Kin} (MeV) ;E_{Kin} (MeV);(dN/dE_{Kin})",nbins,xlow,xup);
	TH1D *hist_helium3 = new TH1D("hist_KinE_helium3","",nbins,xlow,xup);
	TH1D *hist_helium6 = new TH1D("hist_KinE_helium6","",nbins,xlow,xup);

		hist_proton -> GetXaxis() -> CenterTitle();
		hist_proton -> GetYaxis() -> CenterTitle();
		hist_helium4 -> GetXaxis() -> CenterTitle();
		hist_helium4 -> GetYaxis() -> CenterTitle();
	
	//-------------------------------AMD--------------------------------------

    TH1D *amdhist_proton = new TH1D("amdhist_KinE_proton","E_{Kin} (MeV) ;E_{Kin} (MeV);(dN/dE_{Kin})",nbins,xlow,xupamd);
	TH1D *amdhist_deuteron = new TH1D("amdhist_KinE_deuteron","E_{Kin} (MeV) ;E_{Kin} (MeV);(dN/dE_{Kin}",nbins,xlow,xupamd);
	TH1D *amdhist_triton = new TH1D("amdhist_KinE_triton","E_{Kin} (MeV) ;E_{Kin} (MeV);(dN/dE_{Kin}",nbins,xlow,xupamd);
	TH1D *amdhist_helium4 = new TH1D("amdhist_KinE_helium4","E_{Kin} (MeV) ;E_{Kin} (MeV);(dN/dE_{Kin})",nbins,xlow,xupamd);
	TH1D *amdhist_helium3 = new TH1D("amdhist_KinE_helium3","E_{Kin} (MeV) ;E_{Kin} (MeV);(dN/dE_{Kin}",nbins,xlow,xupamd);
	TH1D *amdhist_helium6 = new TH1D("amdhist_KinE_helium6","E_{Kin} (MeV) ;E_{Kin} (MeV);(dN/dE_{Kin}",nbins,xlow,xupamd);
	
		amdhist_proton -> GetXaxis() -> CenterTitle();
		amdhist_proton -> GetYaxis() -> CenterTitle();
		amdhist_helium4 -> GetXaxis() -> CenterTitle();
		amdhist_helium4 -> GetYaxis() -> CenterTitle();
	// ** Kinetic Energy **	
	cvs_proton -> cd();	
	weight= (nbins/(xup-xlow))/nprotonS;
  pidTree -> SetWeight(weight);
	pidTree -> Draw("etot>>hist_KinE_proton","pID==2212");
//  cout << "hist proton : " << hist_proton << endl;
//  weight= (nbins/(xup-xlow))/ndeuteronS;
 // pidTree -> SetWeight(weight);
//  pidTree -> Draw("etot>>hist_KinE_deuteron","pID==1000010020");
//	weight= (nbins/(xup-xlow))/ntritonS;
//	pidTree -> SetWeight(weight);
//  pidTree -> Draw("etot>>hist_KinE_triton","pID==1000010030");
//	weight= (nbins/(xup-xlow))/nhelium4S;
//	pidTree -> SetWeight(weight);
//  pidTree -> Draw("etot>>hist_KinE_helium4","pID==1000020040");
/*	weight= (nbins/(xup-xlow))/nhelium3S;
	pidTree -> SetWeight(weight);
  pidTree -> Draw("etot>>hist_KinE_helium3","pID==1000020030");
	weight= (nbins/(xup-xlow))/nhelium6S;
	pidTree -> SetWeight(weight);
  */
	weight = (nbins/(xupamd-xlow))/nprotonS;
	amdTree -> SetWeight(weight);
	amdTree -> Draw("eKin>>amdhist_KinE_proton","Z==1&&N==0");
/*	weight = (nbins/(xupamd-xlow))/ndeuteronS;
	amdTree -> SetWeight(weight);
	amdTree -> Draw("eKin>>amdhist_KinE_deuteron","Z==1&&N==1");
	weight = (nbins/(xupamd-xlow))/ntritonS;
	amdTree -> SetWeight(weight);
	amdTree -> Draw("eKin>>amdhist_KinE_triton","Z==1&&N==2");
*/
//  weight = (nbins/(xupamd-xlow))/nhelium4S;
//	amdTree -> SetWeight(weight);
//	amdTree -> Draw("eKin>>amdhist_KinE_helium4","Z==2&&N==2");
/*	weight = (nbins/(xupamd-xlow))/nhelium3S;
	amdTree -> SetWeight(weight);
	amdTree -> Draw("eKin>>amdhist_KinE_helium3","Z==2&&N==1");
	weight = (nbins/(xupamd-xlow))/nhelium6S;
	amdTree -> SetWeight(weight);
	amdTree -> Draw("eKin>>amdhist_KinE_helium6","Z==2&&N==4");
*/
  hist_proton->Write();
/*	hist_deuteron -> Write();
	hist_triton -> Write();
	hist_helium4 -> Write();
	hist_helium3 -> Write();
	hist_helium6 -> Write();
*/
//cout << "before write : " << amdhist_proton << endl;

  amdhist_proton -> Write();
//  amdhist_deuteron -> Write();
//  amdhist_triton -> Write();
//  amdhist_helium4 -> Write();
//  amdhist_helium3 -> Write();
//  amdhist_helium6 -> Write();

//cout << "after write : " << amdhist_proton << endl;
//	double mini =  hist_proton -> GetMinimum();
//	double setmini = mini/5;
//	cout << setmini << endl;
	//double minia =  amdhist -> GetMinimum();
	//double setminia = minia/5;
 // hist_proton -> Draw();
//	amdhist_helium4 -> Draw();
//  	hist_helium4 -> Draw("same");
//	hist_triton -> Draw("same");
	amdhist_proton -> Draw();
  hist_proton -> Draw("same");
//  amdhist_triton -> Draw("same");


	hist_proton -> SetLineColor(2);
	hist_helium4 -> SetLineColor(2);
	hist_deuteron -> SetLineColor(2);
	hist_triton -> SetLineColor(3);

	hist_helium4 -> SetLineStyle(2);
  hist_proton-> SetLineStyle(2);
  hist_deuteron-> SetLineStyle(2);
  hist_triton-> SetLineStyle(2);

	amdhist_proton -> SetLineColor(4);
	amdhist_helium4 -> SetLineColor(4);
	amdhist_deuteron -> SetLineColor(4);
	amdhist_triton -> SetLineColor(7);

  amdhist_proton -> SetLineStyle(1);
  amdhist_deuteron -> SetLineStyle(1);
  amdhist_triton -> SetLineStyle(1);
  
	amdhist_helium4 -> SetLineStyle(1);
  amdhist_helium4 -> SetAxisRange(0.000001,0.6,"Y");
  

  TLegend *legendP = new TLegend(0.6,0.7,0.9,0.8);
		 legendP -> SetTextFont(72);
		 legendP -> SetTextSize(0.03);
	         legendP -> AddEntry(amdhist_helium4, "Proton (Generator)", "l");	
	         legendP -> AddEntry(hist_helium4, "Proton (Detector)", "l");
	         legendP -> Draw();

          
  hist_proton -> Write();
  histData->cd();
  cvs_proton->Write();	
}	
