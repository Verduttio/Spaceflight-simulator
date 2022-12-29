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


    void launchRocket() {
        setPowerForAllEngines(100);
        const double deltaT = 1000;  // in ms
        int flightDuration = 0;
        while(true) {
            std::cout << "#TIME# : " << flightDuration<< " s" << std::endl;
            printRocketTelemetry();

            auto initialMass = rocket->calcTotalMass();
            rocket->burnFuel(deltaT/1000);
            auto finalMass = rocket->calcTotalMass();

            double gravityAcceleration = Physics::calcGravityAcceleration(planet->getMass(), planet->getRadius(), rocket->getAltitude());
            double deltaVelocity = Physics::calcDeltaVelocity(deltaT/1000, initialMass, finalMass, rocket->getTotalCurrentExhaustVelocity(), gravityAcceleration);
            double deltaDistance = Physics::calcDeltaDistance(deltaT/1000, rocket->velocity, deltaVelocity);

            rocket->velocity += deltaVelocity;
            rocket->altitude += deltaDistance;

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
        this->rocket->velocity = 0;
    }

    void setPlanet(Planet* _planet) {
        this->planet = _planet;
    }
};

#endif //ABSTRACTPROGRAMMINGPROJECT_OUT_MISSIONCONTROL_H
