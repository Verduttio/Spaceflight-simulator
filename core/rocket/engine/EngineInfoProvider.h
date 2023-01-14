//
// Created by Bartek on 2023-01-14.
//

#ifndef ABSTRACTPROGRAMMINGPROJECT_OUT_ENGINEINFOPROVIDER_H
#define ABSTRACTPROGRAMMINGPROJECT_OUT_ENGINEINFOPROVIDER_H
#include <iostream>
#include "IEngineBuilder.h"

class EngineInfoProvider : public IEngineBuilder {
public:
    void reset() override {
        std::cout << "Resetting engine info provider" << std::endl;
    }

    void initEngineSpace() override {
        std::cout << "Engine info:" << std::endl;
    }

    void setMass(double _mass) override {
        std::cout << "Mass: " << _mass << " kg" << std::endl;
    }

    void setSpecificImpulse(double _specificImpulse) override {
        std::cout << "Specific impulse: " << _specificImpulse << " s" << std::endl;
    }

    void setMassFlowRate(double _massFlowRate) override {
        std::cout << "Mass flow rate: " << _massFlowRate << " kg/s" << std::endl;
    }
};


#endif //ABSTRACTPROGRAMMINGPROJECT_OUT_ENGINEINFOPROVIDER_H
