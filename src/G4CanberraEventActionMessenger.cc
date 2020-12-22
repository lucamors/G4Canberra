#include "G4CanberraEventActionMessenger.hh"
#include "G4CanberraEventAction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithADouble.hh"

G4CanberraEventActionMessenger::G4CanberraEventActionMessenger(G4CanberraEventAction * eventAct)
: G4UImessenger(), fEventAction(eventAct)
{
	// Setting up source directory

	fSourceDir = new G4UIdirectory("/source/");
	fSourceDir->SetGuidance("Source definition commands. ");

	fSourceActivityCmd = new G4UIcmdWithADouble("/source/activity", this);
	fSourceActivityCmd->SetGuidance("Set Source Activity");
	fSourceActivityCmd->SetParameterName("activity", false);
	fSourceActivityCmd->AvailableForStates(G4State_PreInit, G4State_Idle);


}

G4CanberraEventActionMessenger::~G4CanberraEventActionMessenger()
{
	delete fSourceDir;
	delete fSourceActivityCmd;
}

void G4CanberraEventActionMessenger::SetNewValue(G4UIcommand * cmd, G4String newValue)
{
	if(cmd == fSourceActivityCmd)
	{
		fEventAction->SetSourceActivity(std::stod(newValue));
	}

	return ;
}
