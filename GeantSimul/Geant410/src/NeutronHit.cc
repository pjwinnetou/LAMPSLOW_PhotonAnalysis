//lampslow header
#include "NeutronHit.hh"

G4Allocator<NeutronHit> NeutronHitAllocator;

// allocator
NeutronHit::NeutronHit()
:parentID(0), pID(0), prePosition(G4ThreeVector(0,0,0)), preMomentum(G4ThreeVector(0,0,0)),
 time(0), energyDeposit(0) ,detTypeID(0), sectionID(0), copyNum(0), detID(0)
{
}

NeutronHit::NeutronHit(G4int parentID0, G4int pID0, G4ThreeVector prePosition0, G4ThreeVector preMomentum0,
               G4double time0, G4double energyDeposit0, G4int detTypeID0, G4int sectionID0, G4int copyNum0, G4int detID0)
:parentID(parentID0), pID(pID0), prePosition(prePosition0), preMomentum(preMomentum0), 
 time(time0), energyDeposit(energyDeposit0), detTypeID(detTypeID0), sectionID(sectionID0), copyNum(copyNum0), detID(detID0)
{
}

NeutronHit::~NeutronHit()
{
}
