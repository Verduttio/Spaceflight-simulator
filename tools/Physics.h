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

    static double calcDeltaVelocity(double deltaT, double initialMass, double finalMass, double exhaustVelocity,
                             double gravityAcceleration) {
        // SpecificImpulse - m/s
        // deltaT - s
        // initialMass - kg
        // finalMass - kg
        // exhaustVelocity - m/s
        // gravityAcceleration - m/s^2

        return (exhaustVelocity * log(initialMass / finalMass)) - gravityAcceleration * deltaT;
    }

    static double calcDeltaDistance(double deltaT, double initialVelocity, double deltaVelocity) {
        // deltaT - s
        // initialVelocity - m/s
        // deltaVelocity - m/s

        double acceleration = deltaVelocity / deltaT;
        return initialVelocity * deltaT + 0.5 * acceleration * pow(deltaT, 2);
    }

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

    static double calcAccelerationYaxisByForce(double thrust, double angle, double mass, double rocketAltitude) {
        // Gravity force is included (computed by mass and rocketAltitude)

        // The angle determines the direction of the force
        // The angle is measured from the vertical axis
        // The angle is measured in degrees

        // The angle range is [-180, 180].
        // Right side has positive values and left side has negative values.
        // Example:
        // ---->  is 90 degrees
        // <----  is -90 degrees
        // ^
        // |
        // | is 0 degrees

        // |
        // v is 180 degrees


        // Tested in degrees [0, 90]
        double thrustY = cos(convertDegreesToRadians(angle)) * thrust;
        double gravityForce = mass * calcGravityAcceleration(EARTH_MASS, EARTH_RADIUS, rocketAltitude);
        return (thrustY - gravityForce) / mass;
    }

    static double convertDegreesToRadians(double degrees) {
        return degrees * PI / 180;
    }

    static double calcAccelerationXaxisByForce(double thrust, double angle, double mass) {
        // We do not need to include gravity force because it is always perpendicular to the rocket's direction

        // The angle determines the direction of the force
        // The angle is measured from the vertical axis
        // The angle is measured in degrees

        // The angle range is [-180, 180].
        // Right side has positive values and left side has negative values.
        // Example:
        // ---->  is 90 degrees
        // <----  is -90 degrees
        // ^
        // |
        // | is 0 degrees

        // |
        // v is 180 degrees


        // Tested in degrees [0, 90]
        double thrustX = sin(convertDegreesToRadians(angle)) * thrust;
        return thrustX / mass;
    }

    static double calcVelocityBothAxes(double velocityX, double VelocityY) {
        return sqrt(pow(velocityX, 2) + pow(VelocityY, 2));
    }

    static double calcDeltaVelocityInUniformlyAcceleratedMotion(double acceleration, double deltaT) {
        return acceleration * deltaT;
    }

    static double calcDeltaDistanceInUniformlyAcceleratedMotion(double initialVelocity, double acceleration, double deltaT) {
        return initialVelocity * deltaT + 0.5 * acceleration * pow(deltaT, 2);
    }
};

#endif //ABSTRACTPROGRAMMINGPROJECT_OUT_PHYSICS_H
