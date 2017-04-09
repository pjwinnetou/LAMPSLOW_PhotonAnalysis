//Geant4 headers
#include "lampslowDetectorConstruction.hh"
#include "SiCsISD.hh"
#include "NeutronSD.hh"

//Geant4 headers
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4Box.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4Trap.hh"
#include "G4TwistTrapAlphaSide.hh"
#include "G4TwistedTrap.hh"
#include "G4Tubs.hh"
#include "G4PVPlacement.hh"
#include "G4SDManager.hh"
#include "G4FieldManager.hh"
#include "G4SubtractionSolid.hh"
#include <TMath.h>
#include <sstream>
#include <iostream>

//ReadOut
//#include "SiCsIROGeometry.hh"

using std::stringstream;
using namespace std;
using namespace CLHEP;

lampslowDetectorConstruction::lampslowDetectorConstruction()
//:sicsi_PVName("SiCsIPV"), block_PVName("BlockPV")
{
  ConstructMaterials();
  DefineDimensions();
}

lampslowDetectorConstruction::~lampslowDetectorConstruction()
{
  DestructMaterials();
}

void lampslowDetectorConstruction::DefineDimensions()
{
  //Lab
  labX = 1000*CLHEP::mm;
  labY = 1000*CLHEP::mm;
  labZ = 2000*CLHEP::mm;

  
  
  testblock_X = 150*CLHEP::mm;
  testblock_Y = 150*CLHEP::mm;
  testblock_Z = 200*CLHEP::mm;
}

G4VPhysicalVolume* lampslowDetectorConstruction::Construct()
{
  G4VSolid* labSolid = new G4Box("labSolid", labX/2, labY/2, labZ/2);
  G4LogicalVolume* labLV = new G4LogicalVolume(labSolid, Air, "labLV");
  G4VPhysicalVolume* labPV = new G4PVPlacement(0, G4ThreeVector(), "labPV", labLV, 0, false, 0);

 
  //veto test
  G4Box* TestVetoBlock = new G4Box("TestVeto", 101.045*CLHEP::mm, 70.04*CLHEP::mm, 1*cm);
  G4LogicalVolume* TestVetoBlockLV = new G4LogicalVolume(TestVetoBlock, Scint, "TestVetoBlockLV");
  new G4PVPlacement(0, G4ThreeVector(0,0,400*mm+9*cm+10.8*cm), "TestVetoBlock_PV", TestVetoBlockLV, labPV, false,0);

  G4VisAttributes* TestVetoBlockSD = new G4VisAttributes(G4Colour(1.,1.,0.));
  TestVetoBlockLV -> SetVisAttributes(TestVetoBlockSD);
/*
  //Silicon test
  G4Box* TestSiBlock = new G4Box("TestSi", 31.045*CLHEP::mm, 10.04*CLHEP::mm, 250*CLHEP::um);
  G4LogicalVolume* TestSiBlockLV = new G4LogicalVolume(TestSiBlock, Silicon, "TestSiBlockLV");
  new G4PVPlacement(0, G4ThreeVector(0,0,400*mm), "TestSiBlock_PV", TestSiBlockLV, labPV, false,0);

  G4VisAttributes* TestSiBlockSD = new G4VisAttributes(G4Colour(1.,0.,0.));
  TestSiBlockLV -> SetVisAttributes(TestSiBlockSD);
*/
  //CsI test
  G4Box* TestCsIBlock = new G4Box("TestCsI", 60*CLHEP::mm, 47*CLHEP::mm, 60*CLHEP::mm);
  G4LogicalVolume* TestCsIBlockLV = new G4LogicalVolume(TestCsIBlock, CsI, "TestCsIBlockLV");
  new G4PVPlacement(0, G4ThreeVector(0,0,400*mm+6*cm), "TestCsIBlock_PV", TestCsIBlockLV, labPV, false,0);

  G4VisAttributes* TestCsIBlockSD = new G4VisAttributes(G4Colour(0.,0.,1.));
  TestCsIBlockLV -> SetVisAttributes(TestCsIBlockSD);

  //Det Register
  G4SDManager* sdManager = G4SDManager::GetSDMpointer();
/*
  NeutronSD* NSD = new NeutronSD("/Neutron/NeutronSD","Neutron");
  sdManager -> AddNewDetector(NSD);
  BlockLV -> SetSensitiveDetector(NSD);
*/
  SiCsISD* VetoSD = new SiCsISD("/SiCsI/VetoSD","Veto");
  sdManager -> AddNewDetector(VetoSD);
  TestVetoBlockLV -> SetSensitiveDetector(VetoSD);
  /*
  SiCsISD* SiSD = new SiCsISD("/SiCsI/SiSD","Si");
  sdManager -> AddNewDetector(SiSD);
  TestSiBlockLV -> SetSensitiveDetector(SiSD);
  */
  SiCsISD* CsISD = new SiCsISD("/SiCsI/CsISD","CsI");
  sdManager -> AddNewDetector(CsISD);
  TestCsIBlockLV -> SetSensitiveDetector(CsISD);
 // Track_LVSphere -> SetSensitiveDetector(CsISD);

  

  //Define detectors
//  ConstructSiCsI(labPV, sdManager);
//  ConstructBlock(labPV, sdManager);

  return labPV;
}


