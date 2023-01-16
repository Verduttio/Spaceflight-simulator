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
#include "../engine/EngineInfoProvider.h"
#include "../fuelTank/FuelTankInfoProvider.h"

class RocketStageBuilder {
    int rocketStageId;
    RocketStage* rocketStage;
    EngineBuilder* engineBuilder;
    EngineDirector* engineDirector;
    EngineInfoProvider* engineInfoProvider;
    FuelTankBuilder* fuelTankBuilder;
    FuelTankDirector* fuelTankDirector;
    FuelTankInfoProvider* fuelTankInfoProvider;
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
        rocketStage = nullptr;
        engineBuilder = new EngineBuilder();
        engineDirector = new EngineDirector();
        engineInfoProvider = new EngineInfoProvider();
        fuelTankBuilder = new FuelTankBuilder();
        fuelTankDirector = new FuelTankDirector();
        fuelTankInfoProvider = new FuelTankInfoProvider();
    }

    EngineDirector* getEngineDirector() {
        return this->engineDirector;
    }

    EngineInfoProvider* getEngineInfoProvider() {
        return this->engineInfoProvider;
    }

    FuelTankDirector* getFuelTankDirector() {
        return this->fuelTankDirector;
    }

    FuelTankInfoProvider* getFuelTankInfoProvider() {
        return this->fuelTankInfoProvider;
    }

    void mountSpaceXRaptorV1Engine() {
        checkEngineMountPermission();

        engineDirector->constructSpacexRaptorV1Engine(engineBuilder);
        rocketStage->addEngine(engineBuilder->getResult());
    }

    void mountHawkEngineSPF() {
        checkEngineMountPermission();

        engineDirector->constructHawkEngineSPF(engineBuilder);
        rocketStage->addEngine(engineBuilder->getResult());
    }

    void mountSmallFuelTankSPF() {
        checkFuelTankMountPermission();

        fuelTankDirector->constructSmallFuelTankSPF(fuelTankBuilder);
        rocketStage->setFuelTank(fuelTankBuilder->getResult());
    }

    void mountBigFuelTankSPF() {
        checkFuelTankMountPermission();

        fuelTankDirector->constructBigFuelTankSPF(fuelTankBuilder);
        rocketStage->setFuelTank(fuelTankBuilder->getResult());
    }


    void mountSpecificEngine(double mass, double specificImpulse, double massFlowRate) {
        if(mass <= 0 || specificImpulse <= 0 || massFlowRate <= 0) {
            throw std::invalid_argument("Mass, specific impulse and mass flow rate must be greater than 0");
        }

        checkEngineMountPermission();

        engineDirector->constructSpecificEngine(engineBuilder, mass, specificImpulse, massFlowRate);
        rocketStage->addEngine(engineBuilder->getResult());
    }

    void mountStarshipFuelTank() {
        checkFuelTankMountPermission();

        fuelTankDirector->constructStarshipFuelTank(fuelTankBuilder);
        rocketStage->setFuelTank(fuelTankBuilder->getResult());
    }

    void mountSpecificFuelTank(double mass, double fuelAmount, int maxEngineNumberSupport) {
        if(mass <= 0 || fuelAmount <= 0 || maxEngineNumberSupport <= 0) {
            throw std::invalid_argument("Mass, fuel amount and max engine number support must be greater than 0");
        }

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
            throw std::invalid_argument("Fuel tank not mounted! Mount fuel tank first before mounting engine!");
        }

        // Check if engine can be mounted
        if(rocketStage->getFuelTank()->getMaxEngineNumberSupport() <= rocketStage->getEngineNumber()) {
            throw std::invalid_argument("Engine cannot be mounted! Maximum engine number support reached!");
        }
    }

    void checkFuelTankMountPermission() {
        if(rocketStage->getFuelTank() != nullptr) {
            throw std::invalid_argument("Fuel tank cannot be mounted! Fuel tank already mounted!");
        }
    }

};

#endif //ABSTRACTPROGRAMMINGPROJECT_OUT_ROCKETSTAGEBUILDER_H
