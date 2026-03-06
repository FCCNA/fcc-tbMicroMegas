//
// Created by dboccanfuso on 3/6/26.
//

#include "SteppingAction.hh"
#include "EventAction.hh"

#include "G4Step.hh"
#include "G4TouchableHandle.hh"
#include "G4VPhysicalVolume.hh"
#include "G4SystemOfUnits.hh"

SteppingAction::SteppingAction(EventAction* eventAction)
: fEventAction(eventAction)
{}

SteppingAction::~SteppingAction() = default;

void SteppingAction::UserSteppingAction(const G4Step* step)
{
    if(!step) return;

    G4double edep = step->GetTotalEnergyDeposit();

    auto touchable = step->GetPreStepPoint()->GetTouchableHandle();
    if(!touchable) return;

    auto volume = touchable->GetVolume();
    if(!volume) return;

    G4String volName = volume->GetName();

    if(edep > 0.)
    {
        //Micromegas (look in geometry hierarchy)
        for(int i=0; i<=touchable->GetHistoryDepth(); i++)
        {
            auto mother = touchable->GetVolume(i);
            if(!mother) continue;

            G4String name = mother->GetName();
            if(name == "MicroMegas1Phys")
            {
                fEventAction->AddEdepMM1(edep);
                break;
            }
            if(name == "MicroMegas2Phys")
            {
                fEventAction->AddEdepMM2(edep);
                break;
            }
        }

        //Plastic scintillators
        if(volName == "Plastic1Phys")
        {
            fEventAction->AddEdepPlastic1(edep);
        }
        else if(volName == "Plastic2Phys")
        {
            fEventAction->AddEdepPlastic2(edep);
        }

        // ---- Calorimeter (any cell)
        else if(volName.contains("CellPV"))
        {
            fEventAction->AddEdepCalo(edep);
        }
    }
}