#include "TCanvas.h"
#include "TPad.h"
#include "TFile.h"
#include "TMath.h"
#include "TF1.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TTree.h"
#include "TChain.h"
#include "TBranch.h"
#include "TGraph.h"
#include <iostream>

double particleCut(int I, int V, double p);
double particleCutna(int I, int V, double p);

double proton = 0.92827231;
double kaon = 0.493677;
double pion = 0.13956995;
double a1 = 0.00458;
double a2 = 0.00323;
double a3 = 0.175;
double c = 299.792458;
double L = 4100;

void pidAnalysis2()
{
  float ytof, xtof, dxdz3, dydz3, pm, pp, qq, vtz;  
  float adc_top[6], adc_bot[6], prbchi2[3];
  int ntof, itof, ntrk;
  int aero[6], taero[6];
  TChain* chain = new TChain("h1");
  chain -> Add("r*.root");
  chain -> SetBranchAddress("ytof", &ytof);
  chain -> SetBranchAddress("xtof", &xtof);
  chain -> SetBranchAddress("dxdz3",&dxdz3);
  chain -> SetBranchAddress("dydz3",&dydz3);
  chain -> SetBranchAddress("pm", &pm);
  chain -> SetBranchAddress("pp", &pp);
  chain -> SetBranchAddress("qq", &qq);
  chain -> SetBranchAddress("aero", aero);
  chain -> SetBranchAddress("taero", taero);
  chain -> SetBranchAddress("adc_top", adc_top);
  chain -> SetBranchAddress("adc_bot", adc_bot);
  chain -> SetBranchAddress("itof", &itof);
  chain -> SetBranchAddress("prbchi2", prbchi2); 
  chain -> SetBranchAddress("ntof", &ntof);
  chain -> SetBranchAddress("ntrk", &ntrk);

  TCut aerogelCut = "aero[0]<44&&aero[1]<46&&aero[2]<41&&aero[3]<42";
  TCut vtzCut = "-1100<vtz&&vtz<-800";
  TCut eeVetoCut = aerogelCut&&vtzCut;
  TCut FACarea = "480<xtof+dxdz3*440&&xtof+dxdz3*440<700&&-225<ytof+dydz3*440&&ytof+dydz3*440<-115";
  TCut FACarea2 = "510<xtof+dxdz3*440&&xtof+dxdz3*440<700&&-225<ytof+dydz3*440&&ytof+dydz3*440<-120";
  TCut FACareaR = "510<xtof+dxdz3*440&&xtof+dxdz3*440<560&&-225<ytof+dydz3*440&&ytof+dydz3*440<-120";
  TCut FACareaL = "650<xtof+dxdz3*440&&xtof+dxdz3*440<700&&-225<ytof+dydz3*440&&ytof+dydz3*440<-120";
  TCut tdc = "200<taero[4]||200<taero[5]";
  TCut pionPl = "particleCut(1, 0, pp)<pm*qq&&pm*qq<particleCut(1, 1, pp)";
  TCut pionPlna = "particleCutna(1, 0, pp)<pm*qq&&pm*qq<particleCutna(1, 1, pp)";
  TCut pionMi = "-particleCut(1, 1, pp)<pm*qq&&pm*qq<-particleCut(1, 0, pp)";
  TCut pionMina = "-particleCutna(1, 1, pp)<pm*qq&&pm*qq<-particleCutna(1, 0, pp)";
  TCut pionCut = pionPl||pionMi;
  TCut pionCutna = pionPlna||pionMina;
  TCut protonCut = "particleCut(0, 0, pp)<pm*qq&&pm*qq<particleCut(0, 1, pp)";
  TCut protonCutna = "particleCutna(0, 0, pp)<pm*qq&&pm*qq<particleCutna(0, 1, pp)"; 
  TCut electronCut = "-0.025<pm*qq&&pm*qq<0.025";
  TCut FACpion = FACarea&&pionCut;
  TCut FACpionna = FACarea&&pionCutna;
  TCut tofADC24 = "adc_top<2000&&adc_bot<2000&&itof==24";
  TCut tofADC25 = "adc_top<2000&&adc_bot<2000&&itof==25";
  TCut tofADC26 = "adc_top<2000&&adc_bot<2000&&itof==26";
  TCut tofADC = tofADC24||tofADC25||tofADC26;
  TCut chisq = "0.02<prbchi2&&prbchi2<1";
  TCut piNpeCut = chisq&&tofADC&&FACarea2&&pionCutna;
  TCut piNpeCutR = chisq&&tofADC&&FACareaR&&pionCutna; 
  TCut piNpeCutL = chisq&&tofADC&&FACareaL&&pionCutna; 
  TCut pNpeCut = FACarea2&&protonCutna;

  double ped = 42.5;
  double pe4 = 9.94;
  //double pe4p = 19.88;
  double pe5 = 10.8;
  //double pe5p = 19;
  /*//************************************************************************* Compare Npe distribution according to cut condition
  TCanvas* can0 = new TCanvas("can0", "", 800, 800);
  //TH1F* pi0507adc = new TH1F("pi0507adc", "", 120, 0, 30);
  //pi0507adc -> SetLineColor(1);
  //TH1F* pi0709 = new TH1F("pi0709", "", 120, 0, 30);
  //pi0709 -> SetLineColor(1);
  TH1F* pi0708adc = new TH1F("pi0708adc", "", 60, 0, 30);
  pi0708adc -> SetLineColor(1);
  TH1F* pi0809adc = new TH1F("pi0809adc", "", 60, 0, 30);
  pi0809adc -> SetLineColor(1);
  //TH1F* pi0911 = new TH1F("pi0911", "", 120, 0, 30);
  //pi0911 -> SetLineColor(1);
  TH1F* pi0910adc = new TH1F("pi0910adc", "", 60, 0, 30);
  pi0910adc -> SetLineColor(1);
  TH1F* pi1011adc = new TH1F("pi1011adc", "", 60, 0, 30);
  pi1011adc -> SetLineColor(1);
  //TH1F* pi1113 = new TH1F("pi1113", "", 120, 0, 30);
  //pi1113 -> SetLineColor(1);
  TH1F* pi1112adc = new TH1F("pi1112adc", "", 60, 0, 30);
  pi1112adc -> SetLineColor(1);
  TH1F* pi1213adc = new TH1F("pi1213adc", "", 60, 0, 30);
  pi1213adc -> SetLineColor(1);
  //TH1F* pi1315 = new TH1F("pi1315", "", 120, 0, 30);
  //pi1315 -> SetLineColor(1);
  TH1F* pi1314adc = new TH1F("pi1314adc", "", 60, 0, 30);
1314adc -> SetLineColor(1);
  TH1F* pi1415adc = new TH1F("pi1415adc", "", 60, 0, 30);
  pi1415adc -> SetLineColor(1);
  can0 -> Divide(2, 2);
  can0 -> cd(1);
  //chain -> Draw(Form("((aero[4]-%f)/(%f))+((aero[5]-30)/(%f))>>pi0709", ped, pe4, pe5), FACpion&&"0.7<pp&&pp<0.9");
  chain -> Draw(Form("((aero[4]-%f)/(%f))+((aero[5]-30)/(%f))>>pi0708adc", ped, pe4, pe5), piNpeCut&&tdc&&"0.7<pp&&pp<0.8");  
  pi0708adc -> Fit("gaus", "", "", 0, 8);
  //pi0709adc -> Fit("gaus", "", "", 0, 10);
  can0 -> cd(2);
  //chain -> Draw(Form("((aero[4]-%f)/(%f))+((aero[5]-30)/(%f))>>pi0911", ped, pe4, pe5), FACpion&&"0.9<pp&&pp<1.1");
  chain -> Draw(Form("((aero[4]-%f)/(%f))+((aero[5]-30)/(%f))>>pi0809adc", ped, pe4, pe5), piNpeCut&&tdc&&"0.8<pp&&pp<0.9"); 
  pi0809adc -> Fit("gaus", "", "", 0, 10);
  //pi0911adc -> Fit("gaus", "", "", 0, 12);
  can0 -> cd(3);
  //chain -> Draw(Form("((aero[4]-%f)/(%f))+((aero[5]-30)/(%f))>>pi1113", ped, pe4, pe5), FACpion&&"1.1<pp&&pp<1.3");
  chain -> Draw(Form("((aero[4]-%f)/(%f))+((aero[5]-30)/(%f))>>pi0910adc", ped, pe4, pe5), piNpeCut&&tdc&&"0.9<pp&&pp<1.0");
  pi0910adc -> Fit("gaus", "", "", 0, 9);
  //pi1113adc -> Fit("gaus", "", "", 5, 17);
  can0 -> cd(4);
  //chain -> Draw(Form("((aero[4]-%f)/(%f))+((aero[5]-30)/(%f))>>pi1315", ped, pe4, pe5), FACpion&&"1.3<pp&&pp<1.5");
  chain -> Draw(Form("((aero[4]-%f)/(%f))+((aero[5]-30)/(%f))>>pi1011adc", ped, pe4, pe5), piNpeCut&&tdc&&"1.0<pp&&pp<1.1");
  TCanvas* can3 = new TCanvas("can3", "", 800, 800);
  can3 -> Divide(2, 2);
  can3 -> cd(1);
  //chain -> Draw(Form("((aero[4]-%f)/(%f))+((aero[5]-30)/(%f))>>pi0709", ped, pe4, pe5), FACpion&&"0.7<pp&&pp<0.9");                                              
  chain -> Draw(Form("((aero[4]-%f)/(%f))+((aero[5]-30)/(%f))>>pi1112adc", ped, pe4, pe5), piNpeCut&&tdc&&"1.1<pp&&pp<1.2");
  //pi1112adc -> Fit("gaus", "", "", 3, 17);
  //pi0709adc -> Fit("gaus", "", "", 0, 10);                                                                                                                       
  can3 -> cd(2);
  //chain -> Draw(Form("((aero[4]-%f)/(%f))+((aero[5]-30)/(%f))>>pi0911", ped, pe4, pe5), FACpion&&"0.9<pp&&pp<1.1");                                              
  chain -> Draw(Form("((aero[4]-%f)/(%f))+((aero[5]-30)/(%f))>>pi1213adc", ped, pe4, pe5), piNpeCut&&tdc&&"1.2<pp&&pp<1.3");
  pi1213adc -> Fit("gaus", "", "", 2, 14);
  //pi0911adc -> Fit("gaus", "", "", 0, 12);                                                                                                                       
  can3 -> cd(3);
  //chain -> Draw(Form("((aero[4]-%f)/(%f))+((aero[5]-30)/(%f))>>pi1113", ped, pe4, pe5), FACpion&&"1.1<pp&&pp<1.3");                                              
  chain -> Draw(Form("((aero[4]-%f)/(%f))+((aero[5]-30)/(%f))>>pi1314adc", ped, pe4, pe5), piNpeCut&&tdc&&"1.3<pp&&pp<1.4");
  pi1314adc -> Fit("gaus", "", "", 2, 13);
  //pi1113adc -> Fit("gaus", "", "", 5, 17);                                                                                                                       
  can3 -> cd(4);
  //chain -> Draw(Form("((aero[4]-%f)/(%f))+((aero[5]-30)/(%f))>>pi1315", ped, pe4, pe5), FACpion&&"1.3<pp&&pp<1.5");                                              
  chain -> Draw(Form("((aero[4]-%f)/(%f))+((aero[5]-30)/(%f))>>pi1415adc", ped, pe4, pe5), piNpeCut&&tdc&&"1.4<pp&&pp<1.5");
  pi1415adc -> Fit("gaus", "", "", 0, 13);*/

  //************************************************************************* Pion efficiency, proton misidentification according to momentum cut

  int number = 61;
  double NpeThre[61] = {0, };
  int pionIntegral[61] = {0, };
  double pionEff[61] = {0, };
  double pionMis[61] = {0, };
  int protonIntegral[61] = {0, };
  double protonEff[61] = {0, };
  double protonMis[61] = {0, };
  TH1F* NpeProton = new TH1F("NpeProton", "", 120, 0, 60);
  NpeProton -> SetLineColor(2);
  //TH1F* Npe05 = new TH1F("Npe05", "", 120, 0, 30);
  //Npe05 -> SetLineColor(4);
  TH1F* Npe07 = new TH1F("Npe07", "", 120, 0, 60);
  Npe07 -> SetLineColor(4);
  //chain->Project(Npe07->GetName(), Form("((aero[4]-%f)/(%f))+((aero[5]-30)/(%f))>>Npe05", ped, pe4, pe5), piNpeCut&&tdc&&"0.5<pp");
  //Npe07->Draw("same");
  TCanvas* com = new TCanvas("com", "", 550, 550);
  gPad -> SetLogy();
  chain -> Draw(Form("((aero[4]-%f)/(%f))+((aero[5]-30)/(%f))>>NpeProton", ped, pe4, pe5), pNpeCut&&"pp<3");                                                                               
  chain -> Draw(Form("((aero[4]-%f)/(%f))+((aero[5]-30)/(%f))>>Npe07", ped, pe4, pe5), piNpeCut&&tdc&&"0.5<pp", "same");
  double pionTotal = Npe07 -> Integral(0, 120);
  double protonTotal = NpeProton -> Integral(0, 120);
  for (int r=0;r<61;r++)
    {
      NpeThre[r] = r*0.5;
      pionIntegral[r] = Npe07 -> Integral(r, 120);
      //std::cout << pionIntegral[r] << std::endl;
      pionEff[r] = (pionIntegral[r])/(pionTotal);
      std::cout << pionEff[r] << std::endl;
      //std::cout << pionEff[r] << std::endl;
      pionMis[r] = 1-pionEff[r];
      protonIntegral[r] = NpeProton -> Integral(0, r);
      protonEff[r] = (protonIntegral[r])/(protonTotal);
      std::cout << protonEff[r] << std::endl;
      protonMis[r] = 1-protonEff[r];
    }
  TGraph* pionEfficiency = new TGraph(number, NpeThre, pionEff);
  pionEfficiency -> SetMarkerStyle(21);
  pionEfficiency -> SetMarkerColor(kAzure+9);
  TGraph* protonEfficiency = new TGraph(number, NpeThre, protonEff);
  protonEfficiency -> SetMarkerStyle(23);
  protonEfficiency -> SetMarkerColor(46);
  TGraph* pionMisid = new TGraph(number, NpeThre, pionMis);
  pionMisid -> SetMarkerStyle(21);
  pionMisid -> SetMarkerColor(kAzure+9);
  TGraph* protonMisid = new TGraph(number, NpeThre, protonMis);
  protonMisid -> SetMarkerStyle(23);
  protonMisid -> SetMarkerColor(46);
  TH2F* EffCanvas = new TH2F("", "", 60, 0, 30, 11, 0, 1.1);
  TH2F* MisCanvas = new TH2F("", "", 60, 0, 30, 11, 0, 1.1);
  TCanvas* effCanv0 = new TCanvas("effCanv0", "", 550, 550);
  //effCanv0 -> SetLogy();
  EffCanvas -> SetMinimum(0.00000001);
  EffCanvas -> Draw();
  pionEfficiency -> SetMinimum(0.00000001);
  protonEfficiency -> SetMinimum(0.00000001);
  pionEfficiency -> Draw("P");
  protonEfficiency -> Draw("P");
  TCanvas* misCanv0 = new TCanvas("miscanv0", "", 550, 550);
  //misCanv0 -> SetLogy();
  MisCanvas -> SetMinimum(0.00000001);
  MisCanvas -> Draw();
  protonMisid -> SetMinimum(0.00000001);
  pionMisid -> SetMinimum(0.00000001);
  protonMisid -> Draw("P");
  pionMisid -> Draw("P");
 
  //pionEfficiency -> Delete();
  //protonEfficiency -> Delete();
  //pionMisid -> Delete();
  //protonMisid -> Delete();





  /*TCanvas* can1 = new TCanvas("can1", "", 1200, 800);
  TH1F* adc24top = new TH1F("adc1top", "", 440, 0, 2200);
  TH1F* adc24bot = new TH1F("adc1bot", "", 440, 0, 2200);
  TH1F* adc25top = new TH1F("adc2top", "", 440, 0, 2200);
  TH1F* adc25bot = new TH1F("adc2bot", "", 440, 0, 2200);
  TH1F* adc26top = new TH1F("adc3top", "", 440, 0, 2200);
  TH1F* adc26bot = new TH1F("adc3bot", "", 440, 0, 2200);
  can1 -> Divide(3, 2);
  can1 -> cd(1);
  chain -> Draw("adc_top>>adc24top", FACpion&&"itof==24");
  can1 -> cd(2);
  chain -> Draw("adc_top>>adc25top", FACpion&&"itof==25");
  can1 -> cd(3);
  chain -> Draw("adc_top>>adc26top", FACpion&&"itof==26");
  can1 -> cd(4);
  chain -> Draw("adc_bot>>adc24bot", FACpion&&"itof==24");
  can1 -> cd(5);
  chain -> Draw("adc_bot>>adc25bot", FACpion&&"itof==25");
  can1 -> cd(6);
  chain -> Draw("adc_bot>>adc26bot", FACpion&&"itof==26");*/
 
  /*TCanvas* canv = new TCanvas("canv", "", 600, 600);
  chain -> Draw("pm*qq:pp>>(600, 0, 3, 400, -0.5, 1.5)", FACarea);
  TF1* proton_minCut = new TF1("proton_minCut", "particleCut([0], [1], x[0])", 0, 3);
  proton_minCut -> SetParameters(0, 0);
  proton_minCut -> SetLineColor(8);
  proton_minCut -> Draw("same");
  TF1* proton_maxCut = new TF1("proton_maxCut", "particleCut([0], [1], x[0])", 0, 3);
  proton_maxCut -> SetParameters(0, 1);
  proton_maxCut -> SetLineColor(8);
  proton_maxCut -> Draw("same");
  TF1* pion_minCut = new TF1("pion_minCut", "particleCut([0], [1], x[0])", 0, 3);
  pion_minCut -> SetParameters(1, 0);
  pion_minCut -> SetLineColor(8);
  pion_minCut -> Draw("same");
  TF1* pion_maxCut = new TF1("pion_maxCut", "particleCut([0], [1], x[0])", 0, 3);
  pion_maxCut -> SetParameters(1, 1);
  pion_maxCut -> SetLineColor(8);
  pion_maxCut -> Draw("same");*/

  /*TCanvas* canv2 = new TCanvas("canv2", "Particle Npe", 600, 600);
  gPad -> SetLogy();
  chain -> Draw("((aero[4]-42.5)/(13.136))+((aero[5]-30)/(18.455))>>total(120, 0, 30)", FACarea&&eeVetoCut);
  total -> SetLineColor(1);
  total -> Draw();
  chain -> Draw("((aero[4]-42.5)/(13.136))+((aero[5]-30)/(18.455))>>pro(120, 0, 30)", FACarea&&protonCut&&eeVetoCut, "same");
  pro -> SetLineColor(2);
  pro -> Draw("same");
  chain -> Draw("((aero[4]-42.5)/(13.136))+((aero[5]-30)/(18.455))>>pi(120, 0, 30)", FACarea&&pionCut&&eeVetoCut, "same");
  pi -> SetLineColor(4);
  pi -> Draw("same");
  chain -> Draw("((aero[4]-42.5)/(13.136))+((aero[5]-30)/(18.455))>>elec(120, 0, 30)", FACarea&&electronCut&&eeVetoCut, "same"); 
  elec -> SetLineColor(8);
  elec -> Draw("same");
  std::cout << "total: " << chain -> GetEntries(FACarea&&eeVetoCut) << std::endl;
  std::cout << "proton: " << chain -> GetEntries(FACarea&&protonCut&&eeVetoCut) << std::endl;
  std::cout << "pion: " << chain -> GetEntries(FACarea&&pionCut&&eeVetoCut) << std::endl;
  std::cout << "electron: " << chain -> GetEntries(FACarea&&electronCut&&eeVetoCut) << std::endl;

  TCanvas* canv3 = new TCanvas("canv3", "Pion Npe1315", 600, 600);
  gPad -> SetLogy(0);
  chain -> Draw("((aero[4]-42.5)/(13.136))+((aero[5]-30)/(18.455))>>pionCut1315(120, 0, 30)", FACarea&&pionCut&&eeVetoCut&&tdc&&"1.3<pp&&pp<1.5");
  //pionCut1315 -> Fit("gaus", "", "", 0, );
  //pionCut1315 -> Fit("landau", "", "", 0, );

  TCanvas* canv4 = new TCanvas("canv4", "Pion Npe1113", 600, 600);
  gPad -> SetLogy(0);
  chain -> Draw("((aero[4]-42.5)/(13.136))+((aero[5]-30)/(18.455))>>pionCut1113(120, 0, 30)", FACarea&&pionCut&&eeVetoCut&&tdc&&"1.1<pp&&pp<1.3");
  //pionCut1113 -> Fit("gaus", "", "", 0, );     
  //pionCut1113 -> Fit("landau", "", "", 0, );

  TCanvas* canv5 = new TCanvas("canv5", "Pion Npe0911", 600, 600);
  gPad -> SetLogy(0);
  chain -> Draw("((aero[4]-42.5)/(13.136))+((aero[5]-30)/(18.455))>>pionCut0911(120, 0, 30)", FACarea&&pionCut&&eeVetoCut&&tdc&&"0.9<pp&&pp<1.1");
  //pionCut0911 -> Fit("gaus", "", "", 0, ); 
  //pionCut0911 -> Fit("landau", "", "", 0, );

  TCanvas* canv6 = new TCanvas("canv6", "Pion Npe0709", 600, 600);
  gPad -> SetLogy(0);
  chain -> Draw("((aero[4]-42.5)/(13.136))+((aero[5]-30)/(18.455))>>pionCut0709(120, 0, 30)", FACarea&&pionCut&&eeVetoCut&&tdc&&"0.7<pp&&pp<0.9");
  //pionCut0709 -> Fit("gaus", "", "", 0, );  
  //pionCut0709 -> Fit("landau", "", "", 0, );

  TCanvas* canv7 = new TCanvas("canv7", "Pion Npe0507", 600, 600);
  gPad -> SetLogy(0);
  chain -> Draw("((aero[4]-42.5)/(13.136))+((aero[5]-30)/(18.455))>>pionCut0507(120, 0, 30)", FACarea&&pionCut&&eeVetoCut&&tdc&&"0.5<pp&&pp<0.7");
  //pionCut0507 -> Fit("gaus", "", "", 0, );  
  //pionCut0507 -> Fit("landau", "", "", 0, );*/

  /*Npe07 -> SetLineColor(4);                                                                                                                                                                
  //TH1F* Npe09 =new TH1F("Npe09", "", 120, 0,30);                                                                                                                                           
  //Npe09 -> SetLineColor(4);                                                                                                                                                                
  /*TCanvas* NpeCanv0 = new TCanvas("NpeCanv0", "", 550, 550);                                                                                                                               
  gPad -> SetLogy();                                                                                                                                                                         
                                                                                                                                                                                             
#if 0                                                                                                                                                                                        
                                                                                                                                                                                             
#endif                                                                                                                                                                                       
                                                                                                                                                                                             
#if 1                                                                                                                                                                                        
/*                                                                                                                                                                                         
                                                                                                                                                                                             
                                                                                                                                                                                             
  */
#endif
  //chain -> Draw(Form("((aero[4]-%f)/(%f))+((aero[5]-30)/(%f))>>NpeProton", ped, pe4, pe5), pNpeCut&&"pp<3");                                                                               
  //chain -> Draw(Form("((aero[4]-%f)/(%f))+((aero[5]-30)/(%f))>>Npe05", ped, pe4, pe5), piNpeCut&&tdc&&"0.5<pp", "same");*/                                                                 
  //TCanvas* NpeCanv1 = new TCanvas("NpeCanv1", "", 550, 550);                                                                                                                               
  //gPad -> SetLogy();                                                                                                                                                                       
  //chain -> Draw(Form("((aero[4]-%f)/(%f))+((aero[5]-30)/(%f))>>NpeProton", ped, pe4, pe5), pNpeCut&&"pp<3");                                                                      
  //chain -> Draw(Form("((aero[4]-%f)/(%f))+((aero[5]-30)/(%f))>>Npe07", ped, pe4, pe5), piNpeCut&&tdc&&"0.7<pp", "same");                                                                   
  //TCanvas* NpeCanv2 = new TCanvas("NpeCanv2", "", 550, 550);                                                                                                                               
  //gPad -> SetLogy();                                                                                                                                                                       
  //NpeProton -> Draw();                                                                                                                                                                     
  //chain -> Draw(Form("((aero[4]-%f)/(%f))+((aero[5]-30)/(%f))>>Npe09", ped, pe4, pe5), piNpeCut&&tdc&&"0.9<pp", "same");*/

}

