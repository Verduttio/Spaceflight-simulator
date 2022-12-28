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
        engineBuilder->setMass(1.6);
        engineBuilder->setThrust(230);
    }
};

#endif //ABSTRACTPROGRAMMINGPROJECT_OUT_ENGINEDIRECTOR_H
