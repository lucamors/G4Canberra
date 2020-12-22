#include "G4CanberraEventAction.hh"
#include "G4CanberraEventActionMessenger.hh"
#include "G4SDManager.hh"
#include "G4Event.hh"

#include "Randomize.hh"

G4CanberraEventAction::G4CanberraEventAction()
: G4UserEventAction(),fEventID(0), fEventTime(0.0), fGermaniumHCID(-1),fSourceActivity(0.0)
{
  // Retrieve instance of G$AnalysisManager
  fAnalysisManager = G4AnalysisManager::Instance();

  // Retrieve a EventActionMessenger
  fEventMessenger = new G4CanberraEventActionMessenger(this);

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
    // Updating global time by sampling
    // from an exponential distribution
    // with mean 1/Activity
    UpdateGlobalTime();

  return ;
}

void G4CanberraEventAction::EndOfEventAction(const G4Event* event)
{
  // Retrieve event hit collection
  if( fGermaniumHCID == -1)
  {
    fGermaniumHCID = G4SDManager::GetSDMpointer()->GetCollectionID("GermaniumHitsCollection");
  }

  auto germaniumHC = GetHitsCollection(fGermaniumHCID, event);

  // Saving hit collection to ROOT TTree
  G4double hit_energy, hit_time;

  for (size_t i = 0; i < germaniumHC->GetSize(); i++)
  {
    hit_energy = (*germaniumHC)[i]->GetEdep();
    hit_time   = (*germaniumHC)[i]->GetTime();

    fAnalysisManager->FillNtupleDColumn(0,0,fEventID);
    fAnalysisManager->FillNtupleDColumn(0,1,hit_energy);
    fAnalysisManager->FillNtupleDColumn(0,2,hit_time+fEventTime);
    // std::cout << "fTime : " << fEventTime << std::endl;
    // std::cout << "hit time : " << hit_time << std::endl;
    // std::cout << "hit time + EventTime : " << hit_time+fEventTime << std::endl;
    fAnalysisManager->AddNtupleRow(0);

  }

  // Saving Source time distribution
  fAnalysisManager->FillNtupleDColumn(1,0, fEventTime);
  fAnalysisManager->AddNtupleRow(1);

  // Updating Event counter
  fEventID += 1;

  return ;
}

void G4CanberraEventAction::UpdateGlobalTime()
{

  G4double holdup = G4RandExponential::shoot(1.0/fSourceActivity)/CLHEP::picosecond;
  fEventTime += holdup;

  return ;
}

G4double G4CanberraEventAction::GetEventTime(){ return fEventTime; }

void G4CanberraEventAction::SetSourceActivity(G4double act)
{
  fSourceActivity = act;

  return ;
}

G4double G4CanberraEventAction::GetSourceActivity(){ return fSourceActivity; }
