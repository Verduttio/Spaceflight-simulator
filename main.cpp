#include <iostream>
#include <cstdio>
#include <string>
#include "core/places/Shed.h"

void clearConsole() {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    system("cls");
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
#elif defined (__APPLE__)
    system("clear");
#endif
}

void homeScreen(Shed& shed, MissionControl& missionControl);
void buildingOptionsScreen(Shed& shed, MissionControl& missionControl);

void controlRocketScreen(Shed& shed, MissionControl& missionControl) {
    while(true) {
        std::cout << "[t] - display rocket telemetry" << std::endl;
        std::cout << "[abort] - abort the flight" << std::endl;
        // Check input correctness
        std::string userInput;
        while (true) {
            std::cin >> userInput;
            if (userInput != "t" && userInput != "abort") {
                std::cout << "Incorrect input." << std::endl;
            } else {
                break;
            }
        }


        if (userInput == "t") {
            missionControl.printRocketTelemetry();
        } else if (userInput == "abort") {
            missionControl.terminateFlight();
            break;
        }

        std::cout << std::endl << std::endl;

    }
}

void displayRocketBeforeFlightScreen(Shed& shed, MissionControl& missionControl) {
    clearConsole();
    std::cout << "Your rocket: " << std::endl;
    shed.drawRocketStagesASCII();
    shed.printRocketStagesConnections();
    shed.printRocketInfo();
    shed.moveRocketToMissionControl(&missionControl);
    missionControl.setMissionControl();
    std::cout << "When you are ready type [launch!] and press enter to launch the rocket..." << std::endl;

    // Get user input until enter is pressed
    std::string input;
    while (true) {
        std::cin >> input;

        if (input != "launch!" && input != "[launch!]") {
            std::cout << "Invalid input! Type [launch!] and press enter to launch the rocket: ";
        } else {
            break;
        }
    }

    clearConsole();

    // Launch the rocket in a new thread
    // so that we can get user input while the rocket is flying
    std::thread flightThread(&MissionControl::launchRocket, &missionControl);


    // Getting user input to control the rocket
    controlRocketScreen(shed, missionControl);
    flightThread.join();

}

void possibleRocketsScreen(Shed& shed, MissionControl& missionControl) {
    clearConsole();
    std::cout << "Possible rockets:" << std::endl;
    std::cout << "1. Spaceflight Simulator Test Rocket." << std::endl;
    std::cout << "2. Starship Second Stage." << std::endl;
    std::cout << "3. Go back." << std::endl << std::endl;
    std::cout << "Choose an option: ";

    // Get user input until 1, 2 or 3 is pressed
    std::string userChoice;
    while (true) {
        std::cin >> userChoice;
        if (userChoice != "1" && userChoice != "2" && userChoice != "3") {
            std::cout << "Invalid input! Try again: ";
        } else {
            break;
        }
    }

    if (userChoice == "1") {
        shed.buildSpaceFlightSimulatorTestRocket();
        displayRocketBeforeFlightScreen(shed, missionControl);
    } else if (userChoice == "2") {
        shed.buildStarshipSecondStage();
        displayRocketBeforeFlightScreen(shed, missionControl);
    } else if (userChoice == "3") {
        homeScreen(shed, missionControl);
    }

}

