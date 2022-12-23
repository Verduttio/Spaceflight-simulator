cmake_minimum_required(VERSION 3.21)
project(AbstractProgrammingProject.out)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Remove for compiler-specific features
set(CMAKE_CXX_EXTENSIONS OFF)

string(APPEND CMAKE_CXX_FLAGS " -Wall")
string(APPEND CMAKE_CXX_FLAGS " -Wbuiltin-macro-redefined")
string(APPEND CMAKE_CXX_FLAGS " -pedantic")
string(APPEND CMAKE_CXX_FLAGS " -Werror")

# clangd completion
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${CMAKE_SOURCE_DIR})
file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES} core/rocket/RocketComponent.h core/rocket/engine/Engine.h core/rocket/fuelTank/FuelTank.h core/rocket/RocketStage.h core/rocket/MountSide.h core/rocket/Rocket.h core/planet/AtmosphereLayer.h core/planet/Atmosphere.h core/planet/Planet.h core/places/Shed.h core/places/LaunchPad.h core/places/MissionControl.h core/rocket/engine/IEngineBuilder.h core/rocket/fuelTank/IFuelTankBuilder.h core/rocket/engine/EngineBuilder.h core/rocket/engine/EngineDirector.h core/rocket/fuelTank/FuelTankBuilder.h core/rocket/fuelTank/FuelTankDirector.h)
add_executable(tests tests/simpleTest.cpp)

#set(Boost_USE_STATIC_LIBS        ON) # only find static libs
#set(Boost_USE_MULTITHREADED      ON)
#set(Boost_USE_STATIC_RUNTIME    OFF) # do not look for boost libraries linked against static C++ std lib
#
#find_package(Boost REQUIRED COMPONENTS filesystem)
#
#target_link_libraries(${PROJECT_NAME} Boost::filesystem)