#ifndef G4CANBERRA_PRIMARY_GENERATOR_ACTION_H
#define G4CANBERRA_PRIMARY_GENERATOR_ACTION_H

#include "globals.hh"
#include "G4UImessenger.hh"

class G4UIdirectory;
class G4UIcmdWithAString;
class G4CanberraPrimaryGeneratorAction;

class G4CanberraPrimaryGeneratorMessenger : G4UImessenger
{
	public:

		G4CanberraPrimaryGeneratorMessenger(G4CanberraPrimaryGeneratorAction* );
		virtual ~G4CanberraPrimaryGeneratorMessenger();

		virtual void SetNewValue(G4UIcommand*, G4String);

	private:

		G4CanberraPrimaryGeneratorAction* fPrimaryGenerator;

		G4UIdirectory      *fSourceDir;
		G4UIcmdWithAString *fSourceAddIsotopeCmd;
};

#endif
