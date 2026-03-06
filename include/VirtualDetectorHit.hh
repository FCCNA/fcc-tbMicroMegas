//
// Created by dboccanfuso on 3/6/26.
//

#ifndef TBMICROMEGAS_VIRTUALDETECTORHIT_HH
#define TBMICROMEGAS_VIRTUALDETECTORHIT_HH

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4LogicalVolume.hh"
#include "G4Transform3D.hh"

class G4AttDef;
class G4AttValue;

class VirtualDetectorHit : public G4VHit
{
public:
    VirtualDetectorHit() = default;
    ~VirtualDetectorHit() override = default;
    
    VirtualDetectorHit(const VirtualDetectorHit &right) = default;
    VirtualDetectorHit& operator=(const VirtualDetectorHit &right) = default;
    
    int operator==(const VirtualDetectorHit &right) const;
    
    inline void *operator new(size_t);
    inline void operator delete(void *aHit);
    
    void Draw() override;
    void Print() override;

    inline void SetTrackID(G4int z) {fTrackID = z;}
    inline G4int GetTrackID() const {return fTrackID;}

    inline void SetTime(G4double t) {fTime = t;}
    inline G4double GetTime() const {return fTime;}
    
    inline void SetPos(G4ThreeVector xyz) {fPos = xyz;}
    inline G4ThreeVector GetPos() const {return fPos;}
    
    inline void SetMom(G4ThreeVector xyz) {fMom = xyz;}
    inline G4ThreeVector GetMom() const {return fMom;}
    
    inline void SetEnergy(G4double energy) {fEnergy = energy;}
    inline G4double GetEnergy() const {return fEnergy;}

    inline void SetDetID(G4int did) {fDetID = did;}
    inline G4int GetDetID() const {return fDetID;}
    
private:
    G4int fTrackID = -1;
    G4double fTime = 0;
    G4ThreeVector fPos = G4ThreeVector(0., 0., 0.);
    G4ThreeVector fMom = G4ThreeVector(0., 0., 0.);
    G4double fEnergy = 0.;
    G4int fDetID = -1;
};

using VirtualDetectorHitsCollection = G4THitsCollection<VirtualDetectorHit>;

extern G4ThreadLocal G4Allocator<VirtualDetectorHit>* VirtualDetectorHitAllocator;

inline void* VirtualDetectorHit::operator new(size_t)
{
  if (!VirtualDetectorHitAllocator) VirtualDetectorHitAllocator = 
      new G4Allocator<VirtualDetectorHit>;
  return (void *) VirtualDetectorHitAllocator->MallocSingle();
}

inline void VirtualDetectorHit::operator delete(void* aHit)
{
  VirtualDetectorHitAllocator->FreeSingle((VirtualDetectorHit*) aHit);
}


#endif //TBMICROMEGAS_VIRTUALDETECTORHIT_HH