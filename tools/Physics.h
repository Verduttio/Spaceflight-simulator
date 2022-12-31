//
// Created by Bartek on 2022-12-29.
//

#ifndef ABSTRACTPROGRAMMINGPROJECT_OUT_PHYSICS_H
#define ABSTRACTPROGRAMMINGPROJECT_OUT_PHYSICS_H
#include <cmath>

class Physics {
public:
    static constexpr double GRAVITATIONAL_CONSTANT = 6.67408e-11;  // in m^3 kg^-1 s^-2

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
};

#endif //ABSTRACTPROGRAMMINGPROJECT_OUT_PHYSICS_H
