#include "Riostream.h"
#include <iostream>
#include <fstream>
#include "TSystem.h"
#include "TFile.h"
#include "TTree.h"
#include "TF1.h"
#include "TGraph.h"
#include "TMath.h"
#include "var.h"

using std::ofstream;
using namespace std;
TFile *fFile=NULL;
TTree *ftree;
TTree *frtree;
TGraphErrors *fGraph;
TGraphErrors *fGraph_raw;
TGraphErrors *fGraph_fit;
TCanvas *fCvs;

TF1 *FitFunction = new TF1("fFit","[0]*(1/[2]*TMath::Exp(-(x-[1])/[2])+[4]/[3]*TMath::Exp(-(x-[1])/[3])-(1/[2]+[4]/[3])*TMath::Exp(-(x-[1])/[5]))");
TF1 *fFit;

/*class data
{
  public:
  UChar_t fadc_trigger[2];
  UChar_t fadc_tag[6];
  Float_t fadc_FADC[8192];

  Int_t eventID, num_ArrayEvent_SM, num_ArrayEvent, num_Channel;

  static const int MAXNUM=100000;

  Float_t fADC_ch1[MAXNUM];
  Float_t fADC_ch2[MAXNUM];
  Float_t fADC_ch3[MAXNUM];
  Float_t fADC_ch4[MAXNUM];

  Float_t SMfADC_ch1[MAXNUM];
  Float_t SMfADC_ch2[MAXNUM];
  Float_t SMfADC_ch3[MAXNUM];
  Float_t SMfADC_ch4[MAXNUM];

  Float_t err_ch1[MAXNUM];
  Float_t err_ch2[MAXNUM];
  Float_t err_ch3[MAXNUM];
  Float_t err_ch4[MAXNUM];
};
*/
data myData; 

void load(TString file);
void plot(Int_t CH, Int_t eventNum, TCanvas *cvs = NULL);
void plot_fit(Int_t CH, Int_t eventNum, TCanvas *cvs_fit = NULL);
void plot_raw(Int_t CH, Int_t eventNum, TCanvas *cvs_fit = NULL);
void PrepareCanvas(Bool_t reset=0);
void PrepareCanvas_Raw(Bool_t reset=0);
void PrepareCanvas_fit(Bool_t reset=0);

bool treefalse;

void load(TString file)
{
  if(fFile!=NULL)
    delete fFile;

  fFile = new TFile(file);
  
  frtree = (TTree*) fFile -> Get("sortdata");
  ftree = (TTree*) fFile -> Get("finaldata");
  if(frtree ==0 && ftree==0)
  {
    cout << endl;
    cout << "No sortdata tree in root file " << endl;
    cout << "No finaldata tree in root file " << endl;
    cout << endl;
    
    treefalse = false;
    cout << "no final & sort tree ... take raw data file " << endl;
    ftree = (TTree*) fFile -> Get("nfadc400"); 
    ftree -> SetBranchAddress("fadc",myData.fadc_trigger);
  }
  else if(frtree!=0 && ftree!=0) 
  {
    frtree -> SetBranchAddress("eventID",&myData.eventID);
    frtree -> SetBranchAddress("num_ArrayEvent",&myData.num_ArrayEvent);
    frtree -> SetBranchAddress("fADC_ch1",myData.fADC_ch1);
    frtree -> SetBranchAddress("fADC_ch2",myData.fADC_ch2);
    frtree -> SetBranchAddress("fADC_ch3",myData.fADC_ch3);
    frtree -> SetBranchAddress("fADC_ch4",myData.fADC_ch4);
    
    ftree -> SetBranchAddress("eventID",&myData.eventID);
    ftree -> SetBranchAddress("num_ArrayEvent_SM",&myData.num_ArrayEvent_SM);
    ftree -> SetBranchAddress("pedestal",&myData.pedestal);
    ftree -> SetBranchAddress("RMS",&myData.RMS);
    ftree -> SetBranchAddress("SMfADC_ch1",myData.SMfADC_ch1);
    ftree -> SetBranchAddress("SMfADC_ch2",myData.SMfADC_ch2);
    ftree -> SetBranchAddress("SMfADC_ch3",myData.SMfADC_ch3);
    ftree -> SetBranchAddress("SMfADC_ch4",myData.SMfADC_ch4);
    ftree -> SetBranchAddress("err_ch1",myData.err_ch1);
    ftree -> SetBranchAddress("err_ch2",myData.err_ch2);
    ftree -> SetBranchAddress("err_ch3",myData.err_ch3);
    ftree -> SetBranchAddress("err_ch4",myData.err_ch4);
  
    treefalse = true;
  }

  else
  {
    cout << "WRONG ROOT FILE!!! " << endl;
  }

  cout << "LOADING IS OK!!!!" << endl;
}


