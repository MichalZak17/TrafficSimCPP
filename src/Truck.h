#pragma once
#include "LandVehicle.h"
#include <iostream>

class Truck : public LandVehicle {
public:
    Truck(int id, double speed)
        : LandVehicle(id, speed, 6) {
    }

    ~Truck() override = default;

    // Implementation of updateState()
    void updateState() override {
        // Example: Just print that we're updating
        std::cout << "[Truck] ID=" << m_id << " updating state.\n";
    }
};
