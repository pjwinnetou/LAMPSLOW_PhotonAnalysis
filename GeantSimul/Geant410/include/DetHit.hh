#ifndef DetHit_h
#define DetHit_h 1

#include "G4ThreeVector.hh"
#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"

class DetHit: public G4VHit
{
  private:
    G4int parentID;
    G4int pID;
    G4ThreeVector prePosition;
    G4ThreeVector preMomentum;
    G4double time;
    G4double energyDeposit;
    G4int detTypeID;
    G4int sectionID;
    G4int copyNum;
    G4int detID;

  public:
    DetHit();
    DetHit(G4int, G4int, G4ThreeVector, G4ThreeVector, G4double, G4double, G4int, G4int, G4int, G4int);
    virtual ~DetHit();

    DetHit(const DetHit &right);
    const DetHit &operator=(const DetHit &right);

    void *operator new(size_t);
    void operator delete(void *aHit);

    G4int         GetParentID()    const { return parentID;      };
    G4int         GetPID()         const { return pID;           };
    G4ThreeVector GetPrePosition() const { return prePosition;   };
    G4ThreeVector GetPreMomentum() const { return preMomentum;   };
    G4double      GetTime()        const { return time;          };
    G4double      GetEdep()        const { return energyDeposit; };
    G4int         GetDetTypeID()   const { return detTypeID;     }; 
    G4int         GetSectionID()   const { return sectionID;     }; 
    G4int         GetCopyNum()     const { return copyNum;       }; 
    G4int         GetDetID()       const { return detID;         }; 
};

inline DetHit::DetHit(const DetHit &right)
:G4VHit()
{
  parentID      = right.parentID;
  pID           = right.pID;
  prePosition   = right.prePosition;
  preMomentum   = right.preMomentum;
  energyDeposit = right.energyDeposit;
  time          = right.time;
  detTypeID     = right.detTypeID;
  sectionID     = right.sectionID;
  copyNum       = right.copyNum;
  detID         = right.detID;
}

inline const DetHit &DetHit::operator=(const DetHit &right)
{
  parentID      = right.parentID;
  pID           = right.pID;
  prePosition   = right.prePosition;
  preMomentum   = right.preMomentum;
  energyDeposit = right.energyDeposit;
  time          = right.time;
  detTypeID     = right.detTypeID;
  sectionID     = right.sectionID;
  copyNum       = right.copyNum;
  detID         = right.detID;

  return *this;
}

extern G4Allocator<DetHit> DetHitAllocator;

inline void *DetHit::operator new(size_t)
{
  void *aHit = (void *)DetHitAllocator.MallocSingle();
  return aHit;
}

inline void DetHit::operator delete(void *aHit)
{
  DetHitAllocator.FreeSingle((DetHit *) aHit);
}

#endif
