//
// Created by Bartek on 2022-12-22.
//

#ifndef ABSTRACTPROGRAMMINGPROJECT_OUT_ENGINE_H
#define ABSTRACTPROGRAMMINGPROJECT_OUT_ENGINE_H

#include "../RocketComponent.h"

class Engine : public RocketComponent {
    double maxThrust;
    int currentPower; // in %
    double exhaustVelocity;  // in m/s
    double massFlowRate;  // in kg/s


public:
    [[nodiscard]] double getExhaustVelocity() const {
        return this->exhaustVelocity;
    }

    [[nodiscard]] double getMassFlowRate() const {
        return this->massFlowRate;
    }

    void setExhaustVelocity(double _exhaustVelocity) {
        this->exhaustVelocity = _exhaustVelocity;
    }

    void setMassFlowRate(double _massFlowRate) {
        this->massFlowRate = _massFlowRate;
    }

    void setMaxThrust(double _maxThrust) {
        this->maxThrust = _maxThrust;
    }

    [[nodiscard]] double getMaxThrust() const {
        return maxThrust;
    }

    [[nodiscard]] double getCurrentThrust() const {
        return maxThrust * currentPower / 100;
    }

    [[nodiscard]] double getCurrentMassFlowRate() const {
        return massFlowRate * currentPower / 100;
    }

    [[nodiscard]] double getCurrentExhaustVelocity() const {
        return exhaustVelocity * currentPower / 100;
    }

    void setCurrentPower(int _currentPower) {
        this->currentPower = _currentPower;
    }

    [[nodiscard]] int getCurrentPower() const {
        return currentPower;
    }
};

#endif //ABSTRACTPROGRAMMINGPROJECT_OUT_ENGINE_H
