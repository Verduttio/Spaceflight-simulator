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
#include <fstream>
#include <iomanip>

class MissionControl {
    Rocket* rocket;
    Planet* planet;
public:
    MissionControl() {
        rocket = nullptr;
        planet = nullptr;
    };

    void setEnginePower(Engine* engine) {}
    void setRocketAngle(double angle) {}
    void detachStage(RocketStage* rocketStage) {}


    void launchRocket() {
        setPowerForAllEngines(100);
        const double deltaT = 1000;  // in ms
        const double deltaTSeconds = deltaT / 1000.0;
        double flightDuration = 0;
        double maxFuel = rocket->getFuelMass();
        double accelerationR = 0;
        double accelerationPhi = 0;
        double deltaPhi = 0;
        while(flightDuration < 72000) {
            double gravityAcc = Physics::calcGravityAcceleration(planet->getMass(), planet->getRadius(), rocket->getAltitude());
            double enginesCurrentThrust = rocket->getEnginesCurrentThrust(gravityAcc);
            std::cout << "#TIME# : " << flightDuration<< " s" << std::endl;
//            printRocketTelemetry(accelerationPhi, accelerationR, maxFuel, gravityAcc);
            std::cout << "Altitude: " << rocket->altitude << " m" << std::endl;
            std::cout << "Velocity: " << rocket->velocityR << " m/s" << std::endl;


            auto initialMass = rocket->calcTotalMass();
            rocket->burnFuel(deltaTSeconds);
            auto finalMass = rocket->calcTotalMass();


            double centrifugalForce = Physics::calcCentrifugalForce(rocket->velocityPhi, rocket->calcTotalMass(), deltaPhi, deltaTSeconds);

            rocket->velocityR += Physics::calcDeltaVelocityInUniformlyAcceleratedMotion(accelerationR, deltaTSeconds);
            rocket->velocityPhi += Physics::calcDeltaVelocityInUniformlyAcceleratedMotion(accelerationPhi, deltaTSeconds);


            double gravityForce = gravityAcc * rocket->calcTotalMass();
            double forceR = Physics::calcForceR(enginesCurrentThrust, rocket->angle, centrifugalForce, gravityForce);
            double forcePhi = Physics::calcForcePhi(enginesCurrentThrust, rocket->angle, centrifugalForce);


            accelerationPhi = Physics::calcAccelerationByForce(forcePhi, rocket->calcTotalMass());
            accelerationR = Physics::calcAccelerationByForce(forceR, rocket->calcTotalMass());


            rocket->altitude += Physics::calcDeltaDistanceInUniformlyAcceleratedMotion(rocket->velocityR, accelerationR, deltaTSeconds);

            double deltaDistancePhi = Physics::calcDeltaDistanceInUniformlyAcceleratedMotion(rocket->velocityPhi, accelerationPhi, deltaTSeconds);
//            deltaPhi = asin(deltaDistancePhi / getAbsoluteRocketAltitude());  // in radians
            deltaPhi = deltaDistancePhi / getAbsoluteRocketAltitude();  // in radians
            rocket->anglePhi += deltaPhi;


            // For output data
            double x = getAbsoluteRocketAltitude()/1000.0 * sin(rocket->anglePhi);
            double y = getAbsoluteRocketAltitude()/1000.0 * cos(rocket->anglePhi);


            std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(deltaT));
            flightDuration += deltaTSeconds;
        }
    }

    void launchRocketSimulation() {
        std::ofstream rocketPositionFile;
        rocketPositionFile.open("rocketPosition.txt");


        this->rocket->altitude=300000;   // m
        this->rocket->velocityPhi=7734.2;   // m/s     // between 7734.2 a 7734.3
        this->rocket->angle = 90;   // 90 degrees
//        setPowerForAllEngines(100);


        const double deltaT = 1000;  // in ms
        const double deltaTSeconds = deltaT / 1000.0;
        double flightDuration = 0;
        double maxFuel = rocket->getFuelMass();
        double accelerationR = 0;
        double accelerationPhi = 0;
        double deltaPhi = 0;
        while(flightDuration < 72000) {
            double gravityAcc = Physics::calcGravityAcceleration(planet->getMass(), planet->getRadius(), rocket->getAltitude());
            double enginesCurrentThrust = rocket->getEnginesCurrentThrust(gravityAcc);
//            std::cout << "#TIME# : " << flightDuration<< " s" << std::endl;
//            printRocketTelemetry(accelerationPhi, accelerationR, maxFuel, gravityAcc);



            auto initialMass = rocket->calcTotalMass();
            rocket->burnFuel(deltaTSeconds);
            auto finalMass = rocket->calcTotalMass();


            double centrifugalForce = Physics::calcCentrifugalForce(rocket->velocityPhi, rocket->calcTotalMass(), deltaPhi, deltaTSeconds);

            rocket->velocityR += Physics::calcDeltaVelocityInUniformlyAcceleratedMotion(accelerationR, deltaTSeconds);
            rocket->velocityPhi += Physics::calcDeltaVelocityInUniformlyAcceleratedMotion(accelerationPhi, deltaTSeconds);


            double gravityForce = gravityAcc * rocket->calcTotalMass();
            double forceR = Physics::calcForceR(enginesCurrentThrust, rocket->angle, centrifugalForce, gravityForce);
            double forcePhi = Physics::calcForcePhi(enginesCurrentThrust, rocket->angle, centrifugalForce);


            accelerationPhi = Physics::calcAccelerationByForce(forcePhi, rocket->calcTotalMass());
            accelerationR = Physics::calcAccelerationByForce(forceR, rocket->calcTotalMass());


            rocket->altitude += Physics::calcDeltaDistanceInUniformlyAcceleratedMotion(rocket->velocityR, accelerationR, deltaTSeconds);

            double deltaDistancePhi = Physics::calcDeltaDistanceInUniformlyAcceleratedMotion(rocket->velocityPhi, accelerationPhi, deltaTSeconds);
//            deltaPhi = asin(deltaDistancePhi / getAbsoluteRocketAltitude());  // in radians
            deltaPhi = deltaDistancePhi / getAbsoluteRocketAltitude();  // in radians
            rocket->anglePhi += deltaPhi;


            // For output data
            double x = getAbsoluteRocketAltitude()/1000.0 * sin(rocket->anglePhi);
            double y = getAbsoluteRocketAltitude()/1000.0 * cos(rocket->anglePhi);
            rocketPositionFile << flightDuration << "|" << x << "|" << y << "|" << getAbsoluteRocketAltitude() << "|" << enginesCurrentThrust << "|" << rocket->velocityPhi << "|" << rocket->velocityR << "|" << accelerationR << "|" << gravityAcc << "|" << gravityForce << "|" << centrifugalForce << "|" << forceR << "|" << forcePhi << "|" << deltaDistancePhi << "|" << deltaPhi << "|" << rocket->angle << "|" << Physics::convertDegreesToRadians(rocket->angle) << std::endl;
//            if(flightDuration < 10) {
//                std::cout << "flightDuration: " << flightDuration << std::endl;
//                std::cout << std::setprecision(20);
//                std::cout << "centr force: " << centrifugalForce << ", d_fi: " << deltaPhi << ", v_phi: " << rocket->velocityPhi << ", deltaTSeconds: " << deltaTSeconds << std::endl;
//            }


//            std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(deltaT));
            flightDuration += deltaTSeconds;
//            if(flightDuration == 10) {
//                rocket->angle = 5;
//            } else if (flightDuration == 20) {
//                rocket->angle = 10;
//            } else if (flightDuration == 30) {
//                rocket->angle = 20;
//            } else if (flightDuration == 40) {
//                rocket->angle = 30;
//            } else if (flightDuration == 50){
//                rocket->angle = 45;
//            } else if (flightDuration == 64) {
////                rocket->angle = 60;
//            } else if (flightDuration == 82) {
//                rocket->angle = 60;
//            } else if (flightDuration == 100) {
////                setPowerForAllEngines(0);
//            } else if (flightDuration == 120) {
//                rocket->angle = 75;
////                setPowerForAllEngines(100);
//            } else if (flightDuration == 265) {   //268
////                setPowerForAllEngines(0);
//            }
        }
        rocketPositionFile.close();
    }

    void printRocketTelemetry(double accelerationPhi, double accelerationR, double maxFuel, double gravityAcc) {
        std::cout << "Altitude (R == position Y): " << ConversionSI::convertDistanceM_TO_KM(rocket->altitude) << " km" <<
                    " | " << rocket->altitude << " m " << std::endl;
        std::cout << "AnglePhi: " << rocket->anglePhi << " rad" << std::endl;
        std::cout << "Rocket angle (alfa): " << rocket->angle << " deg" << std::endl;
        std::cout << "***" << std::endl;
        std::cout << "Velocity R: " << ConversionSI::convertVelocityMS_s_TO_KM_h(rocket->velocityR) << " km/h" <<
                    " | " << rocket->velocityR << " m/s" << std::endl;
        std::cout << "Velocity Phi: " << ConversionSI::convertVelocityMS_s_TO_KM_h(rocket->velocityPhi) << " km/h" <<
                    " | " << rocket->velocityPhi << " m/s" << std::endl;
        std::cout << "Velocity overall: " << ConversionSI::convertVelocityMS_s_TO_KM_h(Physics::calcOverallVelocity(rocket->velocityPhi, rocket->velocityR)) << " km/h" <<
                  " | " << (Physics::calcOverallVelocity(rocket->velocityPhi, rocket->velocityR)) << " m/s" << std::endl;
        std::cout << "Acceleration R: " << accelerationR << " m/s^2" << std::endl;
        std::cout << "Acceleration Phi: " << accelerationPhi << " m/s^2" << std::endl;
//        std::cout << "Centrifugal acc: " << Physics::calcCentrifugalAcceleration(rocket->velocityPhi, getAbsoluteRocketAltitude()) << " m/s^2" << std::endl;
        std::cout << "Gravity acc: " << Physics::calcGravityAcceleration(planet->getMass(), planet->getRadius(), rocket->getAltitude()) << " m/s^2" << std::endl;
        std::cout << "***" << std::endl;

        std::cout << "Current mass flow rate: " << rocket->getTotalCurrentMassFlowRate() << " kg/s" << std::endl;
        // We assume that all engines have the same power! It is bad, because in the future it will not be like that.
        std::cout << "Current engines power: " << rocket->getEnginesCurrentPower() << " %" << std::endl;
        std::cout << "Current thrust: " << rocket->getEnginesCurrentThrust(gravityAcc) << " N" << std::endl;
        auto rocketWeight = Physics::calcWeight(rocket->calcTotalMass(), Physics::calcGravityAcceleration(planet->getMass(), planet->getRadius(), rocket->altitude));
        std::cout << "Weight rocket: " << rocketWeight << " N" << std::endl;
        std::cout << "Thrust to weight ratio [correct only when angle = 0]: " << rocket->getEnginesCurrentThrust(gravityAcc) / rocketWeight << std::endl;
        std::cout << "***" << std::endl;

        std::cout << "Total mass: " << rocket->calcTotalMass() << " kg" << std::endl;
        std::cout << "Fuel mass: " << rocket->getFuelMass() << " kg" << std::endl;
        std::cout << "Fuel amount: " << rocket->getFuelMass() / maxFuel * 100 << " % " << std::endl;
        std::cout << "----------------------------------------" << std::endl;
    }

    double getAbsoluteRocketAltitude() {
        // Altitude is relative to planet's surface, so we need to add planet's radius to get absolute altitude
        return planet->getRadius() + rocket->altitude;
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
        this->rocket->anglePhi = 0;
        this->rocket->velocityR = 0;
        this->rocket->velocityPhi= 0;
    }

    void setPlanet(Planet* _planet) {
        this->planet = _planet;
    }
};

#endif //ABSTRACTPROGRAMMINGPROJECT_OUT_MISSIONCONTROL_H
