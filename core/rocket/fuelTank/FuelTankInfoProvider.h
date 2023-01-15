//
// Created by Bartek on 2023-01-15.
//

#ifndef ABSTRACTPROGRAMMINGPROJECT_OUT_FUELTANKINFOPROVIDER_H
#define ABSTRACTPROGRAMMINGPROJECT_OUT_FUELTANKINFOPROVIDER_H
#include <iostream>
#include "IFuelTankBuilder.h"

class FuelTankInfoProvider : public IFuelTankBuilder {
public:
    void reset() override {
        std::cout << "Resetting fuel tank info provider" << std::endl;
    }

    void initFuelTankSpace() {
        std::cout << "Fuel tank info:" << std::endl;
    }

    void setFuelAmount(double _fuelAmount) override {
        std::cout << "Fuel amount: " << _fuelAmount << " kg" << std::endl;
    }

    void setMaxEngineNumberSupport(int _maxEngineNumberSupport) override {
        std::cout << "Max engine number support: " << _maxEngineNumberSupport << std::endl;
    }

    void setMass(double _mass) override {
        std::cout << "Mass: " << _mass << " kg" << std::endl;
    }
};


#endif //ABSTRACTPROGRAMMINGPROJECT_OUT_FUELTANKINFOPROVIDER_H
