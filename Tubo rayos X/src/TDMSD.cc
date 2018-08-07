//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: LXePMTSD.cc 73915 2013-09-17 07:32:26Z gcosmo $
//
/// \file optical/LXe/src/LXePMTSD.cc
/// \brief Implementation of the LXePMTSD class
//
//
#include "TDMSD.hh"
#include "TDMHit.hh"
#include "TDM_DetectorConstruction.hh"

#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4ios.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleDefinition.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TDMSD::TDMSD(G4String name)
  : G4VSensitiveDetector(name),fTDMHitCollection(0)
{
  collectionName.insert("pmtHitCollection");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TDMSD::~TDMSD() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TDMSD::Initialize(G4HCofThisEvent* hitsCE){
  fTDMHitCollection = new TDMHitsCollection
                      (SensitiveDetectorName,collectionName[0]);
  //Store collection with event and keep ID
  static G4int hitCID = -1;
  if(hitCID<0){
    hitCID = GetCollectionID(0);
  }
  hitsCE->AddHitsCollection( hitCID, fTDMHitCollection );
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool TDMSD::ProcessHits(G4Step* TDMaStep,G4TouchableHistory*){

	// energy deposit
	  G4double edep = TDMaStep->GetTotalEnergyDeposit(); // Energía depositada en [MeV]

	  G4Track* TDMTrack = TDMaStep -> GetTrack();
	  const G4ParticleDefinition* partdef = TDMTrack-> GetParticleDefinition(); //Tipo de partícula


	  G4ThreeVector Posicion = TDMaStep->GetPostStepPoint()->GetPosition(); //Vector de posición en [mm]
	  G4double posx = Posicion.getX();
	  G4double posy = Posicion.getY();
	  G4double posz = Posicion.getZ();

	  //--------- Posicion y energia ----------------------

	  G4cout << partdef->GetParticleName() << "\t"<< posx <<"\t" << posy <<"\t" << posz <<"\t" << (TDMTrack->GetKineticEnergy()) <<G4endl;

	  if (edep==0.) return false;

	  TDMHit* newHit = new TDMHit();

	  newHit->setfener(edep);
	  newHit->SetTDMPos (TDMaStep->GetPostStepPoint()->GetPosition());

	  fTDMHitCollection->insert( newHit );


	return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TDMSD::EndOfEvent(G4HCofThisEvent* ) {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TDMSD::clear() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TDMSD::DrawAll() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TDMSD::PrintAll() {}
