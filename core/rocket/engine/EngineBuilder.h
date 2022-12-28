//
// Created by Bartek on 2022-12-23.
//

#ifndef ABSTRACTPROGRAMMINGPROJECT_OUT_ENGINEBUILDER_H
#define ABSTRACTPROGRAMMINGPROJECT_OUT_ENGINEBUILDER_H
#include "IEngineBuilder.h"
#include "Engine.h"

class EngineBuilder : public IEngineBuilder {
    Engine* engine;
public:
    void reset() override {
        delete engine;
        engine = new Engine();
    }

    void initEngineSpace() {
        engine = new Engine();
    }

    EngineBuilder() {
        engine = new Engine();
    }

    void setThrust(int _thrust) override {
        engine->setThrust(_thrust);
    }

    void setMass(double _mass) override {
        engine->setMass(_mass);
    }

    Engine* getResult() {
        return this->engine;
    }
};

#endif //ABSTRACTPROGRAMMINGPROJECT_OUT_ENGINEBUILDER_H
