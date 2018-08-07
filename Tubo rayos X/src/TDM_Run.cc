#include "TDM_Run.hh"

TDM_Run::TDM_Run()
: G4Run()
{}

TDM_Run::~TDM_Run()
{}

void TDM_Run::Merge(const G4Run* run)
{
  G4Run::Merge(run);
}
