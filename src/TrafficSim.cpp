#include "TrafficSim.h"
#include "Car.h"
#include "Truck.h"
#include <iostream>
#include <algorithm>
#include <thread>
#include <chrono>
#include <sstream>

// ----------------------------------------------------------------
//    ANSI Escape Codes & Utility
// ----------------------------------------------------------------
static const char *ANSI_CLEAR_SCREEN = "\x1b[2J\x1b[H";
static const char *ANSI_RED = "\x1b[31m";
static const char *ANSI_GREEN = "\x1b[32m";
static const char *ANSI_YELLOW = "\x1b[33m";
static const char *ANSI_RESET = "\x1b[0m";

static const char spinnerChars[] = {'|', '/', '-', '\\'};
static int spinnerIndex = 0;

// Helper to show a rotating spinner or progress
static void printSpinner(int currentStep, int totalSteps)
{
    double fraction = (double)currentStep / totalSteps * 100.0;
    // e.g. "[Step 3/10] Progress: 30% /
    std::cout << "[Step " << currentStep << "/" << totalSteps << "] ";
    std::cout << "Progress: " << (int)fraction << "% ";
    std::cout << spinnerChars[spinnerIndex++ % 4] << "\n";
}

// We can use a utility function to repeat a character (for bar charts)
static std::string repeatChar(char c, int times)
{
    if (times <= 0)
        return "";
    return std::string(times, c);
}

// ----------------------------------------------------------------
//   TrafficSim Constructor/Destructor
// ----------------------------------------------------------------
TrafficSim::TrafficSim()
    : m_numIntersections(0),
      m_vehiclesPerStep(0),
      m_maxSteps(0),
      m_greenTime(3),
      m_redTime(2),
      m_currentStep(0)
{
}

TrafficSim::~TrafficSim()
{
    if (m_logFile.is_open()) {
        m_logFile.close();
    }
}

