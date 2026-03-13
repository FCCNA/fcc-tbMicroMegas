//
// Created by dboccanfuso on 3/9/26.
//

#include "RunActionMessenger.hh"
#include "RunAction.hh"
#include "G4UIcmdWithAString.hh"

RunActionMessenger::RunActionMessenger(RunAction* runaction) : G4UImessenger()
{
    fRunAction = runaction;
    
    fSetFileNameCmd = new G4UIcmdWithAString("/run/setfilenamesave",this);
    fSetFileNameCmd->SetGuidance("Set File Name Save");
    fSetFileNameCmd->SetParameterName("SetFileNameSave",false);
    fSetFileNameCmd->SetDefaultValue("output");
}

RunActionMessenger::~RunActionMessenger() {delete fSetFileNameCmd;}

void RunActionMessenger::SetNewValue(G4UIcommand* command,G4String newValue) 
{
    if (command == fSetFileNameCmd) {
        fRunAction->SetFileName(newValue);
    }
}