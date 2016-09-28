#include <TTree.h>
#include <TChain.h>
#include <TFile.h>
#include <TROOT.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TSystem.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <TRandom3.h>
#include <TMarker.h>
#include <TLatex.h>
#include <TF1.h>
#include <TStyle.h>
#include <TPad.h>

using namespace std;

void Ana_FADC_Gamma_2()
{
  gStyle->SetPalette(1);
  gStyle -> SetOptFit(kTRUE);
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
  
  Double_t ADC_tot, PulseCharge1, PulseCharge2, PulseCharge3, PulseCharge;  

  Int_t eventID;
  
  Int_t numEvents;
	Int_t numData = 0;
	Int_t numData_Mod1 = 0;
	Int_t numData_Mod2 = 0;
	Int_t numData_Det1 = 0;
	Int_t numData_Det2 = 0;
	Int_t numData_Det3 = 0;
	Int_t numData_Det4 = 0;
	Int_t numData_Det5 = 0;
	Int_t numData_Det6 = 0;
	Int_t numData_Det7 = 0;
	Double_t  MaxPeakVal_Mod1Ch4 = 0;
	Double_t  MaxPeakVal_Mod2Ch4 = 0;
	Double_t  MaxPeakVal_Mod1Ch1 = 0;
	Double_t  MaxPeakVal_Mod1Ch2 = 0;
	Double_t  MaxPeakVal_Mod1Ch3 = 0;
	Double_t  MaxPeakVal_Mod2Ch1 = 0;
	Double_t  MaxPeakVal_Mod2Ch2 = 0;
	Double_t  MaxPeakVal_Mod2Ch3 = 0;
	Double_t  MaxPeakVal_Mod2Ch3_2 = 0;
	Double_t  ADCBef;
  Int_t  Beftrig[7]={0};
  Int_t TrT1,TrT2,Tr2T1,Tr2T2,D1T1,D1T2,D2T1,D2T2,D3T1,D3T2,D4T1,D4T2,D5T1,D5T2,D6T1,D6T2;
	Double_t  MaxPeakTimeCount_Mod1Ch4;
	Double_t  MaxPeakTimeCount_Mod1Ch3;
	Double_t  MaxPeakTimeCount_Mod1Ch2;
	Double_t  MaxPeakTimeCount_Mod1Ch1;
	Double_t  MaxPeakTimeCount_Mod2Ch4;
	Double_t  MaxPeakTimeCount_Mod2Ch3;
	Double_t  MaxPeakTimeCount_Mod2Ch3_2;
	Double_t  MaxPeakTimeCount_Mod2Ch2;
	Double_t  MaxPeakTimeCount_Mod2Ch1;
	Double_t  TrigTime_Mod1;
	Double_t  TrigTime_Mod2;
	Double_t  TrigTime_Det1;
	Double_t  TrigTime_Det2;
	Double_t  TrigTime_Det3;
	Double_t  TrigTime_Det4;
	Double_t  TrigTime_Det5;
	Double_t  TrigTime_Det6;
	Double_t  TrigTime_Det7;
	Double_t  TriggerTime_Det1_abs;
	Double_t  TriggerTime_Det2_abs;
	Double_t  TriggerTime_Det3_abs;
	Double_t  TriggerTime_Det4_abs;
	Double_t  TriggerTime_Det5_abs;
	Double_t  TriggerTime_Det6_abs;
	Double_t  TriggerTime_Det7_abs;
	Double_t  TrigWeight1_Mod1;
	Double_t  TrigWeight2_Mod1;
	Double_t  TrigWeight1_Det1;
	Double_t  TrigWeight2_Det1;
	Double_t  TrigWeight1_Det2;
	Double_t  TrigWeight2_Det2;
	Double_t  TrigWeight1_Det3;
	Double_t  TrigWeight2_Det3;
	Double_t  TrigWeight1_Det4;
	Double_t  TrigWeight2_Det4;
	Double_t  TrigWeight1_Det5;
	Double_t  TrigWeight2_Det5;
	Double_t  TrigWeight1_Det6;
	Double_t  TrigWeight2_Det6;
	Double_t  TrigWeight1_Det7;
	Double_t  TrigWeight2_Det7;
  Double_t  PC_Mod1Ch1 = 0;
	Double_t  PC_Mod1Ch2 = 0;
	Double_t  PC_Mod1Ch3 = 0;
	Double_t  PC_Mod2Ch1 = 0;
	Double_t  PC_Mod2Ch2 = 0;
	Double_t  PC_Mod2Ch3 = 0;
	Double_t  PC_Mod2Ch3_2 = 0;
	Double_t  PC_Mod2Ch4 = 0;
	Double_t  PC_Mod1Ch4 = 0;
	Double_t  SumM1C1 = 0;
	Double_t  SumM1C2 = 0;
	Double_t  SumM1C3 = 0;
	Double_t  SumM2C1 = 0;
	Double_t  SumM2C2 = 0;
	Double_t  SumM2C3 = 0;
	Double_t  SumM2C3_2 = 0;
	Double_t  SumM1C4 = 0;
	Double_t  SumM2C4 = 0;
	Double_t  SumPedM1C1 = 0;
	Double_t  SumPedM1C2 = 0;
	Double_t  SumPedM1C3 = 0;
	Double_t  SumPedM2C1 = 0;
	Double_t  SumPedM2C2 = 0;
	Double_t  SumPedM2C3 = 0;
	Double_t  SumPedM2C3_2 = 0;
	Double_t  SumPedM1C4 = 0;
	Double_t  SumPedM2C4 = 0;
  Double_t  RMS_SumM1C1=0;
  Double_t  RMS_SumM1C2=0;
  Double_t  RMS_SumM1C3=0;
  Double_t  RMS_SumM2C1=0;
  Double_t  RMS_SumM2C2=0;
  Double_t  RMS_SumM2C3=0;
  Double_t  RMS_SumM2C3_2=0;
  Double_t  RMS_SumM1C4=0;
  Double_t  RMS_SumM2C4=0;
  Int_t  RMSFail;
  Double_t  RMSFail_CutVal=1.5;
  Int_t  GateStart=0;
  Int_t  GateStartFail=-1;
  Int_t  GateEnd=0;
  Int_t  BeforeGateEndFail=0;
  Int_t  EventTakeOK=-1;
  Double_t  RMS_M1C1,RMS_M1C2,RMS_M1C3,RMS_M2C1,RMS_M2C2,RMS_M2C3,RMS_M2C3_2,RMS_M1C4,RMS_M2C4;
  Double_t RMS_Confirm[16];
  Double_t pedestal_Confirm[16];
  Double_t  rate_Mod1Ch1 =0;
	Double_t  rate_Mod1Ch4 =0;
	Double_t pedestal_Mod1_Ch1 = 0;
	Double_t pedestal_Mod1_Ch2 = 0;
	Double_t pedestal_Mod1_Ch3 = 0;
	Double_t pedestal_Mod1_Ch4 = 0;
	Double_t pedestal_Mod2_Ch1;
	Double_t pedestal_Mod2_Ch2;
	Double_t pedestal_Mod2_Ch3 = 0;
	Double_t pedestal_Mod2_Ch3_2 = 0;
	Double_t pedestal_Mod2_Ch4 = 0;
	Double_t ped =0;
	Double_t adc_value =0;
  Double_t err[500]; 
  
  Double_t IntegralStart_val, IntegralEnd_val, TailStart_val,NDF, fMax_val, fMax_X, PulseHeight, Ratio, tau_r, tau_f, tau_s, t0, A, chisq, chisqprob, TailCharge;
  Double_t IntegralStart_val1, IntegralEnd_val1, TailStart_val1, NDF1, fMax_val1, fMax_X1, PulseHeight1, Ratio1, tau_r1, tau_f1, tau_s1, t01, A1, chisq1, chisqprob1, TailCharge1;
  Double_t IntegralStart_val2, IntegralEnd_val2, TailStart_val2, NDF2, fMax_val2, fMax_X2, PulseHeight2, Ratio2, tau_r2, tau_f2, tau_s2, t02, A2, chisq2, chisqprob2, TailCharge2;
  Double_t IntegralStart_val3, IntegralEnd_val3, TailStart_val3, NDF3, fMax_val3, fMax_X3, PulseHeight3, Ratio3, tau_r3, tau_f3, tau_s3, t03, A3, chisq3, chisqprob3, TailCharge3;
 


  cout << "OK 1 : " << endl;
  TH1D* hist_RMS_Mod1Ch1 = new TH1D("RMS_M1C1","Det1 Pedestal RMS;RMS;Counts",90,-3,7);
  TH1D* hist_RMS_Mod1Ch2 = new TH1D("RMS_M1C2","Det2 Pedestal RMS;RMS;Counts",90,-3,7);
  TH1D* hist_RMS_Mod1Ch3 = new TH1D("RMS_M1C3","Det3 Pedestal RMS;RMS;Counts",90,-3,7);
  TH1D* hist_RMS_Mod2Ch1 = new TH1D("RMS_M2C1","Det4 Pedestal RMS;RMS;Counts",90,-3,7);
  TH1D* hist_RMS_Mod2Ch3 = new TH1D("RMS_M2C3","Det6 Pedestal RMS;RMS;Counts",90,-3,7);
  TH1D* hist_RMS_Mod2Ch3_2 = new TH1D("RMS_M2C3_2","Det7 Pedestal RMS;RMS;Counts",90,-3,7);
	TH1F* hist_PC_Mod1Ch4 = new TH1F("PCM1C4","Trigger1 Charge;ADC;Counts",110,0,7200);
	TH1F* hist_PC_Mod2Ch4 = new TH1F("PCM2C4","Trigger2 Charge;ADC;Counts",110,0,7200);
	TH1F* hist_PC_Mod1Ch1 = new TH1F("PCM1C1","Det1 Charge;ADC;Counts",120,0,5000);
	TH1F* hist_PC_Mod1Ch2 = new TH1F("PCM1C2","Det2 Charge;ADC;Counts",120,0,5000);
	TH1F* hist_PC_Mod1Ch3 = new TH1F("PCM1C3","Det3 Charge;ADC;Counts",120,0,5000);
	TH1F* hist_PC_Mod2Ch1 = new TH1F("PCM2C1","Det4 Charge;ADC;Counts",120,0,5000);
	TH1F* hist_PC_Mod2Ch2 = new TH1F("PCM2C2","Det5 Charge;ADC;Counts",120,0,5000);
	TH1F* hist_PC_Mod2Ch3 = new TH1F("PCM2C3","Det6 Charge;ADC;Counts",120,0,5000);
	TH1F* hist_PC_Mod2Ch3_2 = new TH1F("PCM2C3_2","Det7 Charge;ADC;Counts",120,0,5000);
	TH1F* hist_TrTime_Mod1 = new TH1F("TrTimeMod1","Trigger Time Mod1;Time (ns);Counts",100,0,250);
	TH1F* hist_TrTime_Mod2 = new TH1F("TrTimeMod2","Trigger Time Mod2;Time (ns);Counts",100,0,250);
	TH1F* hist_DetTime_Det1  = new TH1F("TimeDet1","Det1 Time;Time (ns);Counts",100,0,250);
	TH1F* hist_DetTime_Det2  = new TH1F("TimeDet2","Det2 Time;Time (ns);Counts",100,0,250);
	TH1F* hist_DetTime_Det3  = new TH1F("TimeDet3","Det3 Time;Time (ns);Counts",100,0,250);
	TH1F* hist_DetTime_Det4  = new TH1F("TimeDet4","Det4 Time;Time (ns);Counts",100,0,250);
	TH1F* hist_DetTime_Det5  = new TH1F("TimeDet5","Det5 Time;Time (ns);Counts",100,0,250);
	TH1F* hist_DetTime_Det6  = new TH1F("TimeDet6","Det6 Time;Time (ns);Counts",100,0,250);
	TH1F* hist_DetTime_Det7  = new TH1F("TimeDet7","Det7 Time;Time (ns);Counts",100,0,250);
/* 
  for(int t=1;t<8;t++)
  { 
   Form("hist_DetTime_Det%d",t) -> GetXaxis() -> CenterTitle(); 
   Form("hist_DetTime_Det%d",t) -> GetXaxis() -> SetTitleFont(132); 
   Form("hist_DetTime_Det%d",t) -> GetYaxis() -> CenterTitle(); 
   Form("hist_DetTime_Det%d",t) -> GetYaxis() -> SetTitleFont(132); 
  }
*/
  hist_TrTime_Mod1 -> GetXaxis() -> CenterTitle(); 
  hist_TrTime_Mod1 -> GetXaxis() -> SetTitleFont(132); 
  hist_TrTime_Mod1 -> GetYaxis() -> CenterTitle(); 
  hist_TrTime_Mod1 -> GetYaxis() -> SetTitleFont(132); 

  hist_TrTime_Mod2 -> GetXaxis() -> CenterTitle(); 
  hist_TrTime_Mod2 -> GetXaxis() -> SetTitleFont(132); 
  hist_TrTime_Mod2 -> GetYaxis() -> CenterTitle(); 
  hist_TrTime_Mod2 -> GetYaxis() -> SetTitleFont(132); 

  hist_RMS_Mod1Ch1 -> GetXaxis() -> CenterTitle(); 
  hist_RMS_Mod1Ch1 -> GetXaxis() -> SetTitleFont(132); 
  hist_RMS_Mod1Ch1 -> GetYaxis() -> CenterTitle(); 
  hist_RMS_Mod1Ch1 -> GetYaxis() -> SetTitleFont(132); 

  hist_RMS_Mod2Ch1 -> GetXaxis() -> CenterTitle(); 
  hist_RMS_Mod2Ch1 -> GetXaxis() -> SetTitleFont(132); 
  hist_RMS_Mod2Ch1 -> GetYaxis() -> CenterTitle(); 
  hist_RMS_Mod2Ch1 -> GetYaxis() -> SetTitleFont(132); 

  hist_PC_Mod1Ch1 -> GetXaxis() -> CenterTitle(); 
  hist_PC_Mod1Ch1 -> GetXaxis() -> SetTitleFont(132); 
  hist_PC_Mod1Ch1 -> GetYaxis() -> CenterTitle(); 
  hist_PC_Mod1Ch1 -> GetYaxis() -> SetTitleFont(132); 

  hist_PC_Mod2Ch1 -> GetXaxis() -> CenterTitle(); 
  hist_PC_Mod2Ch1 -> GetXaxis() -> SetTitleFont(132); 
  hist_PC_Mod2Ch1 -> GetYaxis() -> CenterTitle(); 
  hist_PC_Mod2Ch1 -> GetYaxis() -> SetTitleFont(132); 

  hist_PC_Mod1Ch4 -> GetXaxis() -> CenterTitle(); 
  hist_PC_Mod1Ch4 -> GetXaxis() -> SetTitleFont(132); 
  hist_PC_Mod1Ch4 -> GetYaxis() -> CenterTitle(); 
  hist_PC_Mod1Ch4 -> GetYaxis() -> SetTitleFont(132); 

  hist_PC_Mod2Ch4 -> GetXaxis() -> CenterTitle(); 
  hist_PC_Mod2Ch4 -> GetXaxis() -> SetTitleFont(132); 
  hist_PC_Mod2Ch4 -> GetYaxis() -> CenterTitle(); 
  hist_PC_Mod2Ch4 -> GetYaxis() -> SetTitleFont(132); 

  cout << "OK 2 : " << endl;
  TH1 *gr_ped_Mod1Ch1 = new TH1D("Mod1Ch1","", 100, 900, 1000); 
	TH1 *gr_rate_adc_Mod1Ch1 = new TH1D("rate_Mod1Ch1","", 500, 0, 500);
	TH1 *gr_rate_adc_Mod1Ch4 = new TH1D("rate_Mod1Ch4","", 500, 0, 500);
  gSystem -> Load("libNFADC400.so");

 
  const int NF=7;
  const int N_RecordingBin=256; 
  TFile *file[NF];
  TTree *AnaTree[NF];
  TFile *writeFile[NF];
	TClonesArray *events_Mod2Ch1=NULL;
	TClonesArray *events_Mod2Ch2=NULL;
  TTree *tree_Mod2Ch1;
  TTree *errorTree;
  TTree *tree_Mod2Ch2;
  NFADC400Header *pedestal_Mod2=NULL;
	NFADC400Event2 *anEvent=NULL;
  pedestal_Mod2_Ch1=0; 
  pedestal_Mod2_Ch2=0; 
  
  Double_t fbegin_val;
  int tt;

cout<<" ped : " << ped << endl;

for(int ii=1;ii<NF;ii++)
//for(int ii=1;ii<2;ii++)
{
    TH1D* hist_RMS_Mod2Ch2 = new TH1D("RMS_M2C2","Det5 Pedestal RMS;RMS;Counts",500,-5,50);
  	//file[ii] = new TFile(Form("../data/CsIGamma/150821_Cs137_CsI_1900_1600_%d.zeroSuppressed.root",ii),"READ");
  	//file[ii] = new TFile(Form("../data/CsIGamma/150821_Cs137_CsI_1900_1600_%d.root",ii),"READ");
  	//file[ii] = new TFile(Form("../data/CsIGamma/150901_Default_Self_CsI_1900_%d.root",ii),"READ");
  	//file[ii] = new TFile(Form("../data/CsIGamma/150821_Default_CsI_1900_1600_%d.root",ii),"READ");
  	file[ii] = new TFile(Form("./newData/Cs137_ST_Smear_error_Test%d.root",ii),"READ");
  	//file[ii] = new TFile(Form("../data/CsIGamma/SelfTriggerdata/selfCo60/Co60_CsI_1900_ST_%d.root",ii),"READ");
    //TChain *file = new TChain("../data/CsIGamma/150821_Cs137_CsI_1900_1600_10.zeroSuppressed.root","READ");
    //writeFile[ii] = new TFile(Form("150821_Co60_CsI_%dTestnew.root",ii),"recreate");
    //writeFile[ii] = new TFile(Form("150901_Default_Self_CsI_%dTestnew.root",ii),"recreate");
    writeFile[ii] = new TFile(Form("1509_CsI_Self_Cs137_Fit_%d.root",ii),"recreate");
    //writeFile[ii] = new TFile(Form("1509_CsI_Self_Co60_%d.root",ii),"recreate");
    tree_Mod2Ch1 = (TTree *) file[ii] -> Get(Form("Mod%dCh%d",2,1));
    tree_Mod2Ch1 -> SetBranchAddress("events",&events_Mod2Ch1);
    tree_Mod2Ch1 -> GetEntry(0);
    tree_Mod2Ch2 = (TTree *) file[ii] -> Get(Form("Mod%dCh%d",2,2));
    tree_Mod2Ch2 -> SetBranchAddress("events",&events_Mod2Ch2);
    tree_Mod2Ch2 -> GetEntry(0);

    errorTree = (TTree *) file[ii] -> Get("error");
    errorTree -> SetBranchAddress("err",&err);

    pedestal_Mod2 = (NFADC400Header *)file[ii] -> Get("Mod2");
    pedestal_Mod2_Ch2 = pedestal_Mod2 -> GetPedestal(1);
    numEvents = events_Mod2Ch1 -> GetEntries();
  
    AnaTree[ii] = new TTree("AnaTree","AnaTree");
    AnaTree[ii] -> Branch("eventID",&eventID,"eventID/I");
    AnaTree[ii] -> Branch("ADC_tot",&ADC_tot,"ADC_tot/D");
    AnaTree[ii] -> Branch("pedestal_Mod2_Ch2",&pedestal_Mod2_Ch2,"pedestal_Mod2_Ch2/D");
    AnaTree[ii] -> Branch("PulseHeight",&PulseHeight,"PulseHeight/D");
    AnaTree[ii] -> Branch("PulseCharge",&PulseCharge,"PulseCharge/D");
    AnaTree[ii] -> Branch("RMS_M2C2",&RMS_M2C2,"RMS_M2C2/D");
    AnaTree[ii] -> Branch("chisq",&chisq,"chisq/D");
    AnaTree[ii] -> Branch("chisqprob",&chisqprob,"chisqprob/D");
    AnaTree[ii] -> Branch("NDF",&NDF,"NDF/D");
    AnaTree[ii] -> Branch("tau_r",&tau_r,"tau_r/D");
    AnaTree[ii] -> Branch("tau_f",&tau_f,"tau_f/D");
    AnaTree[ii] -> Branch("tau_s",&tau_s,"tau_s/D");
    AnaTree[ii] -> Branch("Ratio",&Ratio,"Ratio/D");
    AnaTree[ii] -> Branch("A",&A,"A/D");
    AnaTree[ii] -> Branch("t0",&t0,"t0/D");
    AnaTree[ii] -> Branch("fMax_val",&fMax_val,"fMax_val/D");
    AnaTree[ii] -> Branch("fMax_X",&fMax_X,"fMax_X/D");
    AnaTree[ii] -> Branch("TailCharge",&TailCharge,"TailCharge/D");
    AnaTree[ii] -> Branch("IntegralStart_val",&IntegralStart_val,"IntegralStart_val/D");
    AnaTree[ii] -> Branch("IntegralEnd_val",&IntegralEnd_val,"IntegralEnd_val/D");

  
    cout << "num Events : " << numEvents << endl; 

  for (Int_t i = 0; i < numEvents; i++) 
  //for (Int_t i = 0; i < 1; i++) 
	{
  
    //**************************************************************************
    //******************New Channel Mod1Ch4 Trigger 1***************************
    //**************************************************************************
		
      eventID=i;
      RMSFail=1;
      anEvent = (NFADC400Event2 *) events_Mod2Ch2 -> At(i);
			numData =  anEvent -> GetNumData();
      errorTree->GetEntry(i);
      
      TGraphErrors *fGraph = new TGraphErrors();
      tt=0;
     

      for (Int_t j = 0; j < numData; j++)
			{
         
          //************ Fill data plot by event *************
          fGraph -> SetPoint(j, j, 2*anEvent->GetADC(j));    
          fGraph -> SetPointError(j, 0, 2*err[j]);
     
 /*         cout << endl;
          cout << " ADC : " << 2*anEvent->GetADC(j) << endl;
          cout << " Error : " << 2*err[j] << endl;
          cout << endl;
*/
          //************ Pedestal Calculation ****************
          for(int k=0;k<N_RecordingBin/16;k++)
          {
            if(j<16*(k+1)&&j>=16*k)
            {
              SumPedM2C2 += anEvent->GetADC(j);
              pedestal_Confirm[k] = SumPedM2C2/(j+1-16*k);
              RMS_SumM2C2 += TMath::Power(((double)anEvent->GetADC(j)-pedestal_Mod2_Ch2),2);
              RMS_Confirm[k] = TMath::Sqrt(RMS_SumM2C2/(j+1-16*k));         
            
              if(j==16*(k+1)-1) 
              {
                SumPedM2C2=0;
                RMS_SumM2C2=0;
              }
            }
          }
          
          //************ Maximum Peak Value ***************
          if(MaxPeakVal_Mod2Ch2 < anEvent -> GetADC(j)) 
          {
            MaxPeakVal_Mod2Ch2 = anEvent -> GetADC(j);
            MaxPeakTimeCount_Mod2Ch2 = j;
          }

          if(j>0&&anEvent->GetADC(j)>15) 
          {
            tt++;
            if(tt==1) fbegin_val = j;
          }

			}
  
      //******** Find lowest RMS value and the corresponding pedestal *********
      pedestal_Mod2_Ch2=pedestal_Confirm[0];
      RMS_M2C2=RMS_Confirm[0];
      for(Int_t jj=0;jj<N_RecordingBin/16;jj++)
      { 
       /* cout << endl;
        cout << "eventID : " << eventID << endl;
        cout << "RMS_Confirm[" << jj << "]" << RMS_Confirm[jj] << endl;
        cout << endl;*/
        if(RMS_Confirm[jj]<RMS_M2C2) 
        {
          RMS_M2C2 = RMS_Confirm[jj];
          pedestal_Mod2_Ch2=pedestal_Confirm[jj];
        }
      }
  


      Int_t recordingLength = numData/128;

      fGraph -> SetTitle(Form("Channel 2 - Event %d", i));
      fGraph -> SetLineColor(1);
      fGraph -> SetMarkerColor(1);
      fGraph -> GetHistogram() -> GetXaxis() -> SetTitle("Time Bucket (40 ns)");
      fGraph -> GetHistogram() -> GetXaxis() -> SetLimits(-10,recordingLength*128+10);
      fGraph -> GetHistogram() -> GetXaxis() -> SetRangeUser(-5,numData+5);
      fGraph -> GetHistogram() -> GetXaxis() -> CenterTitle();
      fGraph -> GetHistogram() -> GetYaxis() -> SetTitle("ADC Channel");
      fGraph -> GetHistogram() -> GetYaxis() -> SetLimits(-10,1024+25);
      fGraph -> GetHistogram() -> GetYaxis() -> SetRangeUser(-15,1024+15);
      fGraph -> GetHistogram() -> GetYaxis() -> CenterTitle();

      fGraph -> GetHistogram() -> GetXaxis() -> SetLabelSize(0.08);
      fGraph -> GetHistogram() -> GetXaxis() -> SetTitleSize(0.08);
      fGraph -> GetHistogram() -> GetYaxis() -> SetLabelSize(0.08);
      fGraph -> GetHistogram() -> GetYaxis() -> SetTitleSize(0.08);
      
      gStyle -> SetOptFit(1111111);

      TF1* FitFunction = new TF1("fFit","[0]*(1/[2]*TMath::Exp(-(x-[1])/[2])+[4]/[3]*TMath::Exp(-(x-[1])/[3])-(1/[2]+[4]/[3])*TMath::Exp(-(x-[1])/[5]))");
 
   //   double a = (double)1000./(80./(double)recordingLength)-(double)10./(80./(double)recordingLength);
      double a = fbegin_val -0.8;
      double b = 4500./(40./(double)recordingLength);
      FitFunction -> SetRange(a,b);
  
        
      FitFunction -> SetParName(0,"A");
      FitFunction -> SetParName(1,"t_{0}");
      FitFunction -> SetParName(2,"#tau_{f}");
      FitFunction -> SetParName(3,"#tau_{s}");
      FitFunction -> SetParName(4,"R");
      FitFunction -> SetParName(5,"#tau_{r}");

      FitFunction -> SetParameters(100,15,10,41,0.25,0.5);
      FitFunction -> SetParLimits(0, 20,100000);
      FitFunction -> SetParLimits(1,  1,1000./(40./(double)recordingLength)+20);
      FitFunction -> SetParLimits(2,  5,24);
      FitFunction -> SetParLimits(3,  30,130);
      FitFunction -> SetParLimits(4, 0.1,0.85);
      FitFunction -> SetParLimits(5, 0.1,1.7);
    
      //cvs->cd(); 
     // fGraph -> Draw("APL sameq");  
      fGraph -> Fit("fFit","RQ");
      chisq1 = FitFunction -> GetChisquare();
      NDF1 = FitFunction -> GetNDF();
      chisqprob1 = FitFunction -> GetProb();
      fMax_val1 = FitFunction -> GetMaximum(a,b);
      fMax_X1 = FitFunction -> GetMaximumX(a,b);
      tau_r1 = FitFunction -> GetParameter(5);
      tau_f1 = FitFunction -> GetParameter(2);
      tau_s1 = FitFunction -> GetParameter(3);
      Ratio1 = FitFunction -> GetParameter(4); 
      t01 = FitFunction -> GetParameter(1);
      A1 = FitFunction -> GetParameter(0);
      
      IntegralStart_val1 = FitFunction -> GetX(1,fMax_X1-20,fMax_X1); 
      IntegralEnd_val1 = FitFunction -> GetX(1,fMax_X1,fMax_X1+130); 
      TailStart_val1 = FitFunction -> GetX(fMax_val1*0.85,fMax_X1,fMax_X1+20);

      PulseCharge1 = FitFunction -> Integral(IntegralStart_val1,IntegralEnd_val1);
      TailCharge1 = FitFunction -> Integral(TailStart_val1,IntegralEnd_val1);
      


      fGraph -> Fit("fFit","RQ");
      chisq2 = FitFunction -> GetChisquare();
      NDF2 = FitFunction -> GetNDF();
      chisqprob2 = FitFunction -> GetProb();
      fMax_val2 = FitFunction -> GetMaximum(a,b);
      fMax_X2 = FitFunction -> GetMaximumX(a,b);
      tau_r2 = FitFunction -> GetParameter(5);
      tau_f2 = FitFunction -> GetParameter(2);
      tau_s2 = FitFunction -> GetParameter(3);
      Ratio2 = FitFunction -> GetParameter(4); 
      t02 = FitFunction -> GetParameter(1);
      A2 = FitFunction -> GetParameter(0);
      
      IntegralStart_val2 = FitFunction -> GetX(1,fMax_X2-20,fMax_X2); 
      IntegralEnd_val2 = FitFunction -> GetX(1,fMax_X2,fMax_X2+130); 
      TailStart_val2 = FitFunction -> GetX(fMax_val2*0.85,fMax_X2,fMax_X2+20);

      PulseCharge2 = FitFunction -> Integral(IntegralStart_val2,IntegralEnd_val2);
      TailCharge2 = FitFunction -> Integral(TailStart_val2,IntegralEnd_val2);
      



      fGraph -> Fit("fFit","RQ");
      chisq3 = FitFunction -> GetChisquare();
      NDF3 = FitFunction -> GetNDF();
      chisqprob3 = FitFunction -> GetProb();
      fMax_val3 = FitFunction -> GetMaximum(a,b);
      fMax_X3 = FitFunction -> GetMaximumX(a,b);
      tau_r3 = FitFunction -> GetParameter(5);
      tau_f3 = FitFunction -> GetParameter(2);
      tau_s3 = FitFunction -> GetParameter(3);
      Ratio3 = FitFunction -> GetParameter(4); 
      t03 = FitFunction -> GetParameter(1);
      A3 = FitFunction -> GetParameter(0);
      
      IntegralStart_val3 = FitFunction -> GetX(1,fMax_X3-20,fMax_X3); 
      IntegralEnd_val3 = FitFunction -> GetX(1,fMax_X3,fMax_X2+130); 
      TailStart_val3 = FitFunction -> GetX(fMax_val3*0.85,fMax_X3,fMax_X3+20);

      PulseCharge3 = FitFunction -> Integral(IntegralStart_val3,IntegralEnd_val3);
      TailCharge3 = FitFunction -> Integral(TailStart_val3,IntegralEnd_val3);
      




      if(chisq1/NDF1<chisq2/NDF2) 
      {
        if(chisq1/NDF1<chisq3/NDF3) 
        {
          chisq = chisq1;
          NDF = NDF1;
          chisqprob = chisqprob1;
          fMax_val = fMax_val1;
          fMax_X = fMax_X1;
          tau_r = tau_r1;
          tau_f = tau_f1;
          tau_s = tau_s1;
          Ratio = Ratio1;
          t0 = t01;
          A = A1;
          IntegralStart_val = IntegralStart_val1;
          IntegralEnd_val = IntegralEnd_val1;
          TailStart_val = TailStart_val1;
          PulseCharge = PulseCharge1;
          TailCharge = TailCharge1;
        }
        else if(chisq1/NDF1>chisq3/NDF3) 
        {
          chisq = chisq3;
          NDF = NDF3;
          chisqprob = chisqprob3;
          fMax_val = fMax_val3;
          fMax_X = fMax_X3;
          tau_r = tau_r3;
          tau_f = tau_f3;
          tau_s = tau_s3;
          Ratio = Ratio3;
          t0 = t03;
          A = A3;
          IntegralStart_val = IntegralStart_val3;
          IntegralEnd_val = IntegralEnd_val3;
          TailStart_val = TailStart_val3;
          PulseCharge = PulseCharge3;
          TailCharge = TailCharge3;
        }
      }
      else if(chisq1/NDF1>chisq2/NDF2) 
      {
        if(chisq2/NDF2<chisq3/NDF3)
        {
          chisq = chisq2;
          NDF = NDF2;
          chisqprob = chisqprob2;
          fMax_val = fMax_val2;
          fMax_X = fMax_X2;
          tau_r = tau_r2;
          tau_f = tau_f2;
          tau_s = tau_s2;
          Ratio = Ratio2;
          t0 = t02;
          A = A2;
          IntegralStart_val = IntegralStart_val2;
          IntegralEnd_val = IntegralEnd_val2;
          TailStart_val = TailStart_val2;
          PulseCharge = PulseCharge2;
          TailCharge = TailCharge2;
        }
        else if(chisq2/NDF2>chisq3/NDF3)
        {
          chisq = chisq3;
          NDF = NDF3;
          chisqprob = chisqprob3;
          fMax_val = fMax_val3;
          fMax_X = fMax_X3;
          tau_r = tau_r3;
          tau_f = tau_f3;
          tau_s = tau_s3;
          Ratio = Ratio3;
          t0 = t03;
          A = A3;
          IntegralStart_val = IntegralStart_val3;
          IntegralEnd_val = IntegralEnd_val3;
          TailStart_val = TailStart_val3;
          PulseCharge = PulseCharge3;
          TailCharge = TailCharge3;
        }
      }



//      IntegralStart_val = FitFunction -> GetX(0,fMax_X-20,fMax_X); 
      //IntegralStart_val = fbegin_val - 0.8; 

      for(int k=0;k<numData;k++)
      {
        SumM2C2 += (anEvent -> GetADC(k));
      }
    
      PC_Mod2Ch2 = pedestal_Mod2_Ch2*numData+SumM2C2;
      
      ADC_tot=PC_Mod2Ch2;
      PulseHeight=-pedestal_Mod2_Ch2+MaxPeakVal_Mod2Ch2;
      AnaTree[ii]->Fill();

      delete FitFunction;
      delete fGraph;
//      hist_RMS_Mod2Ch2->Fill(RMS_M2C2);      
//      hist_PC_Mod2Ch2->Fill(PC_Mod2Ch2);

      MaxPeakVal_Mod1Ch1=0; 
      MaxPeakVal_Mod1Ch2=0; 
      MaxPeakVal_Mod1Ch3=0; 
      MaxPeakVal_Mod2Ch1=0; 
      MaxPeakVal_Mod2Ch2=0; 
      MaxPeakVal_Mod2Ch3=0; 
      MaxPeakVal_Mod1Ch4=0; 
      MaxPeakVal_Mod2Ch4=0; 
      SumM1C1=0;
      SumM1C2=0;
      SumM1C3=0;
      SumM2C1=0;
      SumM2C2=0;
      SumM2C3=0;
      SumM1C4=0;
      SumM2C4=0;
      SumPedM1C1=0;
      SumPedM1C2=0;
      SumPedM1C3=0;
      SumPedM2C1=0;
      SumPedM2C2=0;
      SumPedM2C3=0;
      SumPedM1C4=0;
      SumPedM2C4=0;
      RMS_SumM1C4=0;
      RMS_SumM2C4=0;
      RMS_SumM1C1=0;
      RMS_SumM1C2=0;
      RMS_SumM1C3=0;
      RMS_SumM2C1=0;
      RMS_SumM2C2=0;
      RMS_SumM2C3=0;
      RMS_SumM2C3_2=0;
      ADC_tot = -200000;
      GateStart=0;
      GateStartFail=-1;
      GateEnd=0;
      BeforeGateEndFail=0;
      EventTakeOK=-1;

ped =0;  

}
	
  writeFile[ii]->cd();

  AnaTree[ii]->Write();
  hist_PC_Mod2Ch2->Write();
  hist_RMS_Mod2Ch2->Write();
  writeFile[ii]->Write();
  writeFile[ii]->Close();

  delete hist_RMS_Mod2Ch2;
  }
}

