//
// Created by dboccanfuso on 3/4/26.
//

#include "DetectorConstructionMessenger.hh"
#include "DetectorConstruction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithAString.hh"

#include "G4RunManager.hh"
#include "G4ios.hh"

DetectorConstructionMessenger::DetectorConstructionMessenger(DetectorConstruction *mydet) : fDetector(mydet)
{
    fCmdDir = new G4UIdirectory("/testbeam/");
    fCmdDir->SetGuidance("detector control");

    //position of station 1
    //micromegas 1
    fMicroMegas1PositionCmd = new G4UIcmdWithADoubleAndUnit("/det/setMicroMegas1Position", this);
    fMicroMegas1PositionCmd->SetGuidance("Set the position of the micro-megas 1");
    fMicroMegas1PositionCmd->SetParameterName("z position of MM1", true);
    fMicroMegas1PositionCmd->SetDefaultValue(0.0);
    fMicroMegas1PositionCmd->SetDefaultUnit("cm");
    //plastic 1
    fPlastic1PositionCmd = new G4UIcmdWithADoubleAndUnit("/det/setPlastic1Position", this);
    fPlastic1PositionCmd->SetGuidance("Set the position of the plastic scintillator 1");
    fPlastic1PositionCmd->SetParameterName("z position of Plastic 1", true);
    fPlastic1PositionCmd->SetDefaultValue(-1.5);
    fPlastic1PositionCmd->SetDefaultUnit("cm");
    //virtual detector 1
    fVDet1PositionCmd = new G4UIcmdWithADoubleAndUnit("/det/setVirtualDetector1Position", this);
    fVDet1PositionCmd->SetGuidance("Set the position of the virtual detector 1");
    fVDet1PositionCmd->SetParameterName("z position of VDet1", true);
    fVDet1PositionCmd->SetDefaultValue(-1.6);
    fVDet1PositionCmd->SetDefaultUnit("cm");

    //position of station 2
    //micromegas 2
    fMicroMegas2PositionCmd = new G4UIcmdWithADoubleAndUnit("/det/setMicroMegas2Position", this);
    fMicroMegas2PositionCmd->SetGuidance("Set the position of the micro-megas 2");
    fMicroMegas2PositionCmd->SetParameterName("z position of MM2", true);
    fMicroMegas2PositionCmd->SetDefaultValue(30.0);
    fMicroMegas2PositionCmd->SetDefaultUnit("cm");
    //plastic 2
    fPlastic2PositionCmd = new G4UIcmdWithADoubleAndUnit("/det/setPlastic2Position", this);
    fPlastic2PositionCmd->SetGuidance("Set the position of the plastic scintillator 2");
    fPlastic2PositionCmd->SetParameterName("z position of Plastic 0", true);
    fPlastic2PositionCmd->SetDefaultValue(28.5);
    fPlastic2PositionCmd->SetDefaultUnit("cm");
    //virtual detector 2
    fVDet2PositionCmd = new G4UIcmdWithADoubleAndUnit("/det/setVirtualDetector2Position", this);
    fVDet2PositionCmd->SetGuidance("Set the position of the virtual detector 2");
    fVDet2PositionCmd->SetParameterName("z position of VDet2", true);
    fVDet2PositionCmd->SetDefaultValue(28.4);
    fVDet2PositionCmd->SetDefaultUnit("cm");

    //Position of box, calo, last vdet
    //box
    fBoxPositionCmd = new G4UIcmdWithADoubleAndUnit("/det/setBoxPosition", this);
    fBoxPositionCmd->SetGuidance("Set the position of the box");
    fBoxPositionCmd->SetParameterName("z position of Box", true);
    fBoxPositionCmd->SetDefaultValue(60.0);
    fBoxPositionCmd->SetDefaultUnit("cm");
    //virtual detector 3
    fVDet3PositionCmd = new G4UIcmdWithADoubleAndUnit("/det/setVirtualDetector3Position", this);
    fVDet3PositionCmd->SetGuidance("Set the position of the virtual detector 3");
    fVDet3PositionCmd->SetParameterName("z position of VDet3", true);
    fVDet3PositionCmd->SetDefaultValue(89.9);
    fVDet3PositionCmd->SetDefaultUnit("cm");
    //calorimeter
    fCalorimeterPositionCmd = new G4UIcmdWithADoubleAndUnit("/det/setCalorimeterPosition", this);
    fCalorimeterPositionCmd->SetGuidance("Set the position of the calorimeter");
    fCalorimeterPositionCmd->SetParameterName("z position of Calorimeter", true);
    fCalorimeterPositionCmd->SetDefaultValue(90.0);
    fCalorimeterPositionCmd->SetDefaultUnit("cm");

    //rotation of station 1
    fStation1AngleXCmd = new G4UIcmdWithADouble("/det/setStation1AngleX", this);
    fStation1AngleXCmd->SetGuidance("Rotate the station 1 around the X axis");
    fStation1AngleXCmd->SetParameterName("angle X", true);
    fStation1AngleXCmd->SetDefaultValue(0.0);

    fStation1AngleYCmd = new G4UIcmdWithADouble("/det/setStation1AngleY", this);
    fStation1AngleYCmd->SetGuidance("Rotate the station 1 around the Y axis");
    fStation1AngleYCmd->SetParameterName("angle Y", true);
    fStation1AngleYCmd->SetDefaultValue(0.0);

    //rotation of station 2
    fStation2AngleXCmd = new G4UIcmdWithADouble("/det/setStation2AngleX", this);
    fStation2AngleXCmd->SetGuidance("Rotate the station 2 around the X axis");
    fStation2AngleXCmd->SetParameterName("angle X", true);
    fStation2AngleXCmd->SetDefaultValue(0.0);

    fStation2AngleYCmd = new G4UIcmdWithADouble("/det/setStation2AngleY", this);
    fStation2AngleYCmd->SetGuidance("Rotate the station 2 around the Y axis");
    fStation2AngleYCmd->SetParameterName("angle Y", true);
    fStation2AngleYCmd->SetDefaultValue(0.0);
}

