//lampslow headers
#include "lampslowData.hh"

//c++ headers
#include <iostream>

lampslowData::lampslowData()
{
  dataFile = new TFile("./rawData_lampslow.root","recreate");
  generatorTree = new TTree("generator","");
  dataTree = new TTree("data","");
  SetBranch();
}

void lampslowData::SetBranch()
{
  generatorTree -> Branch("eventID",&eventID,"eventID/I");
  generatorTree -> Branch("trackID",&trackID,"trackID/I");
  generatorTree -> Branch("pID",&pID,"pID/I");
  generatorTree -> Branch("energyInit",&energyInit,"energyInit/D");


  dataTree -> Branch("eventID",&eventID,"eventID/I");
  dataTree -> Branch("trackID",&trackID,"trackID/I");
  dataTree -> Branch("pID",&pID,"pID/I");
  dataTree -> Branch("parentID",&parentID,"parentID/I");
  dataTree -> Branch("x_pre",&preX,"x_pre/D");
  dataTree -> Branch("y_pre",&preY,"y_pre/D");
  dataTree -> Branch("z_pre",&preZ,"z_pre/D");
  dataTree -> Branch("pX_pre",&prePx,"pX_pre/D");
  dataTree -> Branch("pY_pre",&prePy,"pY_pre/D");
  dataTree -> Branch("pZ_pre",&prePz,"pZ_pre/D");
  dataTree -> Branch("time",&time,"time/D");
  dataTree -> Branch("edep",&edep,"edep/D");
  dataTree -> Branch("detTypeID",&detTypeID,"detTypeID/I");
  dataTree -> Branch("sectionID",&sectionID,"sectionID/I");
  dataTree -> Branch("copyNum",&copyNum,"copyNum/I");
  dataTree -> Branch("detID",&detID,"detID/I");
}

lampslowData::~lampslowData()
{
  dataFile -> cd();
  dataTree -> Write();
  std::cout << "rawData.root is created!" << std::endl;

  delete dataTree;
  delete dataFile;
}

void lampslowData::BeginOfEvent(int eventN)
{
}

void lampslowData::FillGeneratorData(int pID_val, double energyInit_val)
{
  pID = pID_val;
  energyInit = energyInit_val;

  generatorTree -> Fill();
}



void lampslowData::FillSimulationData(
                        int    pID_val,
                        int    parentID_val,
                        double preX_val,
                        double preY_val,
                        double preZ_val,
                        double prePx_val,
                        double prePy_val,
                        double prePz_val,
                        double time_val,
                        double edep_val,
                        int    detTypeID_val,
                        int    sectionID_val,
                        int    copyNum_val,
                        int    detID_val)
{
//  if(edep_val==0) return;
  pID       = pID_val;
  parentID  = parentID_val;
  preX      = preX_val;
  preY      = preY_val;
  preZ      = preZ_val;
  prePx     = prePx_val;
  prePy     = prePy_val;
  prePz     = prePz_val;
  time      = time_val;
  edep      = edep_val;
  detTypeID = detTypeID_val;
  sectionID = sectionID_val;
  copyNum   = copyNum_val;
  detID     = detID_val;

  dataTree -> Fill();
}
