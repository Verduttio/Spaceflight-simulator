//
// Created by Bartek on 2022-12-22.
//

#ifndef ABSTRACTPROGRAMMINGPROJECT_OUT_ENGINE_H
#define ABSTRACTPROGRAMMINGPROJECT_OUT_ENGINE_H

#include "../RocketComponent.h"

class Engine : public RocketComponent {
    int thrust;

public:
    void setThrust(int _thrust) {
        this->thrust = _thrust;
    }

    [[nodiscard]] int getThrust() const {
        return thrust;
    }
};

#endif //ABSTRACTPROGRAMMINGPROJECT_OUT_ENGINE_H
