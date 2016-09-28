//Geant4 headers
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"

//lampslow headers
#include "lampslowPrimaryGeneratorAction.hh"
#include "lampslowEventAction.hh"
#include "lampslowData.hh"
#include "NeutronHit.hh"
#include "SiCsIHit.hh"
#include "NeutronSD.hh"
#include "SiCsISD.hh"

//c++ headers
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;
lampslowEventAction::lampslowEventAction(lampslowData* lampslowData, lampslowPrimaryGeneratorAction *lampslowPGAPointer)
: lampslow_data(lampslowData), lampslowPGA(lampslowPGAPointer)
{}

lampslowEventAction::~lampslowEventAction() 
{}

void lampslowEventAction::BeginOfEventAction(const G4Event* anEvent) 
{} 

void lampslowEventAction::EndOfEventAction(const G4Event* anEvent)
{
  G4SDManager* sdManager = G4SDManager::GetSDMpointer(); 
  G4HCofThisEvent* HCTE = anEvent -> GetHCofThisEvent();
  if (!HCTE) return;

  G4THitsCollection<SiCsIHit>* HC_SiCsI = NULL; 
  G4THitsCollection<NeutronHit>* HC_Neutron = NULL; 

  hitsCollectionID = sdManager -> GetCollectionID("SiCsIHitCollection_Veto");
  if (HCTE)  HC_SiCsI = (G4THitsCollection<SiCsIHit> *)(HCTE -> GetHC(hitsCollectionID));
  else HC_SiCsI = NULL;

  if(HC_SiCsI)
  {
    G4int numHits = HC_SiCsI -> entries();
  //  G4cout << "nHits : " << numHits << G4endl;
     for(G4int i=0; i!=numHits; i++)
    {
      G4int         pID           = (*HC_SiCsI)[i] -> GetPID();
      G4int         parentID      = (*HC_SiCsI)[i] -> GetParentID();
      G4ThreeVector prePosition   = (*HC_SiCsI)[i] -> GetPrePosition();
      G4ThreeVector preMomentum   = (*HC_SiCsI)[i] -> GetPreMomentum(); // not using for now
      G4double      time          = (*HC_SiCsI)[i] -> GetTime();
      G4double      energyDeposit = (*HC_SiCsI)[i] -> GetEdep();
      G4int         detTypeID     = (*HC_SiCsI)[i] -> GetDetTypeID();
      G4int         sectionID     = (*HC_SiCsI)[i] -> GetSectionID();
      G4int         copyNum       = (*HC_SiCsI)[i] -> GetCopyNum();
      G4int         detID         = (*HC_SiCsI)[i] -> GetDetID();

      lampslow_data -> FillSimulationData(
                            pID,
                            parentID,
                            prePosition.x(),
                            prePosition.y(),
                            prePosition.z(),
                            preMomentum.x(),
                            preMomentum.y(),
                            preMomentum.z(),
                            time,
                            energyDeposit,
                            detTypeID,
                            sectionID,
                            copyNum,
                            detID);
    }
  }
/*
  hitsCollectionID = sdManager -> GetCollectionID("SiCsIHitCollection_Si");
  if (HCTE)  HC_SiCsI = (G4THitsCollection<SiCsIHit> *)(HCTE -> GetHC(hitsCollectionID));
  else HC_SiCsI = NULL;

  if(HC_SiCsI)
  {
    G4int numHits = HC_SiCsI -> entries();
  //  G4cout << "nHits : " << numHits << G4endl;
     for(G4int i=0; i!=numHits; i++)
    {
      G4int         pID           = (*HC_SiCsI)[i] -> GetPID();
      G4int         parentID      = (*HC_SiCsI)[i] -> GetParentID();
      G4ThreeVector prePosition   = (*HC_SiCsI)[i] -> GetPrePosition();
      G4ThreeVector preMomentum   = (*HC_SiCsI)[i] -> GetPreMomentum(); // not using for now
      G4double      time          = (*HC_SiCsI)[i] -> GetTime();
      G4double      energyDeposit = (*HC_SiCsI)[i] -> GetEdep();
      G4int         detTypeID     = (*HC_SiCsI)[i] -> GetDetTypeID();
      G4int         sectionID     = (*HC_SiCsI)[i] -> GetSectionID();
      G4int         copyNum       = (*HC_SiCsI)[i] -> GetCopyNum();
      G4int         detID         = (*HC_SiCsI)[i] -> GetDetID();

      lampslow_data -> FillSimulationData(
                            pID,
                            parentID,
                            prePosition.x(),
                            prePosition.y(),
                            prePosition.z(),
                            preMomentum.x(),
                            preMomentum.y(),
                            preMomentum.z(),
                            time,
                            energyDeposit,
                            detTypeID,
                            sectionID,
                            copyNum,
                            detID);
    }
  }
*/
  hitsCollectionID = sdManager -> GetCollectionID("SiCsIHitCollection_CsI");
  if (HCTE)  HC_SiCsI = (G4THitsCollection<SiCsIHit> *)(HCTE -> GetHC(hitsCollectionID));
//  HC_SiCsI = (G4THitsCollection<SiCsIHit> *)(HCTE -> GetHC(hitsCollectionID));
  else HC_SiCsI = NULL;

  if(HC_SiCsI)
  {
    G4int numHits = HC_SiCsI -> entries();
  
  //  cout << "inthe" << endl;
    for(G4int i=0; i!=numHits; i++)
    {
      G4int         pID           = (*HC_SiCsI)[i] -> GetPID();
      G4int         parentID      = (*HC_SiCsI)[i] -> GetParentID();
      G4ThreeVector prePosition   = (*HC_SiCsI)[i] -> GetPrePosition();
//      G4ThreeVector postPosition  = (*HC_SiCsI)[i] -> GetPostPosition();
      G4ThreeVector preMomentum   = (*HC_SiCsI)[i] -> GetPreMomentum(); // not using for now
      G4double      time          = (*HC_SiCsI)[i] -> GetTime();
      G4double      energyDeposit = (*HC_SiCsI)[i] -> GetEdep();
      G4int         detTypeID     = (*HC_SiCsI)[i] -> GetDetTypeID();
      G4int         sectionID     = (*HC_SiCsI)[i] -> GetSectionID();
      G4int         copyNum       = (*HC_SiCsI)[i] -> GetCopyNum();
      G4int         detID         = (*HC_SiCsI)[i] -> GetDetID();

     // if(det==11 && energyDeposit!=0)
            
      lampslow_data -> FillSimulationData(
                            pID,
                            parentID,
                            prePosition.x(),
                           prePosition.y(),
                            prePosition.z(),
                            preMomentum.x(),
                            preMomentum.y(),
                            preMomentum.z(),
                            time,
                            energyDeposit,
                            detTypeID,
                            sectionID,
                            copyNum,
                            detID);
      
//      cout << "Save ::: " << lampslow_data << endl;
   }
  }
/*
  hitsCollectionID = sdManager -> GetCollectionID("NeutronHitCollection_Neutron");
  if (HCTE)  HC_Neutron = (G4THitsCollection<NeutronHit> *)(HCTE -> GetHC(hitsCollectionID));
  else HC_Neutron = NULL;
  if(HC_Neutron)
  {
    G4int numHits = HC_Neutron -> entries();
  //  G4cout << "nHits : " << numHits << G4endl;
     for(G4int i=0; i!=numHits; i++)
    {
      G4int         pID           = (*HC_Neutron)[i] -> GetPID();
      G4int         parentID      = (*HC_Neutron)[i] -> GetParentID();
      G4ThreeVector prePosition   = (*HC_Neutron)[i] -> GetPrePosition();
      G4ThreeVector preMomentum   = (*HC_Neutron)[i] -> GetPreMomentum(); // not using for now
      G4double      time          = (*HC_Neutron)[i] -> GetTime();
      G4double      energyDeposit = (*HC_Neutron)[i] -> GetEdep();
      G4int         detTypeID     = (*HC_Neutron)[i] -> GetDetTypeID();
      G4int         sectionID     = (*HC_Neutron)[i] -> GetSectionID();
      G4int         copyNum       = (*HC_Neutron)[i] -> GetCopyNum();
      G4int         detID         = (*HC_Neutron)[i] -> GetDetID();

      lampslow_data -> FillSimulationData(
                            pID,
                            parentID,
                            prePosition.x(),
                            prePosition.y(),
                            prePosition.z(),
                            time,
                            energyDeposit,
                            detTypeID,
                            sectionID,
                            copyNum,
                            detID);
    } 
  }
  */
  lampslowPGA -> EndOfTrack();
}
