//
// Created by Bartek on 2022-12-22.
//

#ifndef ABSTRACTPROGRAMMINGPROJECT_OUT_SHED_H
#define ABSTRACTPROGRAMMINGPROJECT_OUT_SHED_H
#include "../rocket/Rocket.h"
#include "LaunchPad.h"

class Shed {
    Rocket* rocket;
public:
    void moveRocketToLaunchPad(LaunchPad& launchPad) {};

    void resetBuilding() {
        delete rocket;
        rocket = new Rocket();
    }


};

#endif //ABSTRACTPROGRAMMINGPROJECT_OUT_SHED_H
