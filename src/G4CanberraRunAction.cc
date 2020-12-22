#include "G4CanberraRunAction.hh"
#include "G4CanberraPhysicsList.hh"
#include "G4CanberraPrimaryGeneratorAction.hh"

G4CanberraRunAction::G4CanberraRunAction(G4CanberraPhysicsList* phys, G4CanberraPrimaryGeneratorAction* beam)
: G4UserRunAction(), fBeam(beam), fPhysics(phys)
{
  fAnalysisManager = G4AnalysisManager::Instance();
  G4cout<< "Using " << fAnalysisManager->GetType() << G4endl;

    fAnalysisManager->SetVerboseLevel(1);
    fAnalysisManager->SetNtupleMerging(true);


    fAnalysisManager->CreateNtuple("hpge_hl", "HpGe Hits List");

    fAnalysisManager->CreateNtupleDColumn("id");
    fAnalysisManager->CreateNtupleDColumn("edep");
    fAnalysisManager->CreateNtupleDColumn("time");
    fAnalysisManager->FinishNtuple();

    fAnalysisManager->CreateNtuple("source_time", "Source event time distribution.");

    fAnalysisManager->CreateNtupleDColumn("time");
    fAnalysisManager->FinishNtuple();

}

G4CanberraRunAction::~G4CanberraRunAction()
{
  delete G4AnalysisManager::Instance();
}

void G4CanberraRunAction::BeginOfRunAction(const G4Run*)
{
    // Open output file
    fAnalysisManager->OpenFile();

    // Initialize Source
   fBeam->InitializeSource();
}

void G4CanberraRunAction::EndOfRunAction(const G4Run*)
{

  fAnalysisManager->Write();
  fAnalysisManager->CloseFile();
}
