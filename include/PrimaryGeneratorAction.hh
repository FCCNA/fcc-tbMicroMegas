//
// Created by dboccanfuso on 3/4/26.
//

#ifndef TBMICROMEGAS_PRIMARYGENERATORACTION_HH
#define TBMICROMEGAS_PRIMARYGENERATORACTION_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"

class G4Event;
class G4GeneralParticleSource;


class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  PrimaryGeneratorAction();
  ~PrimaryGeneratorAction() override;

  void GeneratePrimaries(G4Event* event) override;

private:
  G4GeneralParticleSource* fGPS;

  G4String fParticleType = "e+";
  G4double fEnergy = 5.0*GeV;
};


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif //TBMICROMEGAS_PRIMARYGENERATORACTION_HH