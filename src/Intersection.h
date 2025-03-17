#pragma once
#include <vector>
#include <memory>
#include "Vehicle.h"

class Intersection {
public:
    Intersection(int id)
        : m_id(id),
          m_lightGreenTime(3),
          m_lightRedTime(2),
          m_isGreen(true),
          m_elapsed(0),
          m_throughput(0),
          m_passedThisStep(0) {}

    void setLightTimes(int green, int red) {
        m_lightGreenTime = green;
        m_lightRedTime = red;
    }

    void addVehicle(std::unique_ptr<Vehicle> v) {
        m_vehicles.push_back(std::move(v));
    }

    void update() {
        // Reset how many passed in THIS step
        m_passedThisStep = 0;

        // Update traffic light
        m_elapsed++;
        if (m_isGreen && m_elapsed >= m_lightGreenTime) {
            m_isGreen = false;
            m_elapsed = 0;
        } else if (!m_isGreen && m_elapsed >= m_lightRedTime) {
            m_isGreen = true;
            m_elapsed = 0;
        }

        // If green, let's let all queued vehicles pass this step
        if (m_isGreen && !m_vehicles.empty())
        {
            int passed = static_cast<int>(m_vehicles.size());
            m_throughput += passed;
            m_passedThisStep = passed;
            m_vehicles.clear();
        }
    }

    int getId() const { return m_id; }
    bool isGreen() const { return m_isGreen; }
    int getWaitingCount() const { return static_cast<int>(m_vehicles.size()); }
    int getThroughput() const { return m_throughput; }
    int getPassedThisStep() const { return m_passedThisStep; }

private:
    int m_id;
    int m_lightGreenTime;
    int m_lightRedTime;
    bool m_isGreen;
    int m_elapsed;
    int m_throughput;
    int m_passedThisStep; // number of vehicles passed in the current step

    std::vector<std::unique_ptr<Vehicle>> m_vehicles;
};