void rocketStageConnectionsScreen(Shed& shed, MissionControl& missionControl) {
    clearConsole();
    std::cout << "In this step you have to connect the rocket stages together." << std::endl;
    std::cout << "Possible connections:" << std::endl;
    std::cout << "           up           \n"
                 "        _______         \n"
                 "       |       |        \n"
                 "       |       |        \n"
                 " left  |       |  right \n"
                 "       |       |        \n"
                 "       |       |        \n"
                 "       |       |        \n"
                 "       =========        \n"
                 "         bottom         \n" << std::endl;
    std::cout << "One of the possible sides mean to each side of the previously specified rocket stage you want to connect other stage." << std::endl;
    std::cout << std::endl;
    std::cout << "Connection example: " << std::endl;
    std::cout << "Let's say we have 2 rocket stages" << std::endl;
    std::cout << "                 _____  \n"
                 "   ___          |     | \n"
                 "  |   |         |     | \n"
                 "  |   |         |     | \n"
                 "  |   |         |     | \n"
                 "  =====         ======= \n"
                 "  e              ee     \n"
                 "  No. 0         No. 1   \n"  << std::endl;
    std::cout << "We would like stage No. 1 to connect, to its left side, stage No. 0." << std::endl;
    std::cout << "So we type: 1 left 0, and hit enter..." << std::endl;
    std::cout << "...and the resulting rocket would be: " << std::endl;
    std::cout << "        _____  \n"
                 "   ___ |     | \n"
                 "  |   ||     | \n"
                 "  |   ||     | \n"
                 "  |   ||     | \n"
                 "  ==== ======= \n"
                 "  e      ee     \n" << std::endl;
    std::cout << std::endl << std::endl;

    std::cout << "Your rocket stages: " << std::endl;
    shed.drawRocketStagesASCII();
    std::cout << std::endl;
    std::cout << "Connections: " << std::endl;
    shed.printRocketStagesConnections();
    std::cout << std::endl;

    // if not all rocket stages are connected
    if(!shed.rocketFullyStacked()) {
        // TODO: Validate stage id's (whether they exist)
        // TODO: Reset all connections if user enters "reset"
        std::cout << "Make a connection: " << std::endl;
        std::cout << "Source stage id: ";
        std::string source;
        int sourceInt;
        while (true) {
            std::cin >> source;
            try {
                sourceInt = std::stoi(source);
                break;
            } catch (std::invalid_argument &e) {
                std::cout << "Invalid input! Please provide a number. Source stage id: ";
            }
        }

        std::cout << "Mount side: ";
        std::string mountSide;
        while (true) {
            std::cin >> mountSide;
            if (mountSide != "up" && mountSide != "bottom" && mountSide != "left" && mountSide != "right") {
                std::cout << "Invalid input! Please provide a valid mount side. Mount side: ";
            } else {
                break;
            }
        }
        MountSide mountSideEnum;
        if (mountSide == "up") {
            mountSideEnum = MountSide::up;
        } else if (mountSide == "bottom") {
            mountSideEnum = MountSide::bottom;
        } else if (mountSide == "left") {
            mountSideEnum = MountSide::left;
        } else {
            mountSideEnum = MountSide::right;
        }

        std::cout << "Destination stage id: ";
        std::string destination;
        int destinationInt;
        while (true) {
            std::cin >> destination;
            try {
                destinationInt = std::stoi(destination);
                break;
            } catch (std::invalid_argument &e) {
                std::cout << "Invalid input! Please provide a number. Destination stage id: ";
            }
        }

        shed.connectRocketStages(sourceInt, mountSideEnum, destinationInt);
        rocketStageConnectionsScreen(shed, missionControl);
    } else {
        std::cout << "All rocket stages are connected!" << std::endl;
        std::cout << "When you are ready, type [approve] to end the process of building and stacking rocket!" << std::endl;

        std::string userChoice;
        while (true) {
            std::cin >> userChoice;
            if (userChoice != "approve" && userChoice != "[approve]") {
                std::cout << "Invalid input! type [approve] to end the process of building and stacking rocket!";
            } else {
                break;
            }
        }
        displayRocketBeforeFlightScreen(shed, missionControl);
    }

}

