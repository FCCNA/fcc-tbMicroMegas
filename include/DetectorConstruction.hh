//
// Created by dboccanfuso on 3/4/26.
//

#ifndef TBMICROMEGAS_DETECTORCONSTRUCTION_HH
#define TBMICROMEGAS_DETECTORCONSTRUCTION_HH

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
};


#endif //TBMICROMEGAS_DETECTORCONSTRUCTION_HH