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
    double fuelMassAtStart;
    double deltaT_ms;
    double flightDuration;
    double gravityAcc;
    double enginesCurrentThrust;
    double gravityForce;
    double centrifugalForce;
    double forceR;
    double forcePhi;
    double xPosition;
    double yPosition;


public:
    MissionControl() {
        rocket = nullptr;
        planet = nullptr;
    };

    void setRocketAngle(double angle) {}
    void detachStage(RocketStage* rocketStage) {}

    void rocketFlightLogic(double deltaT_s, double& deltaPhi) {
        gravityAcc = Physics::calcGravityAcceleration(planet->getMass(), planet->getRadius(), rocket->getAltitude());
        enginesCurrentThrust = rocket->getEnginesCurrentThrust(gravityAcc);


        centrifugalForce = Physics::calcCentrifugalForce(rocket->velocityPhi, rocket->calcTotalMass(), deltaPhi, deltaT_s);

        rocket->velocityR += Physics::calcDeltaVelocityInUniformlyAcceleratedMotion(rocket->accelerationR, deltaT_s);
        rocket->velocityPhi += Physics::calcDeltaVelocityInUniformlyAcceleratedMotion(rocket->accelerationPhi, deltaT_s);


        gravityForce = Physics::calcForce(gravityAcc, rocket->calcTotalMass());
        forceR = Physics::calcForceR(enginesCurrentThrust, rocket->angle, centrifugalForce, gravityForce);
        forcePhi = Physics::calcForcePhi(enginesCurrentThrust, rocket->angle, centrifugalForce);


        rocket->accelerationPhi = Physics::calcAccelerationByForce(forcePhi, rocket->calcTotalMass());
        rocket->accelerationR = Physics::calcAccelerationByForce(forceR, rocket->calcTotalMass());


        rocket->altitude += Physics::calcDeltaDistanceInUniformlyAcceleratedMotion(rocket->velocityR, rocket->accelerationR, deltaT_s);

        double deltaDistancePhi = Physics::calcDeltaDistanceInUniformlyAcceleratedMotion(rocket->velocityPhi, rocket->accelerationPhi, deltaT_s);
        deltaPhi = asin(deltaDistancePhi / getAbsoluteRocketAltitude());  // in radians
//            deltaPhi = deltaDistancePhi / getAbsoluteRocketAltitude();  // in radians
        rocket->anglePhi += deltaPhi;

        rocket->burnFuel(deltaT_s);
        flightDuration += deltaT_s;
    }


    void launchRocket() {
        const double deltaT_s = ConversionSI::convertTimeMS_TO_S(deltaT_ms);
        double deltaPhi = 0;
        setPowerForAllEngines(100);
        while(flightDuration < 72000) {
            printRocketTelemetry();

            rocketFlightLogic(deltaT_s, deltaPhi);

            std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(deltaT_ms));
        }
    }

    void launchRocketSimulation() {
        std::ofstream rocketPositionFile;
        rocketPositionFile.open("rocketPosition.txt");

        // init data
        this->rocket->altitude=300000;   // m
        this->rocket->velocityPhi=7734.2;   // m/s     // between 7734.2 a 7734.3
        this->rocket->angle = 90;   // 90 degrees
//        setPowerForAllEngines(100);
        // init data - end

        const double deltaT_s = ConversionSI::convertTimeMS_TO_S(deltaT_ms);
        double deltaPhi = 0;
        while(flightDuration < 72000) {
            rocketFlightLogic(deltaT_s, deltaPhi);

            // For output data
            xPosition = getAbsoluteRocketAltitude()/1000.0 * sin(rocket->anglePhi);
            yPosition = getAbsoluteRocketAltitude()/1000.0 * cos(rocket->anglePhi);
            rocketPositionFile << flightDuration << "|" << xPosition << "|" << yPosition << "|" << getAbsoluteRocketAltitude() << "|" << enginesCurrentThrust << "|" << rocket->velocityPhi << "|" << rocket->velocityR << "|" << rocket->accelerationR << "|" << gravityAcc << "|" << gravityForce << "|" << centrifugalForce << "|" << forceR << "|" << forcePhi << "|" << rocket->angle << "|" << Physics::convertDegreesToRadians(rocket->angle) << std::endl;
        }
        rocketPositionFile.close();
    }

    void printRocketTelemetry() {
        std::cout << "#################TIME############# : " << flightDuration<< " s" << std::endl;

        std::cout << "--------------Position---------------" << std::endl;
        std::cout << "Altitude: " << ConversionSI::convertDistanceM_TO_KM(rocket->altitude) << " km" <<
                    " | " << rocket->altitude << " m " << std::endl;
        std::cout << "Total altitude (R): " << ConversionSI::convertDistanceM_TO_KM(getAbsoluteRocketAltitude()) << " km" <<
                    " | " << getAbsoluteRocketAltitude() << " m " << std::endl;
        std::cout << "Rocket angle (alfa): " << rocket->angle << " deg" << std::endl;
        std::cout << "AnglePhi: " << rocket->anglePhi << " rad" << std::endl;

        std::cout << "--------------Movement---------------" << std::endl;
        std::cout << "Velocity R: " << ConversionSI::convertVelocityMS_s_TO_KM_h(rocket->velocityR) << " km/h" <<
                    " | " << rocket->velocityR << " m/s" << std::endl;
        std::cout << "Velocity Phi: " << ConversionSI::convertVelocityMS_s_TO_KM_h(rocket->velocityPhi) << " km/h" <<
                    " | " << rocket->velocityPhi << " m/s" << std::endl;
        std::cout << "Velocity overall: " << ConversionSI::convertVelocityMS_s_TO_KM_h(Physics::calcOverallVelocity(rocket->velocityPhi, rocket->velocityR)) << " km/h" <<
                  " | " << (Physics::calcOverallVelocity(rocket->velocityPhi, rocket->velocityR)) << " m/s" << std::endl;
        std::cout << "Acceleration R: " << rocket->accelerationR << " m/s^2" << std::endl;
        std::cout << "Acceleration Phi: " << rocket->accelerationPhi << " m/s^2" << std::endl;
        std::cout << "Acceleration gravity: " << gravityAcc << " m/s^2" << std::endl;

        std::cout << "--------------Forces-----------------" << std::endl;
        std::cout << "Gravity force: " << gravityForce << " N" << std::endl;
        std::cout << "Centrifugal force: " << centrifugalForce << " N" << std::endl;
        std::cout << "Thrust: " << enginesCurrentThrust << " N" << std::endl;
        std::cout << "Force R: " << forceR << " N" << std::endl;
        std::cout << "Force Phi: " << forcePhi << " N" << std::endl;

        std::cout << "--------------Engines----------------" << std::endl;
        std::cout << "Current engines power: " << rocket->getEnginesCurrentPower() << " %" << std::endl;  // We assume that all engines work under the same power! It is bad, because in the future it will not be like that, but for now it is ok.
        std::cout << "Current mass flow rate: " << rocket->getTotalCurrentMassFlowRate() << " kg/s" << std::endl;
        if (rocket->angle == 0) std::cout << "Thrust to weight ratio: " << rocket->getEnginesCurrentThrust(gravityAcc) / gravityForce << std::endl;

        std::cout << "----------------Mass-----------------" << std::endl;
        std::cout << "Total mass: " << rocket->calcTotalMass() << " kg" << std::endl;
        std::cout << "Fuel mass: " << rocket->getFuelMass() << " kg" << std::endl;
        std::cout << "Fuel amount: " << rocket->getFuelMass() / fuelMassAtStart * 100 << " % " << std::endl;
        std::cout << "#####################################" << std::endl << std::endl;
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

    void setMissionControl(double _deltaT_ms) {
        if(rocket == nullptr) {
            std::cout << "Cannot set mission control because there is no rocket in mission control!" << std::endl;
            return;
        }
        this->deltaT_ms = _deltaT_ms;
        this->flightDuration = 0;
        this->gravityAcc = 0;
        this->enginesCurrentThrust = 0;
        this->gravityForce = 0;
        this->centrifugalForce = 0;
        this->forceR = 0;
        this->forcePhi = 0;

        this->fuelMassAtStart = rocket->getFuelMass();
    }

    void setRocket(Rocket* _rocket) {
        this->rocket = _rocket;
        this->rocket->angle = 0;
        this->rocket->altitude = 0;
        this->rocket->anglePhi = 0;
        this->rocket->velocityR = 0;
        this->rocket->velocityPhi= 0;
        this->rocket->accelerationPhi = 0;
        this->rocket->accelerationR = 0;
    }

    void setPlanet(Planet* _planet) {
        this->planet = _planet;
    }
};

#endif //ABSTRACTPROGRAMMINGPROJECT_OUT_MISSIONCONTROL_H
