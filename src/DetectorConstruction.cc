//
// Created by dboccanfuso on 3/4/26.
//

#include "DetectorConstruction.hh"
#include "G4PhysicalVolumeStore.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4SubtractionSolid.hh"
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

DetectorConstruction::DetectorConstruction() {
    G4cout << "### DetectorConstruction instantiated ###" << G4endl;
}

G4VPhysicalVolume *DetectorConstruction::Construct() {
    G4bool checkOverlaps = true;

    //define materials
    G4NistManager* nist = G4NistManager::Instance();

    G4Element* Argon = nist->FindOrBuildElement("Ar");
    G4Element* Carbon = nist->FindOrBuildElement("C");
    G4Element* Oxygen = nist->FindOrBuildElement("O");
    G4Element* Bismuth = nist->FindOrBuildElement("Bi");
    G4Element* Silicon = nist->FindOrBuildElement("Si");

    G4Material* Copper = nist->FindOrBuildMaterial("G4_Cu");
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

    //Build the World Volume
    G4Box* worldSolid = new G4Box("World", 2.*m, 2.*m, 4.*m);

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

    //Build MicroMegas

    G4Box* micromegasSolid = new G4Box("MicroMegas", 5*cm, 5*cm, 0.5*cm);

    G4LogicalVolume* micromegasLogic = new G4LogicalVolume(micromegasSolid, MMGas, "MicroMegas");

    G4VisAttributes* micromegasVis = new G4VisAttributes(G4Colour::Yellow());
    micromegasVis->SetForceSolid(true);
    micromegasLogic->SetVisAttributes(micromegasVis);

    auto micromegasPhysical0 = new G4PVPlacement(nullptr, G4ThreeVector(0., 0., 1*m), micromegasLogic, "MicroMegasPhys", worldLogic, false, 0, checkOverlaps);
    auto micromegasPhysical1 = new G4PVPlacement(nullptr, G4ThreeVector(0., 0., 1.5*m), micromegasLogic, "MicroMegasPhys", worldLogic, false, 1, checkOverlaps);

    //Build Plastic Scintillators

    G4Box* plasticSolid = new G4Box("Plastic", 5*cm, 5*cm, 0.5*cm);

    G4LogicalVolume* plasticLogic = new G4LogicalVolume(plasticSolid, Plastic, "Plastic");

    G4VisAttributes* plasticVis = new G4VisAttributes(G4Colour::White());
    plasticVis->SetForceSolid(true);
    plasticLogic->SetVisAttributes(plasticVis);

    auto plasticPhysical0 = new G4PVPlacement(nullptr, G4ThreeVector(0., 0., 90*cm), plasticLogic, "PlasticPhys", worldLogic, false, 0, checkOverlaps);
    auto plasticPhysical1 = new G4PVPlacement(nullptr, G4ThreeVector(0., 0., 140*cm), plasticLogic, "PlasticPhys", worldLogic, false, 1, checkOverlaps);

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
    auto* calorimeterLogical = new G4LogicalVolume(calorimeterSolid, BSO, "Calorimeter");
    new G4PVPlacement(nullptr, G4ThreeVector(0,0,0), //bug fix
        calorimeterLogical, "CalorimeterPhys", worldLogic, false, 0, checkOverlaps);

    //front and rear
    auto* frontSolid  = new G4Box("frontSolid", caloX/2, caloY/2, frontZ/2);
    auto* frontLV = new G4LogicalVolume(frontSolid, BSO, "FrontLV");
    new G4PVPlacement(nullptr,
                      G4ThreeVector(0,0, -caloZ/2 + frontZ/2), //bug fix
                      frontLV, "FrontPV", calorimeterLogical, false, 0, checkOverlaps);
    
    auto* rearSolid  = new G4Box("rearSolid", caloX/2, caloY/2, rearZ/2);
    auto* rearLV = new G4LogicalVolume(rearSolid, BSO, "rearLV");
    new G4PVPlacement(nullptr,
                  G4ThreeVector(0,0, +caloZ/2 - rearZ/2), //bug fix
                  rearLV, "rearPV", calorimeterLogical, false, 0, checkOverlaps);

    // --- Front matrix 3x3 ---
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
    G4Box* virtualDetectorSolid = new G4Box("VirtualDetector", 5*cm, 5*cm, 0.5*mm);

    G4LogicalVolume* virtualDetectorLogic0 = new G4LogicalVolume(virtualDetectorSolid, Air, "VirtualDetector0");
    G4LogicalVolume* virtualDetectorLogic1 = new G4LogicalVolume(virtualDetectorSolid, Air, "VirtualDetector1");

    G4VisAttributes* virtualDetectorVis = new G4VisAttributes(G4Colour::White());
    virtualDetectorLogic0->SetVisAttributes(virtualDetectorVis);
    virtualDetectorLogic1->SetVisAttributes(virtualDetectorVis);

    auto virtualDetecor0 = new G4PVPlacement(nullptr, G4ThreeVector(0., 0., 89*cm), virtualDetectorLogic0, "VirtualDetector0", worldLogic, false, 0, checkOverlaps);
    auto virtualDetecor1 = new G4PVPlacement(nullptr, G4ThreeVector(0., 0., 139*cm), virtualDetectorLogic0, "VirtualDetector1", worldLogic, false, 1, checkOverlaps);

    return worldPhys;
}

void DetectorConstruction::ConstructSDandField() {

}
