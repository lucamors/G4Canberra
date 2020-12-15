/*
  G4CANBERRA
  ------------------------------------------------------------------------------

  Geant4 Application for ReGe Detector.

  Author: Luca Morselli

*/

// Geant4 Includes
#include "G4RunManager.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"
#include "G4UImanager.hh"

// User Defined Action and Initialization Classes
#include "G4CanberraDetectorConstruction.hh"
#include "G4CanberraPhysicsList.hh"
#include "G4CanberraPrimaryGeneratorAction.hh"
#include "G4CanberraEventAction.hh"
#include "G4CanberraRunAction.hh"

#include "G4PhysListFactory.hh"

#include "Randomize.hh"


#include <random>
#include <ctime>
#include <chrono>

int main(int argc, char** argv)
{
  // Detect interactive mode and define UI session
  G4UIExecutive * ui = 0;
  if(argc == 1)
  {
    ui = new G4UIExecutive(argc, argv);
  }

  // Choose the random engine
  G4Random::setTheEngine(new CLHEP::RanecuEngine);
  // Initialize SEED using current time since epoch
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  // Set HepRandom with time dependent seed --> Needed for Cloud Parallelization
  CLHEP::HepRandom::setTheSeed(seed);
  G4Random::setTheSeed(seed);

  // Construct the run manager
  G4RunManager * runManager = new G4RunManager;

  // Set Mandatory initialization classes
  // ---------------------------------------------------------------------------
  G4CanberraDetectorConstruction * det   = new G4CanberraDetectorConstruction();

  // User Defined Physics List
  G4PhysListFactory factory;
  G4CanberraPhysicsList * phys = new G4CanberraPhysicsList();
  phys->SetVerboseLevel(0);

  runManager->SetUserInitialization(det);
  runManager->SetUserInitialization(phys);

  // Set Mandatory action classes
  // ---------------------------------------------------------------------------
  G4CanberraPrimaryGeneratorAction * kin   = new G4CanberraPrimaryGeneratorAction();
  G4CanberraRunAction              * run   = new G4CanberraRunAction();
  G4CanberraEventAction            * event = new G4CanberraEventAction();

  runManager->SetUserAction(kin);
  runManager->SetUserAction(run);
  runManager->SetUserAction(event);

  // Initialize visualization
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();

  // get the pointer to the User Interface Manager
  G4UImanager * uiManager = G4UImanager::GetUIpointer();

  if(!ui)
  {
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    uiManager->ApplyCommand(command+fileName);
  }
  else
  {
    uiManager->ApplyCommand("/control/execute macro/vis.mac");
    ui->SessionStart();
    delete ui;
  }

  // Terminate application
  // All user action and initialization classes are freed by the runManager
  // so they should not be deleted in the main() program
  delete visManager;
  delete runManager;

  return 0;
}