double particleCut(int I, int V, double p)
{
  double protonSigmaMultiple = 4*((proton)**(4))*(1+(proton/p)**(2))*((a1)**(2));
  double protonSigmaLEPS = 4*((proton)**(4))*((p)**(2))*((a2)**(2));
  double protonSigmaToF = 4*((p)**(2))*((p)**(2)+(proton)**(2))*((c/L)**(2))*((a3)**(2));
  double protonSigma = sqrt(protonSigmaMultiple+protonSigmaLEPS+protonSigmaToF);
  double pionSigmaMultiple = 4*((pion)**(4))*(1+(pion/p)**(2))*((a1)**(2));
  double pionSigmaLEPS = 4*((pion)**(4))*((p)**(2))*((a2)**(2));
  double pionSigmaToF = 4*((p)**(2))*((p)**(2)+(pion)**(2))*((c/L)**(2))*((a3)**(2));
  double pionSigma = sqrt(pionSigmaMultiple+pionSigmaLEPS+pionSigmaToF);
  double kaonSigmaMultiple = 4*((kaon)**(4))*(1+(kaon/p)**(2))*((a1)**(2));
  double kaonSigmaLEPS = 4*((kaon)**(4))*((p)**(2))*((a2)**(2));
  double kaonSigmaToF = 4*((p)**(2))*((p)**(2)+(kaon)**(2))*((c/L)**(2))*((a3)**(2));
  double kaonSigma = sqrt(kaonSigmaMultiple+kaonSigmaLEPS+kaonSigmaToF);

  double pK = 1.97;
  double piK = 1.18;
  
  if(I==0)
    {
      if(p<0.9)
	{
	  if(V==0)
	    {
	      return sqrt(0.7);
	    }
	  if(V==1)
	    {
	      return sqrt(1);
	    }
	}
      if(0.9<=p&&p<pK)
	{
	  if(V==0)
	    {
	      return sqrt((proton)**(2)-3*(protonSigma));
	    }
	  if(V==1)
	    {
	      return sqrt((proton)**(2)+3*(protonSigma));
	    }
	}
      if(pK<=p)
	{
	  if(V==0)
	    {
	      return sqrt(0.55);
	    }
	  if(V==1)
	    {
	      return sqrt((proton)**(2)+3*(protonSigma));
	    }
	}
    }

  if(I==1)
    {
      if(p<0.46)
	{
	  if(V==0)
	    {
	      return sqrt((pion)**(2)-3*(pionSigma));
	    }
	  if(V==1)
	    {
	      return sqrt((pion)**(2)+3*(pionSigma));
	    }
	}
      if(0.46<=p&&p<piK)
	{
	  if(V==0)
	    {
	      return 0.025;
	    }
	  if(V==1)
	    {
	      return sqrt((pion)**(2)+3*(pionSigma));
	    }
	}
      if(piK<=p)
	{
	  if(V==0)
	    {
	      return 0.025;
	    }
	  if(V==1)
	    {
	      return sqrt(0.13);
	    }
	}
    }
}

