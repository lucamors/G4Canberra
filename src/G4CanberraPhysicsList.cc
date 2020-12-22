#include "G4NuclideTable.hh"
#include "G4DecayPhysics.hh"
#include "G4CanberraPhysicsList.hh"
#include "G4EmLivermorePhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"

G4CanberraPhysicsList::G4CanberraPhysicsList()
: G4VUserPhysicsList()
{
	// Set verbosity level
	SetVerboseLevel(2);

	// Default physics
	RegisterPhysics(new G4DecayPhysics());

	// Radioactive Decay Physics
	RegisterPhysics(new G4RadioactiveDecayPhysics());

	// EM physics
	RegisterPhysics(new G4EmLivermorePhysics());

}

G4CanberraPhysicsList::~G4CanberraPhysicsList()
{}

void G4CanberraPhysicsList::SetCuts()
{ return ; }
