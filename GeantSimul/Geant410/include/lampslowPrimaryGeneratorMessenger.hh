#ifndef lampslowPrimaryGeneratorMessenger_hh
#define lampslowPrimaryGeneratorMessenger_hh 1

#include "G4RunManager.hh"
#include "G4UIdirectory.hh"
#include "G4UImessenger.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithoutParameter.hh"

class G4RunManager;
class lampslowPrimaryGeneratorAction;
class G4UIcmdWithoutParameter;
class G4UIcmdWithAnInteger;
class G4UIdirectory;

class lampslowPrimaryGeneratorMessenger: public G4UImessenger
{
  public:
    lampslowPrimaryGeneratorMessenger(lampslowPrimaryGeneratorAction*, G4RunManager*);
    ~lampslowPrimaryGeneratorMessenger();

    void SetNewValue(G4UIcommand*, G4String);

  private:
    lampslowPrimaryGeneratorAction* lampslowPGA;
    G4RunManager* runManager;

    G4UIdirectory* amdDirectory;
    G4UIcmdWithoutParameter* run;
    G4UIcmdWithAnInteger*    useAMDData;
    G4UIcmdWithAnInteger*    eventNumber;
};
#endif
