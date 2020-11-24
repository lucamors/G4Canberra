#ifndef G4CANBERRA_PRIMARY_ACTION_GENERATOR_h
#define G4CANBERRA_PRIMARY_ACTION_GENERATOR_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4SystemOfUnits.hh"

class G4Event;
class G4ParticleGun;

class G4CanberraPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:

    G4CanberraPrimaryGeneratorAction();
    virtual ~G4CanberraPrimaryGeneratorAction();

    virtual void GeneratePrimaries(G4Event* event);

    G4ParticleGun* GetParticleGun(){ return fParticleGun; }

    // User Command If requested
    // Activate 1 source, 2 sources etc etc

  private:

    G4ParticleGun * fParticleGun;
    double          fSourceDetectorDistance;

};

#endif
