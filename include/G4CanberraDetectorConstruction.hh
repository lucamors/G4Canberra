#ifndef G4CANBERRA_DETECTOR_CONSTRUCTION_h
#define G4CANBERRA_DETECTOR_CONSTRUCTION_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4Material;

class G4CanberraDetectorConstruction : public G4VUserDetectorConstruction
{
  public:

    G4CanberraDetectorConstruction();
    virtual ~G4CanberraDetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();

    void SetMaterial(G4String );

  private:

    void DefineMaterials();

    // Materials
    G4Material * airMaterial;
    G4Material * steelMaterial;
    G4Material * germaniumMaterial;
    G4Material * berylliumMaterial;
    G4Material * leadMaterial;
    G4Material * aluminumMaterial;



};


#endif
