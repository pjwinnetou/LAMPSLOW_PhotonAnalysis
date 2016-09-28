#include <TROOT.h>
#include <TSystem.h>
#include <Riostream.h>
#include <TFile.h>
#include <TTree.h>
#include <TMath.h>
#include <TChain.h>
#include <fstream>
#include <iostream>
using namespace std;

int main()
{
	TFile *openFile = new TFile("dE_E.root", "READ");

	Int_t eventID, trackID, pID, parentID, detID,pdg;
	Double_t hitTime, energyInit, edep, edep1, edep2,etot;

	TTree *SimulationTree = (TTree *) openFile -> Get("dE_E"); //meaningless?
		SimulationTree -> SetBranchAddress("eventID", &eventID);
		SimulationTree -> SetBranchAddress("trackID", &trackID);
		SimulationTree -> SetBranchAddress("pdg", &pdg);
		SimulationTree -> SetBranchAddress("edep1", &edep1);
		SimulationTree -> SetBranchAddress("edep2", &edep2);


	TFile *writeFile = new TFile("dE_E_real.root", "RECREATE");
	
  TTree *dE_E = new TTree("dE_E", "dE of Si vs. E of CsI");
		dE_E -> Branch("pID", &pID, "pID/I");
		dE_E -> Branch("trackID", &trackID, "trackID/I"); //KYO
		dE_E -> Branch("eventID", &eventID, "eventID/I");
		dE_E -> Branch("edep1", &edep1, "edep1/D");
		dE_E -> Branch("edep2", &edep2, "edep2/D");
		dE_E -> Branch("etot", &etot, "etot/D");

    int simulationEntries = SimulationTree -> GetEntries();
    cout << "simulation entry number : " << simulationEntries << endl;
  	
    for (int i = 0; i < simulationEntries; i++) 
    {
        SimulationTree -> GetEntry(i);
       
        pID=pdg; 
       // cout << "trackID first : " << trackID << endl; 

        if (edep1!=0&&edep2!=0)
        {
            etot = edep1 + edep2;
            dE_E -> Fill();
            etot=0;
        }
    }
  
  writeFile -> cd();
	dE_E -> Write();
  delete dE_E;
	delete writeFile;

	return 0;
}
