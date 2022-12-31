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
        int flightDuration = 0;
        double maxFuel = rocket->getFuelMass();
        while(true) {
            std::cout << "#TIME# : " << flightDuration<< " s" << std::endl;
            printRocketTelemetry();

            auto initialMass = rocket->calcTotalMass();
            rocket->burnFuel(deltaT/1000);
            auto finalMass = rocket->calcTotalMass();

            double gravityAcceleration = Physics::calcGravityAcceleration(planet->getMass(), planet->getRadius(), rocket->getAltitude());
            double deltaVelocity = Physics::calcDeltaVelocity(deltaT/1000, initialMass, finalMass, rocket->getTotalCurrentExhaustVelocity(), gravityAcceleration);
            double deltaDistance = Physics::calcDeltaDistance(deltaT/1000, rocket->velocity, deltaVelocity);

            std::cout << "Acceleration by velocity: " << Physics::calcAccelerationByVelocity(deltaVelocity, deltaT/1000) << " m/s^2" << std::endl;

            // Calculate rocket acceleration by thrust and weight
            double weight = Physics::calcWeight(rocket->calcTotalMass(), gravityAcceleration);
            double resultantForce = Physics::calcResultantForce(rocket->getEnginesCurrentThrust(), weight);
            std::cout << "Current thrust: " << rocket->getEnginesCurrentThrust() << " N" << std::endl;
            std::cout  << "Weight: " << weight << " N" << std::endl;
            std::cout << "Thrust to weight ratio: " << rocket->getEnginesCurrentThrust() / weight << std::endl;
            std::cout << "Resultant force: " << resultantForce << " N" << std::endl;
            double acceleration = Physics::calcAccelerationByForce(resultantForce, rocket->calcTotalMass());
            std::cout << "Acceleration by thrust: " << acceleration << " m/s^2" << std::endl;
            std::cout << "Fuel amount in %: " << rocket->getFuelMass() / maxFuel * 100 << " % " << std::endl;

            std::cout << "----------------------------------------" << std::endl;
            //            rocket->altitude += deltaDistance;
            rocket->altitude += rocket->velocity * deltaT/1000 + 0.5 * acceleration * pow(deltaT/1000, 2);
//            rocket->velocity += deltaVelocity;
            rocket->velocity += acceleration * deltaT/1000;



            std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(deltaT));
            flightDuration++;

        }
    }

    void printRocketTelemetry() {
        std::cout << "Altitude: " << ConversionSI::convertDistanceM_TO_KM(rocket->altitude) << " km" <<
                    " | " << rocket->altitude << " m " << std::endl;
        std::cout << "Velocity: " << ConversionSI::convertVelocityMS_s_TO_KM_h(rocket->velocity) << " km/h" <<
                    " | " << rocket->velocity << " m/s" << std::endl;
        std::cout << "Total mass: " << rocket->calcTotalMass() << " kg" << std::endl;
        std::cout << "Fuel mass: " << rocket->getFuelMass() << " kg" << std::endl;
        std::cout << "Current exhaust velocity: " << rocket->getTotalCurrentExhaustVelocity() << " m/s" << std::endl;
        std::cout << "Current mass flow rate: " << rocket->getTotalCurrentMassFlowRate() << " kg/s" << std::endl;
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
        this->rocket->velocity = 0;
    }

    void setPlanet(Planet* _planet) {
        this->planet = _planet;
    }
};

#endif //ABSTRACTPROGRAMMINGPROJECT_OUT_MISSIONCONTROL_H
