void dataAna_Co(){
  gROOT->Macro("~/rootlogon.C");
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);

  TLatex *lt1 = new TLatex();
  lt1->SetNDC();
  lt1->SetTextSize(0.03);

  TFile *f1 = new TFile("./fitted_New_Co60_2100_140_100000_1_front_32_ss.root","READ");
  TFile *f2 = new TFile("./fitted_noise_2100_140_100000_Co_32_ss.root","READ");

  const int nbins = 234;
  TH1F *hSgn = new TH1F("hSgn",";Full Pulse Charge (Channel);Counts",nbins,1000.0,4000);
  TH1F *hNos = new TH1F("hNos",";Full Pulse Charge (Channel);Counts",nbins,1000.0,4000);
  hSgn->Sumw2();
  hNos->Sumw2();

  TTree *tr1 = (TTree*)f1->Get("tr");
  TTree *tr2 = (TTree*)f2->Get("tr");

  float Pfheight, Pfheight_x, IntEndVal,chisq, NDF, Pint, chisqprob, tau_r;

  tr1->SetBranchAddress("Pint",&Pint);
  tr1->SetBranchAddress("chisq",&chisq);
  tr1->SetBranchAddress("chisqprob",&chisqprob);
  tr1->SetBranchAddress("NDF",&NDF);
  tr1->SetBranchAddress("tau_r",&tau_r);
  tr1->SetBranchAddress("IntEndVal",&IntEndVal);
  tr1->SetBranchAddress("Pfheight",&Pfheight);
  tr1->SetBranchAddress("Pfheight_x",&Pfheight_x);
  
  tr2->SetBranchAddress("Pint",&Pint);
  tr2->SetBranchAddress("chisq",&chisq);
  tr2->SetBranchAddress("chisqprob",&chisqprob);
  tr2->SetBranchAddress("NDF",&NDF);
  tr2->SetBranchAddress("tau_r",&tau_r);
  tr2->SetBranchAddress("IntEndVal",&IntEndVal);
  tr2->SetBranchAddress("Pfheight",&Pfheight);
  tr2->SetBranchAddress("Pfheight_x",&Pfheight_x);

  double sf = 0.0342; // scale factor for noise (3.42%) for co

  const int nbins1 = 234;

  double countperbin = 2000./nbins1;
  TH1D *hSgn1 = new TH1D("hSgn1",Form(";Energy (KeV) ;Events / (%.3f KeV)",countperbin),nbins1,0,2000);
  TH1D *hNos1 = new TH1D("hNos1",";Energy (KeV) ;Counts",nbins1,0,2000);

  // Cut condition applied (23 keV threshold)
  tr1->Draw("Pint>>hSgn","chisq/NDF >0.4 && chisq/NDF < 10.0 && chisqprob < 1.0 && chisqprob > 0.0 && tau_r > 0.2 && tau_r < 7.0 && Pint > 50.0","");
  tr2->Draw("Pint>>hNos","chisq/NDF >0.4 && chisq/NDF < 10.0 && chisqprob < 1.0 && chisqprob > 0.0 && tau_r > 0.2 && tau_r < 7.0 && Pint > 50.0","");
