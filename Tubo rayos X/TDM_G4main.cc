#include "TDM_DetectorConstruction.hh"
#include "TDM_PhysicsList.hh"
#include "TDM_ActionInitialization.hh"

#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "G4UImanager.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
//#include "QBBC.hh"
//#include "G4GeneralParticleSource.hh"

// La la laralala la la la


//
int main(int argc,char** argv) {

  // Run manager
#ifdef G4MULTITHREADED
  auto runManager = new G4MTRunManager;
  runManager->SetNumberOfThreads(3);
#else
  auto runManager = new G4RunManager;
#endif

   G4Random::setTheSeed(1058);

  // UserInitialization classes (mandatory)
  //---
  //  Create Detector
  TDM_DetectorConstruction* detector = new TDM_DetectorConstruction;
  runManager->SetUserInitialization(detector);
  //
  runManager->SetUserInitialization(new TDM_PhysicsList);

  //  runManager->SetUserInitialization(new QBBC);//

  // UserAction classes
  runManager->SetUserInitialization(new TDM_ActionInitialization);

  //Initialize G4 kernel
  runManager->Initialize();

  // Initialize visualization
  //
  //G4VisManager* visManager = new G4VisExecutive;
  // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
  G4VisManager* visManager = new G4VisExecutive("Quiet");
  visManager->Initialize();

  //get the pointer to the User Interface manager
  G4UImanager * pUI = G4UImanager::GetUIpointer();

  if(argc==1)
  // Define (G)UI terminal for interactive mode
  {
     G4UIExecutive* ui = new G4UIExecutive(argc, argv);
     pUI->ApplyCommand("/control/execute vis.mac");
     ui->SessionStart();
     delete ui;
  }
  else
  {
	  G4String command = "/control/execute ";
	  G4String fileName = argv[1];
	  pUI->ApplyCommand(command+fileName);

  }

  delete visManager;
  delete runManager;

  return 0;
}

//

