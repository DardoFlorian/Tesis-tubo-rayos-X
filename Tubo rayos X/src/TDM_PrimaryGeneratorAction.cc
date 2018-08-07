
#include "TDM_PrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4ios.hh"
#include "Randomize.hh"
//#include "globals.hh"

#include <cmath>
#include <map>


TDM_PrimaryGeneratorAction::TDM_PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0)
{

  fParticleGun = new G4GeneralParticleSource();

  // default particle kinematic
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle
    = particleTable->FindParticle(particleName="gamma");
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticlePosition(G4ThreeVector(-0.105*m,0.288*m,0.5255*m)); //Ubicación de la fuente

}

TDM_PrimaryGeneratorAction::~TDM_PrimaryGeneratorAction()
{
  delete fParticleGun;
}

void TDM_PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{

	fParticleGun->GeneratePrimaryVertex(anEvent);

}
