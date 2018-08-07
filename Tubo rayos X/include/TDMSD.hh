#ifndef TDMSD_h
#define TDM_h 1

#include "G4DataVector.hh"
#include "G4VSensitiveDetector.hh"
#include "TDMHit.hh"

#include <vector>

class G4Step;
class G4HCofThisEvent;

class TDMSD : public G4VSensitiveDetector
{

  public:

    TDMSD(G4String name);
    virtual ~TDMSD();

    virtual void Initialize(G4HCofThisEvent* hitCollection);
    virtual G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* history);

    //A version of processHits that keeps aStep constant

    virtual void EndOfEvent(G4HCofThisEvent* hitCollection);
    virtual void clear();
    void DrawAll();
    void PrintAll();

  private:

    TDMHitsCollection* fTDMHitCollection;

};

#endif
