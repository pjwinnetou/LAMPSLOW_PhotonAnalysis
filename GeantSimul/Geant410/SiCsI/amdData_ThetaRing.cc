#include <TTree.h>
#include <TFile.h>
#include <TMath.h>

#include <fstream>
#include <iostream>

using namespace std;

// Declare Function
double CalculateSNN(double e, double p);
double CalculateTotalEnergy(double p, double m);
double CalculateTotalEnergyLab(double e, double pZ, double gamma, double beta);
double CalculateTotalMomentum(double pX, double pY, double pZ);
double CalculateMomentum(double e, double m);
double CalculatePzLab(double e, double pZ, double gamma, double beta);
double CalculateRapdity(double e, double pz);
double CalculateTheta(double pZ, double pT);
//double CalculateThetaLab(double theta, double p, double gamma, double beta, double m);
double CalculatePT(double pX, double pY);
double CalculatePhi(double pX, double pY);



// Definition of Functions

double CalculateSNN(double e, double p) { return TMath::Power(e,2) - TMath::Power(p,2); }
double CalculateTotalEnergy(double p, double m) { return TMath::Sqrt(p*p + m*m); }
double CalculateTotalEnergyLab(double e, double pZ, double gamma, double beta)
{ return gamma*e-gamma*beta*pZ; }
double CalculateTotalMomentum(double pX, double pY, double pZ) { return TMath::Sqrt(pX*pX + pY*pY + pZ*pZ); }
double CalculateMomentum(double e, double m) { return TMath::Sqrt(e*e - m*m); }
double CalculatePzLab(double e, double pZ, double gamma, double beta)
{ return -gamma*beta*e+gamma*pZ; }

double CalculatePT(double pX, double pY)    { return TMath::Sqrt(pX*pX + pY*pY); }
double CalculatePhi(double pX, double pY)  
{ 
  double phi;

  if(pX>=0&&pY>=0) phi = TMath::ATan(pY/pX);
  else if(pX>=0&&pY<0) phi = 2*TMath::Pi()+TMath::ATan(pY/pX);
  else phi = TMath::Pi()+TMath::ATan(pY/pX);

  return phi;
}
double CalculateRapidity(double e, double pZ)   { return TMath::Log((e+pZ)/(e-pZ))/2; }
double CalculateTheta(double pZ, double pT) { return TMath::ATan(pT/pZ); }
//double CalculateThetaLab(double theta, double p, double gamma, double beta, double m)
//{ return TMath::ATan((p*TMath::Sin(theta))/(gamma*(p*TMath::Cos(theta)+beta*m))); }

//double CalculatePBeamLab(double sNN, double m)  { return m*sqrt(TMath::Power((sNN/(2*m*m)-1),2)-1); }


// Main Function

