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
        engineBuilder->setThrust(653720);  // in Newtons
        engineBuilder->setExhaustVelocity(2770);
        engineBuilder->setMassFlowRate(236);
    }

    void constructSpecificEngine(IEngineBuilder* engineBuilder, double mass, double thrust, double exhaustVelocity) {
        engineBuilder->initEngineSpace();
        engineBuilder->setMass(mass);
        engineBuilder->setThrust(thrust);
        engineBuilder->setExhaustVelocity(exhaustVelocity);
        engineBuilder->setMassFlowRate(thrust/ exhaustVelocity);
    }
};

#endif //ABSTRACTPROGRAMMINGPROJECT_OUT_ENGINEDIRECTOR_H
