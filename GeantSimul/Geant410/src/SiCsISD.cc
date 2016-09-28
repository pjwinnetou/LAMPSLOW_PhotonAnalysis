//Geant4 headers
#include "G4VPhysicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4SDManager.hh"

//lampslow headers
#include "SiCsISD.hh"
#include "SiCsIHit.hh"
#include "lampslowData.hh"

//C++ headers
#include <iostream>
#include <sstream>

//Root Headers
#include "TMath.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TStyle.h"

using namespace std;


TH1D *hist = new TH1D("hist_scattering","#theta_{scatt}; #theta (degree);Counts",100,0,180);
TH2D *hist2D = new TH2D("EnergyScatt","Energy vs #theta_{scatt}; #theta (degree);Energy",300,0,180,150,0,13);
TH1D *hist1 = new TH1D("hist_scattering1","#theta_{scatt}; #theta (degree);Counts",100,0,18000);
//TCanvas *cvs = new TCanvas("scattering","",700,700);
//TCanvas *cvs2D = new TCanvas("EnergyScatt","",700,700);


SiCsISD::SiCsISD(const G4String &name, const G4String pv_name)
:G4VSensitiveDetector(name), PVName(pv_name)
{
  //for unique name ...
  /*
  G4int fullID = detTypeID*10000+sectID*100+detID;
  std::ostringstream ss_fullID;
  ss_fullID << fullID;
  G4String str_collectionName = "DetHitsColletion" + G4String(ss_fullID.str());
  collectionName.insert(str_collectionName);
  */
  G4String hitCollectionName = "SiCsIHitCollection_" + PVName; 
  collectionName.insert(hitCollectionName);
}

SiCsISD::~SiCsISD() {}

void SiCsISD::Initialize(G4HCofThisEvent *HCTE)
{
  hitsCollection = new G4THitsCollection<SiCsIHit>(SensitiveDetectorName, collectionName[0]);
  G4int hcid = G4SDManager::GetSDMpointer() -> GetCollectionID(collectionName[0]);
  HCTE -> AddHitsCollection(hcid, hitsCollection);
}
  
G4bool SiCsISD::ProcessHits(G4Step *aStep, G4TouchableHistory *ROHist)
{
  
  gStyle -> SetOptStat(0);
  gStyle -> SetTitleYOffset(1.85);
  gStyle -> SetTitleXOffset(1.45);
  gStyle -> SetTitleSize(0.04,"xy");
  gStyle -> SetPadLeftMargin(0.16);
  gStyle -> SetPadRightMargin(0.05);
  gStyle -> SetPadTopMargin(0.12);
  gStyle -> SetPadBottomMargin(0.15);
  
//  if(!ROHist) return false;

  energyDeposit = aStep -> GetTotalEnergyDeposit();
//  if(energyDeposit == 0.) return false;

  if((aStep -> GetPreStepPoint() -> GetPhysicalVolume() -> GetName() == "TestVetoBlock_PV") &&(energyDeposit!=0.))
  {
    parentID    = aStep -> GetTrack() -> GetParentID();
    pID         = aStep -> GetTrack() -> GetDefinition() -> GetPDGEncoding();
    prePosition = aStep -> GetPreStepPoint() -> GetPosition();
    preMomentum = aStep -> GetPreStepPoint() -> GetMomentum();
    time        = aStep -> GetPreStepPoint() -> GetGlobalTime();
    copyNum     = aStep -> GetPreStepPoint() -> GetTouchableHandle() -> GetCopyNumber();
    detID       = 5;

    SiCsIHit *aHit = new SiCsIHit(parentID, pID, prePosition, preMomentum, time, energyDeposit,
                              detTypeID, sectID, copyNum, detID);
    hitsCollection -> insert(aHit);
    }
/*
  if((aStep -> GetPreStepPoint() -> GetPhysicalVolume() -> GetName() == "TestSiBlock_PV") &&(energyDeposit!=0.))
  {
    parentID    = aStep -> GetTrack() -> GetParentID();
    pID         = aStep -> GetTrack() -> GetDefinition() -> GetPDGEncoding();
    prePosition = aStep -> GetPreStepPoint() -> GetPosition();
    preMomentum = aStep -> GetPreStepPoint() -> GetMomentum();
    time        = aStep -> GetPreStepPoint() -> GetGlobalTime();
    copyNum     = aStep -> GetPreStepPoint() -> GetTouchableHandle() -> GetCopyNumber();
    detID       = 7;

    SiCsIHit *aHit = new SiCsIHit(parentID, pID, prePosition, preMomentum, time, energyDeposit,
                              detTypeID, sectID, copyNum, detID);
    hitsCollection -> insert(aHit);
    }

 */
  if((aStep -> GetPreStepPoint() -> GetPhysicalVolume() -> GetName() == "TestCsIBlock_PV") &&(energyDeposit!=0.))
  {
    parentID    = aStep -> GetTrack() -> GetParentID();
    pID         = aStep -> GetTrack() -> GetDefinition() -> GetPDGEncoding();
    prePosition = aStep -> GetPreStepPoint() -> GetPosition();
    postPosition = aStep -> GetPostStepPoint() -> GetPosition();
    preMomentum = aStep -> GetPreStepPoint() -> GetMomentum();
    time        = aStep -> GetPreStepPoint() -> GetGlobalTime();
    copyNum     = aStep -> GetPreStepPoint() -> GetTouchableHandle() -> GetCopyNumber();
    detID       = 11;

    SiCsIHit *aHit = new SiCsIHit(parentID, pID, prePosition, preMomentum, time, energyDeposit,
                              detTypeID, sectID, copyNum, detID);
    hitsCollection -> insert(aHit);

   }
  
  return true;
}

void SiCsISD::EndOfEvent(G4HCofThisEvent *HCTE)
{
}
