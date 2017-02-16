// This is the macro to draw variables related to pulse taken from data 
// and compare signal and noise
// Please contact to dhmoon@chonnam.ac.kr, if you need

void cutStudy2D(){
  gROOT->Macro("~/rootlogon.C");
  TFile *f1 = new TFile("../fitted_New_JBSet_Cs137_2100_60_100000_1_front_32_ss_4thFits.root","READ");
  TFile *f2 = new TFile("../fitted_New_JBSet_noise_2100_60_100000_Cs_32_ss_4thFits.root","READ");

  TTree *tr1 = (TTree*)f1->Get("tr");
  TTree *tr2 = (TTree*)f2->Get("tr");

  TH2F *h1PintA = new TH2F("h1PintA",";Pint;A",2000,0.0,2000,2000,0.0,2000);
  TH2F *h1PintChi2 = new TH2F("h1PintChi2",";Pint;Chi2",2000,0.0,2000,1000,0.0,100);
  TH2F *h1PintChi2NDF = new TH2F("h1PintChi2NDF",";Pint;Chi2/NDF",2000,0.0,2000,1000,0.0,3.0);
  TH2F *h1PintChi2Prob = new TH2F("h1PintChi2Prob",";Pint;Chi2 Prob",2000,0.0,2000,120,0.9,1.2);
  TH2F *h1PintT0 = new TH2F("h1PintT0",";Pint;T0",2000,0.0,2000,1000,0.0,1000);
  TH2F *h1PintTauR = new TH2F("h1PintTauR",";Pint;tau_r",2000,0.0,2000,1000,0.0,100);
  TH2F *h1PintTauR2 = new TH2F("h1PintTauR2",";Pint;tau_r",2000,0.0,2000,900,0.0,30);
  TH2F *h1PintTauR3 = new TH2F("h1PintTauR3",";Pint;tau_r",2000,0.0,2000,1000,0.0,10);
  TH2F *h1PintTauR4 = new TH2F("h1PintTauR4",";Pint;tau_r",2000,0.0,2000,400,0.0,4);
  TH2F *h1PintTauF = new TH2F("h1PintTauF",";Pint;tau_f",2000,0.0,2000,1000,0.0,100);
  TH2F *h1PintTauF2 = new TH2F("h1PintTauF2",";Pint;tau_f",2000,0.0,2000,1000,0.0,20);
  TH2F *h1PintTauS = new TH2F("h1PintTauS",";Pint;tau_s",2000,0.0,2000,1000,0.0,1000);
  TH2F *h1PintTauS2 = new TH2F("h1PintTauS2",";Pint;tau_s",2000,0.0,2000,600,0.0,200);
  TH2F *h1PintTauS3 = new TH2F("h1PintTauS3",";Pint;tau_s",2000,0.0,2000,400,0.0,80);
  TH2F *h1PintPheightX = new TH2F("h1PintPheightX",";Pint;Pfheight_x;",2000,0.0,2000,1000,0.0,100);
  TH2F *h1PintPheightX2 = new TH2F("h1PintPheightX2",";Pint;Pfheight_x;",2000,0.0,2000,1000,10,20);
  TH2F *h1PintPheight = new TH2F("h1PintPheight",";Pint;Pfheight;",2000,0.0,2000,1000,0.0,200);
  TH2F *h1PintRatio = new TH2F("h1PintRatio",";Pint;ratio",2000,0.0,2000,200,0.0,20);
  TH2F *h1PintEndValPheight = new TH2F("h1PintEndValPheight",";Pint;IntEndVal-Pfheight_x;",2000,0.0,2000,1000,0.0,100);
  TH2F *h1PintEndValPheight2 = new TH2F("h1PintEndValPheight2",";Pint;IntEndVal-Pfheight_x;",2000,0.0,2000,1000,10,50);

  TH2F *h2PintA = new TH2F("h2PintA",";Pint;A",2000,0.0,2000,2000,0.0,2000);
  TH2F *h2PintChi2 = new TH2F("h2PintChi2",";Pint;Chi2",2000,0.0,2000,1000,0.0,100);
  TH2F *h2PintChi2NDF = new TH2F("h2PintChi2NDF",";Pint;Chi2/NDF",2000,0.0,2000,900,0.0,3);
  TH2F *h2PintChi2Prob = new TH2F("h2PintChi2Prob",";Pint;Chi2 Prob",2000,0.0,2000,120,0.9,1.2);
  TH2F *h2PintT0 = new TH2F("h2PintT0",";Pint;T0",2000,0.0,2000,200,0.0,20);
  TH2F *h2PintTauR = new TH2F("h2PintTauR",";Pint;tau_r",2000,0.0,2000,1000,0.0,100);
  TH2F *h2PintTauR2 = new TH2F("h2PintTauR2",";Pint;tau_r",2000,0.0,2000,900,0.0,30);
  TH2F *h2PintTauR3 = new TH2F("h2PintTauR3",";Pint;tau_r",2000,0.0,2000,1000,0.0,10);
  TH2F *h2PintTauR4 = new TH2F("h2PintTauR4",";Pint;tau_r",2000,0.0,2000,400,0.0,4);
  TH2F *h2PintTauF = new TH2F("h2PintTauF",";Pint;tau_f",2000,0.0,2000,1000,0.0,100);
  TH2F *h2PintTauF2 = new TH2F("h2PintTauF2",";Pint;tau_f",2000,0.0,2000,1000,0.0,20);
  TH2F *h2PintTauS = new TH2F("h2PintTauS",";Pint;tau_s",2000,0.0,2000,1000,0.0,1000);
  TH2F *h2PintTauS2 = new TH2F("h2PintTauS2",";Pint;tau_s",2000,0.0,2000,600,0.0,200);
  TH2F *h2PintTauS3 = new TH2F("h2PintTauS3",";Pint;tau_s",2000,0.0,2000,400,0.0,80);
  TH2F *h2PintPheightX = new TH2F("h2PintPheightX",";Pint;Pfheight_x;",2000,0.0,2000,1000,0.0,100);
  TH2F *h2PintPheightX2 = new TH2F("h2PintPheightX2",";Pint;Pfheight_x;",2000,0.0,2000,1000,10,20);
  TH2F *h2PintPheight = new TH2F("h2PintPheight",";Pint;Pfheight;",2000,0.0,2000,1000,0.0,200);
  TH2F *h2PintRatio = new TH2F("h2PintRatio",";Pint;Ratio",2000,0.0,2000,200,0.0,20);
  TH2F *h2PintEndValPheight = new TH2F("h2PintEndValPheight",";Pint;IntEndVal-Pfheight_x;",2000,0.0,2000,1000,0.0,100);
  TH2F *h2PintEndValPheight2 = new TH2F("h2PintEndValPheight2",";Pint;IntEndVal-Pfheight_x;",2000,0.0,2000,1000,0.0,50);


  tr1->Draw("A:Pint>>h1PintA","","colz");
  tr1->Draw("chisq:Pint>>h1PintChi2","","colz");
  tr1->Draw("chisq/NDF:Pint>>h1PintChi2NDF","","colz");
  tr1->Draw("chisqprob:Pint>>h1PintChi2Prob","","colz");
  tr1->Draw("t0:Pint>>h1PintT0","","colz");
  tr1->Draw("tau_r:Pint>>h1PintTauR","","colz");
  tr1->Draw("tau_f:Pint>>h1PintTauF","","colz");
  tr1->Draw("tau_s:Pint>>h1PintTauS","","colz");
  tr1->Draw("tau_r:Pint>>h1PintTauR2","","colz");
  tr1->Draw("tau_r:Pint>>h1PintTauR3","","colz");
  tr1->Draw("tau_r:Pint>>h1PintTauR4","","colz");
  tr1->Draw("tau_f:Pint>>h1PintTauF2","","colz");
  tr1->Draw("tau_s:Pint>>h1PintTauS2","","colz");
  tr1->Draw("tau_s:Pint>>h1PintTauS3","","colz");
  tr1->Draw("Pfheight_x:Pint>>h1PintPheightX","","colz");
  tr1->Draw("Pfheight_x:Pint>>h1PintPheightX2","","colz");
  tr1->Draw("Pfheight:Pint>>h1PintPheight","","colz");
  tr1->Draw("ratio:Pint>>h1PintRatio","","colz");
  tr1->Draw("(IntEndVal-Pfheight_x):Pint>>h1PintEndValPheight","","colz");
  tr1->Draw("(IntEndVal-Pfheight_x):Pint>>h1PintEndValPheight2","","colz");

  tr2->Draw("A:Pint>>h2PintA","","colz");
  tr2->Draw("chisq:Pint>>h2PintChi2","","colz");
  tr2->Draw("chisq/NDF:Pint>>h2PintChi2NDF","","colz");
  tr2->Draw("chisqprob:Pint>>h2PintChi2Prob","","colz");
  tr2->Draw("t0:Pint>>h2PintT0","","colz");
  tr2->Draw("tau_r:Pint>>h2PintTauR","","colz");
  tr2->Draw("tau_f:Pint>>h2PintTauF","","colz");
  tr2->Draw("tau_s:Pint>>h2PintTauS","","colz");
  tr2->Draw("tau_r:Pint>>h2PintTauR2","","colz");
  tr2->Draw("tau_r:Pint>>h2PintTauR3","","colz");
  tr2->Draw("tau_r:Pint>>h2PintTauR4","","colz");
  tr2->Draw("tau_f:Pint>>h2PintTauF2","","colz");
  tr2->Draw("tau_s:Pint>>h2PintTauS2","","colz");
  tr2->Draw("tau_s:Pint>>h2PintTauS3","","colz");
  tr2->Draw("Pfheight_x:Pint>>h2PintPheightX","","colz");
  tr2->Draw("Pfheight_x:Pint>>h2PintPheightX2","","colz");
  tr2->Draw("Pfheight:Pint>>h2PintPheight","","colz");
  tr2->Draw("ratio:Pint>>h2PintRatio","","colz");
  tr2->Draw("(IntEndVal-Pfheight_x):Pint>>h2PintEndValPheight","","colz");
  tr2->Draw("(IntEndVal-Pfheight_x):Pint>>h2PintEndValPheight2","","colz");

  TLatex *lt1 = new TLatex();
  lt1->SetNDC();

  TCanvas *c1 = new TCanvas("c1","",1200,600);
  c1->Divide(2,1);

  c1->cd(1); h1PintA->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Signal");
  c1->cd(2); h2PintA->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Noise");
  c1->SaveAs("plot_2D_PintA.png");

  c1->cd(1); h1PintChi2->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Signal");
  c1->cd(2); h2PintChi2->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Noise");
  c1->SaveAs("plot_2D_PintChi2.png");

  c1->cd(1); h1PintChi2NDF->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Signal");
  c1->cd(2); h2PintChi2NDF->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Noise");
  c1->SaveAs("plot_2D_PintChi2NDF.png");

  c1->cd(1); h1PintChi2Prob->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Signal");
  c1->cd(2); h2PintChi2Prob->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Noise");
  c1->SaveAs("plot_2D_PintChi2Prob.png");

  c1->cd(1); h1PintT0->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Signal");
  c1->cd(2); h2PintT0->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Noise");
  c1->SaveAs("plot_2D_PintT0.png");

  c1->cd(1); h1PintTauR->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Signal");
  c1->cd(2); h2PintTauR->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Noise");
  c1->SaveAs("plot_2D_PintTauR.png");

  c1->cd(1); h1PintTauF->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Signal");
  c1->cd(2); h2PintTauF->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Noise");
  c1->SaveAs("plot_2D_PintTauF.png");

  c1->cd(1); h1PintTauS->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Signal");
  c1->cd(2); h2PintTauS->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Noise");
  c1->SaveAs("plot_2D_PintTauS.png");

  c1->cd(1); h1PintTauR2->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Signal");
  c1->cd(2); h2PintTauR2->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Noise");
  c1->SaveAs("plot_2D_PintTauR2.png");

  c1->cd(1); h1PintTauR3->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Signal");
  c1->cd(2); h2PintTauR3->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Noise");
  c1->SaveAs("plot_2D_PintTauR3.png");

  c1->cd(1); h1PintTauR4->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Signal");
  c1->cd(2); h2PintTauR4->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Noise");
  c1->SaveAs("plot_2D_PintTauR4.png");

  c1->cd(1); h1PintTauF2->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Signal");
  c1->cd(2); h2PintTauF2->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Noise");
  c1->SaveAs("plot_2D_PintTauF2.png");

  c1->cd(1); h1PintTauS2->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Signal");
  c1->cd(2); h2PintTauS2->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Noise");
  c1->SaveAs("plot_2D_PintTauS2.png");

  c1->cd(1); h1PintTauS3->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Signal");
  c1->cd(2); h2PintTauS3->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Noise");
  c1->SaveAs("plot_2D_PintTauS3.png");

  c1->cd(1); h1PintPheightX->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Signal");
  c1->cd(2); h2PintPheightX->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Noise");
  c1->SaveAs("plot_2D_PintPheightX.png");

  c1->cd(1); h1PintPheightX2->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Signal");
  c1->cd(2); h2PintPheightX2->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Noise");
  c1->SaveAs("plot_2D_PintPheightX2.png");

  c1->cd(1); h1PintPheight->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Signal");
  c1->cd(2); h2PintPheight->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Noise");
  c1->SaveAs("plot_2D_PintPheight.png");

  c1->cd(1); h1PintRatio->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Signal");
  c1->cd(2); h2PintRatio->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Noise");
  c1->SaveAs("plot_2D_PintRatio.png");

  c1->cd(1); h1PintEndValPheight->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Signal");
  c1->cd(2); h2PintEndValPheight->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Noise");
  c1->SaveAs("plot_2D_PintEndValPheight.png");

  c1->cd(1); h1PintEndValPheight2->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Signal");
  c1->cd(2); h2PintEndValPheight2->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Noise");
  c1->SaveAs("plot_2D_PintEndValPheight2.png");
}
