#pragma once
#include "LandVehicle.h"
#include <iostream>

class Car : public LandVehicle {
public:
    Car(int id, double speed)
        : LandVehicle(id, speed, 4) {
    }

    ~Car() override = default;

    // Implementation of updateState()
    void updateState() override {
        // Example: Just print that we're updating
        std::cout << "[Car] ID=" << m_id << " updating state.\n";
    }
};
