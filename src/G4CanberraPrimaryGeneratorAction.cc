#include "G4CanberraPrimaryGeneratorAction.hh"
#include "G4CanberraPrimaryGeneratorMessenger.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Event.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4IonTable.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4CanberraDetectorConstruction.hh"
#include <vector>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4CanberraPrimaryGeneratorAction::G4CanberraPrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(), fTotalNumberOfNuclides(0.)
{
	// Creating particle gun
	G4int numberOfParticlePerEvent = 1;
	fParticleGun = new G4ParticleGun(numberOfParticlePerEvent);

	// create commands for interactive definition of the beam type
	fPrimaryMessenger = new G4CanberraPrimaryGeneratorMessenger(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4CanberraPrimaryGeneratorAction::~G4CanberraPrimaryGeneratorAction()
{
  delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void G4CanberraPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
	// Sample Ion species from tables
	SampleFromIsotopeList();

    // Place source at the origin
	fParticleGun->SetParticlePosition(G4ThreeVector(0,0,0*cm));

	// Generate the event
	fParticleGun->GeneratePrimaryVertex(anEvent);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void G4CanberraPrimaryGeneratorAction::SampleFromIsotopeList()
{
	G4ParticleDefinition* ion;
	G4int                 charge;

	// Sampling an Ion
	G4double rnd_choice = G4RandFlat::shoot() * fTotalNumberOfNuclides;

	for (size_t i = 0; i < fIsotopesList.size(); ++i)
	{
		if(rnd_choice < fCumulativeDistribution[i])
		{
			ion = G4IonTable::GetIonTable()->GetIon(fIsotopesList[i].Z,
												   fIsotopesList[i].A,
												   fIsotopesList[i].LVL*CLHEP::keV);
			charge = fIsotopesList[i].Q*eplus;

			break;
		}
	}

	fParticleGun->SetParticleDefinition(ion);
	fParticleGun->SetParticleCharge(charge);

    // Debug
	// G4cout << fParticleGun->GetParticleDefinition()->GetParticleName() << "\t"
	// 	   << fParticleGun->GetParticleDefinition()->GetPDGLifeTime()*0.697	<< G4endl;

	return ;
}

void G4CanberraPrimaryGeneratorAction::AddIsotope(G4int A,
										G4int Z,
										G4int Q,
										G4double LVL,
										G4double amount)
{

	Isotope newIsotope = {A, Z, Q, LVL, amount};

	fIsotopesList.push_back(newIsotope);

	return ;
}

void G4CanberraPrimaryGeneratorAction::InitializeSource()
{
	// Initialize Isotopes cumulative distribution to sample from
	fCumulativeDistribution.reserve(fIsotopesList.size());


	for(size_t i = 0; i < fIsotopesList.size(); i++)
	{
		fTotalNumberOfNuclides += fIsotopesList[i].amount;
		fCumulativeDistribution[i] = fTotalNumberOfNuclides;
	}

	// All isotope are at rest
	fParticleGun->SetParticleEnergy(0);

	return;
}
