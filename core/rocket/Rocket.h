//
// Created by Bartek on 2022-12-22.
//

#ifndef ABSTRACTPROGRAMMINGPROJECT_OUT_ROCKET_H
#define ABSTRACTPROGRAMMINGPROJECT_OUT_ROCKET_H

#include "rocketStage/RocketStage.h"

class Rocket {
    std::vector<RocketStage*> stages;
    double angle;  // in degrees [-180, 180]
    double velocityY;  // in m/s
    double velocityX;  // in m/s
    double altitude;  // in m

    friend class Shed;
    friend class MissionControl;
public:
    void setVelocityY(double _velocity) {
        this->velocityY = _velocity;
    }

    double getTotalCurrentExhaustVelocity() {
        double totalCurrentExhaustVelocity = 0;
        for (RocketStage* stage : stages) {
            for (Engine* engine : stage->getEngines()) {
                totalCurrentExhaustVelocity += engine->getCurrentExhaustVelocity();
            }
        }
        return totalCurrentExhaustVelocity;
    }

    double getTotalCurrentMassFlowRate() {
        double totalCurrentMassFlowRate = 0;
        for (RocketStage* stage : stages) {
            for (Engine* engine : stage->getEngines()) {
                totalCurrentMassFlowRate += engine->getCurrentMassFlowRate();
            }
        }
        return totalCurrentMassFlowRate;
    }

    void burnFuel(double seconds) {
        for (auto stage : stages) {
            stage->burnFuel(seconds);
        }
    }

    [[nodiscard]] double getAltitude() const {
        return altitude;
    }

    double calcTotalMass() {
        double totalMass = 0;
        for (auto stage : stages) {
            totalMass += stage->calcTotalMass();
        }
        return totalMass;
    }

    double getFuelMass() {
        double totalFuelMass = 0;
        for (auto stage : stages) {
            totalFuelMass += stage->getFuelAmount();
        }
        return totalFuelMass;
    }

    double getEnginesMaxThrust() {
        double maxThrust = 0;
        for (auto stage : stages) {
            maxThrust += stage->getEnginesMaxThrust();
        }
        return maxThrust;
    }

    double getEnginesCurrentThrust() {
        double currentThrust = 0;
        for (auto stage : stages) {
            currentThrust += stage->getEnginesCurrentThrust();
        }
        return currentThrust;
    }


};

#endif //ABSTRACTPROGRAMMINGPROJECT_OUT_ROCKET_H
