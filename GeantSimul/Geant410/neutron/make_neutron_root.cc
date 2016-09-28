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
#include <TStyle.h>
#include <TChain.h>
#include <fstream>
#include <iostream>
using namespace std;

void make_neutron_root()
{

  gStyle -> SetOptStat(0);
  gStyle -> SetTitleYOffset(1.75);
  gStyle -> SetTitleXOffset(1.35);
  gStyle -> SetTitleSize(0.04,"xy");
  gStyle -> SetPadLeftMargin(0.16);
  gStyle -> SetPadRightMargin(0.05);
  gStyle -> SetPadTopMargin(0.12);
  gStyle -> SetPadBottomMargin(0.15);
	TFile *openFile = new TFile("./../rawData_lampslow.root", "READ");

	Int_t eventID, trackID, pID, pdg, parentID, sEventID, sTrackID, isSiCsI, detID;
	Double_t hitTime, energyInit, edep, edep1, edep2, edep3, etot,x, y, z, z_csi, z_scint, r_transverse, ScatteringAngle, CsIDepth, ScintDepth;

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


	TFile *writeFile = new TFile("./Neutron_test_5MeV_10000event.root", "RECREATE");
	
  TTree *dE_E = new TTree("Hit", "Neutron Hit");
		dE_E -> Branch("pdg", &pdg, "pdg/I");
		dE_E -> Branch("trackID", &trackID, "trackID/I");
		dE_E -> Branch("CsIDepth", &CsIDepth, "CsIDepth/D");
		dE_E -> Branch("ScintDepth", &ScintDepth, "ScintDepth/D");
		dE_E -> Branch("edep1", &edep1, "edep1/D");
		dE_E -> Branch("edep2", &edep2, "edep2/D");
		dE_E -> Branch("edep3", &edep3, "edep3/D");

    int simulationEntries = SimulationTree -> GetEntries();
    cout << "simulation entry number : " << simulationEntries << endl;
    edep1=0;
    edep2=0;
    edep3=0;
    CsIDepth=0;
    ScintDepth=0;
    
  	for (int i = 0; i < simulationEntries; i++) 
    {
        SimulationTree -> GetEntry(i);
        pdg=pID; 
       // cout << "trackID first : " << trackID << endl; 

          if (detID==7)
					 { edep1 = edep; }
				 	else if (detID==8)
					 { 
             edep2 = edep; 
             CsIDepth = z-400.11;
           }
          else if (detID==9)
          { 
            edep3 = edep;
            ScintDepth = z-450.21;
          }
        
          dE_E -> Fill();
    }
  
  writeFile -> cd();
	dE_E -> Write();
	
	
  TTree *NRecon = new TTree("Recon", "");
		NRecon-> Branch("trackID", &trackID, "trackID/I");
		NRecon-> Branch("edep1", &edep1, "edep1/D");
		NRecon-> Branch("edep2", &edep2, "edep2/D");
  	NRecon-> Branch("edep3", &edep3, "edep3/D");
  	NRecon-> Branch("etot", &etot, "etot/D");

//    cout << "simulation entry number : " << simulationEntries << endl;
    edep1=0;
    edep2=0;
    edep3=0;
  
    SimulationTree->GetEntry(0);
    double trackIDbef=trackID;

    for (int i = 0; i < simulationEntries; i++) 
    {
        SimulationTree -> GetEntry(i);
        
//        cout << "trackID first : " << i << " : " << trackID << endl; 
//        cout << "trackIDbef first : " << i << " : "  << trackIDbef << endl; 

        if (trackID == trackIDbef)
        {
          if (detID==7)
					 { edep1+= edep; }
				 	else if (detID==8)
					 { 
             edep2+= edep; 
    //         CsIDepth = z-400.11;
           }
          else if (detID==9)
          { 
            edep3+= edep;
      //      ScintDepth = z-450.21;
          }
//            cout << endl;
//            cout << "edep3 : " << edep3 << "   compare with edep : " << edep << endl;
        }
        
        
        if (trackID!=trackIDbef)
        {
            SimulationTree -> GetEntry(i-1);
//            cout << "Different trackID : " << trackID << endl;
            etot=edep2+edep3;
            NRecon -> Fill();
            edep1 = 0;
            edep2 = 0;
            edep3 = 0;
            SimulationTree -> GetEntry(i);
            edep3 += edep;
//            cout << "After Fill edep3 : " << edep3 << "compare : " << edep << endl;
        }
        
        if (i == simulationEntries -1)
        {
          etot=edep2+edep3;
          NRecon -> Fill();
        }
  
          trackIDbef = trackID;
    }


  writeFile -> cd();
	NRecon -> Write();
	
  const int NumOfEvent = NRecon->GetEntries();
  const int NumOfEventPure = dE_E->GetEntries();
  int nbin_scint = 200;
  double xlow_scint = 0;
  double xup_scint = 20;
  double weight = (nbin_scint/(xup_scint-xlow_scint))/NumOfEvent;

  int nbin_csi = 200;
  double xlow_csi = 0;
  double xup_csi = 20;

  double xlow_tot = 0;
  double xup_tot = 20;
  
  TCanvas *cvs1 = new TCanvas("edep1","",700,700);
  TCanvas *cvs2 = new TCanvas("edep2","",700,700);
  TCanvas *cvs3 = new TCanvas("edep3","",700,700);
  TCanvas *cvs4 = new TCanvas("edep4","",700,700);
  TH1D *hist0 = new TH1D("hist_edep_Silicon","E_{dep} - Silicon; E_{dep} (MeV);Counts",150,0,5);
  TH1D *hist1 = new TH1D("hist_edep_Scint","E_{dep} - Scint; E_{dep} (MeV);Counts",nbin_scint,xlow_scint,xup_scint);
  TH1D *hist2 = new TH1D("hist_edep_CsI","E_{dep} - CsI; E_{dep} (MeV);Counts",nbin_csi,xlow_csi,xup_csi);
  TH1D *hist3 = new TH1D("hist_edep_Scint_pure","E_{dep}; E_{dep} (MeV);Counts",nbin_scint,xlow_scint,xup_scint);
  TH1D *hist4 = new TH1D("hist_etot","E_{tot}; E_{tot}=E_{csi}+E_{scint} (MeV);Counts",nbin_scint,xlow_scint,xup_scint);
  TH2D *hist_neutron_dE_E = new TH2D("hist_neutron_dE_E","dE vs E; E (MeV);dE (MeV)",400,0,20,100,0,5);

  hist0 -> SetMinimum(0.11);
  hist0 -> GetXaxis() -> CenterTitle(); 
  hist0 -> GetYaxis() -> CenterTitle(); 

  hist1 -> SetMinimum(0.11);
  hist1 -> GetXaxis() -> CenterTitle(); 
  hist1 -> GetYaxis() -> CenterTitle(); 

  hist2 -> SetMinimum(0.11);
  hist2 -> GetXaxis() -> CenterTitle(); 
  hist2 -> GetYaxis() -> CenterTitle(); 
  
  hist3 -> SetMinimum(0);
  hist3 -> GetXaxis() -> CenterTitle(); 
  hist3 -> GetYaxis() -> CenterTitle(); 
  
  hist4 -> SetMinimum(0.11);
  hist4 -> GetXaxis() -> CenterTitle(); 
  hist4 -> GetYaxis() -> CenterTitle(); 

  hist_neutron_dE_E -> GetXaxis() -> CenterTitle(); 
  hist_neutron_dE_E -> GetYaxis() -> CenterTitle(); 


  Int_t ReconNum = NRecon->GetEntries();
  for(int i=0;i<ReconNum;i++)
  {
    NRecon->GetEntry(i);
    double etot_neutronSiCsI = edep1+edep2;
    hist_neutron_dE_E->Fill(etot_neutronSiCsI,edep1);
  }
  
  hist_neutron_dE_E -> Draw("colz");

  cvs1 -> cd();
  cvs1->SetLogy();
  NRecon -> Draw("edep2>>hist_edep_CsI");
  cvs2-> cd();
  cvs2->SetLogy();
  NRecon -> Draw("edep3>>hist_edep_Scint");
  cvs3-> cd();
  cvs3->SetLogy();
  NRecon -> Draw("edep1>>hist_edep_Silicon","edep1!=0");
  cvs4 -> cd();
  cvs4->SetLogy();
//  NRecon -> SetWeight(weight);
//  cvs4 -> cd();
  NRecon -> Draw("etot>>hist_etot");
//  dE_E -> Draw("edep3>>hist_edep_Scint_pure");

  hist0->Write();
  hist1->Write();
  hist2->Write();
  hist3->Write();
  hist4->Write();
  hist_neutron_dE_E -> Write();
  
  double hist1Max = hist1->GetMaximum();
  double hist3Max = hist3->GetMaximum();
  double ratio = hist1Max/hist3Max*100.;

  cout << "max : " << hist1Max << endl;
  cout << "max : " << hist3Max << endl;
  cout << "ratio : " << ratio << endl;

  hist3->Draw();
  hist2->Draw();
  hist1->Draw();
  hist4->Draw();
//  hist1 -> SetLineColor(2);
  hist3 -> SetLineColor(1);

//  hist1 -> SetLineStyle(2);

  hist1 -> SetLineWidth(2.85);
  hist2 -> SetLineWidth(2.85);
  hist3 -> SetLineWidth(2.85);
  hist4 -> SetLineWidth(2.85);

//  hist1 -> SetAxisRange(0,10,"Y");
/*
  TLegend *legend = new TLegend(0.7,0.7,0.9,0.8);
  legend->SetTextFont(40);
  legend->SetTextSize(0.02);
  legend->SetFillColor(0);
  legend->AddEntry(hist3, "Without SiCsI", "l");
  legend->AddEntry(hist1, "With SiCsI", "l");
  legend->Draw();
  delete dE_E;
  delete NRecon;
	delete writeFile;

	return 0;
  */
}
