//
// Created by Bartek on 2022-12-23.
//

#ifndef ABSTRACTPROGRAMMINGPROJECT_OUT_FUELTANKBUILDER_H
#define ABSTRACTPROGRAMMINGPROJECT_OUT_FUELTANKBUILDER_H

#include "IFuelTankBuilder.h"
#include "FuelTank.h"

class FuelTankBuilder : public IFuelTankBuilder {
    FuelTank* fuelTank;
public:
    void reset() override {
        if(fuelTank != nullptr) delete fuelTank;
        fuelTank = new FuelTank();
    }

    FuelTankBuilder() {
        this->reset();
    }

    void setFuelAmount(double _fuelAmount) override {
        fuelTank->setFuelAmount(_fuelAmount);
    }

    void setMaxEngineNumberSupport(int _maxEngineNumberSupport) override {
        fuelTank->setMaxEngineNumberSupport(_maxEngineNumberSupport);
    }

    void setMass(double _mass) override {
        fuelTank->setMass(_mass);
    }

    FuelTank* getResult() {
        return fuelTank;
    }

};

#endif //ABSTRACTPROGRAMMINGPROJECT_OUT_FUELTANKBUILDER_H
