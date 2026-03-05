//
// Created by dboccanfuso on 3/4/26.
//

#ifndef TBMICROMEGAS_DETECTORCONSTRUCTIONMESSENGER_HH
#define TBMICROMEGAS_DETECTORCONSTRUCTIONMESSENGER_HH

#include "G4UImessenger.hh"
#include "globals.hh"

class DetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADouble;
class G4UIcmdWithABool;
class G4UIcmdWith3VectorAndUnit;
class G4UIcmdWithAString;


/// Detector construction messenger class to define custom commands
/// to control the geometry and other settings.

class DetectorConstructionMessenger: public G4UImessenger
{
public:
    DetectorConstructionMessenger(DetectorConstruction* mydet);
    ~DetectorConstructionMessenger() override;

    void SetNewValue(G4UIcommand* command, G4String newValues) override;

private:
    DetectorConstruction* fDetector{nullptr};

    G4UIdirectory* fCmdDir{nullptr};

    //G4UIcmdWithADouble* fCrystalAngleXCmd{nullptr};
    //G4UIcmdWithADouble* fCrystalAngleYCmd{nullptr};

    //Position of 'station' 1
    G4UIcmdWithADoubleAndUnit* fMicroMegas1PositionCmd{nullptr};
    G4UIcmdWithADoubleAndUnit* fPlastic1PositionCmd{nullptr};
    G4UIcmdWithADoubleAndUnit* fVDet1PositionCmd{nullptr};
    //Position of 'station' 2
    G4UIcmdWithADoubleAndUnit* fMicroMegas2PositionCmd{nullptr};
    G4UIcmdWithADoubleAndUnit* fPlastic2PositionCmd{nullptr};
    G4UIcmdWithADoubleAndUnit* fVDet2PositionCmd{nullptr};
    //Position of last vdet
    G4UIcmdWithADoubleAndUnit* fVDet3PositionCmd{nullptr};
    //Position of box and calo
    G4UIcmdWithADoubleAndUnit* fBoxPositionCmd{nullptr};
    G4UIcmdWithADoubleAndUnit* fCalorimeterPositionCmd{nullptr};

    //rotation for station 1 and 2
    G4UIcmdWithADouble* fStation1AngleXCmd{nullptr};
    G4UIcmdWithADouble* fStation1AngleYCmd{nullptr};
    G4UIcmdWithADouble* fStation2AngleXCmd{nullptr};
    G4UIcmdWithADouble* fStation2AngleYCmd{nullptr};

    //G4UIcmdWith3VectorAndUnit* fVirtualDetectorSizeCmd{nullptr};

};


#endif //TBMICROMEGAS_DETECTORCONSTRUCTIONMESSENGER_HH