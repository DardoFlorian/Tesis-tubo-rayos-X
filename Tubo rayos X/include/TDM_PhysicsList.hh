#ifndef TDM_PhysicsList_h
#define TDM_PhysicsList_h 1

#include "globals.hh"
#include "G4VUserPhysicsList.hh"


class TDM_PhysicsList : public G4VUserPhysicsList
{
  public:
    TDM_PhysicsList();
    virtual ~TDM_PhysicsList();

  public:
    virtual void ConstructParticle();
    virtual void ConstructProcess();

    virtual void SetCuts();

    //these methods Construct physics processes and register them
    void ConstructDecay();
    void ConstructEM();

  private:
    G4int fVerboseLebel;
};


#endif /* TDM_PhysicsList_h */
