//
// Created by dboccanfuso on 3/4/26.
//

#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
//#include "EventAction.hh"
//#include "SteppingAction.hh"

void ActionInitialization::BuildForMaster() const
{
    RunAction* runAction = new RunAction;
    SetUserAction(runAction);
}

void ActionInitialization::Build() const
{
    SetUserAction(new PrimaryGeneratorAction);
    RunAction* runAction = new RunAction;
    SetUserAction(runAction);
    //EventAction* eventAction = new EventAction();
    //SetUserAction(eventAction);
}