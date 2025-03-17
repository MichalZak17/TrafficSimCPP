#pragma once
#include "LandVehicle.h"
#include <iostream>

/**
 * @class Car
 * @brief Represents a car in the traffic simulation.
 * 
 * The Car class is derived from the LandVehicle class and represents a car with specific attributes and behaviors.
 */
class Car : public LandVehicle {
public:
    /**
     * @brief Constructor for the Car class.
     * 
     * @param id The unique identifier for the car.
     * @param speed The speed of the car.
     */
    Car(int id, double speed)
        : LandVehicle(id, speed, 4) {
    }

    /**
     * @brief Destructor for the Car class.
     */
    ~Car() override = default;

    /**
     * @brief Updates the state of the car.
     * 
     * This method is called to update the state of the car during each simulation step.
     */
    void updateState() override {
        // Example: Just print that we're updating
        std::cout << "[Car] ID=" << m_id << " updating state.\n";
    }
};
