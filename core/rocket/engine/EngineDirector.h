//
// Created by Bartek on 2022-12-23.
//

#ifndef ABSTRACTPROGRAMMINGPROJECT_OUT_ENGINEDIRECTOR_H
#define ABSTRACTPROGRAMMINGPROJECT_OUT_ENGINEDIRECTOR_H

#include "IEngineBuilder.h"

class EngineDirector {
public:
    void constructSpacexRaptorV1Engine(IEngineBuilder* engineBuilder) {
        engineBuilder->initEngineSpace();
        engineBuilder->setMass(1600);
        engineBuilder->setSpecificImpulse(340);
        engineBuilder->setMassFlowRate(650);
    }

    void constructHawkEngineSPF(IEngineBuilder* engineBuilder) {
        engineBuilder->initEngineSpace();
        engineBuilder->setMass(3500);
        engineBuilder->setSpecificImpulse(240);
        engineBuilder->setMassFlowRate((120*1000)/(240.0));
    }

    void constructSpecificEngine(IEngineBuilder* engineBuilder, double mass, double specificImpulse, double massFlowRate) {
        engineBuilder->initEngineSpace();
        engineBuilder->setMass(mass);
        engineBuilder->setSpecificImpulse(specificImpulse);
        engineBuilder->setMassFlowRate(massFlowRate);
    }
};

#endif //ABSTRACTPROGRAMMINGPROJECT_OUT_ENGINEDIRECTOR_H
