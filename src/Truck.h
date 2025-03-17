#pragma once
#include "LandVehicle.h"
#include <iostream>

/**
 * @class Truck
 * @brief Represents a truck in the traffic simulation.
 * 
 * The Truck class is derived from the LandVehicle class and represents a truck with specific attributes and behaviors.
 */
class Truck : public LandVehicle {
public:
    /**
     * @brief Constructor for the Truck class.
     * 
     * @param id The unique identifier for the truck.
     * @param speed The speed of the truck.
     */
    Truck(int id, double speed)
        : LandVehicle(id, speed, 6) {
    }

    /**
     * @brief Destructor for the Truck class.
     */
    ~Truck() override = default;

    /**
     * @brief Updates the state of the truck.
     * 
     * This method is called to update the state of the truck during each simulation step.
     */
    void updateState() override {
        // Example: Just print that we're updating
        std::cout << "[Truck] ID=" << m_id << " updating state.\n";
    }
};
