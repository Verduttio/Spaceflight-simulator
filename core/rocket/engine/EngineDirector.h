//
// Created by Bartek on 2022-12-23.
//

#ifndef ABSTRACTPROGRAMMINGPROJECT_OUT_ENGINEDIRECTOR_H
#define ABSTRACTPROGRAMMINGPROJECT_OUT_ENGINEDIRECTOR_H

#include "IEngineBuilder.h"

class EngineDirector {
public:
    void constructRaptorEngine(IEngineBuilder* engineBuilder) {
        engineBuilder->initEngineSpace();
        engineBuilder->setMass(1600);
        engineBuilder->setSpecificImpulse(340);
        engineBuilder->setMassFlowRate(650);
    }

//    void constructMerlinEngine(IEngineBuilder* engineBuilder) {
//        engineBuilder->initEngineSpace();
//        engineBuilder->setMass(470);
//        engineBuilder->setThrust(653720);  // in Newtons
//        engineBuilder->setExhaustVelocity(2770);
//        engineBuilder->setMassFlowRate(236);
//    }

    void constructSpecificEngine(IEngineBuilder* engineBuilder, double mass, double specificImpulse, double massFlowRate) {
        engineBuilder->initEngineSpace();
        engineBuilder->setMass(mass);
        engineBuilder->setSpecificImpulse(specificImpulse);
        engineBuilder->setMassFlowRate(massFlowRate);
    }
};

#endif //ABSTRACTPROGRAMMINGPROJECT_OUT_ENGINEDIRECTOR_H
