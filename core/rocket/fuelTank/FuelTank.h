//
// Created by Bartek on 2022-12-22.
//

#ifndef ABSTRACTPROGRAMMINGPROJECT_OUT_FUELTANK_H
#define ABSTRACTPROGRAMMINGPROJECT_OUT_FUELTANK_H

#include "core/rocket/RocketComponent.h"

class FuelTank : public RocketComponent{
    double fuelAmount;  // in tons
    int maxEngineNumberSupport;
public:
    double calcTotalMass() {
        return mass + fuelAmount;
    }

    void setFuelAmount(double _fuelAmount) {
        this->fuelAmount = _fuelAmount;
    }

    void setMaxEngineNumberSupport(int _maxEngineNumberSupport) {
        this->maxEngineNumberSupport = _maxEngineNumberSupport;
    }

    [[nodiscard]] double getFuelAmount() const {
        return this->fuelAmount;
    }

    [[nodiscard]] int getMaxEngineNumberSupport() const {
        return this->maxEngineNumberSupport;
    }
};

#endif //ABSTRACTPROGRAMMINGPROJECT_OUT_FUELTANK_H
