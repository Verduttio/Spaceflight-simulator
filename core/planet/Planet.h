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

private:
    constexpr double angleDelta(size_t numberOfPoints) {
        return (2*Physics::PI / (numberOfPoints-1));
    }

    template<int N, double angleDelta, double planetRadius, typename T>
    constexpr void SetPlanetXValues(T& values) {
        if constexpr (N > 0) {
            values[N-1] = planetRadius * sin(angleDelta * (N-1));
            SetXEarthValues<N-1, angleDelta, planetRadius>(values);
        }
    }

    template<int N, double angleDelta, double planetRadius, typename T>
    constexpr void SetPlanetYValues(T& values) {
        if constexpr (N > 0) {
            values[N-1] = planetRadius * cos(angleDelta * (N-1));
            SetYEarthValues<N-1, angleDelta, planetRadius>(values);
        }
    }

};

#endif //ABSTRACTPROGRAMMINGPROJECT_OUT_PLANET_H
