#include "G4CanberraEventAction.hh"
#include "G4SDManager.hh"
#include "G4Event.hh"

G4CanberraEventAction::G4CanberraEventAction()
: G4UserEventAction(), fGermaniumHCID(-1)
{
  fAnalysisManager = G4AnalysisManager::Instance();
}

G4CanberraEventAction::~G4CanberraEventAction(){}


G4CanberraGermaniumHitsCollection* G4CanberraEventAction::GetHitsCollection(G4int hcID, const G4Event* event ) const
{

  auto HPGe_hitsCollection = static_cast<G4CanberraGermaniumHitsCollection*>(event->GetHCofThisEvent()->GetHC(hcID));

  if( ! HPGe_hitsCollection )
  {
    G4ExceptionDescription msg;
    msg << "Cannot access hitsCollection ID " << hcID;
    G4Exception("G4CanberraEventAction::GetHitsCollection()", "GermaniumHitCollection", FatalException, msg);
  }

  return HPGe_hitsCollection;
}

void G4CanberraEventAction::BeginOfEventAction(const G4Event* event)
{

  return ;
}

void G4CanberraEventAction::EndOfEventAction(const G4Event* event)
{

  if( fGermaniumHCID == -1)
  {
    fGermaniumHCID = G4SDManager::GetSDMpointer()->GetCollectionID("GermaniumHitsCollection");
  }

  auto germaniumHC = GetHitsCollection(fGermaniumHCID, event);


  G4double event_energy = 0;

  for (size_t i = 0; i < germaniumHC->GetSize(); i++)
  {
    event_energy += (*germaniumHC)[i]->GetEdep();
  }

  if(event_energy <= 0) return ;

  fAnalysisManager->FillNtupleDColumn(0,event_energy);
  fAnalysisManager->AddNtupleRow();


  return ;
}
