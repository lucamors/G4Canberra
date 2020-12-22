#include "G4CanberraGermaniumSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

G4CanberraGermaniumSD::G4CanberraGermaniumSD(
  const G4String& name,
  const G4String& hitsCollectionName
)
:
G4VSensitiveDetector(name),
fGermaniumHitsCollection(nullptr)
{
  collectionName.insert(hitsCollectionName);
}

G4CanberraGermaniumSD::~G4CanberraGermaniumSD(){}


void G4CanberraGermaniumSD::Initialize(G4HCofThisEvent* hcHPGe)
{
  // Create the Hit Collection
  fGermaniumHitsCollection = new G4CanberraGermaniumHitsCollection(SensitiveDetectorName, collectionName[0]);
  auto hcID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);

  hcHPGe->AddHitsCollection(hcID, fGermaniumHitsCollection);
}

G4bool G4CanberraGermaniumSD::ProcessHits(G4Step* step, G4TouchableHistory* )
{
  // Creating a G4VHit object
  G4CanberraGermaniumHit * hit = new G4CanberraGermaniumHit();

  // Retrieve Deposited Energy inside active volume
  G4double edep = step->GetTotalEnergyDeposit()/CLHEP::keV;
  // Retrieve Hit Time relative to the beginning of the current event
  G4double time = step->GetTrack()->GetGlobalTime()/CLHEP::picosecond;

  hit->SetEdep(edep);
  hit->SetTime(time);
  fGermaniumHitsCollection->insert(hit);

  return true;
}

void G4CanberraGermaniumSD::EndOfEvent(G4HCofThisEvent*)
{
  return ;
}
