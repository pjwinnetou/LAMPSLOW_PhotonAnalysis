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

int make_dE_E_root()
{
	TFile *openFile = new TFile("../rawData_lampslow.root", "READ");

	Int_t eventID, trackID, pID, pdg, parentID, sEventID, sTrackID, isSiCsI, detID;
	Double_t hitTime, energyInit, edep, edep1, edep2, edep3;

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
		dE_E -> Branch("edep3", &edep3, "edep3/D");

  TCanvas *c1=new TCanvas("c1","",700,700);
  TH2F *h_dE_E = new TH2F("h_dE_E","E1 vs E_{Total} (E1+E2);E_{Total};E1",1000,0,500,250,0,20);
  TH2F *h_dE_E_veto = new TH2F("h_dE_E_veto","E1 vs E_{Total} (E1+E2) with veto;E_{Total};E1",1000,0,500,250,0,20);
    int simulationEntries = SimulationTree -> GetEntries();
//    cout << "simulation entry number : " << simulationEntries << endl;
    edep1=0;
    edep2=0;
    edep3=0;
    SimulationTree -> GetEntry(0);
    int trackIDbef = trackID;
    pdg=pID;
    int ccc = 1;
  	for (int i = 0; i < simulationEntries; i++) 
    {
        SimulationTree -> GetEntry(i);
        
       // cout << "trackID first : " << trackID << endl; 

        if (trackID == trackIDbef)
        {
          if (parentID==0)
           { pdg = pID;}
          if (detID==7)
					 { edep1 += edep; }
				 	else if (detID==11)
					 { edep2 += edep; }
          else if (detID==5) edep3+=edep;
        }
        
        if (trackID!=trackIDbef)
        {
            ccc++;
            SimulationTree -> GetEntry(i-1);
             if(edep1!=0)
             {  
              dE_E -> Fill();
             }
            edep1 = 0;
            edep2 = 0;
            edep3=0;
            SimulationTree -> GetEntry(i);
            if (detID==7)
              { edep1 += edep;}
            else if (detID==11)
              { edep2 += edep;}
            else if (detID==5)
              { edep3 += edep;}
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

  c1->Divide(2,1);
  c1->cd(1);
  dE_E->Draw("edep1:edep1+edep2>>h_dE_E","edep1>0","colz");
  c1->cd(2);
  dE_E->Draw("edep1:edep1+edep2>>h_dE_E_veto","edep1>0&&edep3==0&&edep2>0","colz");

  h_dE_E->Write();
  h_dE_E_veto->Write();
  double reconstN = dE_E -> GetEntries();
  cout << ccc << endl;
  cout << "Reconstructed # of particles : " << reconstN/2010. << endl;
//  delete dE_E;
//	delete writeFile;

	return 0;
}
