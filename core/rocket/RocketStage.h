//
// Created by Bartek on 2022-12-22.
//

#ifndef ABSTRACTPROGRAMMINGPROJECT_OUT_ROCKETSTAGE_H
#define ABSTRACTPROGRAMMINGPROJECT_OUT_ROCKETSTAGE_H

#include <vector>
#include <map>
#include "core/rocket/engine/Engine.h"
#include "core/rocket/fuelTank/FuelTank.h"
#include "MountSide.h"

class RocketStage {
    std::vector<Engine> engines;
    FuelTank fuelTank;
    std::map<MountSide, RocketStage*> connections;
};

#endif //ABSTRACTPROGRAMMINGPROJECT_OUT_ROCKETSTAGE_H
