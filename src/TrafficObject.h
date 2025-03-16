#pragma once

// Abstract base class representing any traffic-related object.
class TrafficObject {
public:
    virtual ~TrafficObject() = default;

    // Pure virtual method for updating object state each simulation step
    virtual void updateState() = 0;
};
