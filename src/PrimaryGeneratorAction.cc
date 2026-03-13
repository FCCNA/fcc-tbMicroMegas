//
// Created by dboccanfuso on 3/4/26.
//

#include "PrimaryGeneratorAction.hh"

#include <G4ParticleTable.hh>
#include "G4GeneralParticleSource.hh"
#include "G4SystemOfUnits.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction() {
    //fMessenger = new PrimaryGeneratorActionMessenger();
    fGPS = new G4GeneralParticleSource();

    G4ParticleDefinition* particle = G4ParticleTable::GetParticleTable()->FindParticle(fParticleType);
    fGPS->SetParticleDefinition(particle);
    //Position of the source
    G4SPSPosDistribution* vPosDist = fGPS->GetCurrentSource()->GetPosDist();
    vPosDist->SetPosDisType("Plane");
    vPosDist->SetPosDisShape("Circle");
    vPosDist->SetRadius(0.25*cm);
    vPosDist->SetCentreCoords(G4ThreeVector(0.0, 0.0, -50.0*cm));
    //angular distribution
    G4SPSAngDistribution* vAngDist = fGPS->GetCurrentSource()->GetAngDist();
    vAngDist->SetParticleMomentumDirection(G4ThreeVector(0.0, 0.0, 1.));
    //energy distribution
    G4SPSEneDistribution* vEneDist = fGPS->GetCurrentSource()->GetEneDist();
    vEneDist->SetEnergyDisType("Mono");
    vEneDist->SetMonoEnergy(fEnergy);

}

PrimaryGeneratorAction::~PrimaryGeneratorAction() {
    delete fGPS;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {
    fGPS->GeneratePrimaryVertex(anEvent);
    /*
    auto particle = anEvent->GetPrimaryVertex(0)
                    ->GetPrimary(0)
                    ->GetParticleDefinition();

    G4cout << particle->GetParticleName() << G4endl;
    */
}
