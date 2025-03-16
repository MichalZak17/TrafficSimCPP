#pragma once
#include "TrafficObject.h"
#include <string>
#include <iostream>

class Vehicle : public TrafficObject {
public:
    // Constructor & destructor
    Vehicle(int id, double speed)
        : m_id(id), m_speed(speed) {}

    virtual ~Vehicle() = default;

    // Copy constructor
    Vehicle(const Vehicle& other)
        : m_id(other.m_id), m_speed(other.m_speed) {}

    // Move constructor
    Vehicle(Vehicle&& other) noexcept
        : m_id(other.m_id), m_speed(other.m_speed) {
        other.m_id = -1;
        other.m_speed = 0.0;
    }

    // Move assignment operator
    Vehicle& operator=(Vehicle&& other) noexcept {
        if (this != &other) {
            m_id = other.m_id;
            m_speed = other.m_speed;
            other.m_id = -1;
            other.m_speed = 0.0;
        }
        return *this;
    }

    // Overload operator<
    // (in C++14, no <=> operator, so we do a simple comparison)
    bool operator<(const Vehicle& other) const {
        // Compare based on ID for demonstration
        return this->m_id < other.m_id;
    }

    // Overload operator==
    bool operator==(const Vehicle& other) const {
        return this->m_id == other.m_id;
    }

    // Overload operator<< for logging
    friend std::ostream& operator<<(std::ostream& os, const Vehicle& v) {
        os << "[Vehicle] ID=" << v.m_id << ", Speed=" << v.m_speed;
        return os;
    }

    // from TrafficObject
    virtual void updateState() override = 0;

    // Accessors
    int getId() const { return m_id; }
    double getSpeed() const { return m_speed; }

protected:
    int m_id;
    double m_speed;
};
