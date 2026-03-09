//
// Created by dboccanfuso on 3/4/26.
//

#ifndef TBMICROMEGAS_RUNACTION_HH
#define TBMICROMEGAS_RUNACTION_HH


#include "G4UserRunAction.hh"
#include "globals.hh"

#include "EventAction.hh"
#include "G4SystemOfUnits.hh"

class G4Run;
class G4GenericMessenger;
class EventAction;

class RunAction : public G4UserRunAction
{
public:
    RunAction();
    ~RunAction() override = default;
    void BeginOfRunAction(const G4Run*);
    void EndOfRunAction(const G4Run*);
};


#endif //TBMICROMEGAS_RUNACTION_HH