//Materials
void lampslowDetectorConstruction::ConstructMaterials()
{
  const G4double labTemp = STP_Temperature + 20.*kelvin;


  G4double densityUniverse = 1.e-25*g/CLHEP::cm3;
  G4double tempUniverse= 2.73 *kelvin;
  //G4double pressureUniverse = 3.e-18*pascal;



  // Elements
  elN  = new G4Element("Nitrogen", "N",  7,  14.000674*g/mole);
  elO  = new G4Element("Oxygen",   "O",  8,  15.9994*g/mole);
  elC  = new G4Element("Carbon",   "C",  6,  12.011*g/mole);
  elH  = new G4Element("Hydrogen", "H",  1,  1.00794*g/mole);
  elAr = new G4Element("Argon",    "Ar", 18, 39.938*g/mole);
  elSi = new G4Element("Silicon",    "Si", 14, 28.0855*g/mole);
  elCs = new G4Element("Cesium",    "Cs", 55, 132.90543*g/mole);
  elI = new G4Element("Iodine",    "I", 53, 126.90447*g/mole);

  // Materials
  Air = new G4Material("Air", 1.2929e-03*g/CLHEP::cm3, 3, kStateGas, labTemp);
  Air -> AddElement(elN, 75.47/99.95);
  Air -> AddElement(elO, 23.20/99.95);
  Air -> AddElement(elAr, 1.28/99.95);

  //Vacuum
  G4double temperature = tempUniverse;
  //G4double pressure = pressureUniverse;
  G4double density = densityUniverse;
   
  Vacuum =  new G4Material("Vacuum", density, 2, kStateGas, temperature);
  Vacuum -> AddElement(elO,.3);
  Vacuum -> AddElement(elN,.7);

  Scint = new G4Material("Scintillator", 1.05*g/cm3, 2, kStateSolid, labTemp);
  Scint -> AddElement(elC, 10);
  Scint -> AddElement(elH, 11);

  //SI
  Silicon = new G4Material("Silicon", 2.33*g/cm3, 1, kStateSolid, labTemp);
  Silicon -> AddElement(elSi, 1);

  //CsI
  CsI = new G4Material("CsI", 4.51*g/cm3, 2, kStateSolid, labTemp);
  CsI -> AddElement(elCs, 1);
  CsI -> AddElement(elI, 1);
 // CsI -> GetIonization() -> SetMeanExcitationEnergy(533.1*eV);


}

void lampslowDetectorConstruction::DestructMaterials()
{
  delete Air;
  delete Vacuum;

  delete elH;
  delete elC;
  delete elAr;
  delete elO;
  delete elN;
  delete Silicon;
  delete CsI;
}