// ----------------------------------------------------------------
//   initialize & loadConfig
// ----------------------------------------------------------------
bool TrafficSim::initialize(const std::string &configPath)
{
    if (!loadConfig(configPath)) {
        return false;
    }

    // Create intersections
    for (int i = 1; i <= m_numIntersections; ++i) {
        Intersection inter(i);
        // If you want to set per-intersection times from config:
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

bool TrafficSim::loadConfig(const std::string &path)
{
    std::ifstream inFile(path);
    if (!inFile.is_open()) {
        std::cerr << "[Error] Could not open config file: " << path << "\n";
        return false;
    }

    std::string line;
    while (std::getline(inFile, line))
    {
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

    return (m_numIntersections > 0 && m_vehiclesPerStep >= 0 && m_maxSteps > 0);
}

void TrafficSim::logMessage(const std::string &message)
{
    if (m_logFile.is_open()) {
        m_logFile << message;
    }
}

// ----------------------------------------------------------------
//   spawnVehicles (basic version)
// ----------------------------------------------------------------
void TrafficSim::spawnVehicles()
{
    for (int i = 0; i < m_vehiclesPerStep; ++i) {
        int vehicleId = m_rng.randomInt(100, 999);
        double speed = m_rng.randomDouble(20.0, 80.0);

        // 50% chance for Car, 50% for Truck
        if (m_rng.randomInt(0, 1) == 0) {
            auto car = std::make_unique<Car>(vehicleId, speed);
            int interId = m_rng.randomInt(1, m_numIntersections);
            m_intersections.at(interId).addVehicle(std::move(car));
            logMessage("[Step " + std::to_string(m_currentStep) + "] Car spawned at intersection " + std::to_string(interId) + ".\n");
        } else {
            auto truck = std::make_unique<Truck>(vehicleId, speed);
            int interId = m_rng.randomInt(1, m_numIntersections);
            m_intersections.at(interId).addVehicle(std::move(truck));
            logMessage("[Step " + std::to_string(m_currentStep) + "] Truck spawned at intersection " + std::to_string(interId) + ".\n");
        }
    }
}

// ----------------------------------------------------------------
//   The "Cool" Printing Functions
// ----------------------------------------------------------------

// 1) ASCII Map
static void printAsciiMap(const std::map<int, Intersection> &intersections)
{
    std::cout << "[ASCII Map]\n";

    std::ostringstream topLine;
    std::ostringstream botLine;

    // We’ll just place them in a row: (I1)---- (I2)---- etc.
    for (auto &kv : intersections)
    {
        const Intersection &inter = kv.second;

        // Red or Green label
        bool g = inter.isGreen();
        const char *color = g ? ANSI_GREEN : ANSI_RED;
        topLine << color << "(I" << inter.getId() << ")" << ANSI_RESET << "----- ";

        // Vehicles in waiting queue
        int waiting = inter.getWaitingCount();
        if (waiting > 0)
        {
            std::string vehicles;
            for (int w = 0; w < waiting; ++w)
            {
                vehicles += "V ";
            }
            botLine << "I" << inter.getId() << ": " << vehicles << "   ";
        }
        else
        {
            botLine << "I" << inter.getId() << ": (empty)   ";
        }
    }

    std::cout << topLine.str() << "\n"
              << botLine.str() << "\n\n";
}

// 2) Intersections Table
static void printIntersectionsTable(const std::map<int, Intersection> &intersections)
{
    std::cout << "ID | Status | Waiting | PassedThisStep | Throughput\n";
    std::cout << "---+--------+---------+----------------+-----------\n";

    for (auto &kv : intersections)
    {
        const Intersection &inter = kv.second;

        bool g = inter.isGreen();
        const char *color = g ? ANSI_GREEN : ANSI_RED;
        std::string colorStr = g ? "GREEN " : "RED   ";

        std::cout << inter.getId() << "  | "
                  << color << colorStr << ANSI_RESET << " | "
                  << inter.getWaitingCount() << "       | "
                  << inter.getPassedThisStep() << "              | "
                  << inter.getThroughput() << "\n";
    }
    std::cout << "\n";
}

// 3) Throughput Bar Chart
static void printThroughputBars(const std::map<int, Intersection> &intersections)
{
    std::cout << "[Throughput Bar Chart]\n";

    // Find max
    int maxThroughput = 0;
    for (auto &kv : intersections)
    {
        if (kv.second.getThroughput() > maxThroughput)
        {
            maxThroughput = kv.second.getThroughput();
        }
    }
    if (maxThroughput == 0)
    {
        maxThroughput = 1; // avoid dividing by zero
    }

    int maxBarWidth = 30;
    for (auto &kv : intersections)
    {
        const Intersection &inter = kv.second;
        int th = inter.getThroughput();

        int barLength = static_cast<int>((double)th / maxThroughput * maxBarWidth);
        const char *color = ANSI_GREEN;
        if (th > 10 && th <= 20)
        {
            color = ANSI_YELLOW;
        }
        else if (th > 20)
        {
            color = ANSI_RED;
        }

        std::string bar = repeatChar('#', barLength);
        std::cout << "Intersection " << inter.getId() << ": "
                  << color << bar << ANSI_RESET
                  << " (" << th << ")\n";
    }
    std::cout << "\n";
}

// ----------------------------------------------------------------
//   runSimulation
// ----------------------------------------------------------------
void TrafficSim::runSimulation()
{
    std::cout << "\nStarting TrafficSim Simulation...\n";

    for (m_currentStep = 1; m_currentStep <= m_maxSteps; ++m_currentStep)
    {
        // 1) Spawn new vehicles
        spawnVehicles();

        // 2) Update each intersection
        for (auto &kv : m_intersections)
        {
            kv.second.update();
        }

        // 3) Fancy display
        std::cout << ANSI_CLEAR_SCREEN;
        std::cout << "=== TrafficSimCPP Live Dashboard ===\n\n";

        // Spinner
        printSpinner(m_currentStep, m_maxSteps);
        std::cout << "\n";

        // ASCII map
        printAsciiMap(m_intersections);

        // Intersections table
        printIntersectionsTable(m_intersections);

        // Throughput bars
        printThroughputBars(m_intersections);

        // Log step info
        logMessage("[Step " + std::to_string(m_currentStep) + "] Updated intersections.\n");

        // Delay so the updates are visible
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
    }

    // Final message
    std::cout << ANSI_CLEAR_SCREEN;
    std::cout << "=== TrafficSimCPP Simulation Complete ===\n\n"
              << "Total steps: " << m_maxSteps << "\n"
              << "Check logs/simulation_log.txt for details.\n\n";

    logMessage("[Simulation Complete] " + std::to_string(m_maxSteps) + " steps processed.\n");
}
