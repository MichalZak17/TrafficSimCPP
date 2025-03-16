#pragma once
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <memory>
#include "Intersection.h"
#include "RandomGen.h"

class TrafficSim {
public:
    TrafficSim();
    ~TrafficSim();

    // Reads config, sets up intersections, etc.
    bool initialize(const std::string& configPath);

    // Runs the simulation for a specified number of steps
    void runSimulation();

private:
    // Helper to load config from file
    bool loadConfig(const std::string& path);

    // Helper to log messages
    void logMessage(const std::string& message);

    // Spawns random vehicles and assigns them to intersections
    void spawnVehicles();

private:
    std::map<int, Intersection> m_intersections;
    int m_numIntersections;
    int m_vehiclesPerStep;
    int m_maxSteps;
    RandomGen m_rng;  // random generator

    // Traffic light times (shared by all intersections for simplicity)
    int m_greenTime;
    int m_redTime;

    // For logging
    std::ofstream m_logFile;
    int m_currentStep;
};