void plot(Int_t CH, Int_t eventNum, TCanvas *cvs)
{
  

  if(cvs != NULL)
  {
    cvs->cd(2*CH) -> Clear();
    cvs->cd(2*CH);

    fGraph = new TGraphErrors();
  }
  else if (fCvs != NULL)
    PrepareCanvas(1);
  else
    PrepareCanvas();
 
  ftree->GetEntry(0);
  Int_t numData, recordingLength, fillInt;
  if(treefalse == true)
  {
    numData = myData.num_ArrayEvent_SM;
    recordingLength = numData*2.5;
    Float_t draw_FADC[numData];

    ftree->GetEntry(eventNum);
    for(int i=0;i<numData;i++)
    {
      if(CH==1) draw_FADC[i] = myData.SMfADC_ch1[i];
      else if(CH==2) draw_FADC[i] = myData.SMfADC_ch2[i];
      else if(CH==3) draw_FADC[i] = myData.SMfADC_ch3[i];
      else if(CH==4) draw_FADC[i] = myData.SMfADC_ch4[i];
    
      else
      {
        cout << endl;
        cout << " PLOTTING ERROR!! WRONG CHANNEL SELECTION!! " << endl;
        cout << endl;
        break;
      }
      fGraph->SetPoint(i,i,draw_FADC[i]);
    }   
  }

  else if(treefalse == false)
  {
    numData = 4096;
    recordingLength = numData*2.5;
    Float_t draw_FADC[numData];
    
    ftree->GetEntry(eventNum);
    for(int i=(CH-1)*4096; i<CH*4096; i++)
    {
      fillInt = i - (CH-1)*4096;
      draw_FADC[fillInt] = myData.fadc_FADC[i];
      fGraph->SetPoint(fillInt, fillInt, draw_FADC[fillInt]);
    }
  }



/*  for(int i=(CH-1)*4096; i<CH*4096; i++)
  {
    fillInt = i - (CH-1)*4096;
    draw_FADC[fillInt] = plotData.fadc_FADC[i];
    fGraph->SetPoint(fillInt, fillInt, draw_FADC[fillInt]);
  }
*/


    fGraph -> SetTitle(Form("Channel %d - Event %d", CH, eventNum));
    fGraph -> SetLineColor(1);
    fGraph -> SetMarkerColor(1);
    fGraph -> GetHistogram() -> GetXaxis() -> SetTitle(" Time (2.5 ns) ");
    fGraph -> GetHistogram() -> GetXaxis() -> CenterTitle();
    fGraph -> GetHistogram() -> GetXaxis() -> SetLimits(-10, numData +10);
    fGraph -> GetHistogram() -> GetXaxis() -> SetRangeUser(-5, numData+5);
    
    fGraph -> GetHistogram() -> GetYaxis() -> SetTitle(" ADC Channel (A.U.)");
    fGraph -> GetHistogram() -> GetYaxis() -> CenterTitle();
    fGraph -> GetHistogram() -> GetYaxis() -> SetLimits(-10, 1024 +10);
    fGraph -> GetHistogram() -> GetYaxis() -> SetRangeUser(-10, 1024 +5);

    if(cvs != NULL)
    {
      fGraph -> GetHistogram() -> GetXaxis() -> SetLabelSize(0.08);
      fGraph -> GetHistogram() -> GetXaxis() -> SetTitleSize(0.08);
      fGraph -> GetHistogram() -> GetYaxis() -> SetLabelSize(0.08);
      fGraph -> GetHistogram() -> GetYaxis() -> SetTitleSize(0.08);
    }
    
    fGraph->Draw("APL same");
}

