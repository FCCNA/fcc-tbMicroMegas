//
// Created by dboccanfuso on 3/4/26.
//

#include "DetectorConstruction.hh"
#include "G4PhysicalVolumeStore.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4SubtractionSolid.hh"
#include "G4RotationMatrix.hh"
#include "G4AssemblyVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4AutoDelete.hh"
#include "G4SDManager.hh"
#include "G4SDChargedFilter.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4PSTrackLength.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

#include "G4RunManager.hh"
#include "G4GenericMessenger.hh"

#include <iostream>
#include <tuple>

#include "DetectorConstructionMessenger.hh"
#include "VirtualDetectorSD.hh"

DetectorConstruction::DetectorConstruction() {
    G4cout << "### DetectorConstruction instantiated ###" << G4endl;
    fMessenger = new DetectorConstructionMessenger(this);
}

G4VPhysicalVolume *DetectorConstruction::Construct() {
    G4bool checkOverlaps = true;

    //define materials
    G4NistManager* nist = G4NistManager::Instance();

    G4Element* Argon = nist->FindOrBuildElement("Ar");
    G4Element* Oxygen = nist->FindOrBuildElement("O");
    G4Element* Bismuth = nist->FindOrBuildElement("Bi");
    G4Element* Silicon = nist->FindOrBuildElement("Si");


    G4Material* Steel = nist->FindOrBuildMaterial("G4_STAINLESS-STEEL");

    // Micromegas materials
    G4Material* Copper = nist->FindOrBuildMaterial("G4_Cu");
    G4Material* Kapton = nist->FindOrBuildMaterial("G4_KAPTON");
    G4Material* Glass = nist->FindOrBuildMaterial("G4_GLASS_PLATE");
    G4Material* CO2 = nist->FindOrBuildMaterial("G4_CARBON_DIOXIDE");
    G4Material* MMGas = new G4Material("MMGas", 1.80*mg/cm3, 2);
    MMGas->AddElement(Argon, 90*perCent);
    MMGas->AddMaterial(CO2, 10*perCent);

    G4Material* Plastic = nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");

    G4Material* BSO = new G4Material("BSO", 6.80*g/cm3, 3);
    BSO->AddElement(Bismuth, 4);
    BSO->AddElement(Silicon, 3);
    BSO->AddElement(Oxygen, 12);

    G4Material* Air = nist->FindOrBuildMaterial("G4_AIR");
    G4Material* Vacuum = nist->FindOrBuildMaterial("G4_Galactic");
    //Build the World Volume
    G4Box* worldSolid = new G4Box("World", 1.*m, 1.*m, 2.*m);

    G4LogicalVolume* worldLogic = new G4LogicalVolume(worldSolid,
                                                      Air,
                                                      "World");

    G4VPhysicalVolume* worldPhys = new G4PVPlacement
                                   (nullptr,              // no rotation
                                   G4ThreeVector(), // centre position
                                   worldLogic,      // its logical volume
                                   "World",       // its name
                                   nullptr,         // its mother volume
                                   false,           // no boolean operation
                                   0,               // copy number
                                   checkOverlaps);  // overlaps checking

    //Rotation matrices
    G4RotationMatrix* station1Rotation = new G4RotationMatrix;
    station1Rotation->rotateX(fStation1AngleX);
    station1Rotation->rotateY(fStation1AngleY);
    G4RotationMatrix* station2Rotation = new G4RotationMatrix;
    station2Rotation->rotateX(fStation2AngleX);
    station2Rotation->rotateY(fStation2AngleY);

    //Build MicroMegas
    //micromegas transverse size
    const G4double mmX = 10.*cm;
    const G4double mmY = 10.*cm;
    //Layer thickness
    const G4double tKapton1 = 120.*um;
    const G4double tCopper1 = 13.*um;
    const G4double tGas     = 5.0*mm;
    const G4double tKapton2 = 60.*um;
    const G4double tCopper2 = 13.*um;
    const G4double tGlass   = 1.6*mm;
    const G4double tCopper3 = 13.*um;
    //total thickness
    const G4double mmZ = tKapton1 + tCopper1 + tGas + tKapton2 + tCopper2 + tGlass + tCopper3;
    G4Box* micromegasSolid = new G4Box("MicroMegas", mmX/2, mmY/2, mmZ/2);


    G4LogicalVolume* micromegasLogic1 = new G4LogicalVolume(micromegasSolid, Vacuum, "MicroMegas1");
    G4LogicalVolume* micromegasLogic2 = new G4LogicalVolume(micromegasSolid,Vacuum, "MicroMegas2");

    G4VisAttributes* micromegasVis = new G4VisAttributes(G4Colour::Yellow());
    micromegasVis->SetForceWireframe(true);
    micromegasLogic1->SetVisAttributes(micromegasVis);
    micromegasLogic2->SetVisAttributes(micromegasVis);

    //Helper to build layers inside a Micromegas envelope
    auto buildMicromegasLayers = [&](G4LogicalVolume* motherLV, const G4String& prefix)
    {
        G4double zCursor = -mmZ/2.;
        auto placeLayer = [&](const G4String& name, G4Material* mat, G4double thickness, const G4Colour& color)
        {
            auto* solid = new G4Box(name + "S", mmX/2, mmY/2, thickness/2.);
            auto* logic = new G4LogicalVolume(solid, mat, name + "LV");

            auto* vis = new G4VisAttributes(color);
            vis->SetForceSolid(true);
            logic->SetVisAttributes(vis);

            const G4double zCenter = zCursor + thickness/2.;

            new G4PVPlacement(nullptr,
                              G4ThreeVector(0., 0., zCenter),
                              logic,
                              name + "PV",
                              motherLV,
                              false,
                              0,
                              checkOverlaps);

            zCursor += thickness;
        };

        placeLayer(prefix + "_Kapton1", Kapton, tKapton1, G4Colour(1.0, 0.5, 0.0));
        placeLayer(prefix + "_Copper1", Copper, tCopper1, G4Colour::Brown());
        placeLayer(prefix + "_Gas",     MMGas,  tGas,     G4Colour::Cyan());
        placeLayer(prefix + "_Kapton2", Kapton, tKapton2, G4Colour(1.0, 0.5, 0.0));
        placeLayer(prefix + "_Copper2", Copper, tCopper2, G4Colour::Brown());
        placeLayer(prefix + "_Glass",   Glass,  tGlass,   G4Colour::Grey());
        placeLayer(prefix + "_Copper3", Copper, tCopper3, G4Colour::Brown());
    };

    //Build internal layers in the two detectors
    buildMicromegasLayers(micromegasLogic1, "MM1");
    buildMicromegasLayers(micromegasLogic2, "MM2");

    auto micromegasPhysical1 = new G4PVPlacement(station1Rotation, G4ThreeVector(0., 0., fMM1Position), micromegasLogic1, "MicroMegas1Phys", worldLogic, false, 0, checkOverlaps);
    auto micromegasPhysical2 = new G4PVPlacement(station2Rotation, G4ThreeVector(0., 0., fMM2Position), micromegasLogic2, "MicroMegas2Phys", worldLogic, false, 1, checkOverlaps);

    //Build Plastic Scintillators

    G4Box* plasticSolid = new G4Box("Plastic", 5*cm, 5*cm, 0.5*cm);

    G4LogicalVolume* plasticLogic1 = new G4LogicalVolume(plasticSolid, Plastic, "Plastic1");
    G4LogicalVolume* plasticLogic2 = new G4LogicalVolume(plasticSolid, Plastic, "Plastic2");

    G4VisAttributes* plasticVis = new G4VisAttributes(G4Colour::White());
    plasticVis->SetForceSolid(true);
    plasticLogic1->SetVisAttributes(plasticVis);
    plasticLogic2->SetVisAttributes(plasticVis);

    auto plasticPhysical1 = new G4PVPlacement(station1Rotation, G4ThreeVector(0., 0., fPlastic1Position), plasticLogic1, "Plastic1Phys", worldLogic, false, 0, checkOverlaps);
    auto plasticPhysical2 = new G4PVPlacement(station2Rotation, G4ThreeVector(0., 0., fPlastic2Position), plasticLogic2, "Plastic2Phys", worldLogic, false, 1, checkOverlaps);

    //build box

    G4Box* boxSolid = new G4Box("Box", 15*cm, 15*cm, 0.75*mm);

    G4LogicalVolume* boxLogic = new G4LogicalVolume(boxSolid, Steel, "Box");

    G4VisAttributes* boxVis = new G4VisAttributes(G4Colour::Grey());
    boxVis->SetForceSolid(true);
    boxLogic->SetVisAttributes(boxVis);

    auto* boxPhysical = new G4PVPlacement(nullptr, G4ThreeVector(0., 0., fBoxPosition), boxLogic, "BoxPhys", worldLogic, false, 0, checkOverlaps);

    //Build Crystal Matrix

    //Cell dimensions
    const G4double cellX = 1.2*cm;
    const G4double cellY = 1.2*cm;
    const G4double frontZ = 5.0*cm;
    const G4double rearZ  = 15.0*cm;
    
    const int nX = 3, nY = 3;

    // Envelope of the calorimeter
    const G4double caloX = nX * cellX;   // 3.6 cm
    const G4double caloY = nY * cellY;   // 3.6 cm
    const G4double caloZ = frontZ + rearZ; // 20 cm
    
    auto* calorimeterSolid  = new G4Box("Calorimeter", caloX/2, caloY/2, caloZ/2);
    auto* calorimeterLogical = new G4LogicalVolume(calorimeterSolid, Vacuum, "Calorimeter");
    new G4PVPlacement(nullptr, G4ThreeVector(0,0, fCalorimeterPosition),
        calorimeterLogical, "CalorimeterPhys", worldLogic, false, 0, checkOverlaps);

    //front and rear
    auto* frontSolid  = new G4Box("frontSolid", caloX/2, caloY/2, frontZ/2);
    auto* frontLV = new G4LogicalVolume(frontSolid, Vacuum, "FrontLV");
    new G4PVPlacement(nullptr,
                      G4ThreeVector(0,0, -caloZ/2 + frontZ/2),
                      frontLV, "FrontPV", calorimeterLogical, false, 0, checkOverlaps);
    
    auto* rearSolid  = new G4Box("rearSolid", caloX/2, caloY/2, rearZ/2);
    auto* rearLV = new G4LogicalVolume(rearSolid, Vacuum, "rearLV");
    new G4PVPlacement(nullptr,
                  G4ThreeVector(0,0, +caloZ/2 - rearZ/2),
                  rearLV, "rearPV", calorimeterLogical, false, 0, checkOverlaps);

    // --- front matrix 3x3 ---
    // 1) Slice in X dentro FrontLV
    auto* frontXsliceS  = new G4Box("FrontXsliceS", cellX/2, caloY/2, frontZ/2);
    auto* frontXsliceLV = new G4LogicalVolume(frontXsliceS, BSO, "FrontXsliceLV");
    new G4PVReplica("FrontXslicePV", frontXsliceLV, frontLV, kXAxis, nX, cellX);

    // 2) Repliche in Y dentro ogni X-slice
    auto* frontCellS  = new G4Box("FrontCellS", cellX/2, cellY/2, frontZ/2);
    auto* frontCellLV = new G4LogicalVolume(frontCellS, BSO, "FrontCellLV");
    new G4PVReplica("FrontCellPV", frontCellLV, frontXsliceLV, kYAxis, nY, cellY);

    // --- rear matrix 3x3 ---
    auto* rearXsliceS  = new G4Box("rearXsliceS", cellX/2, caloY/2, rearZ/2);
    auto* rearXsliceLV = new G4LogicalVolume(rearXsliceS, BSO, "rearXsliceLV");
    new G4PVReplica("rearXslicePV", rearXsliceLV, rearLV, kXAxis, nX, cellX);

    auto* rearCellS  = new G4Box("rearCellS", cellX/2, cellY/2, rearZ/2);
    auto* rearCellLV = new G4LogicalVolume(rearCellS, BSO, "rearCellLV");
    new G4PVReplica("rearCellPV", rearCellLV, rearXsliceLV, kYAxis, nY, cellY);

    // Virtual Detectors
    G4Box* virtualDetectorSolid = new G4Box("VirtualDetector", 10*cm, 10*cm, 0.25*mm);

    virtualDetectorLogic1 = new G4LogicalVolume(virtualDetectorSolid, Air, "VirtualDetector1");
    virtualDetectorLogic2 = new G4LogicalVolume(virtualDetectorSolid, Air, "VirtualDetector2");
    virtualDetectorLogic3 = new G4LogicalVolume(virtualDetectorSolid, Air, "VirtualDetector3");

    G4VisAttributes* virtualDetectorVis = new G4VisAttributes(G4Colour::White());
    virtualDetectorLogic1->SetVisAttributes(virtualDetectorVis);
    virtualDetectorLogic2->SetVisAttributes(virtualDetectorVis);
    virtualDetectorLogic2->SetVisAttributes(virtualDetectorVis);

    auto virtualDetector1 = new G4PVPlacement(station1Rotation, G4ThreeVector(0., 0., fVDet1Position), virtualDetectorLogic1, "VirtualDetector1", worldLogic, false, 0, checkOverlaps);
    auto virtualDetector2 = new G4PVPlacement(station2Rotation, G4ThreeVector(0., 0., fVDet2Position), virtualDetectorLogic2, "VirtualDetector2", worldLogic, false, 1, checkOverlaps);
    auto virtualDetector3 = new G4PVPlacement(nullptr, G4ThreeVector(0., 0., fVDet3Position), virtualDetectorLogic3, "VirtualDetector3", worldLogic, false, 2, checkOverlaps);

    return worldPhys;
}

void DetectorConstruction::ConstructSDandField() {
    auto* virtualDetector = new VirtualDetector("VirtualDetector");
    G4SDManager::GetSDMpointer()->AddNewDetector(virtualDetector);
    virtualDetectorLogic1->SetSensitiveDetector(virtualDetector);
    virtualDetectorLogic2->SetSensitiveDetector(virtualDetector);
    virtualDetectorLogic3->SetSensitiveDetector(virtualDetector);
}
