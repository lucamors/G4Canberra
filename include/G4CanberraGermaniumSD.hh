#ifndef G4CANBERRA_GERMANIUM_SD
#define G4CANBERRA_GERMANIUM_SD 1

#include "G4VSensitiveDetector.hh"
#include "G4CanberraGermaniumHit.hh"
#include <vector>

class G4Step;
class G4HCofThisEvent;

class G4CanberraGermaniumSD : public G4VSensitiveDetector
{
  public:

    G4CanberraGermaniumSD(const G4String& name,
                               const G4String& hitsCollectionName);

    virtual ~G4CanberraGermaniumSD();

    virtual void   Initialize(G4HCofThisEvent* hitCollection);
    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
    virtual void   EndOfEvent(G4HCofThisEvent* hitCollection);

  private:

    G4CanberraGermaniumHitsCollection* fGermaniumHitsCollection;


};

#endif
