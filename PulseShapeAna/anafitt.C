#include <TTree.h>
#include <TFile.h>
#include <TPad.h>
#include <TMath.h>
#include <TH1D.h>
#include <TH2F.h>
#include <TF1.h>
#include <TLegend.h>
#include <TStyle.h>
#include <TROOT.h>
#include <TSystem.h>
#include <TCanvas.h>
#include <TChain.h>
#include <fstream>
#include <iostream>
#include <TGraphErrors.h>
#include <ctime>

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

class fdata
{
  public:
  UChar_t fadc_trigger[2];
  UChar_t fadc_tag[6];
  Float_t fadc_FADC[8192];

  Int_t eventID, RL, num_ArrayEvent_SM, num_ArrayEvent, num_Channel;

  static const int MAXNUM=100000;

  Double_t RMS[4];
  Double_t pedestal[4];

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


void anafitt( int nevt_min = 0, int nevt_max = 10, int chselect = 1)
{
  
  gStyle->SetPalette(1);
  gStyle->SetOptFit(kTRUE);
  gStyle->SetOptStat(0);
  gStyle->SetTextSize(0.01908148);
  gStyle->SetTitleFontSize(0.03);
  gStyle->SetTitleXSize(0.04);
  gStyle->SetTitleXOffset(1.3);
  gStyle->SetTitleYSize(0.04);
  gStyle->SetTitleYOffset(2.2);
  gStyle->SetPadBottomMargin(0.18);
  gStyle->SetPadTopMargin(0.05);
  gStyle->SetPadLeftMargin(0.2);
  gStyle->SetPadRightMargin(0.1);

  data md;
 
  TString inputfile = "noise_2100_60_100000_Cs_32_ss.root";  
  //TString inputfile = "Cs137_2100_60_100000_1_32_ss.root";  
  TString outputfile = inputfile;
  outputfile = "fitted_" + inputfile;
   

  TFile *openFile = new TFile(Form("Ana/ssData/%s",inputfile.Data()),"READ");
  TFile *writeFile = new TFile(Form("%s",outputfile.Data()),"recreate");
  
  TTree *finaltr = (TTree*) openFile -> Get("finaldata");
  TTree *sorttr = (TTree*) openFile -> Get("sortdata"); 

  finaltr->SetBranchAddress("eventID",&md.eventID);
  finaltr->SetBranchAddress("num_ArrayEvent_SM",&md.num_ArrayEvent_SM);
  finaltr->SetBranchAddress("SMfADC_ch1",md.SMfADC_ch1);
  finaltr->SetBranchAddress("SMfADC_ch2",md.SMfADC_ch2);
  finaltr->SetBranchAddress("SMfADC_ch3",md.SMfADC_ch3);
  finaltr->SetBranchAddress("SMfADC_ch4",md.SMfADC_ch4);
  finaltr->SetBranchAddress("err_ch1",md.err_ch1);
  finaltr->SetBranchAddress("err_ch2",md.err_ch2);
  finaltr->SetBranchAddress("err_ch3",md.err_ch3);
  finaltr->SetBranchAddress("err_ch4",md.err_ch4);
  finaltr->SetBranchAddress("pedestal",md.pedestal);
  finaltr->SetBranchAddress("RMS",md.RMS);
  finaltr->SetBranchAddress("RL",&md.RL);

  sorttr->SetBranchAddress("eventID",&md.eventID);
  sorttr->SetBranchAddress("num_ArrayEvent",&md.num_ArrayEvent);
  sorttr->SetBranchAddress("fADC_ch1",md.fADC_ch1);
  sorttr->SetBranchAddress("fADC_ch2",md.fADC_ch2);
  sorttr->SetBranchAddress("fADC_ch3",md.fADC_ch3);
  sorttr->SetBranchAddress("fADC_ch4",md.fADC_ch4);
  

  Float_t PSum = 0.;
  Float_t PInt = 0.;
  Float_t Pfheight1[4], Pfheight_x1[4], Pheight1[4], Ptail1[4]; 
  Float_t chisq1[4], chisqprob1[4], NDF1[4], tau_r1[4], tau_s1[4], tau_f1[4], ratio1[4], t01[4], A1[4];
  Float_t IntStartVal1[4], IntEndVal1[4], TailIntStart1[4];
  Int_t Pheight_x1[4], Ptail_x1[4];
  Float_t Pfheight, Pfheight_x, Pheight, Ptail; 
  Float_t chisq, chisqprob, NDF, tau_r, tau_s, tau_f, ratio, t0, A;
  Float_t IntStartVal, IntEndVal, TailIntStart;
  Int_t Pheight_x, Ptail_x;

  TTree *writeTree = new TTree("tr","");
  writeTree->Branch("eventID",&md.eventID,"eventID/I");
  writeTree->Branch("pedestal",md.pedestal,"pedestal/D");
  writeTree->Branch("RMS",md.RMS,"RMS/D");
  writeTree->Branch("Psum",&PSum,"Psum/F");
  writeTree->Branch("Pint",&PInt,"Pint/F");
  writeTree->Branch("Pfheight",&Pfheight,"Pfheight/F");
  writeTree->Branch("Pfheight_x",&Pfheight_x,"Pfheight_x/F");
  writeTree->Branch("Pheight",&Pheight,"Pheight/F");
  writeTree->Branch("Pheight_x",&Pheight_x,"Pheight_x/I");
  writeTree->Branch("Ptail",&Ptail,"Ptail/F");
  writeTree->Branch("chisq",&chisq,"chisq/F");
  writeTree->Branch("chisqprob",&chisqprob,"chisqprob/F");
  writeTree->Branch("NDF",&NDF,"NDF/F");
  writeTree->Branch("A",&A,"A/F");
  writeTree->Branch("tau_r",&tau_r,"tau_r/F");
  writeTree->Branch("tau_s",&tau_s,"tau_s/F");
  writeTree->Branch("tau_f",&tau_f,"tau_f/F");
  writeTree->Branch("ratio",&ratio,"ratio/F");
  writeTree->Branch("t0",&t0,"t0/F");
  writeTree->Branch("IntStartVal",&IntStartVal,"IntStartVal/F");
  writeTree->Branch("IntEndVal",&IntEndVal,"IntEndVal/F");


  
  Int_t beginfit_val = 0;
  Int_t endfit_val = 0;
  
  Double_t fFitrange_start,fFitrange_end;

  int ts=0;
  int te=0;
  int ich = chselect;


  finaltr->GetEntry(0);
  Int_t RecordLength = (md.RL*128/(md.num_ArrayEvent_SM))*2.5;
  Int_t numData = md.num_ArrayEvent_SM;
  Float_t draw_FADC[numData];
  Float_t err[numData];
  Int_t fillInt;
  Float_t plot_pedestal;
  Float_t MAXFADC;

  int count = 0;

  // event loop start
  if(nevt_max == -1) nevt_max = finaltr->GetEntries();
  

  for(int i=nevt_min; i<nevt_max; ++i)
  {
    
    if(count%1000==0) cout << " reading eventID... : " << count << " / " << nevt_max << " (" << (int)(100.*count/nevt_max) << "%)" << endl;
  
    finaltr->GetEntry(i);
    
    TF1* FitFunction = new TF1("fFit","[0]*(1/[2]*TMath::Exp(-(x-[1])/[2])+[4]/[3]*TMath::Exp(-(x-[1])/[3])-(1/[2]+[4]/[3])*TMath::Exp(-(x-[1])/[5]))");
    TGraphErrors *fGraph = new TGraphErrors();

    // channel loop start 
    for(int j=0;j<md.num_ArrayEvent_SM;j++)
    {
      if(ich==1)
      {
        draw_FADC[j] = md.SMfADC_ch1[j];
        err[j] = md.err_ch1[j];
        plot_pedestal = md.pedestal[0];
      }
      else if(ich==2)
      {
        draw_FADC[j] = md.SMfADC_ch2[j];
        err[j] = md.err_ch2[j];
        plot_pedestal = md.pedestal[1];
      }
      else if(ich==3)
      {
        draw_FADC[j] = md.SMfADC_ch3[j];
        err[j] = md.err_ch3[j];
        plot_pedestal = md.pedestal[2];
      }
      else if(ich==4)
      {
        draw_FADC[j] = md.SMfADC_ch4[j];
        err[j] = md.err_ch4[j];
        plot_pedestal = md.pedestal[3];
      }
      else
      {
        cout << endl;
        cout << " PLOTTING ERROR!! WRONG CHANNEL SELECTION!! " << endl;
        cout << endl;
        break;
      }

      fGraph -> SetPoint(j,j,2*(plot_pedestal-draw_FADC[j]));
      fGraph -> SetPointError(j,0,2*(err[j]));
      
      if(j>3 && (plot_pedestal - draw_FADC[j])>10)
      {
        ts++;
        if(ts==1) beginfit_val = j;
      }
      if(j>numData/2 && (plot_pedestal - draw_FADC[j])<10)
      {
        te++;
        if(te==1) endfit_val = j;
      }
      
      if(j==0) 
      {
        MAXFADC = draw_FADC[0];
        Pheight = plot_pedestal - draw_FADC[0];
        Pheight_x = 0;
      }

      if(MAXFADC > draw_FADC[j]) 
      {
        Pheight = plot_pedestal-draw_FADC[j];
        Pheight_x = j;
      }
      
      MAXFADC = draw_FADC[j];

    }
      
    fGraph -> SetTitle(Form("Channel %d - Event %d", ich, i));
    fGraph -> SetLineColor(1);
    fGraph -> SetMarkerColor(1);
    fGraph -> GetHistogram() -> GetXaxis() -> SetTitle(Form("Time (%d ns) ",RecordLength));
    fGraph -> GetHistogram() -> GetXaxis() -> CenterTitle();
    fGraph -> GetHistogram() -> GetXaxis() -> SetLimits(-10, numData +10);
    fGraph -> GetHistogram() -> GetXaxis() -> CenterTitle();
  
    fGraph -> GetHistogram() -> GetYaxis() -> SetTitle(" ADC Channel (A.U.)");
    fGraph -> GetHistogram() -> GetYaxis() -> CenterTitle();
    fGraph -> GetHistogram() -> GetYaxis() -> SetLimits(-10, 1024+10);
    fGraph -> GetHistogram() -> GetYaxis() -> SetRangeUser(-10, 1024+5);
    

    fGraph -> GetHistogram() -> GetXaxis() -> SetLabelSize(0.08);
    fGraph -> GetHistogram() -> GetXaxis() -> SetTitleSize(0.08);
    fGraph -> GetHistogram() -> GetYaxis() -> SetLabelSize(0.08);
    fGraph -> GetHistogram() -> GetYaxis() -> SetTitleSize(0.08);
    gStyle -> SetOptFit(1111111);
    
    
    if(beginfit_val == 0)
    {
      cout << "ERROR!!!! ::::  beginning of the fitting is 0 ::::: Something strange in the waveform or pedestal " << endl;
    }


   // fFitrange_start = beginfit_val - (double)10./RecordLength;
   // fFitrange_end = endfit_val + (double)10./RecordLength;
    fFitrange_start = beginfit_val - 1.75;
    fFitrange_end = endfit_val + 10.25;
    FitFunction -> SetRange(beginfit_val-1.8, endfit_val+10.25);
    FitFunction -> SetParName(0,"A");
    FitFunction -> SetParName(1,"t_{0}");
    FitFunction -> SetParName(2,"#tau_{f}");
    FitFunction -> SetParName(3,"#tau_{s}");
    FitFunction -> SetParName(4,"R");
    FitFunction -> SetParName(5,"#tau_{r}");

    FitFunction -> SetParameters(485,11,12.06,82.04,4.3355,0.6038);
    FitFunction -> SetParLimits(0, 0.,10000000);
    FitFunction -> SetParLimits(1,  3,60);
    FitFunction -> SetParLimits(2,  0.,7100);
    FitFunction -> SetParLimits(3,  0.,2803);
    FitFunction -> SetParLimits(4, 0., 60.);
    FitFunction -> SetParLimits(5, 0.,150);

    /*
    FitFunction -> SetRange(fFitrange_start, fFitrange_end);
    FitFunction -> SetParName(0,"A");
    FitFunction -> SetParName(1,"t_{0}");
    FitFunction -> SetParName(2,"#tau_{f}");
    FitFunction -> SetParName(3,"#tau_{s}");
    FitFunction -> SetParName(4,"R");
    FitFunction -> SetParName(5,"#tau_{r}");

    FitFunction -> SetParameters(600,14,300,1290,0.7,16);
    FitFunction -> SetParLimits(0, 200,10000000);
    FitFunction -> SetParLimits(1,  5,50);
    FitFunction -> SetParLimits(2,  5,1100);
    FitFunction -> SetParLimits(3,  440,6030);
    FitFunction -> SetParLimits(4, 0.1, 0.97);
    FitFunction -> SetParLimits(5, 0.4,80);
  */
    gROOT -> SetBatch(1);
    gROOT -> ProcessLine("gErrorIgnoreLevel = 2001;");
    for(int iq=0;iq<4;iq++)
    {
      fGraph -> Fit("fFit","REQM");
      fGraph -> Draw("APL same");
      NDF1[iq] = FitFunction->GetNDF();
      chisq1[iq] = FitFunction->GetChisquare();
      chisqprob1[iq] = FitFunction -> GetProb();
      Pfheight1[iq] = FitFunction -> GetMaximum(fFitrange_start,fFitrange_end);   
      Pfheight_x1[iq] = FitFunction -> GetMaximumX(fFitrange_start,fFitrange_end);
      tau_r1[iq] = FitFunction -> GetParameter(5);
      tau_s1[iq] = FitFunction -> GetParameter(3);
      tau_f1[iq] = FitFunction -> GetParameter(2);
      ratio1[iq] = FitFunction -> GetParameter(4);
      t01[iq] = FitFunction -> GetParameter(1);
      A1[iq] = FitFunction -> GetParameter(0);
    } 
    for(int iq=0;iq<3;iq++)
    {
      if(TMath::Abs(chisq1[iq]/NDF1[iq]-1)>=TMath::Abs(chisq1[iq+1]/NDF1[iq+1]-1))
      {
        NDF1[iq] = NDF1[iq+1];
        chisq1[iq] = chisq1[iq+1];
        chisqprob1[iq] = chisqprob1[iq+1];
        Pfheight1[iq] = Pfheight1[iq+1];
        Pfheight_x1[iq] = Pfheight_x1[iq+1];
//        Pheight1[iq] = Pheight[iq+1];
//        Pheight_x1[iq] = Pheight_x[iq+1];
        tau_r1[iq] = tau_r1[iq+1];
        tau_s1[iq] = tau_s1[iq+1];
        tau_f1[iq] = tau_f1[iq+1];
        ratio1[iq] = ratio1[iq+1];
        t01[iq] = t01[iq+1];
        A1[iq] = A1[iq+1];
      }
      else if(TMath::Abs(chisq1[iq]/NDF1[iq]-1)<TMath::Abs(chisq1[iq+1]/NDF1[iq+1]-1))
      {
        NDF1[iq+1] = NDF1[iq];
        chisq1[iq+1] = chisq1[iq];
        chisqprob1[iq+1] = chisqprob1[iq];
        Pfheight1[iq+1] = Pfheight1[iq];
        Pfheight_x1[iq+1] = Pfheight_x1[iq];
//        Pheight1[iq+1] = Pheight[iq];
//        Pheight_x1[iq+1] = Pheight_x[iq];
        tau_r1[iq+1] = tau_r1[iq];
        tau_s1[iq+1] = tau_s1[iq];
        tau_f1[iq+1] = tau_f1[iq];
        ratio1[iq+1] = ratio1[iq];
        t01[iq+1] = t01[iq];
        A1[iq+1] = A1[iq];
      }
    }



    NDF = NDF1[0]; 
    chisq = chisq1[0];
    chisqprob = chisqprob1[0];
    Pfheight = Pfheight1[0];
    Pfheight_x = Pfheight_x1[0];
    tau_r = tau_r1[0];
    tau_s = tau_s1[0];
    tau_f = tau_f1[0];
    ratio = ratio1[0];
    A = A1[0];

    //if(i%100==0 && i>6100){
    /*if(i>6100){
    cout << endl;
    cout << endl;
    cout << " everything is OK....." << " " << i << endl;
    cout << " everything is OK....." << " " << i << endl;
    cout << " everything is OK....." << " " << i << endl;
    cout << " everything is OK....." << " " << i << endl;
    cout << " everything is OK....." << " " << i << endl;
    cout << " everything is OK....." << " " << i << endl;
    cout << " everything is OK....." << " " << i << endl;
    cout << " everything is OK....." << " " << i << endl;
    cout << " everything is OK....." << " " << i << endl;
    cout << " everything is OK....." << " " << i << endl;
    cout << endl;
    cout << endl;
    }
    */
    IntStartVal = FitFunction -> GetX(0.05*Pfheight,fFitrange_start-10./RecordLength,Pfheight_x);
    IntEndVal = FitFunction -> GetX(0.05*Pfheight,Pfheight_x,fFitrange_end+10./RecordLength);
    TailIntStart = FitFunction -> GetX(Pfheight*0.95,Pfheight_x,Pfheight_x + 200./RecordLength);

    PInt = FitFunction -> Integral(IntStartVal,IntEndVal);
    Ptail = FitFunction -> Integral(TailIntStart,IntEndVal);
    for(int isum = 0; isum < (int)IntStartVal; isum++)
    {
      PSum += draw_FADC[isum];
    }    
    writeTree->Fill();

    delete FitFunction;
    delete fGraph;
 
    count++;
  }
 
  writeFile->cd();
  writeTree->Write();

  writeFile->Close();
}



