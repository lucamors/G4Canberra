#ifndef G4CANBERRA_EVENT_ACTION_MESSENGER_h
#define G4CANBERRA_EVENT_ACTION_MESSENGER_h

#include "globals.hh"
#include "G4UImessenger.hh"

class G4UIdirectory;
class G4UIcmdWithADouble;
class G4CanberraEventAction;

class G4CanberraEventActionMessenger : G4UImessenger
{
	public:

		G4CanberraEventActionMessenger(G4CanberraEventAction* );
		virtual ~G4CanberraEventActionMessenger();

		virtual void SetNewValue(G4UIcommand* , G4String );

	private:

		G4CanberraEventAction        * fEventAction;

		G4UIdirectory      * fSourceDir;
		G4UIcmdWithADouble * fSourceActivityCmd;

};


#endif