void plot_fit(Int_t CH, Int_t eventNum, TCanvas *cvs_fit)
{
  ftree->GetEntry(eventNum);
  if(!treefalse)
  {
    cout << "TREEFALSE !! " << endl;
  }

  if(cvs_fit != NULL)
  {
    cvs_fit->cd(2*CH) -> Clear();
    cvs_fit->cd(2*CH);

    fGraph_fit = new TGraphErrors();
  }
  else if (fCvs != NULL)
    PrepareCanvas_fit(1);
  else
    PrepareCanvas_fit();
  
  Int_t numData = myData.num_ArrayEvent_SM;
  Int_t recordingLength = numData*2.5;
  Float_t draw_FADC[numData];
  Float_t err[numData];
  Int_t fillInt;

  float plot_pedestal;
  int ts=0;
  int te=0;
  int beginfit_val=0;
  int endfit_val=0;

  for(int i=0;i<numData;i++)
  {
    if(CH==1) 
    {
      draw_FADC[i] = myData.SMfADC_ch1[i];
      err[i] = myData.err_ch1[i];
      plot_pedestal = myData.pedestal[0];
    }
    else if(CH==2) 
    {
      draw_FADC[i] = myData.SMfADC_ch2[i];
      err[i] = myData.err_ch2[i];
      plot_pedestal = myData.pedestal[1];
    }
    else if(CH==3) 
    {
      draw_FADC[i] = myData.SMfADC_ch3[i];
      err[i] = myData.err_ch3[i];
      plot_pedestal = myData.pedestal[2];
    }
    else if(CH==4) 
    {
      draw_FADC[i] = myData.SMfADC_ch4[i];
      err[i] = myData.err_ch4[i];
      plot_pedestal = myData.pedestal[3];
    }
    else
    {
      cout << endl;
      cout << " PLOTTING ERROR!! WRONG CHANNEL SELECTION!! " << endl;
      cout << endl;
      break;
    }

    fGraph_fit->SetPoint(i,i, 2*(plot_pedestal-draw_FADC[i]));
    fGraph_fit->SetPointError(i,0, 2*(err[i]));
    if(i>3 && plot_pedestal-draw_FADC[i]>10)
    {
      ts++;
      if(ts==1) beginfit_val = i;
    }
    if(i>numData/2&&plot_pedestal-draw_FADC[i]<10)
    {
      te++;
      if(te==1) endfit_val = i;
    }
  
  }
  

    fGraph_fit -> SetTitle(Form("Channel %d - Event %d", CH, eventNum));
    fGraph_fit -> SetLineColor(1);
    fGraph_fit -> SetMarkerColor(1);
    fGraph_fit -> GetHistogram() -> GetXaxis() -> SetTitle(" Time (2.5 ns) ");
    fGraph_fit -> GetHistogram() -> GetXaxis() -> CenterTitle();
    fGraph_fit -> GetHistogram() -> GetXaxis() -> SetLimits(-10, numData +10);
    fGraph_fit -> GetHistogram() -> GetXaxis() -> SetRangeUser(-5, numData+5);
    
    fGraph_fit -> GetHistogram() -> GetYaxis() -> SetTitle(" ADC Channel (A.U.)");
    fGraph_fit -> GetHistogram() -> GetYaxis() -> CenterTitle();
    fGraph_fit -> GetHistogram() -> GetYaxis() -> SetLimits(-10, 1024 +10);
    fGraph_fit -> GetHistogram() -> GetYaxis() -> SetRangeUser(-10, 1024 +5);

    if(cvs_fit != NULL)
    {
      fGraph_fit -> GetHistogram() -> GetXaxis() -> SetLabelSize(0.08);
      fGraph_fit -> GetHistogram() -> GetXaxis() -> SetTitleSize(0.08);
      fGraph_fit -> GetHistogram() -> GetYaxis() -> SetLabelSize(0.08);
      fGraph_fit -> GetHistogram() -> GetYaxis() -> SetTitleSize(0.08);
    }

    gStyle->SetOptFit(11111111);

    fFit -> SetFunction(FitFunction);

    if(beginfit_val==0) 
    {
      cout << "ERROR!!!! ::::  beginning of the fitting is 0 ::::: Something strange in the waveform or pedestal " << endl;
    }
   
    FitFunction -> SetRange(beginfit_val-1.8, endfit_val+10.25);
    FitFunction -> SetParName(0,"A");
    FitFunction -> SetParName(1,"t_{0}");
    FitFunction -> SetParName(2,"#tau_{f}");
    FitFunction -> SetParName(3,"#tau_{s}");
    FitFunction -> SetParName(4,"R");
    FitFunction -> SetParName(5,"#tau_{r}");

    FitFunction -> SetParameters(485,11,12.06,82.04,4.3355,0.6038);
    FitFunction -> SetParLimits(0, 200,10000000);
    FitFunction -> SetParLimits(1,  5,50);
    FitFunction -> SetParLimits(2,  0.1,7100);
    FitFunction -> SetParLimits(3,  0.,1403);
    FitFunction -> SetParLimits(4, 0.1, 40.);
    FitFunction -> SetParLimits(5, 0.1,80);

    fGraph_fit -> Fit("fFit","REM");
    cout << "beginfit       : " << beginfit_val << endl; 
    cout << "chisquare prob : " << (double)FitFunction->GetProb() << endl;
    //cout << "chisquare prob : " << (double)FitFunction->GetProb()*TMath::Power(10000000,10) << endl;

    fGraph_fit->Draw("APL same");

}

