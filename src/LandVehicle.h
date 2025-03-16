#pragma once
#include "Vehicle.h"

class LandVehicle : public Vehicle {
public:
    LandVehicle(int id, double speed, int wheels)
        : Vehicle(id, speed), m_numWheels(wheels) {}

    virtual ~LandVehicle() = default;

    // Example method to show specialized functionality
    int getNumWheels() const { return m_numWheels; }

protected:
    int m_numWheels;
};
