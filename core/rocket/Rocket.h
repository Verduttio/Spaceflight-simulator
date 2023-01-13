//
// Created by Bartek on 2022-12-22.
//

#ifndef ABSTRACTPROGRAMMINGPROJECT_OUT_ROCKET_H
#define ABSTRACTPROGRAMMINGPROJECT_OUT_ROCKET_H

#include "rocketStage/RocketStage.h"

class Rocket {
    std::vector<RocketStage*> stages;
    double angle;  // in degrees [-180, 180]
    double velocityR;  // in m/s
    double velocityPhi;  // in m/s
    double accelerationR;  // in m/s^2
    double accelerationPhi;  // in m/s^2

    // These two are used to determine the position of the rocket in space (2-dimensional) by X and Y values (in meters).
    // X and Y values are calculated by transforming the polar coordinates (angle, radius) to cartesian coordinates (X, Y).
    // In our case angle is anglePhi and radius is altitude + planetRadius.
    double altitude;  // in m
    double anglePhi;  // in radians!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    friend class Shed;
    friend class MissionControl;
public:
    void setVelocityR(double _velocity) {
        this->velocityR = _velocity;
    }

    double getTotalCurrentMassFlowRate() {
        double totalCurrentMassFlowRate = 0;
        for (RocketStage* stage : stages) {
            totalCurrentMassFlowRate += stage->getCurrentMassFlowRate();
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

    //TODO: We assume here that all engines have the same power set,
    //      which in the future, might not be true.
    double getEnginesCurrentPower(){
        // Very bad way of doing this, but it is good for now.
        for (auto stage : stages) {
            for (auto engine : stage->getEngines()) {
                return engine->getCurrentPower();
            }
        }
    }

    double getFuelMass() {
        double totalFuelMass = 0;
        for (auto stage : stages) {
            totalFuelMass += stage->getFuelAmount();
        }
        return totalFuelMass;
    }

    double getEnginesCurrentThrust(double gravityAcc) {
        double currentThrust = 0;
        for (auto stage : stages) {
            currentThrust += stage->getEnginesCurrentThrust(gravityAcc);
        }
        return currentThrust;
    }

    double getEnginesMaxThrust(double gravityAcc) {
        double maxThrust = 0;
        for (auto stage : stages) {
            maxThrust += stage->getEnginesMaxThrust(gravityAcc);
        }
        return maxThrust;
    }

    void printInfo() {
        std::cout << "Rocket info:" << std::endl;
        std::cout << "Mass: " << calcTotalMass() << std::endl;
        std::cout << "Fuel mass: " << getFuelMass() << std::endl;
        std::cout << "Thrust/Weight ratio: " << getEnginesMaxThrust(9.81) / (calcTotalMass()*9.81) << std::endl;
    }


};

#endif //ABSTRACTPROGRAMMINGPROJECT_OUT_ROCKET_H
