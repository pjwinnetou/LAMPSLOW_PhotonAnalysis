#if !defined(__CINT__) || defined(__MAKECINT__)
#include <Riostream.h>
#include <TProfile.h>
#include <TBrowser.h>
#include <TGraph.h>
#include <TNtuple.h>
#include <TString.h>
#include <TMath.h>
//#include <THIDebug.h>
#include <TStyle.h>
#include <TLegend.h>
#include <TInterpreter.h>
#endif
#include <TFile.h>
#include <TROOT.h>
#include <TH1D.h>
#include <TH2.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TSystem.h>
#include <TPaveStats.h>
#include <TLatex.h>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <TRandom.h>
using namespace std;
using std::stringstream;

struct HIT {
   Int_t trackID;
   Int_t parentID;
   Int_t pID;
   Double_t edep;
   Double_t time;
};

void LAND_effi_fromHH()
{
	gROOT->Reset();
	gROOT->Clear();
	gROOT->SetStyle("Plain");

	gStyle->SetTextSize(0.01908148);
	gStyle->SetTitleFontSize(0.07);
	gStyle->SetOptTitle(0);
	//gStyle->SetOptStat(0000);
	gStyle->SetTitleXSize(0.07);
	gStyle->SetTitleXOffset(0.9);
	gStyle->SetTitleYSize(0.07);
	gStyle->SetTitleYOffset(0.85);
	gStyle->SetPadBottomMargin(0.15);
	gStyle->SetPadTopMargin(0.05);
	gStyle->SetPadLeftMargin(0.14);
	gStyle->SetPadRightMargin(0.05);

	Double_t detector_threshold = 0; // MeV
    Int_t track = 5000;
    Int_t pID;
    Int_t trackID;
	Int_t before_trackID =0;
    Double_t time;
    Double_t edep;
	Double_t totEperEvent;
	TH1 *gr_Edep = new TH1F("energyLoss","",150,0,15);
    stringstream file_name;
    file_name << "rawData_lampslow_neutron_10MeV_5000event.root"; 
//rawData_lampslow_neutron_10MeV_5000event.root
    TFile *file = new TFile(file_name.str().c_str());

    TTree *hitTree = (TTree*) file -> Get("data");
    hitTree -> SetBranchAddress("trackID", &trackID);
    hitTree -> SetBranchAddress("pID", &pID);
    hitTree -> SetBranchAddress("time", &time);
    hitTree -> SetBranchAddress("edep", &edep);

     Int_t total_events = hitTree -> GetEntries();
     for (Int_t l = 0; l != total_events; l++)
		{
	 	hitTree -> GetEntry(l);
		totEperEvent += edep;	

		  if(trackID != before_trackID)
		   {
//			cout<<" event id : " << trackID<< " Edep per event : " << totEperEvent << endl;
			gr_Edep -> Fill(totEperEvent);
			totEperEvent = edep;
           	}  
		before_trackID = trackID;
		}  
    cout<<" photo peak # : " << gr_Edep-> Integral(99,101); 

	TCanvas *myCanvas_1 = new TCanvas();    
	myCanvas_1 ->Range(0,0,1,1);    
	myCanvas_1 ->SetBorderSize(2);   
	myCanvas_1 ->SetFrameFillColor(0);
	myCanvas_1 ->SetTopMargin(0.05);
	myCanvas_1 ->SetBottomMargin(0.15);
	myCanvas_1 ->SetRightMargin(0.05);
	myCanvas_1 ->SetLeftMargin(0.15);
	gr_Edep -> Draw();
	gr_Edep -> GetXaxis()-> SetTitle("dE (MeV)");
	gr_Edep -> GetYaxis()-> SetTitle("Counts");
	gr_Edep -> GetYaxis()->SetTitleOffset(1);
}
