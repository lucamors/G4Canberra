#ifndef G4CANBERRA_PHYSICS_LIST_H
#define G4CANBERRA_PHYSICS_LIST_H 1

#include "G4VModularPhysicsList.hh"

class G4CanberraPhysicsList: public G4VModularPhysicsList
{

  public:

    G4CanberraPhysicsList();
    virtual ~G4CanberraPhysicsList();

    virtual void SetCuts();
};

#endif