double particleCutna(int I, int V, double p)
{
  double protonSigmaMultiple = 4*((proton)**(4))*(1+(proton/p)**(2))*((a1)**(2));
  double protonSigmaLEPS = 4*((proton)**(4))*((p)**(2))*((a2)**(2));
  double protonSigmaToF = 4*((p)**(2))*((p)**(2)+(proton)**(2))*((c/L)**(2))*((a3)**(2));
  double protonSigma = sqrt(protonSigmaMultiple+protonSigmaLEPS+protonSigmaToF);
  double pionSigmaMultiple = 4*((pion)**(4))*(1+(pion/p)**(2))*((a1)**(2));
  double pionSigmaLEPS = 4*((pion)**(4))*((p)**(2))*((a2)**(2));
  double pionSigmaToF = 4*((p)**(2))*((p)**(2)+(pion)**(2))*((c/L)**(2))*((a3)**(2));
  double pionSigma = sqrt(pionSigmaMultiple+pionSigmaLEPS+pionSigmaToF);
  double kaonSigmaMultiple = 4*((kaon)**(4))*(1+(kaon/p)**(2))*((a1)**(2));
  double kaonSigmaLEPS = 4*((kaon)**(4))*((p)**(2))*((a2)**(2));
  double kaonSigmaToF = 4*((p)**(2))*((p)**(2)+(kaon)**(2))*((c/L)**(2))*((a3)**(2));
  double kaonSigma = sqrt(kaonSigmaMultiple+kaonSigmaLEPS+kaonSigmaToF);

  double pK = 2.44;
  double piK = 1.45;

  if(I==0)
    {
      if(p<0.9)
        {
          if(V==0)
            {
              return sqrt(0.7);
            }
          if(V==1)
            {
              return sqrt(1);
            }
        }
      if(0.9<=p&&p<pK)
        {
	  if(V==0)
            {
              return sqrt((proton)**(2)-2*(protonSigma));
            }
          if(V==1)
            {
              return sqrt((proton)**(2)+2*(protonSigma));
            }
        }
      if(pK<=p)
        {
          if(V==0)
            {
              return sqrt(0.55);
            }
          if(V==1)
            {
              return sqrt((proton)**(2)+2*(protonSigma));
            }
        }
    }

  if(I==1)
    {
      if(p<0.6)
        {
          if(V==0)
            {
              return sqrt((pion)**(2)-2*(pionSigma));
            }
          if(V==1)
            {
              return sqrt((pion)**(2)+2*(pionSigma));
            }
        }
      if(0.6<=p&&p<piK)
        {
          if(V==0)
            {
              return 0.025;
            }
          if(V==1)
            {
              return sqrt((pion)**(2)+2*(pionSigma));
            }
        }
      if(piK<=p)
        {
          if(V==0)
            {
              return 0.025;
            }
          if(V==1)
            {
              return sqrt(0.13);
            }
        }
    }
}
