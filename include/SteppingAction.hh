//
// Created by dboccanfuso on 3/6/26.
//

#ifndef TBMICROMEGAS_STEPPINGACTION_HH
#define TBMICROMEGAS_STEPPINGACTION_HH

#include <G4Step.hh>
#include <G4UserSteppingAction.hh>
#include "EventAction.hh"


class SteppingAction : public G4UserSteppingAction{
public:
    SteppingAction(EventAction* eventAction);
    ~SteppingAction();

    void UserSteppingAction(const G4Step* step);
private:
    EventAction* fEventAction{nullptr};
};


#endif //TBMICROMEGAS_STEPPINGACTION_HH