//
// Created by Bartek on 2022-12-29.
//

#ifndef ABSTRACTPROGRAMMINGPROJECT_OUT_PHYSICS_H
#define ABSTRACTPROGRAMMINGPROJECT_OUT_PHYSICS_H
#include <cmath>

class Physics {
public:
    static constexpr double GRAVITATIONAL_CONSTANT = 6.67408e-11;  // in m^3 kg^-1 s^-2
    static constexpr double EARTH_MASS = 5.97219e24;  // in kg
    static constexpr double EARTH_RADIUS = 6371000;  // in m
    static constexpr double PI = 3.14159265358979323846;


    static double calcGravityAcceleration(double planetMass, double planetRadius, double rocketAltitude) {
        return (GRAVITATIONAL_CONSTANT * planetMass)/pow((planetRadius + rocketAltitude), 2);
    }

    static double calcAccelerationByVelocity(double deltaVelocity, double deltaT) {
        return deltaVelocity / deltaT;
    }

    static double calcWeight(double rocketMass, double gravityAcceleration) {
        return rocketMass * gravityAcceleration;
    }

    static double calcResultantForce(double thrust, double weight) {
        return thrust - weight;
    }

    static double calcAccelerationByForce(double force, double mass) {
        return force / mass;
    }

    static double calcForce(double mass, double acceleration) {
        return mass * acceleration;
    }

    static double convertDegreesToRadians(double degrees) {
        return degrees * PI / 180;
    }

    static double calcForcePhi (double thrust, double rocketAngle, double centrifugalForce) {
        return thrust*sin(convertDegreesToRadians(rocketAngle)) - centrifugalForce*cos(convertDegreesToRadians(rocketAngle));
    }

    static double calcForceR (double thrust, double rocketAngle, double centrifugalForce, double gravityForce) {
        return thrust*cos(convertDegreesToRadians(rocketAngle)) - gravityForce + centrifugalForce*sin(convertDegreesToRadians(rocketAngle));
    }

    static double calcOverallVelocity(double velocityX, double VelocityY) {
        return sqrt(pow(velocityX, 2) + pow(VelocityY, 2));
    }

    static double calcDeltaVelocityInUniformlyAcceleratedMotion(double acceleration, double deltaT) {
        return acceleration * deltaT;
    }

    static double calcDeltaDistanceInUniformlyAcceleratedMotion(double initialVelocity, double acceleration, double deltaT) {
        return initialVelocity * deltaT + 0.5 * acceleration * pow(deltaT, 2);
    }

    static double calcCentrifugalForceOld(double mass, double velocity, double radius) {
        // https://en.wikipedia.org/wiki/Centrifugal_force
        // Fc = m * v^2 / r
        return mass * pow(velocity, 2) / radius;
    }

    static double calcCentrifugalForce(double velocityPhiPrevious, double mass, double deltaPhiAnglePrevious, double deltaT) {
        return velocityPhiPrevious*sin(deltaPhiAnglePrevious)/deltaT*mass;
    }
};

#endif //ABSTRACTPROGRAMMINGPROJECT_OUT_PHYSICS_H
