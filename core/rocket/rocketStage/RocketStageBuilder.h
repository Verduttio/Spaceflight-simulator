//
// Created by Bartek on 2022-12-28.
//

#ifndef ABSTRACTPROGRAMMINGPROJECT_OUT_ROCKETSTAGEBUILDER_H
#define ABSTRACTPROGRAMMINGPROJECT_OUT_ROCKETSTAGEBUILDER_H
#include "RocketStage.h"
#include "../engine/EngineBuilder.h"
#include "../engine/EngineDirector.h"
#include "../fuelTank/FuelTankBuilder.h"
#include "../fuelTank/FuelTankDirector.h"

class RocketStageBuilder {
    int rocketStageId;
    RocketStage* rocketStage;
    EngineBuilder* engineBuilder;
    EngineDirector* engineDirector;
    FuelTankBuilder* fuelTankBuilder;
    FuelTankDirector* fuelTankDirector;
public:
    void reset() {
        delete rocketStage;
        rocketStage = new RocketStage();
    }

    void initRocketStageSpace() {
        rocketStage = new RocketStage();
        rocketStage->setId(rocketStageId++);
    }

    RocketStageBuilder() {
        rocketStageId = 0;
    }

    void setEngineBuilder(EngineBuilder* _engineBuilder) {
        engineBuilder = _engineBuilder;
    }

    void setEngineDirector(EngineDirector* _engineDirector) {
        engineDirector = _engineDirector;
    }

    void setFuelTankBuilder(FuelTankBuilder* _fuelTankBuilder) {
        fuelTankBuilder = _fuelTankBuilder;
    }

    void setFuelTankDirector(FuelTankDirector* _fuelTankDirector) {
        fuelTankDirector = _fuelTankDirector;
    }

    void mountRaptorEngine() {
        checkEngineMountPermission();

        engineDirector->constructRaptorEngine(engineBuilder);
        rocketStage->addEngine(engineBuilder->getResult());
    }

    void mountMerlinEngine() {
        checkEngineMountPermission();

        engineDirector->constructMerlinEngine(engineBuilder);
        rocketStage->addEngine(engineBuilder->getResult());
    }

    void mountSpecificEngine(double mass, double exhaustVelocity, double massFlowRate) {
        checkEngineMountPermission();

        engineDirector->constructSpecificEngine(engineBuilder, mass, exhaustVelocity, massFlowRate);
        rocketStage->addEngine(engineBuilder->getResult());
    }

    void mountSmallFuelTank() {
        checkFuelTankMountPermission();

        fuelTankDirector->constructSmallFuelTank(fuelTankBuilder);
        rocketStage->setFuelTank(fuelTankBuilder->getResult());
    }

    void mountBigFuelTank() {
        checkFuelTankMountPermission();

        fuelTankDirector->constructBigFuelTank(fuelTankBuilder);
        rocketStage->setFuelTank(fuelTankBuilder->getResult());
    }

    void mountStarshipFuelTank() {
        checkFuelTankMountPermission();

        fuelTankDirector->constructStarshipFuelTank(fuelTankBuilder);
        rocketStage->setFuelTank(fuelTankBuilder->getResult());
    }

    void mountSpecificFuelTank(double mass, double fuelAmount, int maxEngineNumberSupport) {
        checkFuelTankMountPermission();

        fuelTankDirector->constructSpecificFuelTank(fuelTankBuilder, mass, fuelAmount, maxEngineNumberSupport);
        rocketStage->setFuelTank(fuelTankBuilder->getResult());
    }

    RocketStage* getResult() {
        return rocketStage;
    }
private:
    void checkEngineMountPermission() {
        if(rocketStage->getFuelTank() == nullptr) {
            throw "Fuel tank not mounted! Mount fuel tank first before mounting engine!";
        }

        // Check if engine can be mounted
        if(rocketStage->getFuelTank()->getMaxEngineNumberSupport() <= rocketStage->getEngineNumber()) {
            throw "Engine cannot be mounted! Maximum engine number support reached!";
        }
    }

    void checkFuelTankMountPermission() {
        if(rocketStage->getFuelTank() != nullptr) {
            throw "Fuel tank cannot be mounted! Fuel tank already mounted!";
        }
    }

};

#endif //ABSTRACTPROGRAMMINGPROJECT_OUT_ROCKETSTAGEBUILDER_H
