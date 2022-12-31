#include <iostream>
#include "core/places/Shed.h"

int main(int argc, char *argv[]) {
    Shed shed;

//    shed.buildRocketStageSmall();
//    shed.buildRocketStageSmall();
//    shed.buildRocketStageBig();

    //shed.buildStarshipSecondStage();
    auto* rocketStageBuilder = shed.getRocketStageBuilder();
    rocketStageBuilder->initRocketStageSpace();
    rocketStageBuilder->mountSpecificFuelTank(50000, 395700, 9);
//    rocketStageBuilder->mountSpecificEngine(1600, 2400, 650);
    rocketStageBuilder->mountMerlinEngine();
    rocketStageBuilder->mountMerlinEngine();
    rocketStageBuilder->mountMerlinEngine();
//    rocketStageBuilder->mountMerlinEngine();
//    rocketStageBuilder->mountMerlinEngine();
//    rocketStageBuilder->mountMerlinEngine();
//    rocketStageBuilder->mountMerlinEngine();
//    rocketStageBuilder->mountMerlinEngine();
//    rocketStageBuilder->mountMerlinEngine();
    shed.mountRocketStage(rocketStageBuilder->getResult());


    // Make connections
//    shed.connectRocketStages(2, MountSide::left, 0);
//    shed.connectRocketStages(2, MountSide::right, 1);

    shed.drawRocketStagesASCII();
    shed.printRocketStagesConnections();

    // The rocket is stacked and ready to be moved to Mission Control
    MissionControl missionControl{};
    shed.moveRocketToMissionControl(&missionControl);
    Planet earth(5.9722e24, 6373140);
    missionControl.setPlanet(&earth);

    // Launch the rocket
    missionControl.launchRocket();



    return 0;
}