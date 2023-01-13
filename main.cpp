#include <iostream>
#include <cstdio>
#include "core/places/Shed.h"

void clearConsole() {
//#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
//    system("cls");
//#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
//    system("clear");
//#elif defined (__APPLE__)
//    system("clear");
//#endif
    system("clear");
}

void homeScreen(Shed&, MissionControl&);

void displayRocketBeforeFlightScreen(Shed& shed, MissionControl& missionControl) {
    clearConsole();
    std::cout << "Your rocket: " << std::endl;
    shed.drawRocketStagesASCII();
    shed.printRocketInfo();
    shed.moveRocketToMissionControl(&missionControl);
    missionControl.setMissionControl();
    std::cout << "When you are ready type [launch!] and press enter to launch the rocket..." << std::endl;

    // Get user input until enter is pressed
    std::string input;
    do {
        std::cin >> input;
    } while (input != "launch!" && input != "[launch!]");

    clearConsole();
    missionControl.launchRocket();
}

void possibleRocketsScreen(Shed& shed, MissionControl& missionControl) {
    clearConsole();
    std::cout << "Possible rockets:" << std::endl;
    std::cout << "1. Spaceflight Simulator Test Rocket" << std::endl;
    std::cout << "2. Starship Second Stage" << std::endl;
    std::cout << "3. Go back" << std::endl << std::endl;
    std::cout << "Choose an option: ";

    // Get user input until 1, 2 or 3 is pressed
    int userChoice;
    do {
        std::cin >> userChoice;
    } while (userChoice != 1 && userChoice != 2 && userChoice != 3);

    if (userChoice == 1) {
        shed.buildSpaceFlightSimulatorTestRocket();
        displayRocketBeforeFlightScreen(shed, missionControl);
    } else if (userChoice == 2) {
        shed.buildStarshipSecondStage();
        displayRocketBeforeFlightScreen(shed, missionControl);
    } else if (userChoice == 3) {
        homeScreen(shed, missionControl);
    }


}

void homeScreen(Shed& shed, MissionControl& missionControl) {
    clearConsole();
    std::cout << "Welcome to the Rocket Simulator!" << std::endl;
    std::cout << "Here are some options:" << std::endl;
    std::cout << "1. Choose already built rocket." << std::endl;
    std::cout << "2. Build your own rocket." << std::endl;
    std::cout << "3. Exit." << std::endl << std::endl;
    std::cout << "Choose an option: ";

    // Get user input until 1, 2 or 3 is pressed
    int userChoice;
    do {
        std::cin >> userChoice;
    } while (userChoice != 1 && userChoice != 2 && userChoice != 3);


    if (userChoice == 1) {
        possibleRocketsScreen(shed, missionControl);
    }
}



int main(int argc, char *argv[]) {
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


    homeScreen(shed, missionControl);




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
//    shed.moveRocketToMissionControl(&missionControl);
//
//    missionControl.setMissionControl();
//
//
//    // Launch the rocket
//    missionControl.launchRocket();
////    missionControl.launchRocketSimulation();



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