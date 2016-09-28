#ifndef lampslowData_hh
#define lampslowData_hh 1

//Root headers
#include <TFile.h>
#include <TTree.h>

class TFile;
class TTree;

class lampslowData
{
  public:
    lampslowData();
    ~lampslowData();

    void FillSimulationData(
                            int    pID,
                            int    parentID,
                            double preX_val,
                            double preY_val,
                            double preZ_val,
                            double prePx_val,
                            double prePy_val,
                            double prePz_val,
//                            double postX_val,
//                            double postY_val,
//                            double postZ_val,
                            double edep_val,
                            double time_val,
                            int    detTypeID_val,
                            int    sectionID_val,
                            int    copyNum_val,
                            int    detID_val);
    void FillGeneratorData(int pID, double energyInit);

    void SetTrackID(int val) { trackID = val; }
    void SetEventID(int val) { eventID = val; }
    void BeginOfEvent(int eventN);

  private:
    void SetBranch();

    double preX, preY, preZ, prePx, prePy, prePz, time, edep, energyInit, mass;
    int    parentID, pID, detTypeID, sectionID, copyNum, detID, trackID, eventID;

    TFile* dataFile;
    TTree* dataTree;
    TTree* generatorTree;
};

#endif
