#ifndef G4CANBERRA_PRIMARY_ACTION_GENERATOR_h
#define G4CANBERRA_PRIMARY_ACTION_GENERATOR_h 1

#include <vector>

#include "globals.hh"
#include "Analysis.hh"
#include "G4ParticleGun.hh"
#include "G4PhysicalConstants.hh"
#include "G4VUserPrimaryGeneratorAction.hh"

struct Isotope
{
  G4int A;
  G4int Z;
  G4int Q;

  G4double LVL;
  G4double amount;

};

class G4CanberraPrimaryGeneratorMessenger;
class G4ParticleGun;
class G4Event;

class G4CanberraPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:

    G4CanberraPrimaryGeneratorAction();
    virtual ~G4CanberraPrimaryGeneratorAction();

    // method from the base class
    void GeneratePrimaries(G4Event*);

    // method to access particle gun
    G4ParticleGun* GetGeneralGun() { return fParticleGun; }

    void InitializeSource();
    void SampleFromIsotopeList();

    void AddIsotope(G4int, G4int, G4int, G4double, G4double );

  private:

    G4CanberraPrimaryGeneratorMessenger* fPrimaryMessenger;

    G4ParticleGun*  fParticleGun;
    G4String        fSourceName;

    std::vector<Isotope> fIsotopesList;
    std::vector<G4double>   fCumulativeDistribution;

    G4double fTotalNumberOfNuclides;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
