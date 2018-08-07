#ifndef TDM_Run_h
#define TDM_Run_h 1

#include "G4Run.hh"
#include "globals.hh"

class G4Event;

/// Run class
///

class TDM_Run : public G4Run
{
  public:
    TDM_Run();
    virtual ~TDM_Run();

    // method from the base class
    virtual void Merge(const G4Run*);

};


#endif

