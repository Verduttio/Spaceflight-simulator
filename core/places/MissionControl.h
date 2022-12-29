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

class MissionControl {
    static constexpr double GRAVITATIONAL_CONSTANT = 6.67408e-11;  // in m^3 kg^-1 s^-2
    Rocket* rocket;
    Planet* planet;
public:
    MissionControl() = default;

    double calcGravityForce() {
        return (GRAVITATIONAL_CONSTANT * planet->getMass())/pow((planet->getRadius() + rocket->getAltitude()), 2);
    }

    void setEnginePower(Engine* engine) {}
    void setRocketAngle(double angle) {}
    void detachStage(RocketStage* rocketStage) {}

    double calcDeltaVelocity(double deltaT, double initialMass, double finalMass) {
        // SpecificImpulse - m/s
        // deltaT - s
        // initialMass - kg
        // finalMass - kg


        auto specificImpulse = rocket->getTotalCurrentSpecificImpulse();
        return (specificImpulse * log(initialMass/finalMass)) - calcGravityForce()*deltaT;
    }

    double calcDeltaDistance(double deltaT, double initialVelocity, double deltaVelocity) {
        // deltaT - s
        // initialVelocity - m/s
        // deltaVelocity - m/s

        double acceleration = deltaVelocity/deltaT;
        return initialVelocity*deltaT + 0.5*acceleration*pow(deltaT, 2);
    }


    void launchRocket() {
        setPowerForAllEngines(100);
        const double deltaT = 1000;  // in ms

        while(true) {
            printRocketTelemetry();

            auto initialMass = rocket->calcTotalMass();
            rocket->burnFuel(deltaT/1000);
            auto finalMass = rocket->calcTotalMass();

            double deltaVelocity = calcDeltaVelocity(deltaT/1000, initialMass, finalMass);
            double deltaDistance = calcDeltaDistance(deltaT/1000, rocket->velocity, deltaVelocity);

            rocket->velocity += deltaVelocity;
            rocket->altitude += deltaDistance;

            std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(deltaT));

        }
    }

    void printRocketTelemetry() {
        std::cout << "Altitude: " << ConversionSI::convertDistanceM_TO_KM(rocket->altitude) << " km" << std::endl;
        std::cout << "Velocity: " << ConversionSI::convertVelocityMS_s_TO_KM_h(rocket->velocity) << " km/h" << std::endl;
        std::cout << "Total mass: " << rocket->calcTotalMass() << " kg" << std::endl;
        std::cout << "Fuel mass: " << rocket->getFuelMass() << " kg" << std::endl;
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
