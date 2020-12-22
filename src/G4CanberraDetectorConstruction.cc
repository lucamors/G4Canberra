#include "G4CanberraDetectorConstruction.hh"
#include "G4CanberraGermaniumSD.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"
#include "G4NistManager.hh"
#include "G4SDManager.hh"
#include "G4LogicalVolume.hh"
#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4ThreeVector.hh"

#include "G4VSolid.hh"
#include "G4Material.hh"
#include "G4Element.hh"

#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4GDMLParser.hh"

#include "CADMesh.hh"

G4CanberraDetectorConstruction::G4CanberraDetectorConstruction()
{
  // Define materials
  DefineMaterials();

}

G4CanberraDetectorConstruction::~G4CanberraDetectorConstruction()
{
  // deleting messenger
}

void G4CanberraDetectorConstruction::DefineMaterials()
{
  // Define Materials
  G4NistManager * nistManager = G4NistManager::Instance();

  airMaterial        = nistManager->FindOrBuildMaterial("G4_AIR");
  steelMaterial      = nistManager->FindOrBuildMaterial("G4_STAINLESS-STEEL");
  germaniumMaterial  = nistManager->FindOrBuildMaterial("G4_Ge");
  berylliumMaterial  = nistManager->FindOrBuildMaterial("G4_Be");
  leadMaterial       = nistManager->FindOrBuildMaterial("G4_Pb");
  aluminumMaterial   = nistManager->FindOrBuildMaterial("G4_Al");
  plexyglassMaterial = nistManager->FindOrBuildMaterial("G4_PLEXIGLASS");

  return ;
}

