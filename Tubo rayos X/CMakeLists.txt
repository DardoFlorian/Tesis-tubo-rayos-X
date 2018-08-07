#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(TDM_G4Example)

cmake_policy(SET CMP0042 NEW)

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
#
include(${Geant4_USE_FILE})

#----------------------------------------------------------------------------
# Locate sources and headers for this project
#
include_directories(${PROJECT_SOURCE_DIR}/include 
                    ${Geant4_INCLUDE_DIR})
file(GLOB TDM_G4sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB TDM_G4headers ${PROJECT_SOURCE_DIR}/include/*.hh)


#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#

add_executable(TDM_G4exec TDM_G4main.cc ${TDM_G4sources} ${TDM_G4headers})
target_link_libraries(TDM_G4exec ${Geant4_LIBRARIES} )

#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build RE02. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#
set(TDM_SCRIPTS
    vis.mac
    example.mac
    analisis.C
    MODIFICACION.C
    MODIFICACION-p.C
    examplecalibracion.mac
    EspectroEnergia60keV.dat
    generador.py
  )

foreach(_script ${TDM_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()
