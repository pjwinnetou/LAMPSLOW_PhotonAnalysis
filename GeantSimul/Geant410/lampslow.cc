#include "lampslowDetectorConstruction.hh"
#include "lampslowPrimaryGeneratorAction.hh"
#include "lampslowEventAction.hh"

#include "G4RunManager.hh"
#include "G4TransportationManager.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "QGSP_BERT.hh"
#include "QGSP_BIC.hh"


//#include "LAMPSAnaRoot.hh"
#include "lampslowData.hh"

int main(int argc, char ** argv)
{
  CLHEP::HepRandom::setTheSeed(time(NULL));
  lampslowData *lampslow_data = new lampslowData();

  //Run
  G4RunManager *runManager = new G4RunManager();

  lampslowDetectorConstruction* lampslowDC = new lampslowDetectorConstruction();
  runManager -> SetUserInitialization(lampslowDC);

  //Physics List
//  lampslowPhysicsList* physicsList = new lampslowPhysicsList();
//  runManager -> SetUserInitialization(physicsList);
  
  G4VModularPhysicsList* physicslist = new QGSP_BIC;
  physicslist->SetVerboseLevel(1);
  runManager->SetUserInitialization(physicslist);

  lampslowPrimaryGeneratorAction* lampslowPGA = new lampslowPrimaryGeneratorAction(runManager, lampslow_data);
  runManager -> SetUserAction(lampslowPGA);

  lampslowEventAction* lampslowEA = new lampslowEventAction(lampslow_data, lampslowPGA);
  runManager -> SetUserAction(lampslowEA);

  runManager -> Initialize();

  //Visual
  G4VisManager* visManager = new G4VisExecutive();
  visManager -> Initialize();

  // for macro files
  if(argc==1)
  {
    G4UIsession* session = new G4UIterminal(new G4UItcsh);
    session -> SessionStart();
    delete session;
  }

  else
  {
    G4String command = "/control/execute ";
    G4String fileName = argv[1];

    G4UImanager* UI = G4UImanager::GetUIpointer();
    UI -> ApplyCommand(command + fileName);

    G4UIsession* session = new G4UIterminal(new G4UItcsh);
    session -> SessionStart();
    delete session;
  }

  delete runManager;
  delete visManager;
  delete lampslow_data;

  return 0;
}
