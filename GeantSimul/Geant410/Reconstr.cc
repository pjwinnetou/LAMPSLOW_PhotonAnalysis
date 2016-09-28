#include <TROOT.h>
#include <TSystem.h>
#include <Riostream.h>
#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TMath.h>
#include <TLegend.h>
#include <TStyle.h>
#include <TChain.h>
#include <fstream>
#include <iostream>
using namespace std;

void Reconstr()
{

  gStyle -> SetOptStat(0);
  gStyle -> SetTitleYOffset(1.75);
  gStyle -> SetTitleXOffset(1.35);
  gStyle -> SetTitleSize(0.04,"xy");
  gStyle -> SetPadLeftMargin(0.16);
  gStyle -> SetPadRightMargin(0.05);
  gStyle -> SetPadTopMargin(0.12);
  gStyle -> SetPadBottomMargin(0.15);

  TFile *openFile = new TFile("./rawData_lampslow.root", "READ");
	
  Int_t eventID, trackID, pID, pdg, parentID, sEventID, sTrackID, isSiCsI, detID, trackIDbef,trackSaveID;
	Double_t hitTime, EK,Angle, time, energyInit, edep, edeposit, edep1, edep2, edep3, etot,x, y, z, pX_pre,pY_pre,pZ_pre,z_csi, z_scint, ScatteringAngle, pT, pTot,CsIDepth, ScintDepth;
  Double_t neutronmass = 939.5;
	
  Int_t NRecon=1;
  
  TTree *SimulationTree = (TTree *) openFile -> Get("data"); 
		SimulationTree -> SetBranchAddress("pID", &pID);
		SimulationTree -> SetBranchAddress("eventID", &eventID);
		SimulationTree -> SetBranchAddress("trackID", &trackID);
		SimulationTree -> SetBranchAddress("parentID", &parentID);
		SimulationTree -> SetBranchAddress("time", &time);
		SimulationTree -> SetBranchAddress("edep", &edep);
		SimulationTree -> SetBranchAddress("detID", &detID);
	



    //************Fill Type1************** 
    SimulationTree -> GetEntry(0);
    const int Entries = SimulationTree -> GetEntries();
    trackIDbef=trackID;
  	for (int i = 0; i < Entries; i++) 
    {
        SimulationTree -> GetEntry(i);

        if(trackID==trackIDbef)
        {
        }

        else if(trackID!=trackIDbef)
        {
         NRecon++;
        }
       trackIDbef = trackID;   
    }
  

  //#################Cout######################
  
  cout << "***Number of Reconstructed particle***" << " :  " << NRecon << endl;
  cout << endl;
  cout << endl;
}  

