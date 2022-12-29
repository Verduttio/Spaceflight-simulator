//
// Created by Bartek on 2022-12-22.
//

#ifndef ABSTRACTPROGRAMMINGPROJECT_OUT_FUELTANK_H
#define ABSTRACTPROGRAMMINGPROJECT_OUT_FUELTANK_H

#include "../RocketComponent.h"

class FuelTank : public RocketComponent{
    double fuelAmount;  // in kg
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

    void decreaseFuelAmount(double amount) {
        this->fuelAmount -= amount;
    }
};

#endif //ABSTRACTPROGRAMMINGPROJECT_OUT_FUELTANK_H
