//Geant4 headers
#include "G4VPhysicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4SDManager.hh"

//lampslow headers
#include "NeutronSD.hh"
#include "NeutronHit.hh"

//C++ headers
#include <iostream>
#include <sstream>

//Root headers
#include "TMath.h"
using namespace std;
NeutronSD::NeutronSD(const G4String &name, const G4String pv_name)
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
  G4String hitCollectionName = "NeutronHitCollection_" + PVName; 
  collectionName.insert(hitCollectionName);
}

NeutronSD::~NeutronSD() {}

void NeutronSD::Initialize(G4HCofThisEvent *HCTE)
{
  hitsCollection = new G4THitsCollection<NeutronHit>(SensitiveDetectorName, collectionName[0]);
  G4int hcid = G4SDManager::GetSDMpointer() -> GetCollectionID(collectionName[0]);
  HCTE -> AddHitsCollection(hcid, hitsCollection);
}
  
G4bool NeutronSD::ProcessHits(G4Step *aStep, G4TouchableHistory *ROHist)
{
//  if(!ROHist) return false;

  energyDeposit = aStep -> GetTotalEnergyDeposit();
  if(energyDeposit == 0.) return false;
 /* 
  if((aStep -> GetPreStepPoint() -> GetPhysicalVolume() -> GetName() == "Neutron_PV") &&(energyDeposit!=0.))
  {
    parentID    = aStep -> GetTrack() -> GetParentID();
    pID         = aStep -> GetTrack() -> GetDefinition() -> GetPDGEncoding();
    prePosition = aStep -> GetPreStepPoint() -> GetPosition();
    preMomentum = aStep -> GetPreStepPoint() -> GetMomentum();
    time        = aStep -> GetPreStepPoint() -> GetGlobalTime();
    copyNum     = aStep -> GetPreStepPoint() -> GetTouchableHandle() -> GetCopyNumber();
    detID       = 3;   

    NeutronHit *aHit = new NeutronHit(parentID, pID, prePosition, preMomentum, time, energyDeposit,
                              detTypeID, sectID, copyNum, detID);
    hitsCollection -> insert(aHit);
  }
  */
  
  if((aStep -> GetPreStepPoint() -> GetPhysicalVolume() -> GetName() == "testblock_PV")&&(energyDeposit!=0.))
  {
    parentID    = aStep -> GetTrack() -> GetParentID();
    pID         = aStep -> GetTrack() -> GetDefinition() -> GetPDGEncoding();
    prePosition = aStep -> GetPreStepPoint() -> GetPosition();
//    postPosition = aStep -> GetPreStepPoint() -> GetPosition();
    preMomentum = aStep -> GetPreStepPoint() -> GetMomentum();
    time        = aStep -> GetPreStepPoint() -> GetGlobalTime();
    copyNum     = aStep -> GetPreStepPoint() -> GetTouchableHandle() -> GetCopyNumber();
    detID       = 9;   

    NeutronHit *aHit = new NeutronHit(parentID, pID, prePosition, preMomentum, time, energyDeposit,
                              detTypeID, sectID, copyNum, detID);
    hitsCollection -> insert(aHit);

//    cout << "pID : " << pID << endl;
  //  cout << "Pos Neutron Track : " << postPosition << endl;
  }
/*
  if((aStep -> GetPreStepPoint() -> GetPhysicalVolume() -> GetName() == "testblock_PV")&&(aStep -> GetPostStepPoint() -> GetPhysicalVolume() -> GetName() == "Track_PV"))
  {
    parentID    = aStep -> GetTrack() -> GetParentID();
    pID         = aStep -> GetTrack() -> GetDefinition() -> GetPDGEncoding();
    prePosition = aStep -> GetPreStepPoint() -> GetPosition();
    G4ThreeVector postPosition = aStep -> GetPostStepPoint() -> GetPosition();
    preMomentum = aStep -> GetPreStepPoint() -> GetMomentum();
    time        = aStep -> GetPreStepPoint() -> GetGlobalTime();
    copyNum     = aStep -> GetPreStepPoint() -> GetTouchableHandle() -> GetCopyNumber();
    detID       = 0;   

    NeutronHit *aHit = new NeutronHit(parentID, pID, prePosition, preMomentum, time, energyDeposit,
                              detTypeID, sectID, copyNum, detID);
    hitsCollection -> insert(aHit);
  
    G4double Length_PreT = TMath::Sqrt(prePosition(0)*prePosition(0)+prePosition(1)*prePosition(1));
    G4double Length_PostT = TMath::Sqrt(postPosition(0)*postPosition(0)+postPosition(1)*postPosition(1));
    G4double Z_diff = postPosition(2)-prePosition(2);
    G4double Trans_diff = Length_PostT-Length_PreT;
    G4double Tangent_Theta=0;
    if(Z_diff>0&&Trans_diff>0) Tangent_Theta = TMath::ATan(Trans_diff/Z_diff);
    else if(Z_diff<0&&Trans_diff>0) Tangent_Theta = TMath::Pi()-TMath::ATan(TMath::Abs(Trans_diff/Z_diff));
    else if(Z_diff<0&&Trans_diff<0) Tangent_Theta = TMath::Pi()+TMath::ATan(TMath::Abs(Trans_diff/Z_diff));
    else if(Z_diff>0&&Trans_diff<0) Tangent_Theta = 2*TMath::Pi()-TMath::ATan(TMath::Abs(Trans_diff/Z_diff));
    else if(Z_diff==0&&Trans_diff>0) Tangent_Theta = TMath::Pi()/2;
    else if(Z_diff==0&&Trans_diff<0) Tangent_Theta = TMath::Pi()/2*3;
    else if(Z_diff==0&&Trans_diff==0) Tangent_Theta=0;

    G4double ScatteringAngle = Tangent_Theta*180/TMath::Pi();

    cout << "*** Hit ***" << endl;
    cout << "pID : " << pID << endl;
    cout << "Pre Positiion : " << prePosition << endl;
    cout << "Pos Positiion : " << postPosition << endl;
    cout << "Z Difference : " << Z_diff  << endl;
    cout << "T Difference : " << Trans_diff  << endl;
    cout << "Angle : " << ScatteringAngle << endl;
    cout << "Time : " << time << endl;
    cout << "energy dep : " << energyDeposit << endl;
    cout << endl;
    cout << endl;
    cout << endl;
//    cout << "Distance : " << 
  }
*/

  return true;
}

void NeutronSD::EndOfEvent(G4HCofThisEvent *HCTE)
{
}
