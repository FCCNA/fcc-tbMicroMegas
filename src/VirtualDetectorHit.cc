//
// Created by dboccanfuso on 3/6/26.
//

#include "VirtualDetectorHit.hh"
#include "G4ios.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4AttDefStore.hh"
#include "G4AttDef.hh"
#include "G4AttValue.hh"
#include "G4UIcommand.hh"
#include "G4UnitsTable.hh"
#include "G4VisAttributes.hh"
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"

G4ThreadLocal G4Allocator<VirtualDetectorHit>* VirtualDetectorHitAllocator = nullptr;

//constructor is defaulted in the header

int VirtualDetectorHit::operator==(const VirtualDetectorHit &) const
{
    return 0;
}

void VirtualDetectorHit::Print(){};

void VirtualDetectorHit::Draw()
{
    G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
    if (pVVisManager){
        G4Circle circle(fPos);
        circle.SetScreenSize(2);
        circle.SetFillStyle(G4Circle::filled);
        G4Colour colour(1.,1.,0.);
        G4VisAttributes attribs(colour);
        circle.SetVisAttributes(attribs);
        pVVisManager->Draw(circle);
    }
}