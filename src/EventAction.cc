//
// Created by dboccanfuso on 3/6/26.
//

#include "EventAction.hh"
#include <G4SDManager.hh>
#include "VirtualDetectorSD.hh"
#include "G4AnalysisManager.hh"
#include "G4Event.hh"

void EventAction::BeginOfEventAction(const G4Event *event) {
    fEdepMM1 = 0.;
    fEdepMM2 = 0.;
    fEdepPlastic1 = 0.;
    fEdepPlastic2 = 0.;
    fEdepBox = 0.;
    fEdepPreCalo = 0.;
    fEdepCalo = 0.;
}

void EventAction::EndOfEventAction(const G4Event* event) {

    fEdepPreCalo = fEdepMM1 + fEdepMM2 + fEdepPlastic1 + fEdepPlastic2 + fEdepBox;
    G4SDManager* SDman = G4SDManager::GetSDMpointer();
    auto* hce = event->GetHCofThisEvent();
    if (!hce) return;

    static G4int hcID = -1;
    if (hcID < 0) {
        hcID = SDman->GetCollectionID("VirtualDetector/VirtualDetectorHC");
    }

    auto* hitsCollection = static_cast<VirtualDetectorHitsCollection*>(hce->GetHC(hcID));

    if (!hitsCollection) return;

    // Default values
    G4int vd1_hit = 0, vd2_hit = 0, vd3_hit = 0;

    G4double vd1_x = 0., vd1_y = 0., vd1_z = 0.;
    G4double vd1_px = 0., vd1_py = 0., vd1_pz = 0.;
    G4double vd1_t = 0., vd1_E = 0.;

    G4double vd2_x = 0., vd2_y = 0., vd2_z = 0.;
    G4double vd2_px = 0., vd2_py = 0., vd2_pz = 0.;
    G4double vd2_t = 0., vd2_E = 0.;

    G4double vd3_x = 0., vd3_y = 0., vd3_z = 0.;
    G4double vd3_px = 0., vd3_py = 0., vd3_pz = 0.;
    G4double vd3_t = 0., vd3_E = 0.;

    // Loop over hits
    for (size_t i = 0; i < hitsCollection->entries(); ++i) {
        auto* hit = (*hitsCollection)[i];
        if (!hit) continue;

        G4int detID = hit->GetDetID();

        if (detID == 1 && !vd1_hit) {
            vd1_hit = 1;
            vd1_x = hit->GetPos().x();
            vd1_y = hit->GetPos().y();
            vd1_z = hit->GetPos().z();
            vd1_px = hit->GetMom().x();
            vd1_py = hit->GetMom().y();
            vd1_pz = hit->GetMom().z();
            vd1_t = hit->GetTime();
            vd1_E = hit->GetEnergy();
        }
        else if (detID == 2 && !vd2_hit) {
            vd2_hit = 1;
            vd2_x = hit->GetPos().x();
            vd2_y = hit->GetPos().y();
            vd2_z = hit->GetPos().z();
            vd2_px = hit->GetMom().x();
            vd2_py = hit->GetMom().y();
            vd2_pz = hit->GetMom().z();
            vd2_t = hit->GetTime();
            vd2_E = hit->GetEnergy();
        }
        else if (detID == 3 && !vd3_hit) {
            vd3_hit = 1;
            vd3_x = hit->GetPos().x();
            vd3_y = hit->GetPos().y();
            vd3_z = hit->GetPos().z();
            vd3_px = hit->GetMom().x();
            vd3_py = hit->GetMom().y();
            vd3_pz = hit->GetMom().z();
            vd3_t = hit->GetTime();
            vd3_E = hit->GetEnergy();
        }
    }

    auto* analysisManager = G4AnalysisManager::Instance();
    //information from primaries
    const G4PrimaryVertex* primaryVertex = event->GetPrimaryVertex();
    const G4PrimaryParticle* primaryParticle = primaryVertex->GetPrimary();
    G4ThreeVector primaryVertexPosition = primaryVertex->GetPosition();
    G4double px = primaryParticle->GetPx();
    G4double py = primaryParticle->GetPy();
    G4double pz = primaryParticle->GetPz();
    G4double energy = primaryParticle->GetKineticEnergy();

    analysisManager->FillNtupleDColumn(0 ,primaryVertexPosition.x());
    analysisManager->FillNtupleDColumn(1 ,primaryVertexPosition.y());
    analysisManager->FillNtupleDColumn(2 ,primaryVertexPosition.z());
    analysisManager->FillNtupleDColumn(3 , px);
    analysisManager->FillNtupleDColumn(4 , py);
    analysisManager->FillNtupleDColumn(5 , pz);
    analysisManager->FillNtupleDColumn(6 ,energy);

    // VDet1
    analysisManager->FillNtupleIColumn(7, vd1_hit);
    analysisManager->FillNtupleDColumn(8, vd1_x);
    analysisManager->FillNtupleDColumn(9, vd1_y);
    analysisManager->FillNtupleDColumn(10, vd1_z);
    analysisManager->FillNtupleDColumn(11, vd1_px);
    analysisManager->FillNtupleDColumn(12, vd1_py);
    analysisManager->FillNtupleDColumn(13, vd1_pz);
    analysisManager->FillNtupleDColumn(14, vd1_t);
    analysisManager->FillNtupleDColumn(15, vd1_E);

    // VDet2
    analysisManager->FillNtupleIColumn(16, vd2_hit);
    analysisManager->FillNtupleDColumn(17, vd2_x);
    analysisManager->FillNtupleDColumn(18, vd2_y);
    analysisManager->FillNtupleDColumn(19, vd2_z);
    analysisManager->FillNtupleDColumn(20, vd2_px);
    analysisManager->FillNtupleDColumn(21, vd2_py);
    analysisManager->FillNtupleDColumn(22, vd2_pz);
    analysisManager->FillNtupleDColumn(23, vd2_t);
    analysisManager->FillNtupleDColumn(24, vd2_E);

    // VDet3
    analysisManager->FillNtupleIColumn(25, vd3_hit);
    analysisManager->FillNtupleDColumn(26, vd3_x);
    analysisManager->FillNtupleDColumn(27, vd3_y);
    analysisManager->FillNtupleDColumn(28, vd3_z);
    analysisManager->FillNtupleDColumn(29, vd3_px);
    analysisManager->FillNtupleDColumn(30, vd3_py);
    analysisManager->FillNtupleDColumn(31, vd3_pz);
    analysisManager->FillNtupleDColumn(32, vd3_t);
    analysisManager->FillNtupleDColumn(33, vd3_E);

    //Edep
    analysisManager->FillNtupleDColumn(34, fEdepPlastic1);
    analysisManager->FillNtupleDColumn(35, fEdepMM1);
    analysisManager->FillNtupleDColumn(36, fEdepPlastic2);
    analysisManager->FillNtupleDColumn(37, fEdepMM2);
    analysisManager->FillNtupleDColumn(38, fEdepBox);
    analysisManager->FillNtupleDColumn(39, fEdepPreCalo);
    analysisManager->FillNtupleDColumn(40, fEdepCalo);

    analysisManager->AddNtupleRow();

}