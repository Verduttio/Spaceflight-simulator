//
// Created by Bartek on 2023-01-15.
//

#ifndef ABSTRACTPROGRAMMINGPROJECT_OUT_CONSOLEWRITER_H
#define ABSTRACTPROGRAMMINGPROJECT_OUT_CONSOLEWRITER_H
#include <iostream>
#include "utils/PlotMaker.h"
#include "../core/places/Shed.h"


class ConsoleWriter {
public:

    static void clearConsole() {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
        system("cls");
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
        system("clear");
#elif defined (__APPLE__)
    system("clear");
#endif
    }

    static void endingInfo() {
        std::cout << "Thank you for playing my simulator!" << std::endl;
        std::cout << "I hope you enjoyed it!" << std::endl;
        std::cout << "The simulator is still in development, so there are many things to be added and fixed." << std::endl;
        std::cout << std::endl;
        std::cout << "!!!Data about your flight is saved in the file: rocketTelemetry.txt!!!" << std::endl;
        std::cout << "!!!Rocket trajectory is being generated in files: rocketTrajectory.png and rocketTrajectoryFull.png...!!!" << std::endl;
        std::cout << "!!!Please wait a few seconds...!!!" << std::endl;
        std::cout << "Graphics generated!" << std::endl;

        PlotMaker::plotRocketTrajectoryToFiles();
    }

    static void controlRocketScreen(Shed& shed, MissionControl& missionControl) {
        while(!missionControl.getAbortFlightValue()) {
            std::cout << "[t] - display rocket telemetry" << std::endl;
            std::cout << "[abort] - abort the flight" << std::endl;
            std::cout << "[rs] - print rocket stages and its connections" << std::endl;
            std::cout << "[a30] - set rocket angle to 30 (any value from [-180,180])" << std::endl;
            std::cout << "[p60] - set rocket engines power to 60% (any value from [0,100])" << std::endl;
            std::cout << "[d1] - detach stage No. 1" << std::endl;
            // Check input correctness
            std::string userInput;
            while (true) {
                std::cin >> userInput;
                if (validateUserRocketControlInput(userInput) == 0 && !missionControl.getAbortFlightValue()) {
                    std::cout << "Incorrect input." << std::endl;
                } else {
                    break;
                }
            }


            // Trigger the appropriate action
            unsigned int action = validateUserRocketControlInput(userInput);
            if (action == 1) {
                if (userInput == "t") {
                    missionControl.printRocketTelemetry();
                } else if (userInput == "abort") {
                    missionControl.terminateFlight();
                } else if (userInput == "rs") {
                    missionControl.drawRocketStagesASCII();
                    missionControl.printRocketStagesConnections();
                }
            } else if (action == 2) {
                if (userInput[0] == 'a') {
                    std::cout << "Change angle to: |" << std::stoi(userInput.substr(1)) << "|" << std::endl;
                    missionControl.setRocketAngle(std::stoi(userInput.substr(1)));
                } else if (userInput[0] == 'p') {
                    missionControl.setPowerForAllEngines(std::stoi(userInput.substr(1)));
                } else if (userInput[0] == 'd') {
                    missionControl.detachStage(std::stoi(userInput.substr(1)));
                }
            }

            std::cout << std::endl << std::endl;

        }
    }

    static void displayRocketBeforeFlightScreen(Shed& shed, MissionControl& missionControl) {
        clearConsole();
        std::cout << "Your rocket: " << std::endl;
        shed.drawRocketStagesASCII();
        shed.printRocketStagesConnections();
        shed.printRocketInfo();
        shed.moveRocketToMissionControl(&missionControl);
        missionControl.setMissionControl();

        if(!shed.checkThrustToWeightRation()) {
            std::cout << "Your rocket is too heavy!. It will not lift off!" << std::endl;
            exit(0);
        }

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

        // Ending info
        endingInfo();


    }

