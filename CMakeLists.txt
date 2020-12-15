################################################################################
# Setup the project
################################################################################

cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(G4CANBERRA)

################################################################################
# Copy all scripts to the build directory i.e. the directory in which we build
# our application.
################################################################################

set(IRIS_SCRIPTS
    macro/vis.mac
    macro/run_template.mac
    Geometry/CanberraHPGe/crystal.stl
    Geometry/CanberraHPGe/box.stl
    Geometry/CanberraHPGe/cold_end.stl
    Geometry/CanberraHPGe/inner_holder.stl
    Geometry/CanberraHPGe/beryllium_window.stl
  )

foreach(_script ${IRIS_SCRIPTS})
  configure_file(
  ${PROJECT_SOURCE_DIR}/${_script}
  ${PROJECT_BINARY_DIR}/${_script}
  COPYONLY
  )
endforeach()

################################################################################
# Find Geant4 package, activating all available UI and Vis drivers by default
################################################################################

option(WITH_GEANT4_UIVIS "G4CANBERRA" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

################################################################################
# Setup Geant4 include directories and compule definitions
# Setup include directory for this project
################################################################################

include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

################################################################################
# Locate sources and headers for this project
################################################################################

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

################################################################################
# Add the executable, and link it to the Geant4 libraries
################################################################################

add_executable(G4Canberra G4Canberra.cc ${sources} ${headers})
target_link_libraries(G4Canberra ${Geant4_LIBRARIES})
