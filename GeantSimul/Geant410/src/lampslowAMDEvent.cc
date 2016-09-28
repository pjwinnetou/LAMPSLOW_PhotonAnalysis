#include "lampslowAMDEvent.hh"
#include "lampslowPrimaryGeneratorAction.hh"

#include <TFile.h>
#include <TTree.h>

#include <sstream>

lampslowAMDEvent::lampslowAMDEvent(lampslowPrimaryGeneratorAction* lampslowPGAPointer, G4int eventNumberPointer)
:lampslowPGA(lampslowPGAPointer), eventNumber(int(eventNumberPointer))
{
  amdData = new TFile("./../amdData.root","read");
  SelectEvent(eventNumber);
}

lampslowAMDEvent::~lampslowAMDEvent()
{
  delete amdData;
  delete eventTree;
}

void lampslowAMDEvent::SelectEvent(int eventNumber)
{
  std::stringstream eventTreeName;
  eventTreeName << "event_" << eventNumber;

  //eventTree = (TTree*) amdData -> Get(eventTreeName);
  eventTree = (TTree*) amdData -> Get(Form("event_%d",eventNumber));
  eventTree -> SetBranchAddress("N", &N);
  eventTree -> SetBranchAddress("Z", &Z);
  eventTree -> SetBranchAddress("pX", &pX);
  eventTree -> SetBranchAddress("pY", &pY);
  eventTree -> SetBranchAddress("pZ", &pZ);

  numberOfTracks = eventTree -> GetEntries();
  lampslowPGA -> SetNumberOfTracks(numberOfTracks);
}

void lampslowAMDEvent::GetBeam(int trackNumber)
{
  eventTree -> GetEntry(trackNumber);
  lampslowPGA -> SetBeam(N, Z, pX, pY, pZ);
}
