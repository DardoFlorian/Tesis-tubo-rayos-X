#ifndef TDM_PrimaryGeneratorAction_h
#define TDM_PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"
//#include "G4GeneralParticleSource.hh"

//class G4ParticleGun;
class G4GeneralParticleSource;
class G4Event;
class G4Box;

class TDM_PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    TDM_PrimaryGeneratorAction();
    virtual ~TDM_PrimaryGeneratorAction();

    // method from the base class
    virtual void GeneratePrimaries(G4Event* anEvent);
    const G4GeneralParticleSource* GetParticleGun() const { return fParticleGun; }

  private:

    G4GeneralParticleSource* fParticleGun; // pointer a to G4 gun class

};

#endif