void beginnerRocketBuilderScreen(Shed& shed, MissionControl& missionControl) {
    bool buildingStarted = false;
    while(true) {
        clearConsole();
        std::cout << "You can build rocket stages from these listed below." << std::endl;
        std::cout << "After you select one of them you will be able to build another one." << std::endl;
        std::cout << "You will not be able to discard already built rocket stages!" << std::endl;
        std::cout << "It also means when you start building, you will have to launch the rocket!" << std::endl;
        std::cout << "Your already built rocket stages will be displayed on the screen." << std::endl;
        std::cout << "After you build all rocket stages you wish, you will have to connect them (to build a one-piece rocket)." << std::endl;

        std::cout << std::endl;

        if(buildingStarted) {
            std::cout << "Your already built rocket stages: " << std::endl;
            shed.drawRocketStagesASCII();
            std::cout << std::endl;
        }

        std::cout << "Possible rocket stages:" << std::endl;
        std::cout << "1. Small rocket stage. [fuel = 9t, dry mass = 1t, engines=1]" << std::endl;
        std::cout << "2. Big rocket stage. [fuel = 18t, dry mass = 2t, engines=1]" << std::endl;
        if (!buildingStarted) std::cout << "3. Go back." << std::endl << std::endl;
        if (buildingStarted) std::cout << "3. Finish building." << std::endl << std::endl;
        std::cout << "Choose an option: ";

        // Get user input until 1, 2 or 3 is pressed
        std::string userChoice;
        while (true) {
            std::cin >> userChoice;
            if (userChoice != "1" && userChoice != "2" && userChoice != "3") {
                std::cout << "Invalid input! Try again: ";
            } else {
                break;
            }
        }

        if (userChoice == "1") {
            buildingStarted = true;
            shed.buildSmallRocketStage();
        } else if (userChoice == "2") {
            buildingStarted = true;
            shed.buildBigRocketStage();
        } else if (userChoice == "3") {
            if (!buildingStarted) {
                buildingOptionsScreen(shed, missionControl);
            } else {
                rocketStageConnectionsScreen(shed, missionControl);
                break;
            }
        }

    }


}

void buildingOptionsScreen(Shed& shed, MissionControl& missionControl) {
    clearConsole();
    std::cout << "Choose build option:" << std::endl;
    std::cout << "1. Beginner - [build a rocket from already specified rocket stages]." << std::endl;
    std::cout << "2. Advanced - [build a rocket by building rocket stages from already specified components]." << std::endl;
    std::cout << "3. Expert   - [build a rocket stage from scratch. Specify engines and fuel tanks by yourself]." << std::endl;
    std::cout << "4. Go back." << std::endl << std::endl;

    // Get user input until 1, 2, 3 or 4 is pressed
    std::string userChoice;
    while (true) {
        std::cin >> userChoice;
        if (userChoice != "1" && userChoice != "2" && userChoice != "3" && userChoice != "4") {
            std::cout << "Invalid input! Try again: ";
        } else {
            break;
        }
    }

    if (userChoice == "1") {
        beginnerRocketBuilderScreen(shed, missionControl);
    } else if (userChoice == "2") {
        // TODO: Implement this
    } else if (userChoice == "3") {
        // TODO: Implement this
    } else if (userChoice == "4") {
        homeScreen(shed, missionControl);
    }


}

void homeScreen(Shed& shed, MissionControl& missionControl) {
    clearConsole();
    std::cout << "Welcome to the Rocket Simulator!" << std::endl;
    std::cout << "Here are some options:" << std::endl;
    std::cout << "1. Choose already built rocket - [Beginner]." << std::endl;
    std::cout << "2. Build your own rocket - [Advanced]." << std::endl;
    std::cout << "3. Exit." << std::endl << std::endl;
    std::cout << "Choose an option: ";

    // Get user input until 1, 2 or 3 is pressed
    std::string userChoice;
    while (true) {
        std::cin >> userChoice;
        if (userChoice != "1" && userChoice != "2" && userChoice != "3") {
            std::cout << "Invalid input! Try again: ";
        } else {
            break;
        }
    }

    if (userChoice == "1") {
        possibleRocketsScreen(shed, missionControl);
    } else if (userChoice == "2") {
        buildingOptionsScreen(shed, missionControl);
    } else if (userChoice == "3") {
        exit(0);
    }
}



int main(int argc, char *argv[]) {
#if defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    std::cout << "Hello, GNU/Linux!" << '\n';
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    std::cout << "Hello, Windows!" << '\n';
#elif defined (__APPLE__)
    std::cout << "Hello, Apple!" << '\n';
#else
    std::cout << "Hello, Other!" << '\n';
#endif


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