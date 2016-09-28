#ifndef EXMAPLEEVENTACTION_H
#define EXMAPLEEVENTACTION_H 1

//Geant4 headers
#include "G4UserEventAction.hh"

//lampslow headers
#include "lampslowPrimaryGeneratorAction.hh"
#include "lampslowData.hh"

class G4Event;

class lampslowEventAction: public G4UserEventAction
{
  public:
    lampslowEventAction(lampslowData *lampslowDF, lampslowPrimaryGeneratorAction* lampslowPGAPointer);
    virtual ~lampslowEventAction();

    virtual void BeginOfEventAction(const G4Event* anEvent);
    virtual void EndOfEventAction(const G4Event* anEvent);

  private:
    G4int hitsCollectionID;
    lampslowData* lampslow_data;
    lampslowPrimaryGeneratorAction* lampslowPGA;
};

#endif
