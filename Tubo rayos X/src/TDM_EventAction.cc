#include "TDM_EventAction.hh"
#include "TDM_Run.hh"
#include "TDM_RunAction.hh"
#include "TDM_PrimaryGeneratorAction.hh"
#include "TDM_Analysis.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"

#include <sstream>
#include <iostream>

TDM_EventAction::TDM_EventAction()
: G4UserEventAction()
{
	TLDNumber = 3; //Número de detectores

	for(G4int i =0;i<TLDNumber;i++){
	fAbsoEdepHCID[i] = -1;
    fAbsoTrackLengthHCID[i] = -1;
    fAbsoDodepHCID[i] = -1;
	}
}

TDM_EventAction::~TDM_EventAction()
{}


G4THitsMap<G4double>*
TDM_EventAction::GetHitsCollection(G4int hcID,
                                  const G4Event* event) const
{
  auto hitsCollection
    = static_cast<G4THitsMap<G4double>*>(
        event->GetHCofThisEvent()->GetHC(hcID));

  if ( ! hitsCollection ) {
    G4ExceptionDescription msg;
    msg << "Cannot access hitsCollection ID " << hcID;
    G4Exception("B4dEventAction::GetHitsCollection()",
      "MyCode0003", FatalException, msg);
  }

  return hitsCollection;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double TDM_EventAction::GetSum(G4THitsMap<G4double>* hitsMap) const
{
  G4double sumValue = 0.;
  for ( auto it : *hitsMap->GetMap() ) {
    sumValue += *(it.second);
  }
  return sumValue;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TDM_EventAction::PrintEventStatistics(
                            G4double absoEdep, G4double absoTrackLength,G4double absoDodep) const
{
  // Print event statistics

  G4cout
     << "   Absorber: total energy: "
     << std::setw(7) << G4BestUnit(absoEdep, "Energy")
     << "       total track length: "
     << std::setw(7) << G4BestUnit(absoTrackLength, "Length")
	 << "       total dose deposit: "
	 << std::setw(7) << G4BestUnit(absoDodep, "Dose")
	 << G4endl;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


void TDM_EventAction::BeginOfEventAction(const G4Event*)
{}

void TDM_EventAction::EndOfEventAction(const G4Event* event)
{
	// Get hist collections IDs
	// get analysis manager
	auto analysisManager = G4AnalysisManager::Instance();

	G4double * AbsoEdep = new G4double[TLDNumber];
	G4double * AbsoDodep = new G4double[TLDNumber];

	for(G4int n =0;n<TLDNumber;n++){
		AbsoEdep[n]= 0;
		AbsoDodep[n]=0;
	}

	for(G4int i = 0; i<TLDNumber;i++){

		G4String C;
		std::stringstream convert;
		convert << i;
		C = convert.str();

		G4String b = C+"Abso"+"/"+C+"AbsoEdep";
		G4String c = C+"Abso"+"/"+C+"AbsoDodep";


	 if ( fAbsoEdepHCID[i] == -1 ) {
	    fAbsoEdepHCID[i]
	      = G4SDManager::GetSDMpointer()->GetCollectionID(b);
	    fAbsoDodepHCID[i]
	    	    	      = G4SDManager::GetSDMpointer()->GetCollectionID(c);
	 	 	 	 }

	 	 AbsoEdep[i] = GetSum(GetHitsCollection(fAbsoEdepHCID[i], event));
		 AbsoDodep[i] = GetSum(GetHitsCollection(fAbsoDodepHCID[i], event));

	  G4double X = AbsoEdep[i];
	  G4double Y = AbsoDodep[i];

	  // fill ntuple

	  analysisManager->FillNtupleDColumn((2*i), X);
	  analysisManager->FillNtupleDColumn((2*i)+1, Y);

	}

	analysisManager->AddNtupleRow();

	delete AbsoEdep;
	delete AbsoDodep;
}
