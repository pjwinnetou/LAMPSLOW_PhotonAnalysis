void draw3() {
  auto file = new TFile("Co60_2310_385_1.root");
  auto tree = (TTree *) file -> Get("nfadc400");

  Float_t num[8192];
  for (Int_t i = 0; i < 8192; i++)
    num[i] = i;

  tree -> GetEntry(0);
  Float_t *adc = (Float_t *) tree -> GetLeaf("fadc", "FADC") -> GetValuePointer();

  cout << adc[0] << " " << adc[10] << endl;

  auto graph = new TGraph(8192, num, adc);
  graph -> Draw("AL");

/*
  Int_t numEntries = tree -> GetEntries();
  for (Int_t i = 0; i < numEntries; i++) {
    tree -> GetEntry(i);

    cout << tree -> GetLeaf("fadc", "FADC") -> GetValue(0) << endl;
  }
*/
}
