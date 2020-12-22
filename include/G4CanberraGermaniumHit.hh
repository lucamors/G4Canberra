#ifndef G4CANBERRA_GERMANIUM_HITS_COLLECTION
#define G4CANBERRA_GERMANIUM_HITS_COLLECTION 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4Threading.hh"

class G4CanberraGermaniumHit : public G4VHit
{
  public:

    G4CanberraGermaniumHit();
    G4CanberraGermaniumHit(const G4CanberraGermaniumHit& );

    virtual ~G4CanberraGermaniumHit();

    // Operators
    const G4CanberraGermaniumHit& operator=(const G4CanberraGermaniumHit&);
    G4bool operator==(const G4CanberraGermaniumHit&) const;
    inline void * operator new(size_t);
    inline void   operator delete(void *);

    // Methods from base class
    virtual void Draw(){}

    // User Hit Interface
    void     SetEdep(G4double );
    void     SetTime(G4double );
    G4double GetEdep(){ return fEdep; }
    G4double GetTime(){ return fTime; }

  private:

    G4double fEdep;
    G4double fTime;

};

using G4CanberraGermaniumHitsCollection = G4THitsCollection<G4CanberraGermaniumHit>;
extern G4ThreadLocal G4Allocator<G4CanberraGermaniumHit>* GermaniumHitAllocator;

inline void* G4CanberraGermaniumHit::operator new(size_t)
{

  if(!GermaniumHitAllocator)
  {
    GermaniumHitAllocator = new G4Allocator<G4CanberraGermaniumHit>;
  }

  void *hit;

  hit = (void*) GermaniumHitAllocator->MallocSingle();

  return hit;
}

inline void G4CanberraGermaniumHit::operator delete(void * hit)
{
  if(!GermaniumHitAllocator)
  {
    GermaniumHitAllocator = new G4Allocator<G4CanberraGermaniumHit>;
  }

  GermaniumHitAllocator->FreeSingle((G4CanberraGermaniumHit*)hit);

  return ;
}

#endif
