#pragma once
#include "Vehicle.h"

/**
 * @class LandVehicle
 * @brief Represents a land vehicle in the traffic simulation.
 * 
 * The LandVehicle class is derived from the Vehicle class and represents a land vehicle with specific attributes and behaviors.
 */
class LandVehicle : public Vehicle {
public:
    /**
     * @brief Constructor for the LandVehicle class.
     * 
     * @param id The unique identifier for the land vehicle.
     * @param speed The speed of the land vehicle.
     * @param wheels The number of wheels of the land vehicle.
     */
    LandVehicle(int id, double speed, int wheels)
        : Vehicle(id, speed), m_numWheels(wheels) {}

    /**
     * @brief Destructor for the LandVehicle class.
     */
    virtual ~LandVehicle() = default;

    /**
     * @brief Gets the number of wheels of the land vehicle.
     * 
     * @return The number of wheels of the land vehicle.
     */
    int getNumWheels() const { return m_numWheels; }

protected:
    int m_numWheels; ///< The number of wheels of the land vehicle.
};
