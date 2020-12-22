#include "G4CanberraPrimaryGeneratorMessenger.hh"
#include "G4CanberraPrimaryGeneratorAction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"

#include <string>

G4CanberraPrimaryGeneratorMessenger::G4CanberraPrimaryGeneratorMessenger(G4CanberraPrimaryGeneratorAction* gun)
: G4UImessenger(), fPrimaryGenerator(gun)
{
	// Setting Source directory
	fSourceDir = new G4UIdirectory("/source/");
	fSourceDir->SetGuidance("Source Definition Commands");

	fSourceAddIsotopeCmd = new G4UIcmdWithAString("/source/add", this);
	fSourceAddIsotopeCmd->SetGuidance("Add an isotope to the source");
	fSourceAddIsotopeCmd->SetParameterName("<A> <Z> <Q> <LVL> <amount>",false);
	fSourceAddIsotopeCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
}

G4CanberraPrimaryGeneratorMessenger::~G4CanberraPrimaryGeneratorMessenger()
{
	delete fSourceAddIsotopeCmd;
	delete fSourceDir;
}

void G4CanberraPrimaryGeneratorMessenger::SetNewValue(G4UIcommand* cmd, G4String newValue)
{
	if(cmd == fSourceAddIsotopeCmd)
	{
		std::stringstream commandStream(newValue);
		std::string entry;

		G4int A,Z,Q,LVL;
		G4double amount;

		// Getting atomic mass <A>
		getline(commandStream, entry, ' ');
		A = std::stoi(entry);

		// Getting atomic charge <Z>
		getline(commandStream, entry, ' ');
		Z = std::stoi(entry);

		// Getting isotope charge <Q>
		getline(commandStream, entry, ' ');
		Q = std::stoi(entry);

		// Getting Isotope lvl or exc ene <LVL>
		getline(commandStream, entry, ' ');
		LVL = std::stoi(entry);

		// Getting total amount <amount>
		getline(commandStream, entry, ' ');
		amount = std::stod(entry);

		// Add isotope to isotope list
		fPrimaryGenerator->AddIsotope(A,Z,Q,LVL,amount);
	}

	return ;
}
