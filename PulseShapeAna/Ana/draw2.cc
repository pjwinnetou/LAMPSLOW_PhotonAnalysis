class data {
  public:
   UChar_t fadc_trigger[2];
   UChar_t fadc_tag[6];
   Float_t fadc_FADC[8192];
};

void draw2() {
  data myData;

  cout << sizeof(data) << endl;

  auto file = new TFile("Co60_2310_385_1.root");
  auto tree = (TTree *) file -> Get("nfadc400");
  tree -> SetBranchAddress("fadc", myData.fadc_trigger);

  Int_t numEntries = tree -> GetEntries();
  for (Int_t i = 0; i < numEntries; i++) {
    tree -> GetEntry(i);

//    cout << myData.fadc_FADC[0] << endl;
  }
}
