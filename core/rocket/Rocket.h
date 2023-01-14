//
// Created by Bartek on 2022-12-22.
//

#ifndef ABSTRACTPROGRAMMINGPROJECT_OUT_ROCKET_H
#define ABSTRACTPROGRAMMINGPROJECT_OUT_ROCKET_H

#include "rocketStage/RocketStage.h"

class Rocket {
    std::vector<RocketStage*> stages;
    double angle;  // in degrees [-180, 180]
    double velocityR;  // in m/s
    double velocityPhi;  // in m/s
    double accelerationR;  // in m/s^2
    double accelerationPhi;  // in m/s^2

    // These two are used to determine the position of the rocket in space (2-dimensional) by X and Y values (in meters).
    // X and Y values are calculated by transforming the polar coordinates (angle, radius) to cartesian coordinates (X, Y).
    // In our case angle is anglePhi and radius is altitude + planetRadius.
    double altitude;  // in m
    double anglePhi;  // in radians!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    friend class Shed;
    friend class MissionControl;
public:
    void setVelocityR(double _velocity) {
        this->velocityR = _velocity;
    }

    void detachStage(unsigned int stageId) {
        // We assume that side boosters (those which are on the left or on the right side of the main rocket stage)
        // are always one level stages (i.e. they are not connected to any other rocket stage through up/bottom).

        // Main booster (main rocket stage might be multilevel but this is TODO: implement detaching such a booster)

        // We detach side booster by firstly finding on which side of the main booster are they connected.
        // Then we detach this booster (rocket stage) and these connected to the same side from detaching booster.
        // So if rocket stage X is connected to the main rocket stage on the left side,
        // then we detach rocket stage X and all rocket stages connected to the left side of rocket stage X.

        // TODO: If main booster is multilevel then implement detaching its stages

        // After detaching we have to update rocket stages connections - DONE

        // Check if detaching stage is on the left of the main booster
        bool isLeft = false;
        RocketStage* detachingStage = findStageById(stageId);
        RocketStage* currentStageInWalk = detachingStage;
        while(currentStageInWalk != nullptr) {
            if(currentStageInWalk->getId() == 0) {
                isLeft = true;
                break;
            } else {
                auto currentConnections = currentStageInWalk->getConnections();
                auto pair = currentConnections.find(MountSide::right);
                if (pair != currentConnections.end()) {   // so there is a connection on the right side
                    currentStageInWalk = pair->second;
                } else {
                    currentStageInWalk = nullptr;
                }
            }
        }


        // We now know on which side of the main booster is the detaching stage
        // So we go through all stages connected to the same side,
        // remove their connections and remove them from the rocket stages vector.

        // We start from the detaching stage
        currentStageInWalk = detachingStage;
        while(currentStageInWalk != nullptr) {
            // We remove all connections to the detaching stage from other stages
            for(auto& pair : currentStageInWalk->getConnections()) {
                pair.second->disconnect(static_cast<MountSide>((static_cast<int>(pair.first) + 2) % 4));
            }
//            currentStageInWalk->getConnections().clear();  // it doesn't even matter because we are going to remove this stage


            // We remove the current stage from the rocket stages vector
            // https://stackoverflow.com/questions/3385229/c-erase-vector-element-by-value-rather-than-by-position
            stages.erase(std::remove(stages.begin(), stages.end(), currentStageInWalk), stages.end());


            auto currentConnections = currentStageInWalk->getConnections();
            // We go to the next stage
            if(isLeft) {
                auto pair = currentConnections.find(MountSide::left);
                if (pair != currentConnections.end()) {   // so there is a connection on the left side
                    currentStageInWalk = pair->second;
                } else {
                    currentStageInWalk = nullptr;
                }
            } else {
                auto pair = currentConnections.find(MountSide::right);
                if (pair != currentConnections.end()) {   // so there is a connection on the right side
                    currentStageInWalk = pair->second;
                } else {
                    currentStageInWalk = nullptr;
                }
            }
        }

    }

    RocketStage* findStageById(unsigned int stageId) {
        for (auto stage : stages) {
            if (stage->getId() == stageId) {
                return stage;
            }
        }
        return nullptr;
    }

    double getTotalCurrentMassFlowRate() {
        double totalCurrentMassFlowRate = 0;
        for (RocketStage* stage : stages) {
            totalCurrentMassFlowRate += stage->getCurrentMassFlowRate();
        }
        return totalCurrentMassFlowRate;
    }

    void burnFuel(double seconds) {
        for (auto stage : stages) {
            stage->burnFuel(seconds);
        }
    }

    [[nodiscard]] double getAltitude() const {
        return altitude;
    }

    double calcTotalMass() {
        double totalMass = 0;
        for (auto stage : stages) {
            totalMass += stage->calcTotalMass();
        }
        return totalMass;
    }

    //TODO: We assume here that all engines have the same power set,
    //      which in the future, might not be true.
    double getEnginesCurrentPower(){
        // Very bad way of doing this, but it is good for now.
        for (auto stage : stages) {
            for (auto engine : stage->getEngines()) {
                return engine->getCurrentPower();
            }
        }
    }

    double getFuelMass() {
        double totalFuelMass = 0;
        for (auto stage : stages) {
            totalFuelMass += stage->getFuelAmount();
        }
        return totalFuelMass;
    }

    double getEnginesCurrentThrust(double gravityAcc) {
        double currentThrust = 0;
        for (auto stage : stages) {
            currentThrust += stage->getEnginesCurrentThrust(gravityAcc);
        }
        return currentThrust;
    }

    double getEnginesMaxThrust(double gravityAcc) {
        double maxThrust = 0;
        for (auto stage : stages) {
            maxThrust += stage->getEnginesMaxThrust(gravityAcc);
        }
        return maxThrust;
    }

    size_t getNumberOfRocketStages() {
        return stages.size();
    }

    void printInfo() {
        std::cout << "Rocket info:" << std::endl;
        std::cout << "Mass: " << calcTotalMass() << " kg" << std::endl;
        std::cout << "Fuel mass: " << getFuelMass() << " kg" << std::endl;
        std::cout << "Thrust/Weight ratio: " << getEnginesMaxThrust(9.81) / (calcTotalMass()*9.81) << std::endl;
    }


};

#endif //ABSTRACTPROGRAMMINGPROJECT_OUT_ROCKET_H
