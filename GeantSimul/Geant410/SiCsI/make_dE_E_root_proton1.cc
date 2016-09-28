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
	TFile *openFile = new TFile("./rawData_proton1.root", "READ");

	Int_t eventID, trackID, pID, parentID, sEventID, sTrackID, isSiCsI, detID;
	Double_t hitTime, energyInit, edep, edep1, edep2;

	TTree *SimulationTree = (TTree *) openFile -> Get("data"); //meaningless?
		SimulationTree -> SetBranchAddress("eventID", &eventID);
		SimulationTree -> SetBranchAddress("trackID", &trackID);
		SimulationTree -> SetBranchAddress("parentID", &parentID);
		SimulationTree -> SetBranchAddress("edep", &edep);
		SimulationTree -> SetBranchAddress("detID", &detID);


	TFile *writeFile = new TFile("dE_E_proton1.root", "RECREATE");
	
  TTree *dE_E = new TTree("dE_E", "dE of Si vs. E of CsI");
		dE_E -> Branch("pID", &pID, "pID/I");
		dE_E -> Branch("trackID", &trackID, "trackID/I"); //KYO
		dE_E -> Branch("eventID", &eventID, "eventID/I");
		dE_E -> Branch("edep1", &edep1, "edep1/D");
		dE_E -> Branch("edep2", &edep2, "edep2/D");

    int simulationEntries = SimulationTree -> GetEntries();
    cout << "simulation entry number : " << simulationEntries << endl;
    edep1=0;
    edep2=0;
    SimulationTree->GetEntry(0);
    int trackIDbef = trackID;
  	for (int i = 0; i < simulationEntries; i++) 
    {
        SimulationTree -> GetEntry(i);
        
       // cout << "trackID first : " << trackID << endl; 

        if (trackID == trackIDbef)
        {
          if (detID==1)
					 { edep1 += edep; }
				 	else if (detID==2)
					 { edep2 += edep; }
        }
        
        if (trackID!=trackIDbef)
        {
            SimulationTree -> GetEntry(i-1);
            dE_E -> Fill();
            edep1 = 0;
            edep2 = 0;
            SimulationTree -> GetEntry(i);
            if (detID==1)
              { edep1 += edep;}
            else if (detID==2)
              { edep2 += edep;}
        }
        
        if (i == simulationEntries -1)
        {
          dE_E -> Fill();
        }

          trackIDbef = trackID;
         
		
    }
  
  writeFile -> cd();
	dE_E -> Write();
  delete dE_E;
	delete writeFile;

	return 0;
}