    static void possibleRocketsScreen(Shed& shed, MissionControl& missionControl) {
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

    static void rocketStageConnectionsScreen(Shed& shed, MissionControl& missionControl) {
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

        std::cout << "Your rocket stages: " << std::endl << std::endl;
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

    static void beginnerRocketBuilderScreen(Shed& shed, MissionControl& missionControl) {
        bool buildingStarted = false;
        while(true) {
            clearConsole();
            std::cout << "You can build rocket stages from these listed below." << std::endl;
            std::cout << "After you select one of them you will be able to build another one." << std::endl;
            std::cout << "You will not be able to discard already built rocket stages!" << std::endl;
            std::cout << "It also means when you start building, you will have to launch the rocket!" << std::endl;
            std::cout << "***Your first built stage will be the main rocket stage***" << std::endl;
            std::cout << "***It means that while detaching stages during flight, the rocket continuing flight will contain the main stage***" << std::endl;
            std::cout << "***The detached part will be 'discarded' (the part without the main stage)***" << std::endl;
            std::cout << "Your already built rocket stages will be displayed on the screen." << std::endl;
            std::cout << "After you build all rocket stages you wish, you will have to connect them (to build a one-piece rocket)." << std::endl;

            std::cout << std::endl;

            if(buildingStarted) {
                std::cout << "Your already built rocket stages: " << std::endl;
                shed.drawRocketStagesASCII();
                shed.printRocketInfo();
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

    static void advancedRocketBuilderScreen(Shed& shed, MissionControl& missionControl) {
        bool buildingStarted = false;
        while(true) {
            clearConsole();
            std::cout << "In this step you will built you own rocket stages based on given components." << std::endl;
            std::cout << "!!!First rocket stage will be the main rocket stage!!!" << std::endl;
            std::cout
                    << "!!!It means that while detaching stages during flight, the rocket continuing flight will contain the main stage!!!"
                    << std::endl;
            std::cout << "You will not be able to discard already built rocket stages!" << std::endl;
            std::cout << "It also means when you start building, you will have to launch the rocket!" << std::endl;
            std::cout << std::endl;

            if(buildingStarted) {
                std::cout << "Your already built rocket stages: " << std::endl;
                shed.drawRocketStagesASCII();
                shed.printRocketInfo();
                std::cout << std::endl;

                std::cout << "If you want to finish building and move to the stacking process, type [finish] and hit enter." << std::endl;

                std::string userChoice;
                std::cin >> userChoice;
                if (userChoice == "finish") {
                    rocketStageConnectionsScreen(shed, missionControl);
                    break;
                }
            } else {
                std::cout << "Choose an option: " << std::endl;
                std::cout << "1. Start building." << std::endl;
                std::cout << "2. Go back." << std::endl;

                std::string userChoice;
                while (true) {
                    std::cin >> userChoice;
                    if (userChoice != "1" && userChoice != "2") {
                        std::cout << "Invalid input! Try again: ";
                    } else {
                        break;
                    }
                }

                if (userChoice == "1") {
                    buildingStarted = true;
                } else if (userChoice == "2") {
                    buildingOptionsScreen(shed, missionControl);
                    break;
                }
            }



            std::cout << "Possible fuel tanks: " << std::endl;
            FuelTankDirector *fuelTankDirector = shed.getRocketStageBuilder()->getFuelTankDirector();
            FuelTankInfoProvider *fuelTankInfoProvider = shed.getRocketStageBuilder()->getFuelTankInfoProvider();
            std::cout << "Fuel tank No. 1" << std::endl;
            fuelTankDirector->constructSmallFuelTankSPF(fuelTankInfoProvider);
            std::cout << "\nFuel tank No. 2" << std::endl;
            fuelTankDirector->constructBigFuelTankSPF(fuelTankInfoProvider);
            std::cout << "\nFuel tank No. 3" << std::endl;
            fuelTankDirector->constructStarshipFuelTank(fuelTankInfoProvider);

            std::cout << std::endl;


            std::cout << "Possible engines: " << std::endl;
            EngineDirector *engineDirector = shed.getRocketStageBuilder()->getEngineDirector();
            EngineInfoProvider *engineInfoProvider = shed.getRocketStageBuilder()->getEngineInfoProvider();
            std::cout << "Engine No. 1" << std::endl;
            engineDirector->constructHawkEngineSPF(engineInfoProvider);
            std::cout << "\nEngine No. 2" << std::endl;
            engineDirector->constructSpacexRaptorV1Engine(engineInfoProvider);

            // This is a horrible way of doing it, but I don't have time to do it better now...
            int fuelTank1;
            int fuelTank2;
            int fuelTank3;
            int engineType;
            int engineCount;

            // TODO: Verify input!!!!
            std::cout << "Please provide a valid input because, we do not check it here!" << std::endl;
            std::cout << "Number of fuel tank No. 1: ";
            std::cin >> fuelTank1;
            std::cout << "Number of fuel tank No. 2: ";
            std::cin >> fuelTank2;
            std::cout << "Number of fuel tank No. 3: ";
            std::cin >> fuelTank3;
            std::cout << "You can only choose one engine type!" << std::endl;
            std::cout << "Engine type: ";
            std::cin >> engineType;
            std::cout << "Engine count: ";
            std::cin >> engineCount;


            RocketStageBuilder *rocketStageBuilder = shed.getRocketStageBuilder();
            rocketStageBuilder->initRocketStageSpace();
            /// It's bad, we should not have a single FuelTank in our rocket stage, but a vector of FuelTanks!!!
            /// But I don't have time to do refactor it now...
            rocketStageBuilder->mountSpecificFuelTank(fuelTank1 * 1000 + fuelTank2 * 2000 + fuelTank3 * 85000,
                                                      fuelTank1 * 9000 + fuelTank2 * 18000 + fuelTank3 * 500000, 3);
            // Mount engines
            for (int i = 0; i < engineCount; i++) {
                if (engineType == 1) {
                    rocketStageBuilder->mountHawkEngineSPF();
                } else if (engineType == 2) {
                    rocketStageBuilder->mountSpaceXRaptorV1Engine();
                }
            }

            shed.addRocketStage(rocketStageBuilder->getResult());
        }

    }

    static void expertRocketBuilderScreen(Shed& shed, MissionControl& missionControl) {
        clearConsole();
        std::cout << "If you reached here, you probably know what you are doing." << std::endl;
        std::cout << "There is no way back, nor any instructions." << std::endl;
        std::cout << "Rules are the same as in beginner and advanced mode." << std::endl;
        std::cout << "...okay, if you entered here by mistake, you can go back..." << std::endl;
        std::cout << "1. Start building." << std::endl;
        std::cout << "2. Go back." << std::endl;

        std::string userChoice;
        while (true) {
            std::cin >> userChoice;
            if (userChoice != "1" && userChoice != "2") {
                std::cout << "Invalid input! Try again: ";
            } else {
                break;
            }
        }

        if (userChoice == "2") {
            buildingOptionsScreen(shed, missionControl);
        }

        //TODO: Validate input!
        std::cout << "Your input is not validated, because you are an expert!" << std::endl;

        while(true) {
            std::cout << "Fuel tank dry mass (kg): ";
            double fuelTankDryMass;
            std::cin >> fuelTankDryMass;
            std::cout << "Fuel tank fuel mass (kg): ";
            double fuelTankFuelMass;
            std::cin >> fuelTankFuelMass;
            std::cout << "Max engine support: ";
            int maxEngineSupport;
            std::cin >> maxEngineSupport;
            std::cout << "Engine mass (kg): ";
            double engineMass;
            std::cin >> engineMass;
            std::cout << "Engine specific impulse (s): ";
            double engineSpecificImpulse;
            std::cin >> engineSpecificImpulse;
            std::cout << "Engine mass flow rate (kg/s): ";
            double engineMassFlowRate;
            std::cin >> engineMassFlowRate;
            std::cout << "Number of engines: ";
            int engineCount;
            std::cin >> engineCount;

            shed.buildSpecificRocketStage(fuelTankDryMass, fuelTankFuelMass, maxEngineSupport, engineMass, engineSpecificImpulse, engineMassFlowRate, engineCount);

            shed.drawRocketStagesASCII();
            shed.printRocketInfo();

            std::cout << "Type [finish] to finish building, or anything else to continue building, and hit enter: ";
            std::cin >> userChoice;
            if (userChoice == "finish") {
                rocketStageConnectionsScreen(shed, missionControl);
                break;
            }

        }


    }

    static void buildingOptionsScreen(Shed& shed, MissionControl& missionControl) {
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
            advancedRocketBuilderScreen(shed, missionControl);
        } else if (userChoice == "3") {
            expertRocketBuilderScreen(shed, missionControl);
        } else if (userChoice == "4") {
            homeScreen(shed, missionControl);
        }


    }

    static void homeScreen(Shed& shed, MissionControl& missionControl) {
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

private:
    static unsigned int validateUserRocketControlInput(const std::string& input) {
        // Possible options:
        // Single argument commands: t, abort, rs   return 1
        // Double argument commands: aXY, pXY, dX   return 2
        // Invalid input: anything else        return 0

        // Firstly check whether input is a single argument command
        // then check whether input is a double argument command

        if (input == "t" || input == "abort" || input == "rs") {
            return 1;
        } else {
            try {
                std::stoi(input.substr(1));
                return 2;
            } catch (std::invalid_argument& e) {
                return 0;
            }
        }

    }
};

#endif //ABSTRACTPROGRAMMINGPROJECT_OUT_CONSOLEWRITER_H