G4VPhysicalVolume * G4CanberraDetectorConstruction::Construct()
{
  // World Volume
  G4Box * world_solid             = new G4Box("wBox", 5*m,5*m,5*m);
  G4LogicalVolume * world_logical = new G4LogicalVolume(world_solid, airMaterial,"World");

  //////////////////////////////////////////////////////////////////////////////
  // Importing HPGe detector
  //////////////////////////////////////////////////////////////////////////////

  // Canberra BOX
  auto hpge_box_mesh                 = CADMesh::TessellatedMesh::FromSTL("Geometry/CanberraHPGe/box.stl");
  G4VSolid* hpge_box_solid           = hpge_box_mesh->GetSolid();
  G4LogicalVolume * hpge_box_logical = new G4LogicalVolume(hpge_box_solid, airMaterial, "hpge_box");

  // Crystal
  auto hpge_mesh                 = CADMesh::TessellatedMesh::FromSTL("Geometry/CanberraHPGe/crystal.stl");
  G4VSolid* hpge_solid           = hpge_mesh->GetSolid();
  G4LogicalVolume * hpge_logical = new G4LogicalVolume(hpge_solid, germaniumMaterial, "hpge_crystal");

  // Canberra Beryllium Window
  auto hpge_window_mesh          = CADMesh::TessellatedMesh::FromSTL("Geometry/CanberraHPGe/beryllium_window.stl");
  G4VSolid* hpge_window_solid    = hpge_window_mesh->GetSolid();
  G4LogicalVolume* hpge_window_logical = new G4LogicalVolume(hpge_window_solid, berylliumMaterial, "hpge_window");

  // Internal Case
  auto internal_case_mesh                = CADMesh::TessellatedMesh::FromSTL("Geometry/CanberraHPGe/inner_holder.stl");
  G4VSolid* internal_case_solid          = internal_case_mesh->GetSolid();
  G4LogicalVolume* internal_case_logical = new G4LogicalVolume(internal_case_solid, aluminumMaterial, "hpge_involucro_interno");

  // External Case
  auto external_case_mesh = CADMesh::TessellatedMesh::FromSTL("Geometry/CanberraHPGe/cold_end.stl");
  G4VSolid* external_case_solid = external_case_mesh->GetSolid();
  G4LogicalVolume* external_case_logical = new G4LogicalVolume(external_case_solid, aluminumMaterial, "hpge_involucro_esterno");

  //////////////////////////////////////////////////////////////////////////////
  // Source Container
  //////////////////////////////////////////////////////////////////////////////
  G4Box * source_container_solid = new G4Box("container_solid", 5*mm,5*mm,5*mm);
  G4LogicalVolume * source_container_logical = new G4LogicalVolume(source_container_solid, plexyglassMaterial, "source_container");

  //////////////////////////////////////////////////////////////////////////////
  // Detector Placement
  //////////////////////////////////////////////////////////////////////////////

  G4VPhysicalVolume * physicalWorld = new G4PVPlacement(0,
                                                        G4ThreeVector(),
                                                        world_logical,
                                                        "World Volume",
                                                        0,
                                                        false,
                                                        0,
                                                        true);

  G4double source_distance = -25*cm;
  G4ThreeVector source_to_detector_position = G4ThreeVector(0,0,source_distance);

  // // Placing HPGe Box
  new G4PVPlacement(0,
                    source_to_detector_position,
                    hpge_box_logical,
                    "HPGe Box",
                    world_logical,
                    false,
                    0,
                    true);

  // Placing HPGe Crystal
  new G4PVPlacement(0,
                    source_to_detector_position,
                    hpge_logical,
                    "HPGe Crystal",
                    world_logical,
                    false,
                    0,
                    true);

  // Placing Beryllium Window
  new G4PVPlacement(0,
                    source_to_detector_position,
                    hpge_window_logical,
                    "HPGe Window",
                    world_logical,
                    false,
                    0,
                    true);


  // Placing Internal Case
  new G4PVPlacement(0,
                    source_to_detector_position,
                    internal_case_logical,
                    "HPGe Internal Case",
                    world_logical,
                    false,
                    0,
                    true);

  // Placing External Case
  new G4PVPlacement(0,
                    source_to_detector_position,
                    external_case_logical,
                    "HPGe External Case",
                    world_logical,
                    false,
                    0,
                    true);

  // Placing Source Container
  new G4PVPlacement(0,
                    G4ThreeVector(),
                    source_container_logical,
                    "Source Container",
                    world_logical,
                    false,
                    0,
                    true
                    );



  //////////////////////////////////////////////////////////////////////////////
  // Visualization Attributes
  //////////////////////////////////////////////////////////////////////////////

  world_logical->SetVisAttributes(G4VisAttributes::Invisible);

  // HPGe Window
  G4VisAttributes * hpge_window_color = new G4VisAttributes(G4Colour(235./255, 186./255, 52./255)); // #ebba34
  hpge_window_logical->SetVisAttributes(hpge_window_color);

  // HPGe Crystal
  G4VisAttributes * hpge_crystal_color = new G4VisAttributes(G4Colour(101./255, 177./255, 184./255)); // #65b1b8
  hpge_logical->SetVisAttributes(hpge_crystal_color);

  // HPGe Internal Case
  G4VisAttributes * hpge_internal_case_color = new G4VisAttributes(G4Colour(66./255, 66./255, 66./255)); // #424242
  internal_case_logical->SetVisAttributes(hpge_internal_case_color);

  // HPGe External Case
  G4VisAttributes * hpge_external_case_color = new G4VisAttributes(G4Colour(200./255, 200./255, 200./255)); // #c4c4c4
  external_case_logical->SetVisAttributes(hpge_external_case_color);

  // HPGe Box
  G4VisAttributes * hpge_box_color = new G4VisAttributes(G4Colour(176./255, 176./255, 176./255)); // #e6faff
  hpge_box_logical->SetVisAttributes(hpge_box_color);

  return physicalWorld;
}

void G4CanberraDetectorConstruction::ConstructSDandField()
{

  // HPGe Sensitive Detector
  auto hpge_sensitive_detector = new G4CanberraGermaniumSD("GermaniumSD", "GermaniumHitsCollection");

  G4SDManager::GetSDMpointer()->AddNewDetector(hpge_sensitive_detector);
  SetSensitiveDetector("hpge_crystal", hpge_sensitive_detector);

  return ;

}
