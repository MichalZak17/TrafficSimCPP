#pragma once
#include <vector>
#include <memory>
#include "Vehicle.h"

/**
 * @class Intersection
 * @brief Represents a traffic intersection in the simulation.
 * 
 * The Intersection class manages the traffic light and the vehicles waiting at the intersection.
 */
class Intersection {
public:
    /**
     * @brief Constructor for the Intersection class.
     * 
     * @param id The unique identifier for the intersection.
     */
    Intersection(int id)
        : m_id(id),
          m_lightGreenTime(3),
          m_lightRedTime(2),
          m_isGreen(true),
          m_elapsed(0),
          m_throughput(0),
          m_passedThisStep(0) {}

    /**
     * @brief Sets the traffic light times for the intersection.
     * 
     * @param green The duration of the green light.
     * @param red The duration of the red light.
     */
    void setLightTimes(int green, int red) {
        m_lightGreenTime = green;
        m_lightRedTime = red;
    }

    /**
     * @brief Adds a vehicle to the intersection's waiting queue.
     * 
     * @param v A unique pointer to the vehicle to be added.
     */
    void addVehicle(std::unique_ptr<Vehicle> v) {
        m_vehicles.push_back(std::move(v));
    }

    /**
     * @brief Updates the state of the intersection.
     * 
     * This method updates the traffic light and processes the vehicles waiting at the intersection.
     */
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

    /**
     * @brief Gets the unique identifier of the intersection.
     * 
     * @return The unique identifier of the intersection.
     */
    int getId() const { return m_id; }

    /**
     * @brief Checks if the traffic light is green.
     * 
     * @return True if the traffic light is green, false otherwise.
     */
    bool isGreen() const { return m_isGreen; }

    /**
     * @brief Gets the number of vehicles waiting at the intersection.
     * 
     * @return The number of vehicles waiting at the intersection.
     */
    int getWaitingCount() const { return static_cast<int>(m_vehicles.size()); }

    /**
     * @brief Gets the total number of vehicles that have passed through the intersection.
     * 
     * @return The total number of vehicles that have passed through the intersection.
     */
    int getThroughput() const { return m_throughput; }

    /**
     * @brief Gets the number of vehicles that passed through the intersection in the current step.
     * 
     * @return The number of vehicles that passed through the intersection in the current step.
     */
    int getPassedThisStep() const { return m_passedThisStep; }

private:
    int m_id; ///< The unique identifier of the intersection.
    int m_lightGreenTime; ///< The duration of the green light.
    int m_lightRedTime; ///< The duration of the red light.
    bool m_isGreen; ///< Indicates if the traffic light is green.
    int m_elapsed; ///< The elapsed time since the last light change.
    int m_throughput; ///< The total number of vehicles that have passed through the intersection.
    int m_passedThisStep; ///< The number of vehicles that passed through the intersection in the current step.

    std::vector<std::unique_ptr<Vehicle>> m_vehicles; ///< The queue of vehicles waiting at the intersection.
};
