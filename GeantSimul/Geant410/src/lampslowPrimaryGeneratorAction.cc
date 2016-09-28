//lampslow headers
#include "lampslowPrimaryGeneratorAction.hh"

//geant4 headers
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleGun.hh"
#include "G4Event.hh"
#include "G4ParticleTypes.hh"
#include "G4UnitsTable.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleDefinition.hh"
#include "Randomize.hh"

//c++ headers
#include <iostream>
#include <TMath.h>
#include <TRandom.h>
using namespace CLHEP;
lampslowPrimaryGeneratorAction::lampslowPrimaryGeneratorAction(G4RunManager* runManagerPointer, lampslowData* lampslowDataPointer)
:runManager(runManagerPointer), lampslow_data(lampslowDataPointer), gunPosition(G4ThreeVector()), eventNumber(1) 
{
  particleGun = new G4ParticleGun;
  lampslowPGM = new lampslowPrimaryGeneratorMessenger(this, runManager);

  gunPosition = G4ThreeVector(0,0,0);
  PrepareParticles();
  SetSingleParticleBeam();
}

lampslowPrimaryGeneratorAction::~lampslowPrimaryGeneratorAction()
{
  delete particleGun;
  delete lampslowPGM;
  //delete event;
}

void lampslowPrimaryGeneratorAction::PrepareBeam()
{
  if(event) event -> SelectEvent(eventNumber);
  else      event = new lampslowAMDEvent(this, eventNumber);
  trackNumber=0;
}

void lampslowPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  if(event) SetAMDEvent();
  lampslow_data -> SetTrackID(trackNumber);
//  std::cout << trackNumber << ": " << beamParticle -> GetParticleName() << ", " << beamParticle -> GetPDGEncoding() << std::endl;
  SetSingleParticleBeam();
  particleGun -> GeneratePrimaryVertex(anEvent);
}

void lampslowPrimaryGeneratorAction::SetAMDEvent()
{
  event -> GetBeam(trackNumber);

  //momentum
  G4ThreeVector momentum(trackPx*MeV, trackPy*MeV, trackPz*MeV);
  //momentum magnitude
  momentumMagnitude = sqrt(momentum.x()*momentum.x()
                          +momentum.y()*momentum.y()
                          +momentum.z()*momentum.z());
  //momentum direction
  momentumDirection = G4ThreeVector(momentum.x()/momentumMagnitude
                                   ,momentum.y()/momentumMagnitude
                                   ,momentum.z()/momentumMagnitude);
  //particle: GetIon([atomic number],[atomic mass],[excitation energy=0: ground state])
  if(trackZ==0&&trackZ+trackN==1)      beamParticle = particleTable -> FindParticle("neutron");
  else if(trackZ==1&&trackZ+trackN==1) beamParticle = particleTable -> FindParticle("proton");
  else if(trackZ==0&&trackZ+trackN==0) beamParticle = particleTable -> FindParticle("gamma");
  //else                                 beamParticle = particleTable -> GetIon(trackZ, trackZ+trackN, 0);

  //kinetic energy 
  SetKineticEnergy();

  particleGun -> SetParticlePosition(gunPosition);
  particleGun -> SetParticleDefinition(beamParticle);
  particleGun -> SetParticleMomentumDirection(momentumDirection);
  particleGun -> SetParticleEnergy(kineticEnergy);
}

void lampslowPrimaryGeneratorAction::PrepareParticles()
{
  particleTable = G4ParticleTable::GetParticleTable();
}

void lampslowPrimaryGeneratorAction::SetKineticEnergy()
{
  G4double protonMass = 938.272; // MeV/c2
  G4double neutronMass = 939.565; // MeV/c2
  G4double mass = protonMass*trackZ + neutronMass*trackN;
  kineticEnergy = sqrt(momentumMagnitude*momentumMagnitude+mass*mass) - mass;
}

void lampslowPrimaryGeneratorAction::SetSingleParticleBeam()
{

    beamParticle=particleTable->FindParticle("gamma");
    kineticEnergy = (CLHEP::RandGauss::shoot(662,20))*keV;
  

  momentumDirection = G4ThreeVector(0,0,1);

  particleGun -> SetParticlePosition(gunPosition);
  particleGun -> SetParticleDefinition(beamParticle);
  particleGun -> SetParticleMomentumDirection(momentumDirection);
  particleGun -> SetParticleEnergy(kineticEnergy);
}


void lampslowPrimaryGeneratorAction::SetBeam(int N, int Z, double pX, double pY, double pZ)
{
  trackN = N;
  trackZ = Z;
  trackPx = pX;
  trackPy = pY;
  trackPz = pZ;
}

void lampslowPrimaryGeneratorAction::EndOfTrack()
{
  trackNumber++;
}
