cmake_minimum_required(VERSION 3.16...3.21)
project(tbMicroMegas)
set(CMAKE_CXX_STANDARD 14)
#------------------------------------------------------------
# Options
option(WITH_GEANT4_UIVIS "Build with Geant4 UI and Vis drivers" ON)

#------------------------------------------------------------
# Geant4
if(WITH_GEANT4_UIVIS)
    find_package(Geant4 REQUIRED ui_all vis_all)
else()
    find_package(Geant4 REQUIRED)
endif()

include(${Geant4_USE_FILE})

#------------------------------------------------------------
# ROOT
find_package(ROOT REQUIRED COMPONENTS RIO Tree Hist)
include_directories(${ROOT_INCLUDE_DIRS})
add_definitions(${ROOT_CXX_FLAGS})

#------------------------------------------------------------
# Project includes
include_directories(${PROJECT_SOURCE_DIR}/include)
#------------------------------------------------------------
# Sources and headers
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

#------------------------------------------------------------
# Executable and linking
add_executable(tbMicroMegas tbMicroMegas.cc ${sources} ${headers})
target_link_libraries(tbMicroMegas ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})


#------------------------------------------------------------
# Installation
install(TARGETS tbMicroMegas DESTINATION bin)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})