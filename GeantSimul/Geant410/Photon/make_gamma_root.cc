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
	TFile *openFile = new TFile("./../../data/rawData_lampslow.root", "READ");

	Int_t eventID, trackID, pID, pdg, parentID, sEventID, sTrackID, isSiCsI, detID;
	Double_t hitTime, energyInit, edep, edep1, x, y, z, z_primvert, z_secvert, Depth;

	TTree *SimulationTree = (TTree *) openFile -> Get("data"); 
		SimulationTree -> SetBranchAddress("pID", &pID);
		SimulationTree -> SetBranchAddress("eventID", &eventID);
		SimulationTree -> SetBranchAddress("trackID", &trackID);
		SimulationTree -> SetBranchAddress("parentID", &parentID);
		SimulationTree -> SetBranchAddress("x", &x);
		SimulationTree -> SetBranchAddress("y", &y);
		SimulationTree -> SetBranchAddress("z", &z);
		SimulationTree -> SetBranchAddress("edep", &edep);
		SimulationTree -> SetBranchAddress("detID", &detID);


	TFile *writeFile = new TFile("./../../data/Gamma_test_CsI5cm.root", "RECREATE");
	
  TTree *dE_E = new TTree("Hit", "Neutron Hit");
		dE_E -> Branch("pdg", &pdg, "pdg/I");
		dE_E -> Branch("trackID", &trackID, "trackID/I");
		dE_E -> Branch("Depth", &Depth, "Depth/D");
		dE_E -> Branch("edep1", &edep1, "edep1/D");

    int simulationEntries = SimulationTree -> GetEntries();
//    cout << "simulation entry number : " << simulationEntries << endl;
    edep1=0;
    Depth=0;
    
  	for (int i = 0; i < simulationEntries; i++) 
    {
        SimulationTree -> GetEntry(i);
        pdg=pID; 
       // cout << "trackID first : " << trackID << endl; 

          if (detID==8)
					 { 
             edep1 = edep; 
             Depth = z-400.11;
             dE_E -> Fill();
           }
    }
  
  writeFile -> cd();
	dE_E -> Write();
	
	
  TTree *NRecon = new TTree("Recon", "");
		NRecon-> Branch("trackID", &trackID, "trackID/I");
		NRecon-> Branch("edep1", &edep1, "edep1/D");

//    cout << "simulation entry number : " << simulationEntries << endl;
    edep1=0;
  
    SimulationTree->GetEntry(0);
    double trackIDbef=trackID;

    for (int i = 0; i < simulationEntries; i++) 
    {
        SimulationTree -> GetEntry(i);
        
       // cout << "trackID first : " << trackID << endl; 

        if (trackID == trackIDbef)
        {
          if (detID==8)
					 { 
             edep1 += edep;
           }
        }
        
        if (trackID!=trackIDbef)
        {
            SimulationTree -> GetEntry(i-1);
            NRecon -> Fill();
            edep1 = 0;
            SimulationTree -> GetEntry(i);
            if (detID==8)
              { 
                edep1 += edep;
              }
        }
        
        if (i == simulationEntries -1)
        {
          NRecon -> Fill();
        }

          trackIDbef = trackID;
    }


  writeFile -> cd();
	NRecon -> Write();
	
  delete dE_E;
  delete NRecon;
	delete writeFile;

	return 0;
}
