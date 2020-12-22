#ifndef G4CANBERRA_RUN_ACTION_h
#define G4CANBERRA_RUN_ACTION_h 1

#include "G4UserRunAction.hh"
#include "G4Accumulable.hh"
#include "globals.hh"
#include "Analysis.hh"

class G4Run;
class G4CanberraPrimaryGeneratorAction;
class G4CanberraPhysicsList;

class G4CanberraRunAction : public G4UserRunAction
{
  public:

    G4CanberraRunAction();
    G4CanberraRunAction(G4CanberraPhysicsList*, G4CanberraPrimaryGeneratorAction*);
    virtual ~G4CanberraRunAction();

    virtual void BeginOfRunAction(const G4Run *);
    virtual void EndOfRunAction(const G4Run *);

  private:

    G4AnalysisManager                * fAnalysisManager;
    G4CanberraPrimaryGeneratorAction * fBeam;
    G4CanberraPhysicsList            * fPhysics;
};

#endif
