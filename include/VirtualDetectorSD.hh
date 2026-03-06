//
// Created by dboccanfuso on 3/6/26.
//

#ifndef TBMICROMEGAS_VIRTUALDETECTORSD_HH
#define TBMICROMEGAS_VIRTUALDETECTORSD_HH

#include "VirtualDetectorHit.hh"
#include "G4VSensitiveDetector.hh"

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

/// VirtualDetector class.

class VirtualDetector : public G4VSensitiveDetector
{
public:
    VirtualDetector(G4String);
    ~VirtualDetector() override;
    
    void Initialize(G4HCofThisEvent*) override;
    G4bool ProcessHits(G4Step*,G4TouchableHistory*) override;
    void EndOfEvent(G4HCofThisEvent*) override;
       
private:
    VirtualDetectorHitsCollection* fHitsCollection{nullptr};
    G4int fHCID = -1;
};

#endif //TBMICROMEGAS_VIRTUALDETECTORSD_HH