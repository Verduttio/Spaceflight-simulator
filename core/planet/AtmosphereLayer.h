//
// Created by Bartek on 2022-12-22.
//

#ifndef ABSTRACTPROGRAMMINGPROJECT_OUT_ATMOSPHERELAYER_H
#define ABSTRACTPROGRAMMINGPROJECT_OUT_ATMOSPHERELAYER_H

#include <iostream>

class AtmosphereLayer {
    std::string name;
    int altitudeBeginning;
    int altitudeEnding;
    double density;
    double densityChangeFactor;   // how the density changes over the altitude
};

#endif //ABSTRACTPROGRAMMINGPROJECT_OUT_ATMOSPHERELAYER_H
