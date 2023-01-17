//
// Created by Bartek on 2022-12-22.
//

#ifndef ABSTRACTPROGRAMMINGPROJECT_OUT_PLANET_H
#define ABSTRACTPROGRAMMINGPROJECT_OUT_PLANET_H
#include "Atmosphere.h"

class Planet {
    Atmosphere atmosphere;
    double mass;    // in kg
    double radius;  // in m

public:
    explicit Planet(double _mass, double _radius) : mass(_mass), radius(_radius) {}

    void setMass(double _mass) {
        this->mass = _mass;
    }

    [[nodiscard]] double getMass() const {
        return mass;
    }

    void setRadius(double _radius) {
        this->radius = _radius;
    }

    [[nodiscard]] double getRadius() const {
        return radius;
    }

};

#endif //ABSTRACTPROGRAMMINGPROJECT_OUT_PLANET_H
