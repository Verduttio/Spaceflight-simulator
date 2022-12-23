#include <iostream>
#include <cassert>
#include "core/rocket/engine/EngineDirector.h"
#include "core/rocket/engine/EngineBuilder.h"
#include "core/rocket/Rocket.h"
#include "core/rocket/fuelTank/FuelTankDirector.h"
#include "core/rocket/fuelTank/FuelTankBuilder.h"

void TEST_BUILDING_RaptorEngine() {
    auto* director = new EngineDirector();

    auto* builder = new EngineBuilder();
    director->constructRaptorEngine(builder);
    Engine* engine = builder->getResult();

    assert(engine->getThrust() == 230);
    assert(engine->getMass() == 1.6);
}

void TEST_BUILDING_SmallFuelTank() {
    auto* director = new FuelTankDirector();

    auto* builder = new FuelTankBuilder();
    director->constructSmallFuelTank(builder);
    FuelTank* fuelTank = builder->getResult();

    assert(fuelTank->getMass() == 50);
    assert(fuelTank->getFuelAmount() == 80);
    assert(fuelTank->getMaxEngineNumberSupport() == 3);
}



int main() {
    TEST_BUILDING_RaptorEngine();
    TEST_BUILDING_SmallFuelTank();

    return 0;
}