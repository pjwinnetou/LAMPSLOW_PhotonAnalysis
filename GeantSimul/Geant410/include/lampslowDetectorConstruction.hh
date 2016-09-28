#ifndef lampslowDetectorConstrution_h
#define lampslowDetectorConstrution_h 1

//Geant4 headers
#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4SDManager.hh"
#include "G4FieldManager.hh"

class G4VPhysicalVolume;

class lampslowDetectorConstruction: public G4VUserDetectorConstruction
{
  public:
    lampslowDetectorConstruction();
    virtual ~lampslowDetectorConstruction();
    virtual G4VPhysicalVolume* Construct();

  private:
    void DefineDimensions();
    void ConstructMaterials();
    void DestructMaterials();

    void ConstructSiCsI(G4VPhysicalVolume* labPV, G4SDManager* sdManager);
    void ConstructBlock(G4VPhysicalVolume* labPV, G4SDManager* sdManager);

    G4Element* elN;
    G4Element* elO;
    G4Element* elC;
    G4Element* elH;
    G4Element* elAr;
    G4Element* elSi;
    G4Element* elCs;
    G4Element* elI;
    

    G4Material* Air;
    G4Material* Vacuum;
    G4Material* Scint;
    G4Material* Silicon;
    G4Material* CsI;
	
    //Lab
    G4double labX, labY, labZ;


    G4double testblock_X, testblock_Y, testblock_Z;
};
#endif
