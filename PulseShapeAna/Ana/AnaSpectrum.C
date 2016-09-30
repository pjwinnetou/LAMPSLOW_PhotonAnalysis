void AnaSpectrum(){
  gROOT->Macro("~/rootlogon.C");
  TFile *f1 = new TFile("fitted_Cs137_2100_60_100000_1_front_32_ss.root","READ");
  TTree *tr = (TTree*)f1->Get("tr");
  TH1F *h = new TH1F("h",";Energy;Counts",100,0.0,2000);

  TCanvas *c1 = new TCanvas();
  tr->Draw("Pint>>h","chisq/NDF < 2.0 && Pfheight > 10 && (IntEndVal-Pfheight_x) > 20 && tau_f < 15.0","");
  h->Draw();
  c1->SaveAs("simple_energy.png");

  tr->Draw("Pint>>h","chisq/NDF < 2.0 && Pfheight > 10 && (IntEndVal-Pfheight_x) > 20 && tau_f < 15.0 && tau_s > 15","");
  h->Draw();
  c1->SaveAs("simple_energy_taus.png");

  tr->Draw("Pint>>h","chisq/NDF < 2.0 && Pfheight > 10 && (IntEndVal-Pfheight_x) > 20 && tau_f < 15.0 && tau_r < 10","");
  h->Draw();
  c1->SaveAs("simple_energy_taur.png");

  tr->Draw("Pint>>h","chisq > 20.0 && chisq < 80.0 && Pfheight > 10 && (IntEndVal-Pfheight_x) > 20 ","");
  h->Draw();
  c1->SaveAs("simple_energy_with_chi2.png");

  tr->Draw("Pint>>h","chisq/NDF < 2.0 && Pfheight > 10 && (IntEndVal-Pfheight_x) > 20 && tau_r > 0.25 && tau_f < 15.0 ","");
  h->Draw();
  c1->SaveAs("simple_energy_with_tauR.png");

  tr->Draw("Pint>>h","chisq/NDF < 2.0 && Pfheight > 10 && (IntEndVal-Pfheight_x) > 20 && A > 1000","");
  h->Draw();
  c1->SaveAs("simple_energy_withA.png");

  tr->Draw("Pint>>h","chisq/NDF < 2.0 && Pfheight > 10 && (IntEndVal-Pfheight_x) > 20 && tau_f < 10.0","");
  h->Draw();
  c1->SaveAs("simple_energy_tauf10.png");

  tr->Draw("Pint>>h","chisq/NDF < 2.0 && Pfheight > 10 && (IntEndVal-Pfheight_x) > 20 && tau_f < 5.0","");
  h->Draw();
  c1->SaveAs("simple_energy_tauf5.png");

  tr->Draw("Pint>>h","Pfheight > 10 && (IntEndVal-Pfheight_x) > 20 && tau_f < 15.0","");
  h->Draw();
  c1->SaveAs("simple_energy_no_chisq.png");

  tr->Draw("Pint>>h","chisq/NDF < 2.0 && (IntEndVal-Pfheight_x) > 20 && tau_f < 15.0","");
  h->Draw();
  c1->SaveAs("simple_energy_no_Pfheight.png");

  tr->Draw("Pint>>h","chisq/NDF < 2.0 && Pfheight > 10 && tau_f < 15.0","");
  h->Draw();
  c1->SaveAs("simple_energy_no_intval.png");

  tr->Draw("Pint>>h","chisq/NDF < 2.0 && Pfheight > 10 && (IntEndVal-Pfheight_x) > 20 ","");
  h->Draw();
  c1->SaveAs("simple_energy_no_tauf.png");

}
