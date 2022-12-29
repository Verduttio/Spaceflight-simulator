//
// Created by Bartek on 2022-12-22.
//

#ifndef ABSTRACTPROGRAMMINGPROJECT_OUT_ROCKETCOMPONENT_H
#define ABSTRACTPROGRAMMINGPROJECT_OUT_ROCKETCOMPONENT_H

class RocketComponent {
protected:
    // Raw component's mass
    // without any additional objects like fuel.
    double mass;    // in kg
public:
    void setMass(double _mass) {
        this->mass = _mass;
    }

    [[nodiscard]] double getMass() const {
        return this->mass;
    }
};

#endif //ABSTRACTPROGRAMMINGPROJECT_OUT_ROCKETCOMPONENT_H
