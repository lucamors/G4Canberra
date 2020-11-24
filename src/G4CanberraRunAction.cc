#include "G4CanberraRunAction.hh"


G4CanberraRunAction::G4CanberraRunAction()
: G4UserRunAction()
{
  fAnalysisManager = G4AnalysisManager::Instance();
  G4cout<< "Using " << fAnalysisManager->GetType() << G4endl;

  fAnalysisManager->SetVerboseLevel(1);
  fAnalysisManager->SetNtupleMerging(true);

  fAnalysisManager->CreateNtuple("hpge_edep", "HPGe Response Function");
  fAnalysisManager->CreateNtupleDColumn("edep");
  fAnalysisManager->FinishNtuple();

}

G4CanberraRunAction::~G4CanberraRunAction()
{
  delete G4AnalysisManager::Instance();
}

void G4CanberraRunAction::BeginOfRunAction(const G4Run*)
{
    fAnalysisManager->OpenFile();
}

void G4CanberraRunAction::EndOfRunAction(const G4Run*)
{

  fAnalysisManager->Write();
  fAnalysisManager->CloseFile();
}
