#ifndef TDM_EventAction_h
#define TDM_EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

#include "G4THitsMap.hh"
#include <sstream>
#include <iostream>

/// Event action class

class TDM_EventAction : public G4UserEventAction
{
  public:
    TDM_EventAction();
    virtual ~TDM_EventAction();

    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);

    /***************** Primitive Score ******************/

  private:
    // methods
    G4THitsMap<G4double>* GetHitsCollection(G4int hcID,
                                            const G4Event* event) const;
    G4double GetSum(G4THitsMap<G4double>* hitsMap) const;
    void PrintEventStatistics(G4double absoEdep, G4double absoTrackLength,G4double absoDodep) const;

    // data members

    G4int TLDNumber ; //número de detectores

    //Define el tamaño en relación a la cantidad de detectores
    G4int * fAbsoEdepHCID = new G4int[TLDNumber];
    G4int * fAbsoDodepHCID = new G4int[TLDNumber];
    G4int * fAbsoTrackLengthHCID = new G4int[TLDNumber];

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
