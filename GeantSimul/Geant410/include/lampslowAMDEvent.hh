#ifndef lampslowAMDEvent_hh
#define lampslowAMDEvent_hh 1

#include <TFile.h>
#include <TTree.h>
#include "lampslowPrimaryGeneratorAction.hh"

class lampslowPrimaryGeneratorAction;

class lampslowAMDEvent
{
  public:
    lampslowAMDEvent(lampslowPrimaryGeneratorAction* lampslowPGA, G4int eventNumber);
    ~lampslowAMDEvent();

    void GetBeam(int trackNumber);
    void SelectEvent(int eventNumber);

  private:
    lampslowPrimaryGeneratorAction* lampslowPGA;

    int eventNumber;
    int numberOfTracks;

    int N, Z; 
    double pX, pY, pZ;
    
    TFile* amdData;
    TTree* eventTree;
};
#endif
