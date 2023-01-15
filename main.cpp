#include <iostream>
#include "core/places/Shed.h"
#include "pages/ConsoleWriter.h"

void testOS() {
#if defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    std::cout << "Hello, GNU/Linux!" << '\n';
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    std::cout << "Hello, Windows!" << '\n';
#elif defined (__APPLE__)
    std::cout << "Hello, Apple!" << '\n';
#else
    std::cout << "Hello, Other!" << '\n';
#endif
}


int main(int argc, char *argv[]) {
    testOS();

    Shed shed;
    MissionControl missionControl;
    Planet earth(Physics::EARTH_MASS, Physics::EARTH_RADIUS);
    missionControl.setPlanet(&earth);

    //// ROCKET LIFE CYCLE
    // Set planet for mission control
    // Build the rocket
    // Make connections
    // Move the rocket to Mission Control
    // Set mission control
    // Launch the rocket

    ConsoleWriter::homeScreen(shed, missionControl);


    return 0;
}




























//#include <iostream>
//#include "core/places/Shed.h"
//
//int main(int argc, char *argv[]) {
//    Shed shed;
//
////    shed.buildRocketStageSmall();
////    shed.buildRocketStageSmall();
////    shed.buildRocketStageBig();
//
//    //shed.buildStarshipSecondStage();
////    auto* rocketStageBuilder = shed.getRocketStageBuilder();
////    rocketStageBuilder->initRocketStageSpace();
////    rocketStageBuilder->mountSpecificFuelTank(50000, 395700, 9);
////    rocketStageBuilder->mountSpecificEngine(1600, 2400, 650);
//
////    rocketStageBuilder->mountSpecificFuelTank(2000*4, 18000*4, 1);
////    rocketStageBuilder->mountSpecificEngine(3500+4400, 120000*9.81 ,240*9.81);
//
////    rocketStageBuilder->mountMerlinEngine();
////    rocketStageBuilder->mountMerlinEngine();
////    rocketStageBuilder->mountMerlinEngine();
////    rocketStageBuilder->mountMerlinEngine();
////    rocketStageBuilder->mountMerlinEngine();
////    rocketStageBuilder->mountMerlinEngine();
////    rocketStageBuilder->mountMerlinEngine();
////    rocketStageBuilder->mountMerlinEngine();
////    rocketStageBuilder->mountMerlinEngine();
////    shed.mountRocketStage(rocketStageBuilder->getResult());
//
//
//    shed.buildSpaceFlightSimulatorTestRocket();
//
//    // Make connections
////    shed.connectRocketStages(2, MountSide::left, 0);
////    shed.connectRocketStages(2, MountSide::right, 1);
//
//    shed.drawRocketStagesASCII();
//    shed.printRocketStagesConnections();
//
//    // The rocket is stacked and ready to be moved to Mission Control
//    MissionControl missionControl{};
//    shed.moveRocketToMissionControl(&missionControl);
//    double deltaT_ms = 1000;
//    missionControl.setMissionControl(deltaT_ms);
//    Planet earth(Physics::EARTH_MASS, Physics::EARTH_RADIUS);
//    missionControl.setPlanet(&earth);
//
//    // Launch the rocket
//    missionControl.launchRocket();
////    missionControl.launchRocketSimulation();
//
//
//
//    return 0;
//}