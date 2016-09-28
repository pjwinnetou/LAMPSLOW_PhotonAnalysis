#include <TROOT.h>
#include <TSystem.h>
#include <Riostream.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TTree.h>
#include <TMath.h>
#include <TChain.h>
#include <fstream>
#include <iostream>
#include <TF1.h>
#include <TF2.h>
#include <TStyle.h>
using namespace std;

int edep1()
{
    gStyle->SetOptStat(0);
	TFile *openFile = new TFile("../rawData_lampslow.root", "READ");

	Int_t eventID, trackID, pID, pdg, parentID, sEventID, sTrackID, isSiCsI, detID;
	Double_t hitTime, energyInit,  edep, edep1, edep2, edep3;

	TTree *SimulationTree = (TTree *) openFile -> Get("data"); 
		SimulationTree -> SetBranchAddress("pID", &pID);
		SimulationTree -> SetBranchAddress("eventID", &eventID);
		SimulationTree -> SetBranchAddress("trackID", &trackID);
		SimulationTree -> SetBranchAddress("parentID", &parentID);
		SimulationTree -> SetBranchAddress("edep", &edep);
		SimulationTree -> SetBranchAddress("detID", &detID);


	TFile *writeFile = new TFile("dE_E.root", "RECREATE");
	
  TTree *dE_E = new TTree("dE_E", "dE of Si vs. E of CsI");
		dE_E -> Branch("pdg", &pdg, "pdg/I");
		dE_E -> Branch("trackID", &trackID, "trackID/I");
		dE_E -> Branch("eventID", &eventID, "eventID/I");
		dE_E -> Branch("edep1", &edep1, "edep1/D");
		dE_E -> Branch("edep2", &edep2, "edep2/D");

  TCanvas *c1=new TCanvas("c1","",1400,700);

  TH1F *h_dE_E = new TH1F("h_dE_E","Cs^{137} Gamma Spectrum;Energy;Counts",1000,0,1);

    int simulationEntries = SimulationTree -> GetEntries();


    edep1=0;
    edep2=0;
    SimulationTree -> GetEntry(0);
    int trackIDbef = trackID;
    pdg=pID;
  	for (int i = 0; i < simulationEntries; i++) 
    {
        SimulationTree -> GetEntry(i);
        

        if (trackID == trackIDbef)
        {
          if (parentID==0)
           { pdg = pID;}
          if (detID==11)
		 { edep1 += edep; }
	else if (detID==5)
		 { edep2 += edep; }
        }
        
        if (trackID!=trackIDbef)
        {
            SimulationTree -> GetEntry(i-1);
             if(edep1!=0)
             {  
              dE_E -> Fill();
             }
            edep1 = 0;
            edep2 = 0;
            SimulationTree -> GetEntry(i);
            if (detID==11)
              { edep1 += edep;}
            else if (detID==5)
              { edep2 += edep;}

        }
        
        if (i == simulationEntries -1)
        {
          if(edep1!=0)
          {
          dE_E -> Fill();
          }
        }

          trackIDbef = trackID;
         
		
    }
  
  writeFile -> cd();
	dE_E -> Write();


  dE_E->Draw("edep1>>h_dE_E","","colz");

  c1->SaveAs("Gamma_Spectrum.png");

	return 0;
}
