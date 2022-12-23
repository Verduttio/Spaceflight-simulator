//
// Created by Bartek on 2022-12-23.
//

#ifndef ABSTRACTPROGRAMMINGPROJECT_OUT_FUELTANKDIRECTOR_H
#define ABSTRACTPROGRAMMINGPROJECT_OUT_FUELTANKDIRECTOR_H

#include "IFuelTankBuilder.h"

class FuelTankDirector {
public:
    void constructSmallFuelTank(IFuelTankBuilder* fuelTankBuilder) {
        fuelTankBuilder->reset();
        fuelTankBuilder->setMass(50);
        fuelTankBuilder->setFuelAmount(80);
        fuelTankBuilder->setMaxEngineNumberSupport(3);
    }
};

#endif //ABSTRACTPROGRAMMINGPROJECT_OUT_FUELTANKDIRECTOR_H
