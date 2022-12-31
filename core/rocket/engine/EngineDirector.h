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
        engineBuilder->setThrust(185);
//        engineBuilder->setExhaustVelocity(3210);
        engineBuilder->setExhaustVelocity(3000);
        engineBuilder->setMassFlowRate(650);
    }

    void constructMerlinEngine(IEngineBuilder* engineBuilder) {
        engineBuilder->initEngineSpace();
        engineBuilder->setMass(470);
        engineBuilder->setExhaustVelocity(2700);
        engineBuilder->setMassFlowRate(260);
    }

    void constructSpecificEngine(IEngineBuilder* engineBuilder, double mass, double exhaustVelocity, double massFlowRate) {
        engineBuilder->initEngineSpace();
        engineBuilder->setMass(mass);
        engineBuilder->setExhaustVelocity(exhaustVelocity);
        engineBuilder->setMassFlowRate(massFlowRate);
    }
};

#endif //ABSTRACTPROGRAMMINGPROJECT_OUT_ENGINEDIRECTOR_H
