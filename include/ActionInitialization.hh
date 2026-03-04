//
// Created by dboccanfuso on 3/4/26.
//

#ifndef TBMICROMEGAS_ACTIONINITIALIZATION_HH
#define TBMICROMEGAS_ACTIONINITIALIZATION_HH

#include "G4VUserActionInitialization.hh"

class ActionInitialization : public G4VUserActionInitialization
{
public:
    ActionInitialization() = default;
    ~ActionInitialization() override = default;

    void BuildForMaster() const override;
    void Build() const override;
};

#endif //TBMICROMEGAS_ACTIONINITIALIZATION_HH