DetectorConstructionMessenger::~DetectorConstructionMessenger() {
    delete fCmdDir;

    delete fMicroMegas1PositionCmd;
    delete fPlastic1PositionCmd;
    delete fVDet1PositionCmd;

    delete fMicroMegas2PositionCmd;
    delete fPlastic2PositionCmd;
    delete fVDet2PositionCmd;

    delete fVDet3PositionCmd;
    delete fBoxPositionCmd;
    delete fCalorimeterPositionCmd;

    delete fStation1AngleXCmd;
    delete fStation2AngleXCmd;
    delete fStation1AngleYCmd;
    delete fStation2AngleYCmd;
}

void DetectorConstructionMessenger::SetNewValue(G4UIcommand *command, G4String newValue) {
    if (command == fMicroMegas1PositionCmd) {
        fDetector->SetMicroMegas1Position(fMicroMegas1PositionCmd->GetNewDoubleValue(newValue));
    }
    if (command == fPlastic1PositionCmd) {
        fDetector->SetPlastic1Position(fPlastic1PositionCmd->GetNewDoubleValue(newValue));
    }
    if (command == fVDet1PositionCmd) {
        fDetector->SetVDet1Position(fVDet1PositionCmd->GetNewDoubleValue(newValue));
    }
    if (command == fMicroMegas2PositionCmd) {
        fDetector->SetMicroMegas2Position(fMicroMegas2PositionCmd->GetNewDoubleValue(newValue));
    }
    if (command == fPlastic2PositionCmd) {
        fDetector->SetPlastic2Position(fPlastic2PositionCmd->GetNewDoubleValue(newValue));
    }
    if (command == fVDet2PositionCmd) {
        fDetector->SetVDet2Position(fVDet2PositionCmd->GetNewDoubleValue(newValue));
    }
    if (command == fBoxPositionCmd) {
        fDetector->SetBoxPosition(fBoxPositionCmd->GetNewDoubleValue(newValue));
    }
    if (command == fVDet3PositionCmd) {
        fDetector->SetVDet3Position(fVDet3PositionCmd->GetNewDoubleValue(newValue));
    }
    if (command == fCalorimeterPositionCmd) {
        fDetector->SetCalorimeterPosition(fCalorimeterPositionCmd->GetNewDoubleValue(newValue));
    }

    if (command == fStation1AngleXCmd) {
        fDetector->SetStation1AngleX(fStation1AngleXCmd->GetNewDoubleValue(newValue));
    }
    if (command == fStation2AngleXCmd) {
        fDetector->SetStation2AngleX(fStation2AngleXCmd->GetNewDoubleValue(newValue));
    }
    if (command == fStation1AngleYCmd) {
        fDetector->SetStation1AngleY(fStation1AngleYCmd->GetNewDoubleValue(newValue));
    }
    if (command == fStation2AngleYCmd) {
        fDetector->SetStation2AngleY(fStation2AngleYCmd->GetNewDoubleValue(newValue));
    }

}
