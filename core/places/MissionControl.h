//
// Created by Bartek on 2022-12-22.
//

#ifndef ABSTRACTPROGRAMMINGPROJECT_OUT_MISSIONCONTROL_H
#define ABSTRACTPROGRAMMINGPROJECT_OUT_MISSIONCONTROL_H

#include "../planet/Planet.h"
#include "../rocket/Rocket.h"
#include <cmath>
#include <thread>
#include <chrono>
#include "../../tools/ConversionsSI.h"
#include "../../tools/Physics.h"

class MissionControl {
    Rocket* rocket;
    Planet* planet;
public:
    MissionControl() = default;

    void setEnginePower(Engine* engine) {}
    void setRocketAngle(double angle) {}
    void detachStage(RocketStage* rocketStage) {}


    [[noreturn]] void launchRocket() {
        setPowerForAllEngines(100);
        const double deltaT = 1000;  // in ms
        const int deltaTSeconds = deltaT / 1000;
        int flightDuration = 0;
        double maxFuel = rocket->getFuelMass();
        double accelerationX = 0;
        double accelerationY = 0;
        while(true) {
            std::cout << "#TIME# : " << flightDuration<< " s" << std::endl;
            printRocketTelemetry(accelerationX, accelerationY, maxFuel);

            auto initialMass = rocket->calcTotalMass();
            rocket->burnFuel(deltaTSeconds);
            auto finalMass = rocket->calcTotalMass();

            // Old type of calculation acceleration
//            double gravityAcceleration = Physics::calcGravityAcceleration(planet->getMass(), planet->getRadius(), rocket->getAltitude());
//            double deltaVelocity = Physics::calcDeltaVelocity(deltaTSeconds, initialMass, finalMass, rocket->getTotalCurrentExhaustVelocity(), gravityAcceleration);
//            std::cout << "Acceleration by velocity: " << Physics::calcAccelerationByVelocity(deltaVelocity, deltaTSeconds) << " m/s^2" << std::endl;


            // Calculate rocket acceleration by thrust and weight - new type of calculation
//            double weight = Physics::calcWeight(rocket->calcTotalMass(), gravityAcceleration);
            accelerationY = Physics::calcAccelerationYaxisByForce(rocket->getEnginesCurrentThrust(), rocket->angle, rocket->calcTotalMass(), rocket->altitude);
            accelerationX = Physics::calcAccelerationXaxisByForce(rocket->getEnginesCurrentThrust(), rocket->angle, rocket->calcTotalMass());

            rocket->altitude += Physics::calcDeltaDistanceInUniformlyAcceleratedMotion(rocket->velocityY, accelerationY, deltaTSeconds);
            rocket->velocityY += Physics::calcDeltaVelocityInUniformlyAcceleratedMotion(accelerationY, deltaTSeconds);
            rocket->velocityX += Physics::calcDeltaVelocityInUniformlyAcceleratedMotion(accelerationX, deltaTSeconds);

            std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(deltaT));
            flightDuration++;
            if(flightDuration == 10) {
                setPowerForAllEngines(60);
//                rocket->angle = -80;
            } else if (flightDuration == 20) {
//                rocket->angle = 30;
            }
        }
    }

    void printRocketTelemetry(double accelerationX, double accelerationY, double maxFuel) {
        std::cout << "Altitude: " << ConversionSI::convertDistanceM_TO_KM(rocket->altitude) << " km" <<
                    " | " << rocket->altitude << " m " << std::endl;
        std::cout << "Angle: " << rocket->angle << " deg" << std::endl;

        std::cout << "***" << std::endl;
        std::cout << "Velocity Y-axis: " << ConversionSI::convertVelocityMS_s_TO_KM_h(rocket->velocityY) << " km/h" <<
                    " | " << rocket->velocityY << " m/s" << std::endl;
        std::cout << "Velocity X-axis: " << ConversionSI::convertVelocityMS_s_TO_KM_h(rocket->velocityX) << " km/h" <<
                    " | " << rocket->velocityX << " m/s" << std::endl;
        std::cout << "Velocity overall: " << ConversionSI::convertVelocityMS_s_TO_KM_h(Physics::calcVelocityBothAxes(rocket->velocityX, rocket->velocityY)) << " km/h" <<
                  " | " << (Physics::calcVelocityBothAxes(rocket->velocityX, rocket->velocityY)) << " m/s" << std::endl;
        std::cout << "Acceleration by thrust Y-axis: " << accelerationY << " m/s^2" << std::endl;
        std::cout << "Acceleration by thrust X-axis: " << accelerationX << " m/s^2" << std::endl;
        std::cout << "***" << std::endl;

        std::cout << "Current exhaust velocity: " << rocket->getTotalCurrentExhaustVelocity() << " m/s" << std::endl;
        std::cout << "Current mass flow rate: " << rocket->getTotalCurrentMassFlowRate() << " kg/s" << std::endl;
        // We assume that all engines have the same power! It is bad, because in the future it will not be like that.
        std::cout << "Current engines power: " << rocket->getEnginesCurrentPower() << " %" << std::endl;
        std::cout << "Current thrust: " << rocket->getEnginesCurrentThrust() << " N" << std::endl;
        auto rocketWeight = Physics::calcWeight(rocket->calcTotalMass(), Physics::calcGravityAcceleration(planet->getMass(), planet->getRadius(), rocket->altitude));
        std::cout << "Weight rocket: " << rocketWeight << " N" << std::endl;
        std::cout << "Thrust to weight ratio [only Y-axis, correct only when angle = 0]: " << rocket->getEnginesCurrentThrust() / rocketWeight << std::endl;
        std::cout << "***" << std::endl;

        std::cout << "Total mass: " << rocket->calcTotalMass() << " kg" << std::endl;
        std::cout << "Fuel mass: " << rocket->getFuelMass() << " kg" << std::endl;
        std::cout << "Fuel amount: " << rocket->getFuelMass() / maxFuel * 100 << " % " << std::endl;
        std::cout << "----------------------------------------" << std::endl;
    }

    void setPowerForAllEngines(int power) {
        for (auto stage : rocket->stages) {
            for (auto engine : stage->getEngines()) {
                engine->setCurrentPower(power);
            }
        }
    }

    void setRocket(Rocket* _rocket) {
        this->rocket = _rocket;
        this->rocket->angle = 0;
        this->rocket->altitude = 0;
        this->rocket->velocityY = 0;
        this->rocket->velocityX = 0;
    }

    void setPlanet(Planet* _planet) {
        this->planet = _planet;
    }
};

#endif //ABSTRACTPROGRAMMINGPROJECT_OUT_MISSIONCONTROL_H
