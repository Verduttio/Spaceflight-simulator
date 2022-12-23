//
// Created by Bartek on 2022-12-23.
//

#ifndef ABSTRACTPROGRAMMINGPROJECT_OUT_IFUELTANKBUILDER_H
#define ABSTRACTPROGRAMMINGPROJECT_OUT_IFUELTANKBUILDER_H

class IFuelTankBuilder {
public:
    virtual void reset() = 0;
    virtual void setFuelAmount(double) = 0;
    virtual void setMaxEngineNumberSupport(int) = 0;
    virtual void setMass(double) = 0;
};

#endif //ABSTRACTPROGRAMMINGPROJECT_OUT_IFUELTANKBUILDER_H