int main(int argc, char** argv)
{

   //----------------------Information per nucleon--------------------------------------------//
   
   //general
   double mProton = 938.272;
   double mNeutron = 939.565;
   double mNucleon = (mProton + mNeutron)/2;
   
   //Projectile 132Sn
   int ZBeam = 50;
   int NBeam = 82;
   int ABeam = 132;
   double mBeam = mProton*ZBeam + mNeutron*NBeam;
   
   //Target 124Sn
   int ZTarget = 50;
   int NTarget = 74;
   int ATarget = 124;
   double mTarget = mProton*ZTarget + mNeutron*NTarget;
   
   //Lab Frame
   double eKinBeam_Lab = 20;
   double eTotalBeam_Lab = eKinBeam_Lab + mNucleon;
   double eTotalAll = eTotalBeam_Lab + mNucleon;
   double pTotalBeam_Lab = CalculateMomentum(eTotalBeam_Lab, mNucleon); 
   double rapidityBeam_Lab = CalculateRapidity(eTotalBeam_Lab, pTotalBeam_Lab); //pTotalBeam_Lab : only z-direction

   //CM Energy
   double sNN = CalculateSNN(eTotalAll, pTotalBeam_Lab);
   double sqrt_sNN = TMath::Sqrt(sNN);
   double cmEnergy = sqrt_sNN - 2*mNucleon;
 
   //CM Frame
   double eBeam_CM = sqrt_sNN/2;
   double eKin_CM = eBeam_CM - mNucleon;
   double pBeam_CM = TMath::Sqrt(eBeam_CM*eBeam_CM - mNucleon*mNucleon);
   double rapidityBeam_CM = CalculateRapidity(eBeam_CM, pBeam_CM);
   
   double beta = -pTotalBeam_Lab/eTotalAll;
   double gamma = 1/sqrt(1-beta*beta);
   double rapidityShift = TMath::Log(sqrt((1-beta)/(1+beta)));

   std::cout << "*** General ***" << std::endl;
   std::cout << "mProton   : " << mProton << std::endl;
   std::cout << "mNeutron  : " << mNeutron << std::endl;
   std::cout << "mNucleon  : " << std::endl;
   std::cout << "sqrt_sNN  : " << sqrt_sNN  << std::endl;
   std::cout << "cm energy : " << cmEnergy  << std::endl;
   std::cout << "beta      : " << beta  << std::endl;
   std::cout << "gamma     : " << gamma << std::endl;
   std::cout << std::endl;
   std::cout << "*** LAB ***"<< std::endl;
   std::cout << "KineticEnergy_Beam/u  : " << eKinBeam_Lab  << std::endl;
   std::cout << "TotalEnergy_Beam/u    : " << eTotalBeam_Lab << std::endl;
   std::cout << "TotalMomentum_Beam/u  : " << pTotalBeam_Lab << std::endl;
   std::cout << "rapidity              : " << rapidityBeam_Lab << std::endl;
   std::cout << std::endl;
   std::cout << "*** CM ***" << std::endl;
   std::cout << "KineticEnergy_Beam/u : " << eKin_CM << std::endl;
   std::cout << "TotalEnergy_Beam/u   : " << eBeam_CM << std::endl;
   std::cout << "TotalMomentum_Beam/u : " << pBeam_CM << std::endl;
   std::cout << "rapidity             : " <<  rapidityBeam_CM << std::endl;
   std::cout << std::endl;
   std::cout << "rapidity shift : " << rapidityShift << std::endl;
   std::cout << std::endl;
   //--------------------------------------------------------------------------------------//


  // Tree raw

  const int totalEntry = 124715;

  int Z, N, eventID, dI;
  double pX, pY, pZ, dD; 

  fstream openFile("../../data/rawData.dat");
  TFile *writeFile = new TFile("../../data/amdData_ThetaRing.root", "recreate");
  TTree *rawTree = new TTree("raw", "rawTree");
         rawTree -> Branch("Z", &Z, "Z/I");
         rawTree -> Branch("N", &N, "N/I");
         rawTree -> Branch("pX", &pX, "pX/D");
         rawTree -> Branch("pY", &pY, "pY/D");
         rawTree -> Branch("pZ", &pZ, "pZ/D");
	 
   for(int i=0; i<totalEntry; i++)
   {
	openFile >> Z >> N >> pX >> pY >> pZ >> dI >> dI >> dD >> dD >> eventID >> dI;
	rawTree -> Fill();
   }
   openFile.close();




   // Tree CM Frame

   int    A;
   double pTotCM, pTCM, thetaCM, phi, eKinCM, eTotBeamCM, rapidityCM, m0;



   TTree *cmTree = new TTree("cm", "CM Frame");
	  cmTree -> Branch("A", &A, "A/I");
	  cmTree -> Branch("Z", &Z, "Z/I");
	  cmTree -> Branch("N", &N, "N/I");
	  cmTree -> Branch("pX", &pX, "pX/D");
	  cmTree -> Branch("pY", &pY, "pY/D");
	  cmTree -> Branch("pZ", &pZ, "pZ/D");
	  cmTree -> Branch("pT", &pTCM, "pT/D");
	  cmTree -> Branch("theta", &thetaCM, "theta/D");
	  cmTree -> Branch("phi", &phi, "phi/D");
	  cmTree -> Branch("eTot", &eTotBeamCM, "eTot/D");
	  cmTree -> Branch("eKin", &eKinCM, "eKin/D");
	  cmTree -> Branch("rapidity", &rapidityCM, "rapidity/D");
	  cmTree -> Branch("eventID", &eventID, "eventID/I");
 
   //int entries = rawTree -> GetEntries();
   //for(int iEntry=0; iEntry<entries; iEntry++)
 
   for(int entryN = 0; entryN<totalEntry; entryN++)
   {
	rawTree -> GetEntry(entryN);
	
	A = Z+N;
	
	pX=pX*A;
	pY=pY*A;
	pZ=pZ*A;
	pTotCM=CalculateTotalMomentum(pX, pY, pZ);
	pTCM=CalculatePT(pX, pY);
	thetaCM = CalculateTheta(pZ, pTCM);
	if(thetaCM<0) thetaCM = thetaCM+TMath::Pi();

	phi = CalculatePhi(pX, pY);

	m0         = mProton*Z + mNeutron*N;
	eTotBeamCM = CalculateTotalEnergy(pTotCM, m0);
	eKinCM     = eTotBeamCM - m0;
	rapidityCM = CalculateRapidity(eTotBeamCM, pZ)/rapidityBeam_CM; //Normalization

	cmTree -> Fill();
   }




   // Tree LAB Frame


   double thetaLab, rapidityLab, pZLab, pTotLab, eKinLab, eTotBeamLab;

   TTree *labTree1 = new TTree("event_1", "LAB Frame");	
	  labTree1 -> Branch("A", &A, "A/I");
	  labTree1 -> Branch("Z", &Z, "Z/I");
	  labTree1 -> Branch("N", &N, "N/I");
	  labTree1 -> Branch("pT", &pTCM, "pT/D");
	  labTree1 -> Branch("pZ", &pZLab, "pZ/D");
	  labTree1 -> Branch("pX", &pX, "pX/D");
	  labTree1 -> Branch("pY", &pY, "pY/D");
	  labTree1 -> Branch("pTot", &pTotLab, "pTot/D");
	  labTree1 -> Branch("theta", &thetaLab, "theta/D");
	  labTree1 -> Branch("phi", &phi, "phi/D");
	  labTree1 -> Branch("eTot", &eTotBeamLab, "eTot/D");
	  labTree1 -> Branch("eKin", &eKinLab, "eKin/D");
	  labTree1 -> Branch("rapidity", &rapidityLab, "rapidity/D");

   for(int entryN = 0; entryN<totalEntry; entryN++)
   {
	cmTree -> GetEntry(entryN);
	
	pZLab = -eTotBeamCM*beta*gamma + pZ*gamma;
	eTotBeamLab = eTotBeamCM*gamma - pZ*beta*gamma;
	eKinLab = eTotBeamLab - (mProton*Z + mNeutron*N);
	rapidityLab = CalculateRapidity(eTotBeamLab, pZLab)/rapidityBeam_Lab;
	pTotLab = TMath::Sqrt(pTCM*pTCM + pZLab*pZLab);
	thetaLab = CalculateTheta(pZLab, pTCM);
	if(thetaLab<0) thetaLab = thetaLab + TMath::Pi();

  if(thetaLab>17.5*TMath::Pi()/180&&thetaLab<=32.5*TMath::Pi()/180&&Z!=0)
    {  
	    labTree1 -> Fill();
    }
   }

   writeFile -> cd();
   labTree1 -> Write();
   
   TTree *labTree2 = new TTree("event_2", "LAB Frame");	
	  labTree2 -> Branch("A", &A, "A/I");
	  labTree2 -> Branch("Z", &Z, "Z/I");
	  labTree2 -> Branch("N", &N, "N/I");
	  labTree2 -> Branch("pT", &pTCM, "pT/D");
	  labTree2 -> Branch("pZ", &pZLab, "pZ/D");
	  labTree2 -> Branch("pX", &pX, "pX/D");
	  labTree2 -> Branch("pY", &pY, "pY/D");
	  labTree2 -> Branch("pTot", &pTotLab, "pTot/D");
	  labTree2 -> Branch("theta", &thetaLab, "theta/D");
	  labTree2 -> Branch("phi", &phi, "phi/D");
	  labTree2 -> Branch("eTot", &eTotBeamLab, "eTot/D");
	  labTree2 -> Branch("eKin", &eKinLab, "eKin/D");
	  labTree2 -> Branch("rapidity", &rapidityLab, "rapidity/D");

   for(int entryN = 0; entryN<totalEntry; entryN++)
   {
	cmTree -> GetEntry(entryN);
	
	pZLab = -eTotBeamCM*beta*gamma + pZ*gamma;
	eTotBeamLab = eTotBeamCM*gamma - pZ*beta*gamma;
	eKinLab = eTotBeamLab - (mProton*Z + mNeutron*N);
	rapidityLab = CalculateRapidity(eTotBeamLab, pZLab)/rapidityBeam_Lab;
	pTotLab = TMath::Sqrt(pTCM*pTCM + pZLab*pZLab);
	thetaLab = CalculateTheta(pZLab, pTCM);
	if(thetaLab<0) thetaLab = thetaLab + TMath::Pi();

  if(thetaLab>32.5*TMath::Pi()/180&&thetaLab<=47.5*TMath::Pi()/180&&Z!=0)
    {  
	    labTree2 -> Fill();
    }
   }

   writeFile -> cd();
   labTree2 -> Write();

   TTree *labTree3 = new TTree("event_3", "LAB Frame");	
	  labTree3 -> Branch("A", &A, "A/I");
	  labTree3 -> Branch("Z", &Z, "Z/I");
	  labTree3 -> Branch("N", &N, "N/I");
	  labTree3 -> Branch("pT", &pTCM, "pT/D");
	  labTree3 -> Branch("pZ", &pZLab, "pZ/D");
	  labTree3 -> Branch("pX", &pX, "pX/D");
	  labTree3 -> Branch("pY", &pY, "pY/D");
	  labTree3 -> Branch("pTot", &pTotLab, "pTot/D");
	  labTree3 -> Branch("theta", &thetaLab, "theta/D");
	  labTree3 -> Branch("phi", &phi, "phi/D");
	  labTree3 -> Branch("eTot", &eTotBeamLab, "eTot/D");
	  labTree3 -> Branch("eKin", &eKinLab, "eKin/D");
	  labTree3 -> Branch("rapidity", &rapidityLab, "rapidity/D");

   for(int entryN = 0; entryN<totalEntry; entryN++)
   {
	cmTree -> GetEntry(entryN);
	
	pZLab = -eTotBeamCM*beta*gamma + pZ*gamma;
	eTotBeamLab = eTotBeamCM*gamma - pZ*beta*gamma;
	eKinLab = eTotBeamLab - (mProton*Z + mNeutron*N);
	rapidityLab = CalculateRapidity(eTotBeamLab, pZLab)/rapidityBeam_Lab;
	pTotLab = TMath::Sqrt(pTCM*pTCM + pZLab*pZLab);
	thetaLab = CalculateTheta(pZLab, pTCM);
	if(thetaLab<0) thetaLab = thetaLab + TMath::Pi();

  if(thetaLab>47.5*TMath::Pi()/180&&thetaLab<=62.5*TMath::Pi()/180&&Z!=0)
    {  
	    labTree3 -> Fill();
    }
   }

   writeFile -> cd();
   labTree3 -> Write();
  
  
   TTree *labTree4 = new TTree("event_4", "LAB Frame");	
	  labTree4 -> Branch("A", &A, "A/I");
	  labTree4 -> Branch("Z", &Z, "Z/I");
	  labTree4 -> Branch("N", &N, "N/I");
	  labTree4 -> Branch("pT", &pTCM, "pT/D");
	  labTree4 -> Branch("pZ", &pZLab, "pZ/D");
	  labTree4 -> Branch("pX", &pX, "pX/D");
	  labTree4 -> Branch("pY", &pY, "pY/D");
	  labTree4 -> Branch("pTot", &pTotLab, "pTot/D");
	  labTree4 -> Branch("theta", &thetaLab, "theta/D");
	  labTree4 -> Branch("phi", &phi, "phi/D");
	  labTree4 -> Branch("eTot", &eTotBeamLab, "eTot/D");
	  labTree4 -> Branch("eKin", &eKinLab, "eKin/D");
	  labTree4 -> Branch("rapidity", &rapidityLab, "rapidity/D");

   for(int entryN = 0; entryN<totalEntry; entryN++)
   {
	cmTree -> GetEntry(entryN);
	
	pZLab = -eTotBeamCM*beta*gamma + pZ*gamma;
	eTotBeamLab = eTotBeamCM*gamma - pZ*beta*gamma;
	eKinLab = eTotBeamLab - (mProton*Z + mNeutron*N);
	rapidityLab = CalculateRapidity(eTotBeamLab, pZLab)/rapidityBeam_Lab;
	pTotLab = TMath::Sqrt(pTCM*pTCM + pZLab*pZLab);
	thetaLab = CalculateTheta(pZLab, pTCM);
	if(thetaLab<0) thetaLab = thetaLab + TMath::Pi();

  if(thetaLab>62.5*TMath::Pi()/180&&thetaLab<=77.5*TMath::Pi()/180&&Z!=0)
    {  
	    labTree4 -> Fill();
    }
   }

   writeFile -> cd();
   labTree4 -> Write();


   TTree *labTree5 = new TTree("event_5", "LAB Frame");	
	  labTree5 -> Branch("A", &A, "A/I");
	  labTree5 -> Branch("Z", &Z, "Z/I");
	  labTree5 -> Branch("N", &N, "N/I");
	  labTree5 -> Branch("pT", &pTCM, "pT/D");
	  labTree5 -> Branch("pZ", &pZLab, "pZ/D");
	  labTree5 -> Branch("pX", &pX, "pX/D");
	  labTree5 -> Branch("pY", &pY, "pY/D");
	  labTree5 -> Branch("pTot", &pTotLab, "pTot/D");
	  labTree5 -> Branch("theta", &thetaLab, "theta/D");
	  labTree5 -> Branch("phi", &phi, "phi/D");
	  labTree5 -> Branch("eTot", &eTotBeamLab, "eTot/D");
	  labTree5 -> Branch("eKin", &eKinLab, "eKin/D");
	  labTree5 -> Branch("rapidity", &rapidityLab, "rapidity/D");

   for(int entryN = 0; entryN<totalEntry; entryN++)
   {
	cmTree -> GetEntry(entryN);
	
	pZLab = -eTotBeamCM*beta*gamma + pZ*gamma;
	eTotBeamLab = eTotBeamCM*gamma - pZ*beta*gamma;
	eKinLab = eTotBeamLab - (mProton*Z + mNeutron*N);
	rapidityLab = CalculateRapidity(eTotBeamLab, pZLab)/rapidityBeam_Lab;
	pTotLab = TMath::Sqrt(pTCM*pTCM + pZLab*pZLab);
	thetaLab = CalculateTheta(pZLab, pTCM);
	if(thetaLab<0) thetaLab = thetaLab + TMath::Pi();

  if(thetaLab>77.5*TMath::Pi()/180&&thetaLab<=102*TMath::Pi()/180&&Z!=0)
    {  
	    labTree5 -> Fill();
    }
   }

   writeFile -> cd();
   labTree5 -> Write();


   TTree *labTree6 = new TTree("event_6", "LAB Frame");	
	  labTree6 -> Branch("A", &A, "A/I");
	  labTree6 -> Branch("Z", &Z, "Z/I");
	  labTree6 -> Branch("N", &N, "N/I");
	  labTree6 -> Branch("pT", &pTCM, "pT/D");
	  labTree6 -> Branch("pZ", &pZLab, "pZ/D");
	  labTree6 -> Branch("pX", &pX, "pX/D");
	  labTree6 -> Branch("pY", &pY, "pY/D");
	  labTree6 -> Branch("pTot", &pTotLab, "pTot/D");
	  labTree6 -> Branch("theta", &thetaLab, "theta/D");
	  labTree6 -> Branch("phi", &phi, "phi/D");
	  labTree6 -> Branch("eTot", &eTotBeamLab, "eTot/D");
	  labTree6 -> Branch("eKin", &eKinLab, "eKin/D");
	  labTree6 -> Branch("rapidity", &rapidityLab, "rapidity/D");

   for(int entryN = 0; entryN<totalEntry; entryN++)
   {
	cmTree -> GetEntry(entryN);
	
	pZLab = -eTotBeamCM*beta*gamma + pZ*gamma;
	eTotBeamLab = eTotBeamCM*gamma - pZ*beta*gamma;
	eKinLab = eTotBeamLab - (mProton*Z + mNeutron*N);
	rapidityLab = CalculateRapidity(eTotBeamLab, pZLab)/rapidityBeam_Lab;
	pTotLab = TMath::Sqrt(pTCM*pTCM + pZLab*pZLab);
	thetaLab = CalculateTheta(pZLab, pTCM);
	if(thetaLab<0) thetaLab = thetaLab + TMath::Pi();

  if(thetaLab>102*TMath::Pi()/180&&thetaLab<=126*TMath::Pi()/180&&Z!=0)
    {  
	    labTree6 -> Fill();
    }
   }

   writeFile -> cd();
   labTree6 -> Write();


   TTree *labTree7 = new TTree("event_7", "LAB Frame");	
	  labTree7 -> Branch("A", &A, "A/I");
	  labTree7 -> Branch("Z", &Z, "Z/I");
	  labTree7 -> Branch("N", &N, "N/I");
	  labTree7 -> Branch("pT", &pTCM, "pT/D");
	  labTree7 -> Branch("pZ", &pZLab, "pZ/D");
	  labTree7 -> Branch("pX", &pX, "pX/D");
	  labTree7 -> Branch("pY", &pY, "pY/D");
	  labTree7 -> Branch("pTot", &pTotLab, "pTot/D");
	  labTree7 -> Branch("theta", &thetaLab, "theta/D");
	  labTree7 -> Branch("phi", &phi, "phi/D");
	  labTree7 -> Branch("eTot", &eTotBeamLab, "eTot/D");
	  labTree7 -> Branch("eKin", &eKinLab, "eKin/D");
	  labTree7 -> Branch("rapidity", &rapidityLab, "rapidity/D");

   for(int entryN = 0; entryN<totalEntry; entryN++)
   {
	cmTree -> GetEntry(entryN);
	
	pZLab = -eTotBeamCM*beta*gamma + pZ*gamma;
	eTotBeamLab = eTotBeamCM*gamma - pZ*beta*gamma;
	eKinLab = eTotBeamLab - (mProton*Z + mNeutron*N);
	rapidityLab = CalculateRapidity(eTotBeamLab, pZLab)/rapidityBeam_Lab;
	pTotLab = TMath::Sqrt(pTCM*pTCM + pZLab*pZLab);
	thetaLab = CalculateTheta(pZLab, pTCM);
	if(thetaLab<0) thetaLab = thetaLab + TMath::Pi();

  if(thetaLab>126*TMath::Pi()/180&&thetaLab<=150*TMath::Pi()/180&&Z!=0)
    {  
	    labTree7 -> Fill();
    }
   }

   writeFile -> cd();
   labTree7 -> Write();

   double N1 = labTree1 -> GetEntries();
   double N2 = labTree2 -> GetEntries();
   double N3 = labTree3 -> GetEntries();
   double N4 = labTree4 -> GetEntries();
   double N5 = labTree5 -> GetEntries();
   double N6 = labTree6 -> GetEntries();
   double N7 = labTree7 -> GetEntries();

   cout << "Generated # of charged particles 1 : " << N1/2010. << endl;
   cout << "Generated # of charged particles 2 : " << N2/2010. << endl;
   cout << "Generated # of charged particles 3 : " << N3/2010. << endl;
   cout << "Generated # of charged particles 4 : " << N4/2010. << endl;
   cout << "Generated # of charged particles 5 : " << N5/2010. << endl;
   cout << "Generated # of charged particles 6 : " << N6/2010. << endl;
   cout << "Generated # of charged particles 7 : " << N7/2010. << endl;



   delete rawTree;
   delete cmTree;
   delete labTree1;
   delete labTree2;
   delete labTree3;
   delete labTree4;
   delete labTree5;
   delete labTree6;
   delete labTree7;
   delete writeFile;

   return 0;
}


