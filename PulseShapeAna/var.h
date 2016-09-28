#ifndef var_C
#define var_C

class data
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

//TString inputfile = "Cs137_2310_214_1_32_ss.root";
//TString inputfile = "Cs137_2310_214_2_32_ss.root";
TString inputfile = "Cs137_2310_214_32_ss.root";


#endif
