#include <iostream>
#include "TGraphErrors.h" 
#include "TROOT.h"

void resolution()
{
  TGraphErrors *g1 = new TGraphErrors();

  g1->SetPoint(0,662,12.2); 
  g1->SetPoint(1,1170,8.3); 
  g1->SetPoint(2,1330,7.9);

  g1->SetPointError(0,0,0.001);
  g1->SetPointError(1,0,0.002);
  g1->SetPointError(2,0,0.002);

  g1->SetMarkerColor(kRed+2);
  g1->SetMarkerStyle(20);
  g1->Draw("AP");
  g1->GetHistogram()->GetYaxis()->SetRangeUser(0,18);
  g1->GetHistogram()->GetXaxis()->SetRangeUser(300,1500);
  g1->GetHistogram()->GetXaxis()->SetTitle("Energy (KeV)");
  g1->GetHistogram()->GetYaxis()->SetTitle("FWHM (%)");
}
