#include "TDM_ActionInitialization.hh"
#include "TDM_PrimaryGeneratorAction.hh"
#include "TDM_RunAction.hh"
#include "TDM_EventAction.hh"

TDM_ActionInitialization::TDM_ActionInitialization()
 : G4VUserActionInitialization()
{}

TDM_ActionInitialization::~TDM_ActionInitialization()
{}

void TDM_ActionInitialization::BuildForMaster() const
{
  SetUserAction(new TDM_RunAction);
}

void TDM_ActionInitialization::Build() const
{
  SetUserAction(new TDM_PrimaryGeneratorAction);
  SetUserAction(new TDM_RunAction);
  SetUserAction(new TDM_EventAction);

}
