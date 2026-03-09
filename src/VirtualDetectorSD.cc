//
// Created by dboccanfuso on 3/6/26.
//

#include "VirtualDetectorSD.hh"
#include "VirtualDetectorHit.hh"

#include "G4HCofThisEvent.hh"
#include "G4TouchableHistory.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include "G4Track.hh"

VirtualDetector::VirtualDetector(G4String name) : G4VSensitiveDetector(name) {
    collectionName.insert("VirtualDetectorHC");
}

VirtualDetector::~VirtualDetector() {}

void VirtualDetector::Initialize(G4HCofThisEvent* HCE) {
    fHitsCollection = new VirtualDetectorHitsCollection(SensitiveDetectorName, collectionName.at(0));
    if (fHCID < 0) {
        fHCID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
    }
    HCE->AddHitsCollection(fHCID, fHitsCollection);
}

G4bool VirtualDetector::ProcessHits(G4Step* aStep, G4TouchableHistory*) {
    G4Track* aTrack = aStep->GetTrack();
    G4StepPoint* preStepPoint = aStep->GetPreStepPoint();
    if (!(preStepPoint->GetStepStatus() == fGeomBoundary)) {return true;}
    if (!(aTrack->GetParentID() == 0)) {return true;}

    G4int detectorID = preStepPoint->GetTouchableHandle()->GetVolume()->GetCopyNo() +1; //copy number start from 0 and vdet id from 1

    G4int trackID = aTrack->GetTrackID();
    G4double time = preStepPoint->GetGlobalTime();
    G4ThreeVector position = preStepPoint->GetPosition();
    G4ThreeVector momentum = preStepPoint->GetMomentum();
    G4double energy = preStepPoint->GetKineticEnergy();

    VirtualDetectorHit* aHit = new VirtualDetectorHit();
    aHit->SetTrackID(trackID);
    aHit->SetTime(time);
    aHit->SetPos(position);
    aHit->SetMom(momentum);
    aHit->SetEnergy(energy);
    aHit->SetDetID(detectorID);

    fHitsCollection->insert(aHit);
    return true;
}

void VirtualDetector::EndOfEvent(G4HCofThisEvent*) {}


