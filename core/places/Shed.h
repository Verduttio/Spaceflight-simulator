//
// Created by Bartek on 2022-12-22.
//

#ifndef ABSTRACTPROGRAMMINGPROJECT_OUT_SHED_H
#define ABSTRACTPROGRAMMINGPROJECT_OUT_SHED_H
#include "../rocket/Rocket.h"
#include "../rocket/rocketStage/RocketStageBuilder.h"
#include "MissionControl.h"

class Shed {
    Rocket* rocket;
    RocketStageBuilder* rocketStageBuilder;
    EngineBuilder* engineBuilder;
    EngineDirector* engineDirector;
    FuelTankBuilder* fuelTankBuilder;
    FuelTankDirector* fuelTankDirector;

public:
    Shed(){
        rocket = new Rocket();
        rocketStageBuilder = new RocketStageBuilder();
        engineBuilder = new EngineBuilder();
        engineDirector = new EngineDirector();
        fuelTankBuilder = new FuelTankBuilder();
        fuelTankDirector = new FuelTankDirector();

        rocketStageBuilder->setEngineBuilder(engineBuilder);
        rocketStageBuilder->setEngineDirector(engineDirector);
        rocketStageBuilder->setFuelTankBuilder(fuelTankBuilder);
        rocketStageBuilder->setFuelTankDirector(fuelTankDirector);
    }

    void moveRocketToMissionControl(MissionControl* missionControl) {
        missionControl->setRocket(rocket);
    };

    void resetBuilding() {
        delete rocket;
        rocket = new Rocket();
    }

    void buildSmallRocketStage() {
        rocketStageBuilder->initRocketStageSpace();
        rocketStageBuilder->mountSmallFuelTankSPF();
        rocketStageBuilder->mountHawkEngineSPF();

        rocket->stages.push_back(rocketStageBuilder->getResult());
    }

    void buildBigRocketStage() {
        rocketStageBuilder->initRocketStageSpace();
        rocketStageBuilder->mountBigFuelTankSPF();
        rocketStageBuilder->mountHawkEngineSPF();
        rocketStageBuilder->mountHawkEngineSPF();

        rocket->stages.push_back(rocketStageBuilder->getResult());
    }


    void buildStarshipSecondStage() {
        rocketStageBuilder->initRocketStageSpace();
        rocketStageBuilder->mountStarshipFuelTank();
        rocketStageBuilder->mountSpaceXRaptorV1Engine();
        rocketStageBuilder->mountSpaceXRaptorV1Engine();
        rocketStageBuilder->mountSpaceXRaptorV1Engine();

        rocket->stages.push_back(rocketStageBuilder->getResult());
    }

    void buildSpaceFlightSimulatorTestRocket() {
        rocketStageBuilder->initRocketStageSpace();
        rocketStageBuilder->mountSpecificFuelTank(2000*4, 18000*4, 1);    // Specs for test rocket in spaceflight simulator
//        rocketStageBuilder->mountSpecificFuelTank(2000*1, 18000*1, 1);
//        rocketStageBuilder->mountSpecificFuelTank(2000000, 0, 1);
        rocketStageBuilder->mountSpecificEngine(3500+4400, 240, (120*1000)/(240.0));   // Specs for test rocket in spaceflight simulator
//        rocketStageBuilder->mountSpecificEngine(3500+4400, 500, (120*1000)/(240.0));
//        rocketStageBuilder->mountSpecificEngine(0, 500, (120*1000)/(240.0));

        rocket->stages.push_back(rocketStageBuilder->getResult());
    }

    void buildSpecificRocketStage(double mass, double fuelAmount, int maxEngineNumberSupport, const std::string& engineType, int numberOfEngines) {
        rocketStageBuilder->initRocketStageSpace();
        rocketStageBuilder->mountSpecificFuelTank(mass, fuelAmount, maxEngineNumberSupport);
        for (int i = 0; i < numberOfEngines; i++) {
            if (engineType == "Raptor") {
                rocketStageBuilder->mountSpaceXRaptorV1Engine();
            } else {
                throw std::invalid_argument("Engine type not supported");
            }
        }
        rocket->stages.push_back(rocketStageBuilder->getResult());
    }

    void mountRocketStage(RocketStage* rocketStage) {
        rocket->stages.push_back(rocketStage);
    }

    RocketStageBuilder* getRocketStageBuilder() {
        return rocketStageBuilder;
    }

    void connectRocketStages(int sourceStageId, MountSide mountSide, int destinationStageId) {
        //Connects rocket stages
        //Connects source stage to destination stage on mount side,
        //then connects destination stage to source stage on opposite mount side.

        RocketStage* sourceStage = findRocketStage(sourceStageId);
        RocketStage* destinationStage = findRocketStage(destinationStageId);

        sourceStage->connect(destinationStage, mountSide);
        destinationStage->connect(sourceStage, static_cast<MountSide>((static_cast<int>(mountSide) + 2) % 4));
    }

    //Find rocketStage by id
    RocketStage* findRocketStage(int id) {
        for (auto rocketStage : rocket->stages) {
            if (rocketStage->getId() == id) {
                return rocketStage;
            }
        }
        return nullptr;
    }

    void drawRocketStagesASCII() {
        for(auto stage : rocket->stages) {
            stage->drawASCII();
            std::cout << "No. " << stage->getId() << std::endl;
            std::cout << std::endl;
        }
    }

    void printRocketStagesConnections() {
        for(auto stage : rocket->stages) {
            stage->printConnections();
        }
    }

    void printRocketInfo() {
        rocket->printInfo();
    }


};

#endif //ABSTRACTPROGRAMMINGPROJECT_OUT_SHED_H
