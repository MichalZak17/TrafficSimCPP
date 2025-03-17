#pragma once

/**
 * @class TrafficObject
 * @brief Abstract base class representing any traffic-related object.
 * 
 * The TrafficObject class serves as a base class for all traffic-related objects in the simulation.
 * It defines a pure virtual method for updating the state of the object during each simulation step.
 */
class TrafficObject {
public:
    /**
     * @brief Virtual destructor for the TrafficObject class.
     */
    virtual ~TrafficObject() = default;

    /**
     * @brief Pure virtual method for updating the state of the object.
     * 
     * This method must be implemented by derived classes to update the state of the object during each simulation step.
     */
    virtual void updateState() = 0;
};
