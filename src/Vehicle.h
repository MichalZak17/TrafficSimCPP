#pragma once
#include "TrafficObject.h"
#include <string>
#include <iostream>

/**
 * @class Vehicle
 * @brief Abstract base class representing a vehicle in the traffic simulation.
 * 
 * The Vehicle class serves as a base class for all types of vehicles in the simulation.
 * It defines common attributes and methods for vehicles, including ID, speed, and state update.
 */
class Vehicle : public TrafficObject {
public:
    /**
     * @brief Constructor for the Vehicle class.
     * 
     * @param id The unique identifier for the vehicle.
     * @param speed The speed of the vehicle.
     */
    Vehicle(int id, double speed)
        : m_id(id), m_speed(speed) {}

    /**
     * @brief Virtual destructor for the Vehicle class.
     */
    virtual ~Vehicle() = default;

    /**
     * @brief Copy constructor for the Vehicle class.
     * 
     * @param other The Vehicle object to copy from.
     */
    Vehicle(const Vehicle& other)
        : m_id(other.m_id), m_speed(other.m_speed) {}

    /**
     * @brief Move constructor for the Vehicle class.
     * 
     * @param other The Vehicle object to move from.
     */
    Vehicle(Vehicle&& other) noexcept
        : m_id(other.m_id), m_speed(other.m_speed) {
        other.m_id = -1;
        other.m_speed = 0.0;
    }

    /**
     * @brief Move assignment operator for the Vehicle class.
     * 
     * @param other The Vehicle object to move from.
     * @return A reference to the assigned Vehicle object.
     */
    Vehicle& operator=(Vehicle&& other) noexcept {
        if (this != &other) {
            m_id = other.m_id;
            m_speed = other.m_speed;
            other.m_id = -1;
            other.m_speed = 0.0;
        }
        return *this;
    }

    /**
     * @brief Overloads the less-than operator for the Vehicle class.
     * 
     * @param other The Vehicle object to compare with.
     * @return True if this Vehicle's ID is less than the other Vehicle's ID, false otherwise.
     */
    bool operator<(const Vehicle& other) const {
        // Compare based on ID for demonstration
        return this->m_id < other.m_id;
    }

    /**
     * @brief Overloads the equality operator for the Vehicle class.
     * 
     * @param other The Vehicle object to compare with.
     * @return True if this Vehicle's ID is equal to the other Vehicle's ID, false otherwise.
     */
    bool operator==(const Vehicle& other) const {
        return this->m_id == other.m_id;
    }

    /**
     * @brief Overloads the stream insertion operator for the Vehicle class.
     * 
     * @param os The output stream.
     * @param v The Vehicle object to insert into the stream.
     * @return A reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Vehicle& v) {
        os << "[Vehicle] ID=" << v.m_id << ", Speed=" << v.m_speed;
        return os;
    }

    /**
     * @brief Pure virtual method for updating the state of the vehicle.
     * 
     * This method must be implemented by derived classes to update the state of the vehicle during each simulation step.
     */
    virtual void updateState() override = 0;

    /**
     * @brief Gets the unique identifier of the vehicle.
     * 
     * @return The unique identifier of the vehicle.
     */
    int getId() const { return m_id; }

    /**
     * @brief Gets the speed of the vehicle.
     * 
     * @return The speed of the vehicle.
     */
    double getSpeed() const { return m_speed; }

protected:
    int m_id; ///< The unique identifier of the vehicle.
    double m_speed; ///< The speed of the vehicle.
};
