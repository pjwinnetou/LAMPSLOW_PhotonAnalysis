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
	TFile *openFile = new TFile("./rawData_amd_ThetaRing1.root", "READ");

	Int_t eventID, trackID, pID, pdg, parentID, sEventID, sTrackID, isSiCsI, detID;
	Double_t hitTime, energyInit, edep, edep1, edep2;

	TTree *SimulationTree = (TTree *) openFile -> Get("data"); //meaningless?
		SimulationTree -> SetBranchAddress("pID", &pID);
		SimulationTree -> SetBranchAddress("eventID", &eventID);
		SimulationTree -> SetBranchAddress("trackID", &trackID);
		SimulationTree -> SetBranchAddress("parentID", &parentID);
		SimulationTree -> SetBranchAddress("edep", &edep);
		SimulationTree -> SetBranchAddress("detID", &detID);


	TFile *writeFile = new TFile("dE_E_ThetaRing1.root", "RECREATE");
	
  TTree *dE_E = new TTree("dE_E", "dE of Si vs. E of CsI");
		dE_E -> Branch("pdg", &pdg, "pdg/I");
		dE_E -> Branch("trackID", &trackID, "trackID/I"); 
		dE_E -> Branch("eventID", &eventID, "eventID/I");
		dE_E -> Branch("edep1", &edep1, "edep1/D");
		dE_E -> Branch("edep2", &edep2, "edep2/D");

    int simulationEntries = SimulationTree -> GetEntries();
    cout << "simulation entry number : " << simulationEntries << endl;
    edep1=0;
    edep2=0;

    SimulationTree -> GetEntry(0);
    int trackIDbef = trackID;
    pdg=pID;
  	for (int i = 0; i < simulationEntries; i++) 
    {
        SimulationTree -> GetEntry(i);
        
       // cout << "trackID first : " << trackID << endl; 

        if (trackID == trackIDbef)
        {
          if (parentID==0)
           { pdg = pID;}
          if (detID==1)
					 { edep1 += edep; }
				 	else if (detID==2)
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
