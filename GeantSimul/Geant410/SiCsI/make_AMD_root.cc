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
	TFile *openFile = new TFile("amd.root", "READ");
	TFile *open = new TFile("dE_E_real.root", "READ");

	Int_t eventID, trackID,A,Z,N, pID,trackN, parentID, detID,pdg;
	Double_t hitTime,eKin, energyInit, edep, edep1, edep2,etot;

	TTree *SimulationTree = (TTree *) openFile -> Get("lab"); //meaningless?
		SimulationTree -> SetBranchAddress("Z", &Z);
		SimulationTree -> SetBranchAddress("N", &N);
		SimulationTree -> SetBranchAddress("A", &A);
		SimulationTree -> SetBranchAddress("eKin", &eKin);
  

	TTree *SimulationTreeA = (TTree *) open -> Get("dE_E"); //meaningless?
		SimulationTreeA -> SetBranchAddress("trackID", &trackID);
	
  TFile *writeFile = new TFile("AMD_trackSelect.root", "RECREATE");
	
  TTree *lab = new TTree("dE_E", "dE of Si vs. E of CsI");
		lab -> Branch("trackN", &trackN, "trackN/I"); //KYO
		lab -> Branch("A", &A, "A/I");
		lab-> Branch("N", &N, "N/I");
		lab -> Branch("Z", &Z, "Z/I");
		lab -> Branch("eKin", &eKin, "eKin/D");

    int simulationEntries = SimulationTree -> GetEntries();
    int simN = SimulationTreeA -> GetEntries();
    cout << "simulation entry number : " << simulationEntries << endl;
  
    for (int i = 0; i < simulationEntries; i++) 
    {
          SimulationTree -> GetEntry(i);
        trackN=i;
        for(int j=0; j<simN;j++)
        {
          SimulationTreeA -> GetEntry(j);
          if(trackN ==trackID){
       // cout << "trackID first : " << trackID << endl; 
        lab->Fill();}
        }
    }
  
  writeFile -> cd();
	lab -> Write();
  delete lab;
	delete writeFile;

	return 0;
    }