void plot_raw(Int_t CH, Int_t eventNum, TCanvas *cvs)
{
  frtree->GetEntry(eventNum);
  
  if(!treefalse)
  {
    cout << "TREEFALSE !! " << endl;
  }

  if(cvs != NULL)
  {
    cvs->cd(2*CH) -> Clear();
    cvs->cd(2*CH);

    fGraph = new TGraphErrors();
  }
  else if (fCvs != NULL)
    PrepareCanvas_Raw(1);
  else
    PrepareCanvas_Raw();
  
  Int_t numData = myData.num_ArrayEvent;
  Int_t recordingLength = numData*2.5;
  Float_t draw_FADC[numData];
  Int_t fillInt;

  for(int i=0;i<numData;i++)
  {
    if(CH==1) draw_FADC[i] = myData.fADC_ch1[i];
    else if(CH==2) draw_FADC[i] = myData.fADC_ch2[i];
    else if(CH==3) draw_FADC[i] = myData.fADC_ch3[i];
    else if(CH==4) draw_FADC[i] = myData.fADC_ch4[i];
  
    else
    {
      cout << endl;
      cout << " PLOTTING ERROR!! WRONG CHANNEL SELECTION!! " << endl;
      cout << endl;
    }

    fGraph_raw->SetPoint(i,i,draw_FADC[i]);
  }

/*  for(int i=(CH-1)*4096; i<CH*4096; i++)
  {
    fillInt = i - (CH-1)*4096;
    draw_FADC[fillInt] = plotData.fadc_FADC[i];
    fGraph->SetPoint(fillInt, fillInt, draw_FADC[fillInt]);
  }
  */


    fGraph_raw -> SetTitle(Form("Channel %d - Event %d", CH, eventNum));
    fGraph_raw -> SetLineColor(1);
    fGraph_raw -> SetMarkerColor(1);
    fGraph_raw -> GetHistogram() -> GetXaxis() -> SetTitle(" Time (2.5 ns) ");
    fGraph_raw -> GetHistogram() -> GetXaxis() -> CenterTitle();
    fGraph_raw -> GetHistogram() -> GetXaxis() -> SetLimits(-10, numData +10);
    fGraph_raw -> GetHistogram() -> GetXaxis() -> SetRangeUser(-5, numData+5);
    
    fGraph_raw -> GetHistogram() -> GetYaxis() -> SetTitle(" ADC Channel (A.U.)");
    fGraph_raw -> GetHistogram() -> GetYaxis() -> CenterTitle();
    fGraph_raw -> GetHistogram() -> GetYaxis() -> SetLimits(-10, 1024 +10);
    fGraph_raw -> GetHistogram() -> GetYaxis() -> SetRangeUser(-10, 1024 +5);

    if(cvs != NULL)
    {
      fGraph_raw -> GetHistogram() -> GetXaxis() -> SetLabelSize(0.08);
      fGraph_raw -> GetHistogram() -> GetXaxis() -> SetTitleSize(0.08);
      fGraph_raw -> GetHistogram() -> GetYaxis() -> SetLabelSize(0.08);
      fGraph_raw -> GetHistogram() -> GetYaxis() -> SetTitleSize(0.08);
    }

    fGraph_raw->Draw("APL same");

}

