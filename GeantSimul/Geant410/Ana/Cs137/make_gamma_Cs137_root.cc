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

void make_gamma_Cs137_root(double CsIZ=47, double Resol = 3)
{
	TFile *openFile = new TFile(Form("./rawData_lampslow_%.f.root",Resol), "READ");

	Int_t eventID, trackID, pID, pdg, parentID, sEventID, sTrackID, isSiCsI, detID;
	Double_t hitTime, energyInit, edep, edep1, x_pre, y_pre, z_pre, z_primvert, z_secvert, Depth;

	TTree *SimulationTree = (TTree *) openFile -> Get("data"); 
		SimulationTree -> SetBranchAddress("pID", &pID);
		SimulationTree -> SetBranchAddress("eventID", &eventID);
		SimulationTree -> SetBranchAddress("trackID", &trackID);
		SimulationTree -> SetBranchAddress("parentID", &parentID);
		SimulationTree -> SetBranchAddress("x_pre", &x_pre);
		SimulationTree -> SetBranchAddress("y_pre", &y_pre);
		SimulationTree -> SetBranchAddress("z_pre", &z_pre);
		SimulationTree -> SetBranchAddress("edep", &edep);
		SimulationTree -> SetBranchAddress("detID", &detID);


	TFile *writeFile = new TFile(Form("./Gamma_Cs137_1M_CsI%.fmm_res%.f.root",CsIZ,Resol), "RECREATE");
	
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

          if (detID==11)
					 { 
             edep1 = edep; 
             Depth = z_pre-400.11;
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
          if (detID==11)
					 { 
             edep1 += edep;
           }
        }
        
        if (trackID!=trackIDbef)
        {
            SimulationTree -> GetEntry(i-1);
            if(edep1!=0) NRecon -> Fill();
            edep1 = 0;
            SimulationTree -> GetEntry(i);
            if (detID==11)
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
	
}
