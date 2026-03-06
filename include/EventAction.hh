//
// Created by dboccanfuso on 3/6/26.
//

#ifndef TBMICROMEGAS_EVENTACTION_HH
#define TBMICROMEGAS_EVENTACTION_HH

#include "G4UserEventAction.hh"
#include "G4ThreeVector.hh"

class EventAction : public G4UserEventAction
{
public:
    EventAction() = default;
    ~EventAction() override = default;

    void BeginOfEventAction(const G4Event* event) override;
    void EndOfEventAction(const G4Event* event) override;

    void AddEdepMM1(G4double e)      { fEdepMM1 += e; }
    void AddEdepMM2(G4double e)      { fEdepMM2 += e; }

    void AddEdepPlastic1(G4double e) { fEdepPlastic1 += e; }
    void AddEdepPlastic2(G4double e) { fEdepPlastic2 += e; }

    void AddEdepCalo(G4double e)     { fEdepCalo += e; }

private:

    G4double fEdepMM1 = 0.;
    G4double fEdepMM2 = 0.;

    G4double fEdepPlastic1 = 0.;
    G4double fEdepPlastic2 = 0.;

    G4double fEdepCalo = 0.;
};

#endif //TBMICROMEGAS_EVENTACTION_HH