void PrepareCanvas(Bool_t reset)
{
  if(reset)
  {
    delete fGraph;
    fGraph = new TGraphErrors();
  }
  else
  {
    gStyle -> SetPadLeftMargin(0.09);
    gStyle -> SetPadRightMargin(0.03);
    gStyle -> SetPadBottomMargin(0.1);
    gStyle -> SetTitleSize(0.05, "x");
    gStyle -> SetTitleOffset(1.00, "x");
    gStyle -> SetTitleSize(0.05, "y");
    gStyle -> SetTitleOffset(0.80, "y");
    fCvs = new TCanvas("fCvs","",800,450);
    fGraph = new TGraphErrors();
  }
}

void PrepareCanvas_Raw(Bool_t reset)
{
  if(reset)
  {
    delete fGraph_raw;
    fGraph_raw = new TGraphErrors();
  }
  else
  {
    gStyle -> SetPadLeftMargin(0.09);
    gStyle -> SetPadRightMargin(0.03);
    gStyle -> SetPadBottomMargin(0.1);
    gStyle -> SetTitleSize(0.05, "x");
    gStyle -> SetTitleOffset(1.00, "x");
    gStyle -> SetTitleSize(0.05, "y");
    gStyle -> SetTitleOffset(0.80, "y");
    fCvs = new TCanvas("fCvs","",800,450);
    fGraph_raw = new TGraphErrors();
  }
}

void PrepareCanvas_fit(Bool_t reset)
{
  if(reset)
  {
    delete fGraph_fit;
    fGraph_fit = new TGraphErrors();
    fFit = new TF1();
  }
  else
  {
    gStyle -> SetPadLeftMargin(0.09);
    gStyle -> SetPadRightMargin(0.03);
    gStyle -> SetPadBottomMargin(0.1);
    gStyle -> SetTitleSize(0.05, "x");
    gStyle -> SetTitleOffset(1.00, "x");
    gStyle -> SetTitleSize(0.05, "y");
    gStyle -> SetTitleOffset(0.80, "y");
    fCvs = new TCanvas("fCvs","",800,450);
    fGraph_fit = new TGraphErrors();
    fFit = new TF1();
  }
}

