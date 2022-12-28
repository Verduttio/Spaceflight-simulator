#include <iostream>
#include "core/places/Shed.h"

int main(int argc, char *argv[]) {
    Shed shed;

    shed.buildRocketStageSmall();
    shed.buildRocketStageSmall();
    shed.buildRocketStageBig();


    // Make connections
    shed.connectRocketStages(2, MountSide::left, 0);
    shed.connectRocketStages(2, MountSide::right, 1);

    shed.drawRocketStagesASCII();
    shed.printRocketStagesConnections();

    return 0;
}