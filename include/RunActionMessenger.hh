//
// Created by dboccanfuso on 3/9/26.
//

#ifndef TBMICROMEGAS_RUNACTIONMESSENGER_HH
#define TBMICROMEGAS_RUNACTIONMESSENGER_HH

#include "globals.hh"
#include "G4UImessenger.hh"

class RunAction;
class G4UIcmdWithAString;

class RunActionMessenger : public G4UImessenger {
public:
    RunActionMessenger(RunAction*);
    ~RunActionMessenger();

    void SetNewValue(G4UIcommand*, G4String);

private:
    RunAction* fRunAction{nullptr};
    G4UIcmdWithAString* fSetFileNameCmd{nullptr};
};


#endif //TBMICROMEGAS_RUNACTIONMESSENGER_HH