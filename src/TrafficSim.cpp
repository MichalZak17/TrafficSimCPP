#include "TrafficSim.h"
#include "Car.h"
#include "Truck.h"
#include <iostream>
#include <algorithm>
#include <thread>       // for std::this_thread::sleep_for
#include <chrono>       // for std::chrono::milliseconds

// ANSI color codes
static const char* ANSI_RED   = "\x1b[31m";
static const char* ANSI_GREEN = "\x1b[32m";
static const char* ANSI_RESET = "\x1b[0m";

// Helper function to print a progress bar on a single line
void printProgressBar(int current, int total) {
    // Use carriage return to go back to line start
    std::cout << "\r"; 

    // Calculate percentage
    double fraction = static_cast<double>(current) / total;
    int barWidth = 50;  // width in characters
    int progress = static_cast<int>(fraction * barWidth);

    // Construct the progress bar
    std::cout << "[";
    for (int i = 0; i < barWidth; ++i) {
        if (i < progress) {
            std::cout << "#";
        } else {
            std::cout << " ";
        }
    }
    std::cout << "] " << (int)(fraction * 100) << "% completed";

    // Flush so we see updates immediately
    std::cout.flush();
}

TrafficSim::TrafficSim()
    : m_numIntersections(0),
      m_vehiclesPerStep(0),
      m_maxSteps(0),
      m_greenTime(3),
      m_redTime(2),
      m_currentStep(0)
{
}

TrafficSim::~TrafficSim() {
    if (m_logFile.is_open()) {
        m_logFile.close();
    }
}

bool TrafficSim::initialize(const std::string& configPath) {
    if (!loadConfig(configPath)) {
        return false;
    }

    // Create intersections
    for (int i = 1; i <= m_numIntersections; ++i) {
        Intersection inter(i);
        // For demonstration, set intersection green/red times from config
        inter.setLightTimes(m_greenTime, m_redTime);
        m_intersections.insert({ i, std::move(inter) });
    }

    // Open log file
    m_logFile.open("logs/simulation_log.txt", std::ios::out);
    if (!m_logFile.is_open()) {
        std::cerr << "[Error] Could not open simulation_log.txt for writing.\n";
        return false;
    }

    logMessage("[Initialize] Loaded config. Created intersections.\n");
    return true;
}

void TrafficSim::runSimulation() {
    std::cout << "\nStarting TrafficSim Simulation...\n";

    for (m_currentStep = 1; m_currentStep <= m_maxSteps; ++m_currentStep) {
        spawnVehicles();

        // Update each intersection
        for (auto& kv : m_intersections) {
            Intersection& inter = kv.second;
            inter.update();

            // Color-coded traffic light display in terminal
            bool green = inter.isGreen();
            // Print intersection ID and status
            if (green) {
                std::cout << ANSI_GREEN 
                          << "[Intersection " << inter.getId() << "] GREEN\n" 
                          << ANSI_RESET;
            } else {
                std::cout << ANSI_RED 
                          << "[Intersection " << inter.getId() << "] RED\n" 
                          << ANSI_RESET;
            }
        }

        // Progress bar for the simulation steps
        printProgressBar(m_currentStep, m_maxSteps);

        // Optionally slow down the update to illustrate changes visually
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        // Log step info
        logMessage("[Step " + std::to_string(m_currentStep) + "] Updated intersections.\n");
    }

    // Finish the progress bar line
    std::cout << std::endl << "[Simulation Complete] " 
              << m_maxSteps << " steps processed.\n";
    logMessage("[Simulation Complete] " + std::to_string(m_maxSteps) + " steps processed.\n");
}

bool TrafficSim::loadConfig(const std::string& path) {
    std::ifstream inFile(path);
    if (!inFile.is_open()) {
        std::cerr << "[Error] Could not open config file: " << path << "\n";
        return false;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        // Basic parsing logic (not robust) for "key = value" lines
        if (line.find("intersections") != std::string::npos) {
            m_numIntersections = std::stoi(line.substr(line.find("=") + 1));
        }
        else if (line.find("vehicles_per_step") != std::string::npos) {
            m_vehiclesPerStep = std::stoi(line.substr(line.find("=") + 1));
        }
        else if (line.find("max_simulation_steps") != std::string::npos) {
            m_maxSteps = std::stoi(line.substr(line.find("=") + 1));
        }
        else if (line.find("traffic_light_green_time") != std::string::npos) {
            m_greenTime = std::stoi(line.substr(line.find("=") + 1));
        }
        else if (line.find("traffic_light_red_time") != std::string::npos) {
            m_redTime = std::stoi(line.substr(line.find("=") + 1));
        }
    }
    inFile.close();

    // Basic checks
    return (m_numIntersections > 0 && m_vehiclesPerStep >= 0 && m_maxSteps > 0);
}

void TrafficSim::logMessage(const std::string& message) {
    if (m_logFile.is_open()) {
        m_logFile << message;
    }
}

void TrafficSim::spawnVehicles() {
    // For simplicity, let's create random Car/Truck objects and place them in random intersections
    for (int i = 0; i < m_vehiclesPerStep; ++i) {
        int vehicleId = m_rng.randomInt(100, 999);
        double speed = m_rng.randomDouble(20.0, 80.0);

        // 50% chance for Car, 50% chance for Truck
        if (m_rng.randomInt(0, 1) == 0) {
            auto car = std::make_unique<Car>(vehicleId, speed);
            // Random intersection
            int interId = m_rng.randomInt(1, m_numIntersections);
            m_intersections[interId].addVehicle(std::move(car));
            logMessage("[Step " + std::to_string(m_currentStep) + "] Car spawned at intersection " + std::to_string(interId) + ".\n");
        } else {
            auto truck = std::make_unique<Truck>(vehicleId, speed);
            int interId = m_rng.randomInt(1, m_numIntersections);
            m_intersections[interId].addVehicle(std::move(truck));
            logMessage("[Step " + std::to_string(m_currentStep) + "] Truck spawned at intersection " + std::to_string(interId) + ".\n");
        }
    }
}
