#include "G4CanberraGermaniumHit.hh"
#include "G4UnitsTable.hh"
#include "G4VisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include <iomanip>

G4ThreadLocal G4Allocator<G4CanberraGermaniumHit>* GermaniumHitAllocator = 0;

G4CanberraGermaniumHit::G4CanberraGermaniumHit()
: G4VHit(){}

G4CanberraGermaniumHit::~G4CanberraGermaniumHit(){}

G4CanberraGermaniumHit::G4CanberraGermaniumHit(const G4CanberraGermaniumHit& right)
: G4VHit()
{
  fEdep = right.fEdep;
}

const G4CanberraGermaniumHit& G4CanberraGermaniumHit::operator=(const G4CanberraGermaniumHit& right)
{
  fEdep = right.fEdep;
  return *this;
}
G4bool G4CanberraGermaniumHit::operator==(const G4CanberraGermaniumHit& right) const
{
  return (this == &right) ? true : false;
}

void G4CanberraGermaniumHit::SetEdep(G4double edep)
{

  fEdep = edep;
  return ;
}

void G4CanberraGermaniumHit::SetTime(G4double time)
{
	fTime = time;

	return ;
}
