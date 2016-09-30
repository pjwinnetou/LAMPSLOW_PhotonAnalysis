void cutStudy2D(){
  gROOT->Macro("~/rootlogon.C");
  TFile *f1 = new TFile("../Cs137_Ana_Sgn_Front.root","READ");
  TFile *f2 = new TFile("../Cs137_Ana_Noise.root","READ");

  TH2F *h1PintChi2 = (TH2F*)f1->Get("hPintChi2");
  TH2F *h1PintChi2NDF = (TH2F*)f1->Get("hPintChi2NDF");
  TH2F *h1PintRMS = (TH2F*)f1->Get("hPintRMS");
  TH2F *h1PintChi2Prob = (TH2F*)f1->Get("hPintChi2Prob");
  TH2F *h1PintPheightX = (TH2F*)f1->Get("hPintPheightX");
  TH2F *h1PintPheight = (TH2F*)f1->Get("hPintPheight");
  TH2F *h1PintT0 = (TH2F*)f1->Get("hPintT0");
  TH2F *h1PintA = (TH2F*)f1->Get("hPintA");
  TH2F *h1PintTauF = (TH2F*)f1->Get("hPintTauF");
  TH2F *h1PintTauF2 = (TH2F*)f1->Get("hPintTauF2");
  TH2F *h1PintTauF3 = (TH2F*)f1->Get("hPintTauF3");
  TH2F *h1PintTauR = (TH2F*)f1->Get("hPintTauR");
  TH2F *h1PintTauR2 = (TH2F*)f1->Get("hPintTauR2");
  TH2F *h1PintTauS = (TH2F*)f1->Get("hPintTauS");
  TH2F *h1PintRatio = (TH2F*)f1->Get("hPintRatio");
  TH2F *h1PinthEndValPheight = (TH2F*)f1->Get("hPintEndValPheight");
  TH2F *h1Chi2NDFRMS = (TH2F*)f1->Get("hChi2NDFRMS");
  TH2F *h1Chi2NDFChi2Prob = (TH2F*)f1->Get("hChi2NDFChi2Prob");
  TH2F *h1Chi2NDFPheightX = (TH2F*)f1->Get("hChi2NDFPheightX");
  TH2F *h1Chi2NDFPheight = (TH2F*)f1->Get("hChi2NDFPheight");
  TH2F *h1Chi2NDFT0 = (TH2F*)f1->Get("hChi2NDFT0");
  TH2F *h1Chi2NDFA = (TH2F*)f1->Get("hChi2NDFA");
  TH2F *h1Chi2NDFTauF = (TH2F*)f1->Get("hChi2NDFTauF");
  TH2F *h1Chi2NDFTauF2 = (TH2F*)f1->Get("hChi2NDFTauF2");
  TH2F *h1Chi2NDFTauR = (TH2F*)f1->Get("hChi2NDFTauR");
  TH2F *h1Chi2NDFTauS = (TH2F*)f1->Get("hChi2NDFTauS");
  TH2F *h1Chi2NDFRatio = (TH2F*)f1->Get("hChi2NDFRatio");
  TH2F *h1Chi2NDFhEndValPheight = (TH2F*)f1->Get("hChi2NDFEndValPheight");


  TH2F *h2PintChi2 = (TH2F*)f2->Get("hPintChi2");
  TH2F *h2PintChi2NDF = (TH2F*)f2->Get("hPintChi2NDF");
  TH2F *h2PintRMS = (TH2F*)f2->Get("hPintRMS");
  TH2F *h2PintChi2Prob = (TH2F*)f2->Get("hPintChi2Prob");
  TH2F *h2PintPheightX = (TH2F*)f2->Get("hPintPheightX");
  TH2F *h2PintPheight = (TH2F*)f2->Get("hPintPheight");
  TH2F *h2PintT0 = (TH2F*)f2->Get("hPintT0");
  TH2F *h2PintA = (TH2F*)f2->Get("hPintA");
  TH2F *h2PintTauF = (TH2F*)f2->Get("hPintTauF");
  TH2F *h2PintTauF2 = (TH2F*)f2->Get("hPintTauF2");
  TH2F *h2PintTauF3 = (TH2F*)f2->Get("hPintTauF3");
  TH2F *h2PintTauR = (TH2F*)f2->Get("hPintTauR");
  TH2F *h2PintTauR2 = (TH2F*)f2->Get("hPintTauR2");
  TH2F *h2PintTauS = (TH2F*)f2->Get("hPintTauS");
  TH2F *h2PintRatio = (TH2F*)f2->Get("hPintRatio");
  TH2F *h2PinthEndValPheight = (TH2F*)f2->Get("hPintEndValPheight");
  TH2F *h2Chi2NDFRMS = (TH2F*)f2->Get("hChi2NDFRMS");
  TH2F *h2Chi2NDFChi2Prob = (TH2F*)f2->Get("hChi2NDFChi2Prob");
  TH2F *h2Chi2NDFPheightX = (TH2F*)f2->Get("hChi2NDFPheightX");
  TH2F *h2Chi2NDFPheight = (TH2F*)f2->Get("hChi2NDFPheight");
  TH2F *h2Chi2NDFT0 = (TH2F*)f2->Get("hChi2NDFT0");
  TH2F *h2Chi2NDFA = (TH2F*)f2->Get("hChi2NDFA");
  TH2F *h2Chi2NDFTauF = (TH2F*)f2->Get("hChi2NDFTauF");
  TH2F *h2Chi2NDFTauF2 = (TH2F*)f2->Get("hChi2NDFTauF2");
  TH2F *h2Chi2NDFTauR = (TH2F*)f2->Get("hChi2NDFTauR");
  TH2F *h2Chi2NDFTauS = (TH2F*)f2->Get("hChi2NDFTauS");
  TH2F *h2Chi2NDFRatio = (TH2F*)f2->Get("hChi2NDFRatio");
  TH2F *h2Chi2NDFhEndValPheight = (TH2F*)f2->Get("hChi2NDFEndValPheight");


  TLatex *lt1 = new TLatex();
  lt1->SetNDC();

  TCanvas *c1 = new TCanvas("c1","",1200,600);
  c1->Divide(2,1);

  c1->cd(1); h1PintChi2NDF->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Signal");
  c1->cd(2); h2PintChi2NDF->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Noise");
  c1->SaveAs("plot_2D_Chi2NDF.png");


  c1->cd(1); h1PintChi2->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Signal");
  c1->cd(2); h2PintChi2->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Noise");
  c1->SaveAs("plot_2D_Chi2.png");

  c1->cd(1); h1PintRMS->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Signal");
  c1->cd(2); h2PintRMS->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Noise");
  c1->SaveAs("plot_2D_RMS.png");

  c1->cd(1); h1PintChi2Prob->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Signal");
  c1->cd(2); h2PintChi2Prob->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Noise");
  c1->SaveAs("plot_2D_Chi2Prob.png");

  c1->cd(1); h1PintPheightX->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Signal");
  c1->cd(2); h2PintPheightX->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Noise");
  c1->SaveAs("plot_2D_PheightX.png");

  c1->cd(1); h1PintPheight->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Signal");
  c1->cd(2); h2PintPheight->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Noise");
  c1->SaveAs("plot_2D_Pheight.png");

  c1->cd(1); h1PintT0->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Signal");
  c1->cd(2); h2PintT0->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Noise");
  c1->SaveAs("plot_2D_ParmT0.png");
  
  c1->cd(1); h1PintA->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Signal");
  c1->cd(2); h2PintA->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Noise");
  c1->SaveAs("plot_2D_ParmA.png");

  c1->cd(1); h1PintTauF->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Signal");
  c1->cd(2); h2PintTauF->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Noise");
  c1->SaveAs("plot_2D_ParmTauF.png");

  c1->cd(1); h1PintTauF2->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Signal");
  c1->cd(2); h2PintTauF2->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Noise");
  c1->SaveAs("plot_2D_ParmTauF2.png");

  c1->cd(1); h1PintTauF3->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Signal");
  c1->cd(2); h2PintTauF3->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Noise");
  c1->SaveAs("plot_2D_ParmTauF3.png");

  c1->cd(1); h1PintTauR->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Signal");
  c1->cd(2); h2PintTauR->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Noise");
  c1->SaveAs("plot_2D_ParmTauR.png");

  c1->cd(1); h1PintTauR2->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Signal");
  c1->cd(2); h2PintTauR2->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Noise");
  c1->SaveAs("plot_2D_ParmTauR2.png");

  c1->cd(1); h1PintTauS->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Signal");
  c1->cd(2); h2PintTauS->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Noise");
  c1->SaveAs("plot_2D_ParmTauS.png");

  c1->cd(1); h1PintRatio->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Signal");
  c1->cd(2); h2PintRatio->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Noise");
  c1->SaveAs("plot_2D_Ratio.png");

  c1->cd(1); h1PinthEndValPheight->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Signal");
  c1->cd(2); h2PinthEndValPheight->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Noise");
  c1->SaveAs("plot_2D_EndValPheight.png");

  c1->cd(1); h1Chi2NDFRMS->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Signal");
  c1->cd(2); h2Chi2NDFRMS->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Noise");
  c1->SaveAs("plot_2D_Chi2NDFRMS.png");

  c1->cd(1); h1Chi2NDFChi2Prob->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Signal");
  c1->cd(2); h2Chi2NDFChi2Prob->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Noise");
  c1->SaveAs("plot_2D_Chi2NDFChi2Prob.png");

  c1->cd(1); h1Chi2NDFPheightX->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Signal");
  c1->cd(2); h2Chi2NDFPheightX->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Noise");
  c1->SaveAs("plot_2D_Chi2NDFPheightX.png");

  c1->cd(1); h1Chi2NDFPheight->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Signal");
  c1->cd(2); h2Chi2NDFPheight->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Noise");
  c1->SaveAs("plot_2D_Chi2NDFPheight.png");

  c1->cd(1); h1Chi2NDFT0->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Signal");
  c1->cd(2); h2Chi2NDFT0->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Noise");
  c1->SaveAs("plot_2D_Chi2NDFParmT0.png");
  
  c1->cd(1); h1Chi2NDFA->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Signal");
  c1->cd(2); h2Chi2NDFA->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Noise");
  c1->SaveAs("plot_2D_Chi2NDFParmA.png");

  c1->cd(1); h1Chi2NDFTauF->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Signal");
  c1->cd(2); h2Chi2NDFTauF->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Noise");
  c1->SaveAs("plot_2D_Chi2NDFParmTauF.png");

  c1->cd(1); h1Chi2NDFTauF2->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Signal");
  c1->cd(2); h2Chi2NDFTauF2->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Noise");
  c1->SaveAs("plot_2D_Chi2NDFParmTauF2.png");

  c1->cd(1); h1Chi2NDFTauR->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Signal");
  c1->cd(2); h2Chi2NDFTauR->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Noise");
  c1->SaveAs("plot_2D_Chi2NDFParmTauR.png");

  c1->cd(1); h1Chi2NDFTauS->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Signal");
  c1->cd(2); h2Chi2NDFTauS->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Noise");
  c1->SaveAs("plot_2D_Chi2NDFParmTauS.png");

  c1->cd(1); h1Chi2NDFRatio->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Signal");
  c1->cd(2); h2Chi2NDFRatio->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Noise");
  c1->SaveAs("plot_2D_Chi2NDFRatio.png");

  c1->cd(1); h1Chi2NDFhEndValPheight->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Signal");
  c1->cd(2); h2Chi2NDFhEndValPheight->Draw("colz"); lt1->DrawLatex(0.8,0.9,"Noise");
  c1->SaveAs("plot_2D_Chi2NDFEndValPheight.png");
}
