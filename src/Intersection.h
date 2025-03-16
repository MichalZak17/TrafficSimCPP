#pragma once
#include <vector>
#include <memory>
#include "Vehicle.h"

// Simple Intersection class that holds a list of vehicles
class Intersection {
    public:
    Intersection(int id)
        : m_id(id),
          m_lightGreenTime(3),
          m_lightRedTime(2),
          m_isGreen(true),
          m_elapsed(0)
    {}

    void setLightTimes(int green, int red) {
        m_lightGreenTime = green;
        m_lightRedTime = red;
    }

    // DEFAULT CONSTRUCTOR - fix compile error
    Intersection()
      : m_id(0), m_lightGreenTime(3), m_lightRedTime(2),
        m_isGreen(true), m_elapsed(0) {}

    // Add a vehicle to this intersection
    void addVehicle(std::unique_ptr<Vehicle> v) {
        m_vehicles.push_back(std::move(v));
    }

    // Update intersection state (traffic light, vehicles, etc.)
    void update() {
        // Toggle traffic light based on elapsed time
        m_elapsed++;
        if (m_isGreen && m_elapsed >= m_lightGreenTime) {
            m_isGreen = false;
            m_elapsed = 0;
        } else if (!m_isGreen && m_elapsed >= m_lightRedTime) {
            m_isGreen = true;
            m_elapsed = 0;
        }

        // Update each vehicle state
        for (auto& v : m_vehicles) {
            v->updateState();
        }

        // In a real simulation, you might remove vehicles that have passed, etc.
        // This minimal version just prints updates.
    }

    int getId() const { return m_id; }
    bool isGreen() const { return m_isGreen; }

private:
    int m_id;
    int m_lightGreenTime;
    int m_lightRedTime;
    bool m_isGreen;
    int m_elapsed;  // how long current light has been active
    std::vector<std::unique_ptr<Vehicle>> m_vehicles;
};
