//
// Created by Bartek on 2022-12-22.
//

#ifndef ABSTRACTPROGRAMMINGPROJECT_OUT_ROCKETSTAGE_H
#define ABSTRACTPROGRAMMINGPROJECT_OUT_ROCKETSTAGE_H

#include <vector>
#include <map>
#include "../engine/Engine.h"
#include "../fuelTank/FuelTank.h"
#include "../MountSide.h"

class RocketStage {
    int id;
    std::vector<Engine*> engines;
    FuelTank* fuelTank;
    std::map<MountSide, RocketStage*> connections;
public:
    void setId(int _id) {
        this->id = _id;
    }

    [[nodiscard]] int getId() const {
        return this->id;
    }

    void connect(RocketStage* rocketStage, MountSide mountSide) {
        connections[mountSide] = rocketStage;
    }

    void disconnect(MountSide mountSide) {
        connections.erase(mountSide);
    }

    void addEngine(Engine* engine) {
        engines.push_back(engine);
    }

    void removeEngine(Engine* engine) {
        engines.erase(std::remove(engines.begin(), engines.end(), engine), engines.end());
    }

    void setFuelTank(FuelTank* _fuelTank) {
        this->fuelTank = _fuelTank;
    }

    void removeFuelTank() {
        this->fuelTank = nullptr;
    }

    std::vector<Engine*> getEngines() {
        return engines;
    }

    FuelTank* getFuelTank() {
        return fuelTank;
    }

    double getFuelAmount() {
        return fuelTank->getFuelAmount();
    }

    std::map<MountSide, RocketStage*> getConnections() {
        return connections;
    }

    void burnFuel(double seconds) {
        double totalMassFlowRate = 0;
        for (auto engine : engines) {
            totalMassFlowRate += engine->getCurrentMassFlowRate();
        }
        fuelTank->decreaseFuelAmount(totalMassFlowRate * seconds);
    }

    double getEnginesMaxThrust() {
        double maxThrust = 0;
        for (auto engine : engines) {
            maxThrust += engine->getMaxThrust();
        }
        return maxThrust;
    }

    double getEnginesCurrentThrust() {
        double currentThrust = 0;
        for (auto engine : engines) {
            currentThrust += engine->getCurrentThrust();
        }
        return currentThrust;
    }

    double calcTotalMass() {
        double totalMass = 0;
        for (auto engine : engines) {
            totalMass += engine->getMass();
        }
        totalMass += fuelTank->calcTotalMass();

        return totalMass;
    }

    void printConnections() {
        std::cout << "Connections of stage number: " << id << std::endl;

        //Iterate over map
        for (auto const& [key, val] : connections) {
            std::cout << translateMountSide(key) << ": " << val->id << std::endl;
        }
        std::cout << std::endl;

    }

    //TODO: move to utils
    static std::string translateMountSide(MountSide mountSide) {
        switch (mountSide) {
            case MountSide::bottom:
                return "bottom";
            case MountSide::left:
                return "left";
            case MountSide::right:
                return "right";
            case MountSide::up:
                return "up";
        }
        return "unknown";
    }


    bool isEngineConnected(Engine* engine) {
        return std::find(engines.begin(), engines.end(), engine) != engines.end();
    }

    size_t getEngineNumber() {
        return engines.size();
    }

    void drawASCII() {
        if(fuelTank->getMass() <= 1000) {
            std::cout << "___" << std::endl;
            std::cout << "| |" << std::endl;
            std::cout << "| |" << std::endl;
            std::cout << "| |" << std::endl;
            std::cout << "===" << std::endl;
        } else if (fuelTank->getMass() <= 2000) {
            std::cout << "_____" << std::endl;
            std::cout << "|   |" << std::endl;
            std::cout << "|   |" << std::endl;
            std::cout << "|   |" << std::endl;
            std::cout << "|   |" << std::endl;
            std::cout << "=====" << std::endl;
        } else {
            std::cout << "______" << std::endl;
            std::cout << "|    |" << std::endl;
            std::cout << "|    |" << std::endl;
            std::cout << "|    |" << std::endl;
            std::cout << "|    |" << std::endl;
            std::cout << "======" << std::endl;
        }

        // Draw engines
        for(int i = 0; i < getEngineNumber(); i++) {
            std::cout << "e";
        }
        std::cout << std::endl;
    }
};

#endif //ABSTRACTPROGRAMMINGPROJECT_OUT_ROCKETSTAGE_H
