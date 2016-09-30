void dataAna(){
  gROOT->Macro("~/rootlogon.C");
  TFile *f1 = new TFile("../Cs137_Ana_Sgn_Front.root","READ");
  TFile *f2 = new TFile("../Cs137_Ana_Noise.root","READ");

  const int nbins = 200;
  TH1F *hSgn = new TH1F("hSgn",";Full Pulse Charge (Channel);Counts",nbins,0.0,2000);
  TH1F *hNos = new TH1F("hNos",";Full Pulse Charge (Channel);Counts",nbins,0.0,2000);
  hSgn->Sumw2();
  hNos->Sumw2();

  TTree *tr1 = (TTree*)f1->Get("data");
  TTree *tr2 = (TTree*)f2->Get("data");

  // Cut condition applied 
  //tr1->Draw("Pint>>hSgn","","");
  //tr2->Draw("Pint>>hNos","","");
  //tr1->Draw("Pint>>hSgn","Pfheight > 40 && chisq < 0.006 && tau_r > 0.20 && tau_f < 20.0 && (IntEndVal-Pfheight_x) > 30","");
  //tr2->Draw("Pint>>hNos","Pfheight > 40 && chisq < 0.006 && tau_r > 0.20 && tau_f < 20.0 && (IntEndVal-Pfheight_x) > 30","");
  //tr1->Draw("Pint>>hSgn","Pfheight > 10 && chisq/NDF < 2.0 && tau_f < 15.0 && (IntEndVal-Pfheight_x) > 20 && tau_r < 15","");
  //tr2->Draw("Pint>>hNos","Pfheight > 10 && chisq/NDF < 2.0 && tau_f < 15.0 && (IntEndVal-Pfheight_x) > 20 && tau_r < 15","");
  tr1->Draw("Pint>>hSgn","Pfheight > 10 && chisq/NDF < 2.0 && tau_f < 15.0 && (IntEndVal-Pfheight_x) > 20 && tau_r < 10 && tau_s > 15","");
  tr2->Draw("Pint>>hNos","Pfheight > 10 && chisq/NDF < 2.0 && tau_f < 15.0 && (IntEndVal-Pfheight_x) > 20 && tau_r < 10 && tau_s > 15","");

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

  c3->SaveAs("plot_Sgn_comp2.png");


  TCanvas *c1 = new TCanvas("c1","",1200, 600);
  c1->Divide(2,1);
  c1->cd(1);
  hSgn->Draw();
  c1->cd(2);
  hNos->Draw();

  c1->SaveAs("plot_Sgn_Noise2.png");

  TCanvas *c2 = new TCanvas("c2","",1200,600);
  c2->cd();
  hSgn->Add(hNos,-1);
  hSgn->SetMinimum(0.0);
  hSgn->Draw("HIST");

  c2->SaveAs("plot_Sgn_sub2.png");

}
