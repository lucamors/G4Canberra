#ifndef G4ISOLPHARMIRIS_EVENT_ACTION_h
#define G4ISOLPHARMIRIS_EVENT_ACTION_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "G4CanberraGermaniumHit.hh"
#include "Analysis.hh"

class G4CanberraEventActionMessenger;

class G4CanberraEventAction : public G4UserEventAction
{
  public:

    G4CanberraEventAction();
    virtual ~G4CanberraEventAction();

    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);

    void UpdateGlobalTime();
    void SetSourceActivity(G4double );

    G4double GetSourceActivity();

    G4double GetEventTime();

  private:

    G4CanberraGermaniumHitsCollection* GetHitsCollection(G4int hcID, const G4Event* event) const;


    G4int    fEventID;
    G4double fEventTime;
    G4int    fGermaniumHCID;
    G4double fSourceActivity;

    G4AnalysisManager              * fAnalysisManager;
    G4CanberraEventActionMessenger * fEventMessenger;

};

#endif