/*  tr1->Draw("Pint>>hSgn1","chisq/NDF >0.4 && chisq/NDF < 10.0 && chisqprob < 1.0 && chisqprob > 0.0 && tau_r > 0.2 && tau_r < 7.0 && Pint > 50.0","");
  tr2->Draw("Pint>>hNos1","chisq/NDF >0.4 && chisq/NDF < 10.0 && chisqprob < 1.0 && chisqprob > 0.0 && tau_r > 0.2 && tau_r < 7.0 && Pint > 50.0","");
*/  //tr1->Draw("Pint>>hSgn","chisq/NDF >0.4 && chisq/NDF < 2.0 && chisqprob < 1.0 && chisqprob > 0.0 && tau_r > 0.2 && Pint > 50.0","");
  //tr2->Draw("Pint>>hNos","chisq/NDF >0.4 && chisq/NDF < 2.0 && chisqprob < 1.0 && chisqprob > 0.0 && tau_r > 0.2 && Pint > 50.0","")

  for(int i=0;i<tr1->GetEntries();i++)
  {
    tr1->GetEntry(i);
    if(chisq/NDF >0.4 && chisq/NDF < 5.0 && IntEndVal-Pfheight_x>20 && chisqprob < 1.0 && chisqprob > 0.0 && tau_r> 0.2 && Pint > 50.0) hSgn1->Fill(Pint*160/371+53.4501348);
  }
  for(int i=0;i<tr1->GetEntries();i++)
  {
    tr2->GetEntry(i);
    if(chisq/NDF >0.4 && chisq/NDF < 5.0 && chisqprob < 1.0 && chisqprob > 0.0 && tau_r > 0.2 && Pint > 50.0) hNos1->Fill(Pint*160/371+53.4501348);
  }


  TF1 *ff = new TF1("ff", "gaus(0)+gaus(3)+[6]*x+[7]",930 , 1444);
  ff->SetParameters(420.877,1169.75,41.5825,539.165,1330.18,45.0762,-0.348473,553.134);
  ff->SetParLimits(0,80,700);
  ff->SetParLimits(1,1000,1300);
  ff->SetParLimits(2,0,200);
  ff->SetParLimits(3,100,900);
  ff->SetParLimits(4,1200,1500);
  ff->SetParLimits(5,20,120);
  ff->SetParLimits(6,-1.04542,1.04542);
  ff->SetParLimits(7,-1659.4,1659.4);
  

  TCanvas *cc = new TCanvas("cc","",800,800);
  hNos1->Scale(sf);
  hSgn1->Add(hNos1,-1);
  cc->cd();
  hSgn1->Draw("pe");
  hSgn1->Fit("ff","REM");

  hSgn1->SetLineColor(kBlue+2);
  hSgn1->SetMarkerColor(kBlue+2);
  hSgn1->SetMarkerStyle(20);

  double errmean1 = ff->GetParError(1);
  double errsigma1 = ff->GetParError(2);
  double errmean2 = ff->GetParError(4);
  double errsigma2 = ff->GetParError(5);

  double mean1 = ff->GetParameter(1);
  double sigma1 = ff->GetParameter(2);
  double mean2 = ff->GetParameter(4);
  double sigma2 = ff->GetParameter(5);

  double errsm1 = sigma1/mean1*TMath::Sqrt(TMath::Power(errsigma1/sigma1,2)+TMath::Power(errmean1/mean1,2));
  double errsm2 = sigma2/mean2*TMath::Sqrt(TMath::Power(errsigma2/sigma2,2)+TMath::Power(errmean2/mean2,2));

  double perc1 = ff->GetParameter(2)/ff->GetParameter(1);
  double perc2 = ff->GetParameter(5)/ff->GetParameter(4);
  double FWHM1;
  double FWHM2;
  FWHM1 = perc1*2.355;
  FWHM2 = perc2*2.355;
  double errFH1_r = errsm1/perc1;
  double errFH2_r = errsm2/perc2;
  
  double errFH1 = FWHM1*errFH1_r;
  double errFH2 = FWHM2*errFH2_r;

  lt1->DrawLatex(0.16,0.85,Form("#chi^{2}/ndf (1) : %0.2f/%d",ff->GetChisquare(),ff->GetNDF()));
  lt1->DrawLatex(0.16,0.79,Form("Mean (1) : %0.1f #pm %0.1f",ff->GetParameter(1),ff->GetParError(1)));
  lt1->DrawLatex(0.16,0.73,Form("FWHM (1) : %0.1f #pm %0.3f %%",FWHM1*100,errFH1));
  
  lt1->DrawLatex(0.16,0.65,Form("#chi^{2}/ndf (2) : %0.2f/%d",ff->GetChisquare(),ff->GetNDF()));
  lt1->DrawLatex(0.16,0.59,Form("Mean (2) : %0.1f #pm %0.1f",ff->GetParameter(4),ff->GetParError(4)));
  lt1->DrawLatex(0.16,0.53,Form("FWHM (2) : %0.1f #pm %0.3f %%",FWHM2*100,errFH2));

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

  TF1 *Gaus1 = new TF1("Gaus1","[0]*TMath::Gaus(x,[1],[2],1)",2390,2750);
  TF1 *Gaus2 = new TF1("Gaus2","[0]*TMath::Gaus(x,[1],[2],1)",2750,3400);
  Gaus1->SetParNames("Yields","Mean","Sigma");
  Gaus1->SetLineColor(kRed+2);
  Gaus1->SetLineStyle(2);
  Gaus1->SetParameters(5,2500,100);
  Gaus2->SetParNames("Yields","Mean","Sigma");
  Gaus2->SetLineColor(kRed+2);
  Gaus2->SetLineStyle(2);
  Gaus2->SetParameters(5,2900,100);

  TF1 *TwoGaus = new TF1("TwoGaus","[0]*TMath::Gaus(x,[1],[2],1)+[3]*TMath::Gaus(x,[4],[5],1)",2390,3400);
  TwoGaus->SetParNames("Yields1","Mean1","Sigma1","Yields2","Mean2","Sigma2");
  TwoGaus->SetLineColor(kRed+2);
  TwoGaus->SetLineStyle(2);
  TwoGaus->SetParameters(5,2500,100,5,2900,100);

  TwoGaus->SetParameters(0, Gaus1->GetParameter(0));
  TwoGaus->SetParameters(1, Gaus1->GetParameter(1));
  TwoGaus->SetParameters(2, Gaus1->GetParameter(2));
  TwoGaus->SetParameters(3, Gaus2->GetParameter(0));
  TwoGaus->SetParameters(4, Gaus2->GetParameter(1));
  TwoGaus->SetParameters(5, Gaus2->GetParameter(2));

  Double_t par[9];
  TF1 *g1    = new TF1("g1","gaus",2390,2750);
  TF1 *g2    = new TF1("g2","gaus",2790,3200);
  TF1 *exp   = new TF1("exp","TMath::Exp([0]-x*[1])",2350,3250);
  TF1 *total = new TF1("total","gaus(0)+gaus(3)",2390,3200);
  TF1 *totalEx = new TF1("totalEx","gaus(0)+gaus(3)+exp(6)",2300,3300);
  total->SetLineColor(2);
  total->SetLineStyle(1);
