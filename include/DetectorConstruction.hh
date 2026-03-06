//
// Created by dboccanfuso on 3/4/26.
//

#ifndef TBMICROMEGAS_DETECTORCONSTRUCTION_HH
#define TBMICROMEGAS_DETECTORCONSTRUCTION_HH

#include "DetectorConstructionMessenger.hh"
#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4RotationMatrix.hh"
#include "G4SystemOfUnits.hh"

class G4VPhysicalVolume;
class G4GenericMessenger;

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
    DetectorConstruction();
    ~DetectorConstruction() override = default;
    G4VPhysicalVolume* Construct() override;
    void ConstructSDandField() override;

    void SetMicroMegas1Position(G4double newValue) {fMM1Position = newValue;};
    void SetPlastic1Position(G4double newValue) {fPlastic1Position = newValue;};
    void SetVDet1Position(G4double newValue) {fVDet1Position = newValue;};
    void SetMicroMegas2Position(G4double newValue) {fMM2Position = newValue;};
    void SetPlastic2Position(G4double newValue) {fPlastic2Position = newValue;};
    void SetVDet2Position(G4double newValue) {fVDet2Position = newValue;};
    void SetBoxPosition(G4double newValue) {fBoxPosition = newValue;};
    void SetCalorimeterPosition(G4double newValue) {fCalorimeterPosition = newValue;};
    void SetVDet3Position(G4double newValue) {fVDet3Position = newValue;};
    void SetStation1AngleX(G4double newValue) {fStation1AngleX = newValue;};
    void SetStation1AngleY(G4double newValue) {fStation1AngleY = newValue;};
    void SetStation2AngleX(G4double newValue) {fStation2AngleX = newValue;};
    void SetStation2AngleY(G4double newValue) {fStation2AngleY = newValue;};

private:
    DetectorConstructionMessenger* fMessenger{nullptr};

    G4LogicalVolume* virtualDetectorLogic1{nullptr};
    G4LogicalVolume* virtualDetectorLogic2{nullptr};
    G4LogicalVolume* virtualDetectorLogic3{nullptr};

    G4double fMM1Position = 0.0*cm;
    G4double fPlastic1Position = -1.5*cm;
    G4double fVDet1Position = -0.6*cm;
    G4double fMM2Position = 30.0*cm;
    G4double fPlastic2Position = 28.5*cm;
    G4double fVDet2Position = 29.4*cm;
    G4double fBoxPosition = 60.0*cm;
    G4double fCalorimeterPosition = 90.0*cm;
    G4double fVDet3Position = 79.9*cm;

    G4double fStation1AngleX = 0;
    G4double fStation1AngleY = 0;
    G4double fStation2AngleX = 0;
    G4double fStation2AngleY = 0;

};


#endif //TBMICROMEGAS_DETECTORCONSTRUCTION_HH