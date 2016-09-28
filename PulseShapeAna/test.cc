#include <iostream>
#include <fstream>
#include <sstream>

#include "TTree.h"
#include "TFile.h"
#include "TMath.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TStyle.h"

using namespace std;

void test()
{
  TFile *f = new TFile("CH1_100.root","READ");
  TTree *t = (TTree*) f->Get("nfadc400");

  TBranch *fadc; 
  float FADC[10000];
  bool trigger[10];
  bool tag[10];
  
  float newFADC[10000];
  TLeaf *fadcleaf;

  fadc = t->GetBranch("fadc");
  fadcleaf = fadc->GetLeaf("FADC");

  TH2D *h1 = new TH2D("h1","",8192,0,8192,100,800,900);
  TCanvas *c1 = new TCanvas("c1","",700,700);

  TGraph *fgraph = new TGraph();


  const int numEvents = fadc -> GetEntries();

  for(int i=0; i<numEvents; i++)
  {
    t->GetEntry(i);

    for(int j=0; j<4096; j++)
    {
      newFADC[j] = fadcleaf->GetValue(j);
  
      if(i==1)
      {
        fgraph->SetPoint(j,j*2.5,newFADC[j]);
      }
    }
  }

  c1->cd();
  fgraph->Draw();
}
