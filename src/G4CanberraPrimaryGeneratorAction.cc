#include "G4CanberraPrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"

#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"

#include "G4ThreeVector.hh"

#include<random>
#include<cmath>
#include<chrono>

G4CanberraPrimaryGeneratorAction::G4CanberraPrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
fParticleGun(nullptr)
{
  G4int nofParticles = 1;
  fParticleGun = new G4ParticleGun(nofParticles);

  G4ParticleDefinition* gamma = G4ParticleTable::GetParticleTable()->FindParticle("gamma");
  fParticleGun->SetParticleDefinition(gamma);
  fParticleGun->SetParticleEnergy(511.0*CLHEP::keV);

  // Defining source-detector distance

}

G4CanberraPrimaryGeneratorAction::~G4CanberraPrimaryGeneratorAction()
{
  delete fParticleGun;
}

void G4CanberraPrimaryGeneratorAction::GeneratePrimaries(G4Event * event)
{
  // Sample a direction on the unit sphere
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::mt19937 generator (seed);
  std::uniform_real_distribution<double> uniform(0.0, 1.0);
  double theta = 2 * M_PI * uniform(generator);
  double phi = acos(1 - 2 * uniform(generator));
  double x = sin(phi) * cos(theta);
  double y = sin(phi) * sin(theta);
  double z = cos(phi);

  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(x,y,z));

  // Set Beam Origin
  fParticleGun->SetParticlePosition(G4ThreeVector(-10*cm,0,0*cm));

  // Generate primary vertex
  fParticleGun->GeneratePrimaryVertex(event);

}
