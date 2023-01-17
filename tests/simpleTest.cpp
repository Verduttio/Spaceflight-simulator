#include <iostream>
#include <cassert>
#include "../core/rocket/engine/EngineDirector.h"
#include "../core/rocket/engine/EngineBuilder.h"
#include "../core/rocket/Rocket.h"
#include "../core/rocket/fuelTank/FuelTankDirector.h"
#include "../core/rocket/fuelTank/FuelTankBuilder.h"
#include "../core/places/Shed.h"
#include "../physics/ConversionsSI.h"
#include "../physics/Physics.h"

void TEST_BUILDING_RAPTOR_ENGINE() {
    auto* director = new EngineDirector();

    auto* builder = new EngineBuilder();
    director->constructSpacexRaptorV1Engine(builder);
    Engine* engine = builder->getResult();

    assert(engine->getMass() == 1600);
    assert(engine->getspecificImpulse() == 340);
    assert(engine->getMassFlowRate() == 650);
}

void TEST_BUILDING_ROCKET_STAGE() {
    auto* shed = new Shed();
    double mass = 10000;
    double fuelAmount = 50000;
    double specificImpulse = 340;
    double massFlowRate = 650;
    double engineMass = 1400;
    int maxEngineNumberSupport = 4;
    int numberOfEngines = 3;

    shed->buildSpecificRocketStage(mass, fuelAmount, maxEngineNumberSupport, engineMass, specificImpulse, massFlowRate, numberOfEngines);
    RocketStage* rocketStage = shed->getRocketStageBuilder()->getResult();

    assert(rocketStage->calcTotalMass() == mass+fuelAmount+engineMass*numberOfEngines);
    assert(rocketStage->getFuelAmount() == fuelAmount);
    double enginesCurrentPower = 88;
    for(auto engine:rocketStage->getEngines()) {
        engine->setCurrentPower(88);
    }
    assert(rocketStage->getCurrentMassFlowRate() == massFlowRate*numberOfEngines*enginesCurrentPower/100);
}

void TEST_ROCKET_STAGE_CONNECTIONS() {
    Shed shed;

    shed.buildSmallRocketStage();
    shed.buildSmallRocketStage();
    shed.buildBigRocketStage();


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
void TEST_DETACHING_ROCKET_STAGES() {
    Shed shed;
    MissionControl missionControl;

    shed.buildBigRocketStage();      // 0
    shed.buildSmallRocketStage();   // 1
    shed.buildSmallRocketStage();   // 2
    shed.buildSmallRocketStage();   // 3
    shed.buildSmallRocketStage();   // 4



    // Make connections
    shed.connectRocketStages(0, MountSide::left, 1);
    shed.connectRocketStages(0, MountSide::right, 2);
    shed.connectRocketStages(1, MountSide::left, 3);
    shed.connectRocketStages(2, MountSide::right, 4);


    auto* rocketStageNo0 = shed.findRocketStage(0);
    auto* rocketStageNo1 = shed.findRocketStage(1);
    auto* rocketStageNo2 = shed.findRocketStage(2);
    auto* rocketStageNo3 = shed.findRocketStage(3);
    auto* rocketStageNo4 = shed.findRocketStage(4);

    shed.moveRocketToMissionControl(&missionControl);
    missionControl.setMissionControl();

    // Connections
    // 3 1 0 2 4

    // Detach rocket stage 4
    missionControl.detachStage(4);
    // Connections
    // 3 1 0 2

    // Check if rocket stage 4 is detached
    // RocketStage 0 connections
    for(auto const& [key, val] : rocketStageNo0->getConnections()) {
        assert(key == MountSide::left || key == MountSide::right);
        if(key == MountSide::left) {
            assert(val->getId() == 1);
        } else if (key == MountSide::right) {
            assert(val->getId() == 2);
        }
    }

    // RocketStage 1 connections
    for(auto const& [key, val] : rocketStageNo1->getConnections()) {
        assert(key == MountSide::left || key == MountSide::right);
        if(key == MountSide::left) {
            assert(val->getId() == 3);
        } else if (key == MountSide::right) {
            assert(val->getId() == 0);
        }
    }

    // RocketStage 2 connections
    for(auto const& [key, val] : rocketStageNo2->getConnections()) {
        assert(key == MountSide::left);
        if(key == MountSide::left) {
            assert(val->getId() == 0);
        }
    }

    // RocketStage 3 connections
    for(auto const& [key, val] : rocketStageNo3->getConnections()) {
        assert(key == MountSide::right);
        if(key == MountSide::right) {
            assert(val->getId() == 1);
        }
    }

}

void TEST_ROCKET_FULLY_STACKED() {
    Shed shed;

    shed.buildBigRocketStage();      // 0
    shed.buildSmallRocketStage();   // 1
    shed.buildSmallRocketStage();   // 2
    shed.buildSmallRocketStage();   // 3
    shed.buildSmallRocketStage();   // 4



    // Make connections
    shed.connectRocketStages(0, MountSide::left, 1);
    shed.connectRocketStages(0, MountSide::right, 2);
    shed.connectRocketStages(1, MountSide::left, 3);
    shed.connectRocketStages(2, MountSide::right, 4);

    assert(shed.rocketFullyStacked());
}

void TEST_ROCKET_NOT_FULLY_STACKED() {
    Shed shed;

    shed.buildBigRocketStage();      // 0
    shed.buildSmallRocketStage();   // 1
    shed.buildSmallRocketStage();   // 2
    shed.buildSmallRocketStage();   // 3
    shed.buildSmallRocketStage();   // 4



    // Make connections
    shed.connectRocketStages(0, MountSide::left, 1);
    shed.connectRocketStages(0, MountSide::right, 2);
    shed.connectRocketStages(2, MountSide::right, 4);

    assert(!shed.rocketFullyStacked());
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
    TEST_BUILDING_RAPTOR_ENGINE();
    TEST_ROCKET_STAGE_CONNECTIONS();
    TEST_CALC_EARTH_GRAVITY_ON_SURFACE();
    TEST_CONVERSIONS();
    TEST_DETACHING_ROCKET_STAGES();
    TEST_ROCKET_FULLY_STACKED();
    TEST_ROCKET_NOT_FULLY_STACKED();
    TEST_BUILDING_ROCKET_STAGE();

    return 0;
}