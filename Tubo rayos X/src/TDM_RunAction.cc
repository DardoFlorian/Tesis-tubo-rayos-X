#include "TDM_RunAction.hh"
#include "TDM_PrimaryGeneratorAction.hh"
#include "TDM_DetectorConstruction.hh"
#include "TDM_Run.hh"
#include "TDM_Analysis.hh"
#include "TDM_RunActionMessenger.hh"

#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "G4WorkerRunManager.hh"
#include <G4WorkerThread.hh>
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
//#include "CLHEP/Random/Random.h"
#include "Randomize.hh"

#include <ctime>
#include <string>
#include <vector>

#include <stdio.h>      /* puts */
#include <time.h>       /* time_t, struct tm, time, localtime, strftime */

 #include "G4Threading.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TDM_RunAction::TDM_RunAction()
: G4UserRunAction()
{

		TheSeed = G4Random::getTheSeed();; //Obtener la semilla que se esta utilizando
		//create a messenger for this class
		//MessengerAction = new TDM_RunActionMessenger(this);

	 G4RunManager::RMType TType = G4RunManager::GetRunManager()->GetRunManagerType();
	 switch( TType ){
		 case G4RunManager::RMType::sequentialRM:
		 {
			 G4cout << "Corriendo en modo secuencial" << G4endl;
			 break;
		 }
		 case G4RunManager::RMType::masterRM:
		 {

			 G4cout << "Corriendo en el hilo maestro" << G4endl;
			 break;
		 }
		 case G4RunManager::RMType::workerRM:
		 {

			 G4cout << "Corriendo en un hilo esclavo" << G4endl;
			 const TDM_RunAction *MasterRunAction = static_cast<const TDM_RunAction*>(G4MTRunManager::GetMasterRunManager()->GetUserRunAction());
			 G4int tmp = MasterRunAction->GetSemilla();
			 G4cout<<"master seed: "<< tmp << G4endl;
			 G4int TId = G4Threading::G4GetThreadId();
			 G4int tmp2 = tmp*(TId+2);
			 G4Random::setTheSeed(tmp2);
			 break;
		 }
	 }

	G4cout<<"Thread ID is: "<< G4Threading::G4GetThreadId() << G4endl;

	int startSeed = G4Random::getTheSeed();
	G4cout<<"TDM_RunAction::TDM_RunAction Semilla: " << startSeed << G4endl;

	  auto analysisManager = G4AnalysisManager::Instance();
	  G4cout << "Using " << analysisManager->GetType() << G4endl;

	  // Create directories

	  analysisManager->SetVerboseLevel(1);
	  analysisManager->SetNtupleMerging(true);
	    // Note: merging ntuples is available only with Root output

	  G4int TLDNumber = 3; //Número de detectores

	  // Creating ntuple
	  //
	  analysisManager->CreateNtuple("TDM", "Edep and Dodep");
	  for (G4int n = 0;n<TLDNumber;n++){

		 	 G4String N;
		 	 std::stringstream convert;
		 	 convert << n;
		 	 N = convert.str();

		 	 G4String a = N+"AbsoEdep";
		 	 G4String b = N+"AbsoDodep";

	  analysisManager->CreateNtupleDColumn(a);
	  analysisManager->CreateNtupleDColumn(b);
	  }
	  analysisManager->FinishNtuple();
}

TDM_RunAction::~TDM_RunAction()
{
	  delete G4AnalysisManager::Instance();
	 // delete MessengerAction; //Descomentar al activar la opcion de mensaje

}

G4Run* TDM_RunAction::GenerateRun()
{
  return new TDM_Run;
}

void TDM_RunAction::BeginOfRunAction(const G4Run*)
{

	   // Get analysis manager
	  auto analysisManager = G4AnalysisManager::Instance();

	  //Definiendo el tiempo actual de máquina

	  time_t rawtime;
	    struct tm * timeinfo;
	    char buffer [80];

	    time (&rawtime);
	    timeinfo = localtime (&rawtime);

	    strftime (buffer,80,"%Y%m%d%H%M%S",timeinfo);

	    G4String M;
	    std::stringstream convert;
	    convert << buffer;
	    M = convert.str();

	  // Abriendo un archivo de salida
	  //
	  G4String fileName = "TDM-output-" + M;
	  analysisManager->OpenFile(fileName);
}

void TDM_RunAction::EndOfRunAction(const G4Run*)
{

	  auto analysisManager = G4AnalysisManager::Instance();

	  //Guardando y escribiendo la salida en el archivo root
	  analysisManager->Write();
	  analysisManager->CloseFile();
}

void TDM_RunAction::SetSemilla (G4int M){
	TheSeed = M;
	G4cout << "Semilla del archivo: " << M << G4endl;
}
