#ifndef SICSISD_h
#define SICSISD_h 1

//Geant4 headers
#include "G4VSensitiveDetector.hh"
#include "G4ThreeVector.hh"

//lampslow headers
#include "SiCsIHit.hh"
#include "lampslowData.hh"

//Root Headers
#include "TH1D.h"
#include "TCanvas.h"

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

class SiCsISD: public G4VSensitiveDetector
{
  public: 
    SiCsISD(const G4String& name, const G4String pv_name);
    virtual ~SiCsISD();

    virtual G4bool ProcessHits(G4Step *aStep, G4TouchableHistory *ROHist);
    virtual void Initialize(G4HCofThisEvent *HCTE);
    virtual void EndOfEvent(G4HCofThisEvent *HCTE);

  private:
    G4THitsCollection<SiCsIHit> *hitsCollection;

    const G4String PVName;

    //ID
    G4int detTypeID; // 0~2: si-layers, 3:csi, 4: block
    G4int sectID;    // such as theta division
    G4int detID;     // ID inside the section
    G4int copyNum;   // Copy Number inside the section

    G4double time, parentID, pID, energyDeposit;
    G4ThreeVector preMomentum, prePosition, postPosition;
    lampslowData* lampsData;
};
#endif
