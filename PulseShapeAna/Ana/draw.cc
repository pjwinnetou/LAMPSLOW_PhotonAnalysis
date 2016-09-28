#include "nfadc400.C"

void draw() {
  nfadc400 a;

/*
  Float_t num[8192];
  for (Int_t i = 0; i < 8192; i++)
    num[i] = i;

  auto graph = new TGraph(8192, num, a.fadc_FADC);
  graph -> Draw("AL");
*/

  Int_t numEntries = a.fChain -> GetEntries();
  for (Int_t iEvent = 0; iEvent < numEntries; iEvent++) {
    a.GetEntry(iEvent); // <--- Event number

    cout << a.fadc_FADC[0] << endl;
  }
}
