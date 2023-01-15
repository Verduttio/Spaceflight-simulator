//
// Created by Bartek on 2022-12-29.
//

#ifndef ABSTRACTPROGRAMMINGPROJECT_OUT_CONVERSIONSSI_H
#define ABSTRACTPROGRAMMINGPROJECT_OUT_CONVERSIONSSI_H

class ConversionSI {
public:
    // Convert ms/s to km/h
    static double convertVelocityMS_s_TO_KM_h(double velocity) {
        return velocity * 3.6;
    }

    // Convert m to km
    static double convertDistanceM_TO_KM(double distance) {
        return distance / 1000;
    }

    // Convert ms to seconds
    static double convertTimeMS_TO_S(double time) {
        return time / 1000;
    }

};

#endif //ABSTRACTPROGRAMMINGPROJECT_OUT_CONVERSIONSSI_H