//  hSgn->Fit(g1,"REM");
//  hSgn->Fit(g2,"REM+");
  //hSgn->Fit(exp,"R+");
  g1->GetParameters(&par[0]);
  g2->GetParameters(&par[3]);
  //exp->SetParameters(&par[6]);
  total->SetParameters(par);
  //totalEx->SetParameters(par);

  TCanvas *c2 = new TCanvas("c2","",800,600);
  c2->cd();
  hSgn->Add(hNos,-1);
  hSgn->SetMinimum(0.0);
  hSgn->SetMarkerStyle(20);
  //hSgn->Fit("Gaus1","R");
  //hSgn->Fit("Gaus2","R+");

  TwoGaus->SetParameters(0, Gaus1->GetParameter(0));
  TwoGaus->SetParameters(1, Gaus1->GetParameter(1));
  TwoGaus->SetParameters(2, Gaus1->GetParameter(2));
  TwoGaus->SetParameters(3, Gaus2->GetParameter(0));
  TwoGaus->SetParameters(4, Gaus2->GetParameter(1));
  TwoGaus->SetParameters(5, Gaus2->GetParameter(2));

  totalEx->SetLineColor(1);

//  hSgn->Fit("total","REM+");
  //hSgn->Fit("totalEx","R+");
  //hSgn->Fit("TwoGaus","R+");

  //hSgn->Draw("E");
  //hSgn->Draw("HIST");
  lt1->DrawLatex(0.17,0.9,Form("#chi^{2}/ndf (1) : %0.2f/%d",g1->GetChisquare(),g1->GetNDF()));
  lt1->DrawLatex(0.17,0.84,Form("Mean (1) : %0.1f #pm %0.1f",g1->GetParameter(1),g1->GetParError(1)));
  lt1->DrawLatex(0.17,0.78,Form("#sigma (1) : %0.1f #pm %0.2f (%0.1f%%)",g1->GetParameter(2),g1->GetParError(2),g1->GetParameter(2)/g1->GetParameter(1)*100));

  lt1->DrawLatex(0.17,0.70,Form("#chi^{2}/ndf (2) : %0.2f/%d",g2->GetChisquare(),g2->GetNDF()));
  lt1->DrawLatex(0.17,0.64,Form("Mean (2) : %0.1f #pm %0.1f",g2->GetParameter(1),g2->GetParError(1)));
  lt1->DrawLatex(0.17,0.58,Form("#sigma (2) : %0.1f #pm %0.2f (%0.1f%%)",g2->GetParameter(2),g2->GetParError(2),g2->GetParameter(2)/g2->GetParameter(1)*100));

  c2->SaveAs("plot_Sgn_sub.png");

}
