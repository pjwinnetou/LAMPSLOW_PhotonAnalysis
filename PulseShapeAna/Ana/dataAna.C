void dataAna(){
  gROOT->Macro("~/rootlogon.C");
  gStyle->SetOptFit(0);

  TLatex *lt1 = new TLatex();
  lt1->SetNDC();

  TFile *f1 = new TFile("../fitted_New_JBSet_Cs137_2100_60_100000_1_front_32_ss_4thFits.root","READ");
  TFile *f2 = new TFile("../fitted_New_JBSet_noise_2100_60_100000_Cs_32_ss_4thFits.root","READ");

  const int nbins = 200;
  TH1F *hSgn = new TH1F("hSgn",";Full Pulse Charge (Channel);Counts",nbins,0.0,2000);
  TH1F *hNos = new TH1F("hNos",";Full Pulse Charge (Channel);Counts",nbins,0.0,2000);
  hSgn->Sumw2();
  hNos->Sumw2();

  TTree *tr1 = (TTree*)f1->Get("tr");
  TTree *tr2 = (TTree*)f2->Get("tr");

  // Cut condition applied (23 keV threshold)
  tr1->Draw("Pint>>hSgn","chisq/NDF >0.4 && chisq/NDF < 2.0 && chisqprob < 1.0 && chisqprob > 0.0 && tau_r > 0.2 && Pint > 50.0","");
  tr2->Draw("Pint>>hNos","chisq/NDF >0.4 && chisq/NDF < 2.0 && chisqprob < 1.0 && chisqprob > 0.0 && tau_r > 0.2 && Pint > 50.0","");

  hSgn->Draw();
  hNos->Draw();

  double sf = 0.14; // scale factor for noise (14%)

  hSgn->SetLineColor(kBlue+2);
  hNos->SetLineColor(kRed+2);
  hSgn->SetMarkerColor(kBlue+2);
  hNos->SetMarkerColor(kRed+2);
  hNos->SetLineStyle(2);
  hSgn->SetMarkerStyle(20);
  hNos->SetMarkerStyle(20);
  hNos->Scale(sf);

  TCanvas *c3 = new TCanvas("c3","",600,600);
  c3->cd();
  hSgn->Draw("Hist");
  hNos->Draw("same Hist");

  c3->SaveAs("plot_Sgn_comp.png");


  TCanvas *c1 = new TCanvas("c1","",1200, 600);
  c1->Divide(2,1);
  c1->cd(1);
  hSgn->Draw();
  c1->cd(2);
  hNos->Draw();

  c1->SaveAs("plot_Sgn_Noise.png");

  TF1 *Gaus = new TF1("Gaus","[0]*TMath::Gaus(x,[1],[2],1)",1300,1500);
  Gaus->SetParNames("Yields","Mean","Sigma");
  Gaus->SetLineColor(kRed+2);
  Gaus->SetLineStyle(2);
  Gaus->SetParameters(5,1400,100);

  TCanvas *c2 = new TCanvas("c2","",800,600);
  c2->cd();
  hSgn->Add(hNos,-1);
  hSgn->SetMinimum(0.0);
  hSgn->Fit("Gaus","MQR");
  //hSgn->Draw("E");
  //hSgn->Draw("HIST");
  lt1->DrawLatex(0.2,0.9,Form("#chi^{2}/ndf : %0.2f/%d",Gaus->GetChisquare(),Gaus->GetNDF()));
  lt1->DrawLatex(0.2,0.84,Form("Mean : %0.1f #pm %0.1f",Gaus->GetParameter(1),Gaus->GetParError(1)));
  lt1->DrawLatex(0.2,0.78,Form("#sigma : %0.1f #pm %0.2f (%0.1f%%)",Gaus->GetParameter(2),Gaus->GetParError(2),Gaus->GetParameter(2)/Gaus->GetParameter(1)*100));
  cout<<" NDF : "<<Gaus->GetNDF()<<endl;

  c2->SaveAs("plot_Sgn_sub.png");

}
