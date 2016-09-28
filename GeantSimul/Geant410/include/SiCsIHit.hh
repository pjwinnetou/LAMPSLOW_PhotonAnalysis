#ifndef SiCsIHit_h
#define SiCsIHit_h 1

#include "G4ThreeVector.hh"
#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"

class SiCsIHit: public G4VHit
{
  private:
    G4int parentID;
    G4int pID;
    G4ThreeVector prePosition;
    G4ThreeVector postPosition;
    G4ThreeVector preMomentum;
    G4double time;
    G4double energyDeposit;
    G4int detTypeID;
    G4int sectionID;
    G4int copyNum;
    G4int detID;

  public:
    SiCsIHit();
    SiCsIHit(G4int, G4int, G4ThreeVector, G4ThreeVector, G4double, G4double, G4int, G4int, G4int, G4int);
    virtual ~SiCsIHit();

    SiCsIHit(const SiCsIHit &right);
    const SiCsIHit &operator=(const SiCsIHit &right);

    void *operator new(size_t);
    void operator delete(void *aHit);

    G4int         GetParentID()    const { return parentID;      };
    G4int         GetPID()         const { return pID;           };
    G4ThreeVector GetPrePosition() const { return prePosition;   };
//    G4ThreeVector GetPostPosition() const { return postPosition;   };
    G4ThreeVector GetPreMomentum() const { return preMomentum;   };
    G4double      GetTime()        const { return time;          };
    G4double      GetEdep()        const { return energyDeposit; };
    G4int         GetDetTypeID()   const { return detTypeID;     }; 
    G4int         GetSectionID()   const { return sectionID;     }; 
    G4int         GetCopyNum()     const { return copyNum;       }; 
    G4int         GetDetID()       const { return detID;         }; 
};

inline SiCsIHit::SiCsIHit(const SiCsIHit &right)
:G4VHit()
{
  parentID      = right.parentID;
  pID           = right.pID;
  prePosition   = right.prePosition;
//  postPosition   = right.postPosition;
  preMomentum   = right.preMomentum;
  energyDeposit = right.energyDeposit;
  time          = right.time;
  detTypeID     = right.detTypeID;
  sectionID     = right.sectionID;
  copyNum       = right.copyNum;
  detID         = right.detID;
}

inline const SiCsIHit &SiCsIHit::operator=(const SiCsIHit &right)
{
  parentID      = right.parentID;
  pID           = right.pID;
  prePosition   = right.prePosition;
//  postPosition   = right.postPosition;
  preMomentum   = right.preMomentum;
  energyDeposit = right.energyDeposit;
  time          = right.time;
  detTypeID     = right.detTypeID;
  sectionID     = right.sectionID;
  copyNum       = right.copyNum;
  detID         = right.detID;

  return *this;
}

extern G4Allocator<SiCsIHit> SiCsIHitAllocator;

inline void *SiCsIHit::operator new(size_t)
{
  void *aHit = (void *)SiCsIHitAllocator.MallocSingle();
  return aHit;
}

inline void SiCsIHit::operator delete(void *aHit)
{
  SiCsIHitAllocator.FreeSingle((SiCsIHit *) aHit);
}

#endif
