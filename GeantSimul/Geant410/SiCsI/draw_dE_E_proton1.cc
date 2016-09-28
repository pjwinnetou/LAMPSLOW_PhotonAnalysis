#include <Riostream.h>
#include <TROOT.h>
#include <TSystem.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH2D.h>
#include <TH1D.h>
#include <TPaletteAxis.h>
#include <TPaveStats.h>
#include <TFile.h>
#include <TTree.h>
#include <TDirectory.h>

#include <sstream>
#include <string>

using namespace std;

int main()
{
	// start drawing
	gStyle -> SetPalette(1);
	gStyle -> SetOptTitle(0);
	gStyle -> SetLabelSize(0.035, "X");
	gStyle -> SetLabelSize(0.035, "Y");
	gStyle -> SetTitleXOffset(1.0);
	gStyle -> SetTitleYOffset(1.0);
	gStyle -> SetTitleXSize(0.07);
	gStyle -> SetTitleYSize(0.07);
	gStyle -> SetPadLeftMargin(0.15);
	gStyle -> SetPadTopMargin(0.05);
	gStyle -> SetPadBottomMargin(0.15);

	// read root file (TChain instead of Project)
  
  Double_t deltaE, largeE;
	Double_t edep1, edep2, etot;
  Int_t trackID;
 
  TFile *openFile = new TFile("dE_E_proton1.root","read");
  
  TTree *dataTree = (TTree *) openFile -> Get("dE_E");
         dataTree -> SetBranchAddress("trackID", &trackID);
         dataTree -> SetBranchAddress("edep1", &edep1);
         dataTree -> SetBranchAddress("edep2", &edep2);

  TFile *writeFile = new TFile("dE_E_Hist_proton1.root","recreate");       

  TTree *writeTree = new TTree("Energy","");
          writeTree -> Branch("trackID",&trackID, "trackID/I");
          writeTree -> Branch("edep1",&edep1, "edep1/D");
          writeTree -> Branch("edep2",&edep2, "edep2/D");
          writeTree -> Branch("etot",&etot, "etot/D");
		
	//draw histogram/
  TCanvas *cvs = new TCanvas("cvs", "canvas", 800, 600);

	  cvs -> cd();
	TH2D *hist = new TH2D("hist", "dE vs E",300, 0, 100, 150, 0, 50);


  Int_t entries = dataTree -> GetEntries();
  cout << "entryN : " << entries << endl;
	for (Int_t i=0; i<entries; i++)
  {
   edep1=0;
	 edep2=0;
   etot=0;

   dataTree -> GetEntry(i);
   etot = edep1 + edep2;
   if(edep1!=0&&edep2!=0)
   {
     hist->Fill(etot, edep1);
     writeTree -> Fill();
   }
  }
writeFile -> cd();
writeTree -> Write();
    hist -> GetXaxis() -> SetTitle("E (MeV)");
		hist -> GetXaxis() -> SetTitleFont(132);
		hist -> GetXaxis() -> SetTitleSize(0.05);
		hist -> GetXaxis() -> CenterTitle();
		hist -> GetYaxis() -> SetTitle("dE (MeV)");
		hist -> GetYaxis() -> SetTitleFont(132);
		hist -> GetYaxis() -> SetTitleSize(0.05);
		hist -> GetYaxis() -> CenterTitle();
		hist -> SetStats(0); //stats
		hist -> Draw("colz");

	cvs -> Update();

	TPaletteAxis *palette = (TPaletteAxis *) hist -> FindObject("palette");
		palette -> SetLabelSize(0.022);

	//TPaveStats *stats = (TPaveStats *) hist -> FindObject("stats");
	//	stats -> SetX1NDC(0.68);
	//	stats -> SetX2NDC(0.87);
	//	stats -> SetY1NDC(0.74);
	//	stats -> SetY2NDC(0.93);

	cvs -> Update();

	cvs -> SaveAs("dE_E_proton1.png");
  cvs->Write();
  hist->Write();


  
  return 0;
}
