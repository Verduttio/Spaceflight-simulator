//
// Created by Bartek on 2022-12-23.
//

#ifndef ABSTRACTPROGRAMMINGPROJECT_OUT_FUELTANKDIRECTOR_H
#define ABSTRACTPROGRAMMINGPROJECT_OUT_FUELTANKDIRECTOR_H

#include "IFuelTankBuilder.h"

class FuelTankDirector {
public:
    void constructSmallFuelTankSPF(IFuelTankBuilder* fuelTankBuilder) {
        fuelTankBuilder->initFuelTankSpace();
        fuelTankBuilder->setMass(1000);
        fuelTankBuilder->setFuelAmount(9000);
        fuelTankBuilder->setMaxEngineNumberSupport(3);
    }

    void constructBigFuelTankSPF(IFuelTankBuilder* fuelTankBuilder) {
        fuelTankBuilder->initFuelTankSpace();
        fuelTankBuilder->setMass(2000);
        fuelTankBuilder->setFuelAmount(18000);
        fuelTankBuilder->setMaxEngineNumberSupport(5);
    }

    void constructStarshipFuelTank(IFuelTankBuilder* fuelTankBuilder) {
        fuelTankBuilder->initFuelTankSpace();
        fuelTankBuilder->setMass(85000);
        fuelTankBuilder->setFuelAmount(1200000);
        fuelTankBuilder->setMaxEngineNumberSupport(3);
    }

    void constructSpecificFuelTank(IFuelTankBuilder* fuelTankBuilder, double mass, double fuelAmount, int maxEngineNumberSupport) {
        fuelTankBuilder->initFuelTankSpace();
        fuelTankBuilder->setMass(mass);
        fuelTankBuilder->setFuelAmount(fuelAmount);
        fuelTankBuilder->setMaxEngineNumberSupport(maxEngineNumberSupport);
    }
};

#endif //ABSTRACTPROGRAMMINGPROJECT_OUT_FUELTANKDIRECTOR_H
