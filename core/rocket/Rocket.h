//
// Created by Bartek on 2022-12-22.
//

#ifndef ABSTRACTPROGRAMMINGPROJECT_OUT_ROCKET_H
#define ABSTRACTPROGRAMMINGPROJECT_OUT_ROCKET_H

#include "rocketStage/RocketStage.h"

class Rocket {
    std::vector<RocketStage*> stages;
    double angle;  // in degrees [-180, 180]
    double velocity;  // in m/s
    double altitude;  // in m

    friend class Shed;
    friend class MissionControl;
public:
    void setVelocity(double _velocity) {
        this->velocity = _velocity;
    }

    double getTotalCurrentSpecificImpulse() {
        double totalCurrentSpecificImpulse = 0;
        for (RocketStage* stage : stages) {
            for (Engine* engine : stage->getEngines()) {
                totalCurrentSpecificImpulse += engine->getCurrentSpecificImpulse();
            }
        }
        return totalCurrentSpecificImpulse;
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
