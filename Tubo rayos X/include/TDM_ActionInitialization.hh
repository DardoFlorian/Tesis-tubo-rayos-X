#ifndef TDM_ActionInitialization_h
#define TDM_ActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

/// Action initialization class.

class TDM_ActionInitialization : public G4VUserActionInitialization
{
  public:
    TDM_ActionInitialization();
    virtual ~TDM_ActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
};

#endif
