//
// Created by Bartek on 2022-12-23.
//

#ifndef ABSTRACTPROGRAMMINGPROJECT_OUT_IENGINEBUILDER_H
#define ABSTRACTPROGRAMMINGPROJECT_OUT_IENGINEBUILDER_H

class IEngineBuilder {
public:
    virtual void reset() = 0;
    virtual void initEngineSpace() = 0;
    virtual void setSpecificImpulse(double) = 0;
    virtual void setMass(double) = 0;
    virtual void setMassFlowRate(double) = 0;
};

#endif //ABSTRACTPROGRAMMINGPROJECT_OUT_IENGINEBUILDER_H
