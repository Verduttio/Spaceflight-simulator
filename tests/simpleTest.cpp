#include <iostream>
#include <cassert>
#include "../core/rocket/engine/EngineDirector.h"
#include "../core/rocket/engine/EngineBuilder.h"
#include "../core/rocket/Rocket.h"
#include "../core/rocket/fuelTank/FuelTankDirector.h"
#include "../core/rocket/fuelTank/FuelTankBuilder.h"
#include "../core/places/Shed.h"
#include "../tools/ConversionsSI.h"
#include "../tools/Physics.h"

void TEST_BUILDING_RaptorEngine() {
    auto* director = new EngineDirector();

    auto* builder = new EngineBuilder();
    director->constructRaptorEngine(builder);
    Engine* engine = builder->getResult();

    assert(engine->getMaxThrust() == 185);
    assert(engine->getMass() == 1600);
}

//void TEST_BUILDING_SmallFuelTank() {
//    auto* director = new FuelTankDirector();
//
//    auto* builder = new FuelTankBuilder();
//    director->constructSmallFuelTank(builder);
//    FuelTank* fuelTank = builder->getResult();
//
//    assert(fuelTank->getMass() == 50);
//    assert(fuelTank->getFuelAmount() == 80);
//    assert(fuelTank->getMaxEngineNumberSupport() == 3);
//}

void TEST_ROCKETSTAGE_Connections() {
    Shed shed;

    shed.buildRocketStageSmall();
    shed.buildRocketStageSmall();
    shed.buildRocketStageBig();


    // Make connections
    shed.connectRocketStages(2, MountSide::left, 0);
    shed.connectRocketStages(2, MountSide::right, 1);

    auto* rocketStageNo0 = shed.findRocketStage(0);
    auto* rocketStageNo1 = shed.findRocketStage(1);
    auto* rocketStageNo2 = shed.findRocketStage(2);

    // RocketStage 0 connections
    for(auto const& [key, val] : rocketStageNo0->getConnections()) {
        assert(key == MountSide::right);
        assert(val->getId() == 2);
    }

    // RocketStage 1 connections
    for(auto const& [key, val] : rocketStageNo1->getConnections()) {
        assert(key == MountSide::left);
        assert(val->getId() == 2);
    }

    // RocketStage 2 connections
    for(auto const& [key, val] : rocketStageNo2->getConnections()) {
        assert(key == MountSide::left || key == MountSide::right);
        if(key == MountSide::left) {
            assert(val->getId() == 0);
        } else if (key == MountSide::right) {
            assert(val->getId() == 1);
        }
    }
}

void TEST_CALC_EARTH_GRAVITY_ON_SURFACE() {
    Planet earth(5.9722e24, 6373140);

    auto gravityAcceleration = Physics::calcGravityAcceleration(earth.getMass(), earth.getRadius(), 0);
    double earthGravityAcceleration = 9.81;

    assert(gravityAcceleration - earthGravityAcceleration < 0.01);
}

void TEST_CONVERSIONS() {
    assert(ConversionSI::convertDistanceM_TO_KM(1000) == 1);
    assert(ConversionSI::convertVelocityMS_s_TO_KM_h(10) == 36);
}





int main() {
    TEST_BUILDING_RaptorEngine();
    TEST_ROCKETSTAGE_Connections();
    TEST_CALC_EARTH_GRAVITY_ON_SURFACE();
    TEST_CONVERSIONS();

    return 0;
}