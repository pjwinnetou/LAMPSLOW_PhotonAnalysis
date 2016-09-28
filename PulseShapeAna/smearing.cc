#include <TFile.h>
#include <TSystem.h>
#include <TROOT.h>
#include <TTree.h>
#include <TLeaf.h>
#include <TMath.h>
#include <TStyle.h>
#include <TH1.h>
#include <TH2.h>
#include <TPad.h>
#include <TLegend.h>
#include <TRandom.h>

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class data {
  public:
   UChar_t fadc_trigger[2];
   UChar_t fadc_tag[6];
   Float_t fadc_FADC[8192];
};

int main(int argc, char* argv[])
{
  gStyle -> SetPalette(1);
  gStyle -> SetOptFit(kTRUE);
  gStyle -> SetOptStat(0);
  gStyle -> SetTextSize(0.01908148);
  gStyle -> SetTitleFontSize(0.03);
  gStyle -> SetTitleXSize(0.04);
  gStyle -> SetTitleXOffset(1.3);
  gStyle -> SetTitleYSize(0.04);
  gStyle -> SetTitleYOffset(2.2);
  gStyle -> SetPadBottomMargin(0.05);
  gStyle -> SetPadTopMargin(0.05);
  gStyle -> SetPadLeftMargin(0.2);
  gStyle -> SetPadRightMargin(0.1);

  data myData;


  //**************** SMEARING START ********************

  TString inputFileName;
  TString nItemString;
  int nItem;
  int NumOfError = 0;


  cout << endl;
  cout << endl;
  cout << " ***************************************************** " << endl;
  cout << " **************** LAMPS Collaboration **************** " << endl;
  cout << " *************** Pulse Shape Analysis **************** " << endl;
  cout << " ***************************************************** " << endl;
  cout << endl;
  cout << " **** NOTICE FADC 400MHz PSD **** " << endl;
  cout << endl;
  cout << endl;
  cout << " **** Pulse Smearing & Sorting Process **** " << endl;
  cout << " First : Sorting data into each channel " << endl;
  cout << " Second : Averaging selected number of points " << endl;
  cout << endl;
  cout << " INPUT1 : raw data file name 'input file name'.root " << endl;
  cout << " INPUT2 : # of smearing points " << endl;
  cout << " Output : File name with - 'input file name'_'# of smeared point'_smeared.root " << endl;
  cout << endl;
  cout << endl;

  if(argc!=3)
  {
    cout << " *********** START *********** " << endl;
    cout << " Write the raw data file name    : "; cin >> inputFileName;
    cout << " Write the # of smearing points  : "; cin >> nItemString;
    nItem = atoi(nItemString);
  }
  else
  {
    inputFileName = argv[1];
    nItem = atoi(argv[2]);
  }
  cout << endl;

  cout << " Reading file        : " << inputFileName << " .... " << endl;
  cout << " # of smeared points : " << nItem << endl; 
  cout << endl;

  TFile *fp = new TFile(Form("./data/201512_CNUFADC_GAMMA_DATA/%s",inputFileName.Data()),"READ");
  

  TString outputFileName = inputFileName;
  outputFileName.ReplaceAll(".root",Form("_%d_ss.root",nItem)); // sort & smeared

  TFile *writeFile = new TFile(Form("./Ana/ssData/%s",outputFileName.Data()),"recreate");
  
  TTree *tr = (TTree*) fp -> Get("nfadc400");
  TTree *head = (TTree*) fp -> Get("head");
  tr -> SetBranchAddress("fadc", myData.fadc_trigger);

  Int_t RL;
  head->GetEntry(0);
  Int_t rl = (Int_t )head -> GetLeaf("head1","rl") -> GetValue(); 
  cout << "rl : " << rl << endl;
  Int_t num_ArrayCount; // number of counts is FADC array
  Int_t num_ArrayEvent = rl * 128; // number of points recorded in each channel
  Int_t num_Channel; // number of channels used
  Int_t fillInt; 
  Int_t eventID=-1;
  RL = rl;

  cout << "declear " << endl;
  num_ArrayCount = sizeof(myData.fadc_FADC)/sizeof(myData.fadc_FADC[0]);
  num_Channel = num_ArrayCount/num_ArrayEvent;
  
  cout << endl;
  cout << " ++++ RAW DATA FILE INFO ++++ " << endl;
  cout << " Recording Length (num_ArrayEvent*2.5)    :  " << num_ArrayEvent*2.5 << endl;
  cout << " Counts of FADC array (num_ArrayCount)    :  " << num_ArrayCount << endl;
  cout << " # of points in channel (num_ArrayEvent)  :  " << num_ArrayEvent << endl;
  cout << " # of channels (num_Channel)              :  " << num_Channel << endl;
  cout << " rl value                                 :  " << rl << endl;
  cout << endl;


  Float_t fADC_ch1[num_ArrayEvent];
  Float_t fADC_ch2[num_ArrayEvent];
  Float_t fADC_ch3[num_ArrayEvent];
  Float_t fADC_ch4[num_ArrayEvent];

  for(int iinit=0; iinit<num_ArrayEvent;iinit++)
  {
    fADC_ch1[iinit] = -1000;
    fADC_ch2[iinit] = -1000;
    fADC_ch3[iinit] = -1000;
    fADC_ch4[iinit] = -1000;
  }



  cout << endl;
  cout << " Making new tree (sorted tree) .... " << endl;
  cout << endl;
  
  TTree *newtr = new TTree("sortdata","Sort data file");
  newtr -> Branch("eventID",&eventID,"eventID/I");
  newtr -> Branch("num_ArrayCount",&num_ArrayCount,"num_ArrayCount/I");
  newtr -> Branch("num_ArrayEvent",&num_ArrayEvent,"num_ArrayEvent/I");
  newtr -> Branch("num_Channel",&num_Channel,"num_Channel/I");
  newtr -> Branch("RL",&RL,"RL/I");
  newtr -> Branch("fADC_ch1",&fADC_ch1,"fADC_ch1[num_ArrayEvent]/F");
  newtr -> Branch("fADC_ch2",&fADC_ch2,"fADC_ch2[num_ArrayEvent]/F");
  newtr -> Branch("fADC_ch3",&fADC_ch3,"fADC_ch3[num_ArrayEvent]/F");
  newtr -> Branch("fADC_ch4",&fADC_ch4,"fADC_ch4[num_ArrayEvent]/F");
  
  cout << " Tree making done  " << endl;
  cout << endl;
  

  cout << endl;
  cout << " + Now starting event loop of sorting + " << endl;
  cout << endl;
  
  const int numEntries = tr -> GetEntries();

  cout << " Number of events : " << numEntries << endl;

  int count = 0;
  for(int i=0; i<numEntries;i++)
  {
    tr->GetEntry(i);
    eventID = i;
    
    if(eventID != i) 
    {
      cout << endl;
      cout << "===================================" << endl;
      cout << "      +++++++ ERROR!!! ++++++++   "  << endl;
      cout << " EventID not matched!!!" << endl;
      cout << " event number from the raw tree : " << i << endl;
      cout << " eventID for writing : " << eventID << endl;
      cout << "===================================" << endl;
      cout << endl;
      NumOfError++;
    }
    for(int j=0; j<num_ArrayCount; j++)
    {
      int tt=0;
      for(int k=0; k<4;k++)
      {
        if(j>=num_ArrayEvent*k && j<num_ArrayEvent*(k+1))
        {
          fillInt = j-num_ArrayEvent*k; 
          if(tt==0) fADC_ch1[fillInt] = myData.fadc_FADC[j];
          else if(tt==1) fADC_ch2[fillInt] = myData.fadc_FADC[j];
          else if(tt==2) fADC_ch3[fillInt] = myData.fadc_FADC[j];
          else if(tt==3) fADC_ch4[fillInt] = myData.fadc_FADC[j];

          if((j==0 && tt!=0) || (j==0 && k!=0) || (j==0 && fillInt!=0))
          {
            cout << endl;
            cout << "============================================" << endl;
            cout << "        +++++++ CH1 ERROR!!! ++++++++   "  << endl;
            cout << " Initial filling is wrong!!!   "  << endl;
            cout << " Fill start point for ch1 (fillInt)     : " << fillInt << endl;
            cout << " Current reading point for in array (j) : " << j << endl;
            cout << " Current reading the channel (tt)       : " << tt << endl;
            cout << " Current channel loop integer (k)       : " << k << endl;
            cout << "============================================" << endl;
            cout << endl;
            NumOfError++;
          }
          else if((j==num_ArrayEvent && tt!=1) || (j==num_ArrayEvent && k!=1) || (j==num_ArrayEvent && fillInt!=0))
          {
            cout << endl;
            cout << "============================================" << endl;
            cout << "        +++++++ CH2 ERROR!!! ++++++++   "  << endl;
            cout << " Initial filling is wrong!!!   "  << endl;
            cout << " Fill start point for ch2 (fillInt)     : " << fillInt << endl;
            cout << " Current reading point for in array (j) : " << j << endl;
            cout << " Current reading the channel (tt)       : " << tt << endl;
            cout << " Current channel loop integer (k)       : " << k << endl;
            cout << "============================================" << endl;
            cout << endl;
            NumOfError++;
          }
          else if((j==num_ArrayEvent*2 && tt!=2) || (j==num_ArrayEvent*2 && k!=2) || (j==num_ArrayEvent*2 && fillInt!=0))
          {
            cout << endl;
            cout << "============================================" << endl;
            cout << "        +++++++ CH3 ERROR!!! ++++++++   "  << endl;
            cout << " Initial filling is wrong!!!   "  << endl;
            cout << " Fill start point for ch3 (fillInt)     : " << fillInt << endl;
            cout << " Current reading point for in array (j) : " << j << endl;
            cout << " Current reading the channel (tt)       : " << tt << endl;
            cout << " Current channel loop integer (k)       : " << k << endl;
            cout << "============================================" << endl;
            cout << endl;
            NumOfError++;
          }
          else if((j==num_ArrayEvent*3 && tt!=3) || (j==num_ArrayEvent*3 && k!=3) || (j==num_ArrayEvent*3 && fillInt!=0))
          {
            cout << endl;
            cout << "============================================" << endl;
            cout << "        +++++++ CH4 ERROR!!! ++++++++   "  << endl;
            cout << " Initial filling is wrong!!!   "  << endl;
            cout << " Fill start point for ch4 (fillInt)     : " << fillInt << endl;
            cout << " Current reading point for in array (j) : " << j << endl;
            cout << " Current reading the channel (tt)       : " << tt << endl;
            cout << " Current channel loop integer (k)       : " << k << endl;
            cout << "============================================" << endl;
            cout << endl;
            NumOfError++;
          }

        }
        tt++;
      }
    }
    newtr->Fill();
    count++;
    if(count%10000==0) cout << " reading eventID... : " << count << " / " << numEntries << " (" << (int)(100.*count/numEntries) << "%)" << endl;
  }

  cout << endl;
  cout << endl;
  cout << " Sorting is done! " << endl;
  cout << endl;
  cout << endl;

  cout << " ++++ NOW BEGINNING AVERAGING ++++ " << endl;
  cout << " # of smearing points : " << nItem << endl; 
  cout << endl;
    
  const int numEntries_sort = newtr -> GetEntries();

  cout << " Number of sorted events : " << numEntries_sort << endl;
  if(numEntries != numEntries_sort)
  {
    cout << endl;
    cout << " ============================================ " << endl;
    cout << "            ******  ERROR!!!  ******         " << endl;
    cout << " # of events from raw vs. sorted mismatch!! " << endl;
    cout << " # of events in raw  :  " << numEntries << endl;
    cout << " # of events in sort :  " << numEntries_sort << endl;
    cout << " ============================================ " << endl;
    cout << endl;
    NumOfError++;
  }

  cout << " Making final tree for smearing ... " << endl;
  
  Int_t num_ArrayEvent_SM = num_ArrayEvent/nItem;
  
  Float_t ch1_max[num_ArrayEvent_SM];
  Float_t ch1_min[num_ArrayEvent_SM];
  Float_t ch2_max[num_ArrayEvent_SM];
  Float_t ch2_min[num_ArrayEvent_SM];
  Float_t ch3_max[num_ArrayEvent_SM];
  Float_t ch3_min[num_ArrayEvent_SM];
  Float_t ch4_max[num_ArrayEvent_SM];
  Float_t ch4_min[num_ArrayEvent_SM];
  
  Float_t diffR_ch1[num_ArrayEvent_SM];
  Float_t diffR_ch2[num_ArrayEvent_SM];
  Float_t diffR_ch3[num_ArrayEvent_SM];
  Float_t diffR_ch4[num_ArrayEvent_SM];

  Float_t SMfADC_ch1[num_ArrayEvent_SM]; 
  Float_t SMfADC_ch2[num_ArrayEvent_SM]; 
  Float_t SMfADC_ch3[num_ArrayEvent_SM]; 
  Float_t SMfADC_ch4[num_ArrayEvent_SM];

  Float_t err_ch1[num_ArrayEvent_SM]; 
  Float_t err_ch2[num_ArrayEvent_SM]; 
  Float_t err_ch3[num_ArrayEvent_SM]; 
  Float_t err_ch4[num_ArrayEvent_SM]; 

  for(int iinit=0; iinit<num_ArrayEvent_SM; iinit++)
  {
    ch1_max[iinit]=0;
    ch2_max[iinit]=0;
    ch3_max[iinit]=0;
    ch4_max[iinit]=0;
    
    ch1_min[iinit]=0;
    ch2_min[iinit]=0;
    ch3_min[iinit]=0;
    ch4_min[iinit]=0;
  
    diffR_ch1[iinit]=0;
    diffR_ch2[iinit]=0;
    diffR_ch3[iinit]=0;
    diffR_ch4[iinit]=0;

    SMfADC_ch1[iinit]=0;
    SMfADC_ch2[iinit]=0;
    SMfADC_ch3[iinit]=0;
    SMfADC_ch4[iinit]=0;

    err_ch1[iinit]=0;
    err_ch2[iinit]=0;
    err_ch3[iinit]=0;
    err_ch4[iinit]=0;
  }

  Double_t pedestal[4]={0.};
  Double_t RMS[4]={0.};
  Double_t SumPed[4] = {0.};
  Double_t RMSsum[4] = {0.};

  const int MATRIXMAX = 10000;

  Double_t *pedcon_ch1 = new Double_t[num_ArrayEvent];
  pedcon_ch1[num_ArrayEvent] = {0.};
  Double_t pedcon_ch2[MATRIXMAX]={0.};
  Double_t pedcon_ch3[MATRIXMAX]={0.};
  Double_t pedcon_ch4[MATRIXMAX]={0.};
  
  Double_t RMScon_ch1[MATRIXMAX] = {0.};
  Double_t RMScon_ch2[MATRIXMAX] = {0.};
  Double_t RMScon_ch3[MATRIXMAX] = {0.};
  Double_t RMScon_ch4[MATRIXMAX] = {0.};

  TTree *finaltr = new TTree("finaldata","sort + smeared data");
  finaltr -> Branch("eventID",&eventID,"eventID/I");
  finaltr -> Branch("num_ArrayEvent_SM",&num_ArrayEvent_SM,"num_ArrayEvent_SM/I");
  finaltr -> Branch("num_Channel",&num_Channel,"num_Channel/I");
  finaltr -> Branch("RL",&RL,"RL/I");
  finaltr -> Branch("pedestal",&pedestal,"pedestal[4]/D");
  finaltr -> Branch("RMS",&RMS,"RMS[4]/D");
  finaltr -> Branch("SMfADC_ch1",&SMfADC_ch1,"SMfADC_ch1[num_ArrayEvent_SM]/F");
  finaltr -> Branch("SMfADC_ch2",&SMfADC_ch2,"SMfADC_ch2[num_ArrayEvent_SM]/F");
  finaltr -> Branch("SMfADC_ch3",&SMfADC_ch3,"SMfADC_ch3[num_ArrayEvent_SM]/F");
  finaltr -> Branch("SMfADC_ch4",&SMfADC_ch4,"SMfADC_ch4[num_ArrayEvent_SM]/F");
  finaltr -> Branch("err_ch1",&err_ch1,"err_ch1[num_ArrayEvent_SM]/F");
  finaltr -> Branch("err_ch2",&err_ch2,"err_ch2[num_ArrayEvent_SM]/F");
  finaltr -> Branch("err_ch3",&err_ch3,"err_ch3[num_ArrayEvent_SM]/F");
  finaltr -> Branch("err_ch4",&err_ch4,"err_ch4[num_ArrayEvent_SM]/F");


/*  
  fADC_ch1[num_ArrayEvent] = {0};
  fADC_ch2[num_ArrayEvent] = {0};
  fADC_ch3[num_ArrayEvent] = {0};
  fADC_ch4[num_ArrayEvent] = {0};
*/
  count =0;

  for(int i=0; i< numEntries_sort; i++)
  {
    newtr->GetEntry(i);
    eventID = i;

    for(int l=0;l<num_ArrayEvent;l++)
    {
      for(int il=0;il<num_ArrayEvent/32;il++)
      {
        if(l<32*(il+1)&&l>=32*il)
        {
          SumPed[0] += fADC_ch1[l];
          SumPed[1] += fADC_ch2[l];
          SumPed[2] += fADC_ch3[l];
          SumPed[3] += fADC_ch4[l];
          
          pedcon_ch1[il] = SumPed[0]/(l+1-32*il);
          pedcon_ch2[il] = SumPed[1]/(l+1-32*il);
          pedcon_ch3[il] = SumPed[2]/(l+1-32*il);
          pedcon_ch4[il] = SumPed[3]/(l+1-32*il);
       
          RMSsum[0] += TMath::Power((fADC_ch1[l]-pedcon_ch1[il]),2);
          RMSsum[1] += TMath::Power((fADC_ch2[l]-pedcon_ch2[il]),2);
          RMSsum[2] += TMath::Power((fADC_ch3[l]-pedcon_ch3[il]),2);
          RMSsum[3] += TMath::Power((fADC_ch4[l]-pedcon_ch4[il]),2);
       
          RMScon_ch1[l] = TMath::Sqrt(RMSsum[0]/(l+1-32*il));
          RMScon_ch2[l] = TMath::Sqrt(RMSsum[1]/(l+1-32*il));
          RMScon_ch3[l] = TMath::Sqrt(RMSsum[2]/(l+1-32*il));
          RMScon_ch4[l] = TMath::Sqrt(RMSsum[3]/(l+1-32*il));

          if(l==32*(il+1)-1)
          {
            SumPed[0] = 0;
            SumPed[1] = 0;
            SumPed[2] = 0;
            SumPed[3] = 0;
        
            RMSsum[0] = 0;
            RMSsum[1] = 0;
            RMSsum[2] = 0;
            RMSsum[3] = 0;
          }
        }
      }
    }

    pedestal[0] = pedcon_ch1[0];
    pedestal[1] = pedcon_ch2[0];
    pedestal[2] = pedcon_ch3[0];
    pedestal[3] = pedcon_ch4[0];
    
    RMS[0] = RMScon_ch1[0];
    RMS[1] = RMScon_ch2[0];
    RMS[2] = RMScon_ch3[0];
    RMS[3] = RMScon_ch4[0];

    for(int iped=0;iped<num_ArrayEvent/32;iped++)
    {
      if(RMScon_ch1[iped]<RMS[0])
      {
        RMS[0] = RMScon_ch1[iped];
        pedestal[0] = pedcon_ch1[iped];
      }
      
      if(RMScon_ch2[iped]<RMS[1])
      {
        RMS[1] = RMScon_ch2[iped];
        pedestal[1] = pedcon_ch2[iped];
      }
      
      if(RMScon_ch3[iped]<RMS[2])
      {
        RMS[2] = RMScon_ch3[iped];
        pedestal[2] = pedcon_ch3[iped];
      }
      
      if(RMScon_ch4[iped]<RMS[3])
      {
        RMS[3] = RMScon_ch4[iped];
        pedestal[3] = pedcon_ch4[iped];
      }
    }



    for(int j=0; j<num_ArrayEvent_SM; j++)
    {
      ch1_max[j] = fADC_ch1[nItem*j];
      ch1_min[j] = fADC_ch1[nItem*j];
      
      ch2_max[j] = fADC_ch2[nItem*j];
      ch2_min[j] = fADC_ch2[nItem*j];
      
      ch3_max[j] = fADC_ch3[nItem*j];
      ch3_min[j] = fADC_ch3[nItem*j];
      
      ch4_max[j] = fADC_ch4[nItem*j];
      ch4_min[j] = fADC_ch4[nItem*j];
    
      for(int k=0; k<nItem; k++)
      {
        if(fADC_ch1[nItem*j+k]>ch1_max[j]) ch1_max[j]=fADC_ch1[nItem*j+k];
        if(fADC_ch1[nItem*j+k]<ch1_min[j]) ch1_min[j]=fADC_ch1[nItem*j+k];
        
        if(fADC_ch2[nItem*j+k]>ch2_max[j]) ch2_max[j]=fADC_ch2[nItem*j+k];
        if(fADC_ch2[nItem*j+k]<ch2_min[j]) ch2_min[j]=fADC_ch2[nItem*j+k];
        
        if(fADC_ch3[nItem*j+k]>ch3_max[j]) ch3_max[j]=fADC_ch3[nItem*j+k];
        if(fADC_ch3[nItem*j+k]<ch3_min[j]) ch3_min[j]=fADC_ch3[nItem*j+k];
        
        if(fADC_ch4[nItem*j+k]>ch4_max[j]) ch4_max[j]=fADC_ch4[nItem*j+k];
        if(fADC_ch4[nItem*j+k]<ch4_min[j]) ch4_min[j]=fADC_ch4[nItem*j+k];
        
        SMfADC_ch1[j] += fADC_ch1[nItem*j+k];
        SMfADC_ch2[j] += fADC_ch2[nItem*j+k];
        SMfADC_ch3[j] += fADC_ch3[nItem*j+k];
        SMfADC_ch4[j] += fADC_ch4[nItem*j+k];
      }
      
      SMfADC_ch1[j] = SMfADC_ch1[j]/(float)nItem;
      SMfADC_ch2[j] = SMfADC_ch2[j]/(float)nItem;
      SMfADC_ch3[j] = SMfADC_ch3[j]/(float)nItem;
      SMfADC_ch4[j] = SMfADC_ch4[j]/(float)nItem;
      
      diffR_ch1[j] = TMath::Abs(ch1_max[j] - ch1_min[j]);
      diffR_ch2[j] = TMath::Abs(ch2_max[j] - ch2_min[j]);
      diffR_ch3[j] = TMath::Abs(ch3_max[j] - ch3_min[j]);
      diffR_ch4[j] = TMath::Abs(ch4_max[j] - ch4_min[j]);

      err_ch1[j] = diffR_ch1[j]/(2*TMath::Sqrt(nItem)); 
      err_ch2[j] = diffR_ch2[j]/(2*TMath::Sqrt(nItem)); 
      err_ch3[j] = diffR_ch3[j]/(2*TMath::Sqrt(nItem)); 
      err_ch4[j] = diffR_ch4[j]/(2*TMath::Sqrt(nItem)); 
    }
    
    finaltr -> Fill();
    for(int jj=0;jj<num_ArrayEvent_SM;jj++)
    {
      SMfADC_ch1[jj]=0;
      SMfADC_ch2[jj]=0;
      SMfADC_ch3[jj]=0;
      SMfADC_ch4[jj]=0;
    }
    count++;
    if(count%10000==0) cout << " reading eventID... : " << count << " / " << numEntries << " (" << (int)(100.*count/numEntries) << "%)" << endl;
  } 
 
  const int numEntries_final = finaltr->GetEntries();
  cout << endl; 
  cout << endl;
  cout << " Done ! " << endl;
  cout << " Event loop end ! " << endl;
  cout << endl;
  cout << " Fill Check " << endl;
  cout << endl;

  if( (count!=numEntries_final) || (numEntries_final!=numEntries_sort) || (numEntries_final!=numEntries) )
  {
    cout << " ERROR !! " << endl;
    cout << " Total # of event mismatch! " << endl;
    cout << " count : " << count << endl;
    cout << " fill  : " << finaltr->GetEntries() << endl;
    cout << " newtr : " << newtr->GetEntries() << endl;
    NumOfError++;
  }

  //check 25 samples :: 5 random events with 5 random points
  Float_t checkSMfadc=0.;
  Float_t checkfadc=0;
  TRandom* rnd = new TRandom();
  Int_t ranEvtN[5], ranArrN[5];
  for(int iran=0; iran<5; iran++)
  {
    ranEvtN[iran] = rnd->Integer(numEntries_sort);
    ranArrN[iran] = rnd->Integer(num_ArrayEvent_SM);
  }
  
  for(int ievt=0; ievt<5; ievt++)
  {
    newtr->GetEntry(ranEvtN[ievt]);
    finaltr->GetEntry(ranEvtN[ievt]);
    for(int iarr=0; iarr<5; iarr++)
    {
      checkSMfadc = SMfADC_ch1[ranArrN[iarr]];
      for(int j=0; j<nItem; j++)
      {
        checkfadc += fADC_ch1[ranArrN[iarr]*nItem+j];
      }
      
      checkfadc = checkfadc/(float)nItem;
      if(checkfadc != checkSMfadc)
      {
        cout << endl;
        cout << " *********************************** " << endl;
        cout << " ERROR!!!! SMEARING MISMATCH!! " << endl;
        cout << " Wrong smearing during sample check " << endl;
        cout << " Random Event Number : " << ranEvtN[ievt] << endl;
        cout << " Random Point after smearing : " << ranArrN[iarr] << endl;
        cout << " Random Point before smearing from : " << ranArrN[iarr]*nItem << " until " << (ranArrN[iarr]*nItem+nItem-1) << endl;
        cout << " # of smearing points (nItem) : " << nItem << endl;
        cout << endl;
        cout << " ADC after smearing (checkSMfadc) : " << checkSMfadc << endl;
        cout << " ADC befor smearing (checkfadc) : " << checkfadc << endl;
        cout << " *********************************** " << endl;
        cout << endl;
        NumOfError++;
      }
      checkSMfadc = 0;
      checkfadc = 0;
    }
  }
  
  cout << endl;
  cout << " Fill check done !!! " << endl;
  cout << endl; 
  cout << endl; 
  cout << endl; 

  cout << " ********************************************************************* " << endl;
  cout << " ********************************************************************* " << endl;
  cout << " ******** ############### SMEARING SUMMARY ################# ********* " << endl;
  cout << " ********                                                    ********* " << endl;
  cout << " Number of events original            : " << numEntries << endl;
  cout << " Number of events sorted              : " << numEntries_sort << endl;
  cout << " Number of events smeared             : " << numEntries_final << endl;
  cout << " Number of used channel               : " << num_Channel << endl;
  cout << " Recording Length in sorted (ns)      : " << num_ArrayEvent*2.5 << endl;
  cout << " Number of points in array (sorted)   : " << num_ArrayEvent << endl;
  cout << " Number of points in array (smeared)  : " << num_ArrayEvent_SM << endl;
  cout << " Number of smeared points             : " << nItem << endl;
  cout << " Name of reading file                 : " << inputFileName << endl;
  cout << " Name of writing file                 : " << outputFileName << endl;
  cout << " Number of Errors occured             : " << NumOfError << endl;
  cout << " ********                                                    ********* " << endl;
  cout << " ********************************************************************* " << endl;
  cout << " ********************************************************************* " << endl;
  cout << endl; 
  cout << endl; 
  if(NumOfError==0)
  {
    cout << endl;
    cout << " #################### " << endl;
    cout << " Number of Error!! : " << NumOfError << endl;
    cout << " No Error Found! Everything is OK! " << endl;
    cout << " #################### " << endl;
    cout << endl;
    cout << " Now write and close file " << endl;
    cout << endl;

    writeFile -> cd();
    finaltr -> Write(); 
    newtr -> Write(); 

    cout << " **** FINISH **** " << endl;
    cout << " output file : " << outputFileName << " is written ! " << endl;
    cout << " **** DONE   **** " << endl;
    writeFile->Close();
  }
  else if(NumOfError!=0)
  {
    cout << endl;
    cout << " ERROR!!! ERROR!!! ERROR!!!" << endl;
    cout << " Error occured !! " << endl;
    cout << " # of errors  : " << NumOfError << endl;
    cout << endl;
    cout << " CANNOT WRITE .... CLOSE FILE ..." << endl;
    cout << endl;
  }
    
  
 /*
        else if(j>=num_ArrayEvent*k && j<num_ArrayEvent*(k+1) && k==1) fADC_ch2[fillInt] = myData.fadc_FADC[j]; 
        else if(j>=num_ArrayEvent*k && j<num_ArrayEvent*(k+1) && k==2) fADC_ch3[fillInt] = myData.fadc_FADC[j]; 
        else if(j>=num_ArrayEvent*k && j<num_ArrayEvent*(k+1) && k==3) fADC_ch4[fillInt] = myData.fadc_FADC[j];
  */      
    return 0;
         
}  
  
   



























