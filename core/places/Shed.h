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

    void buildRocketStageSmall() {
        rocketStageBuilder->initRocketStageSpace();
        rocketStageBuilder->mountSmallFuelTank();
        rocketStageBuilder->mountRaptorEngine();
        rocket->stages.push_back(rocketStageBuilder->getResult());
    }

    void buildRocketStageBig() {
        rocketStageBuilder->initRocketStageSpace();
        rocketStageBuilder->mountBigFuelTank();
        rocketStageBuilder->mountRaptorEngine();
//        rocketStageBuilder->mountRaptorEngine();
//        rocketStageBuilder->mountRaptorEngine();
        rocket->stages.push_back(rocketStageBuilder->getResult());
    }

    void buildStarshipSecondStage() {
        rocketStageBuilder->initRocketStageSpace();
        rocketStageBuilder->mountStarshipFuelTank();
        rocketStageBuilder->mountRaptorEngine();
//        rocketStageBuilder->mountRaptorEngine();
//        rocketStageBuilder->mountRaptorEngine();
        rocket->stages.push_back(rocketStageBuilder->getResult());
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


};

#endif //ABSTRACTPROGRAMMINGPROJECT_OUT_SHED_H
