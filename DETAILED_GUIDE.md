# Detailed Guide for TrafficSimCPP

## Adding More Vehicles

To add more vehicles to the TrafficSimCPP project, follow these steps:

1. **Create a New Vehicle Class**:
   - Derive the new vehicle class from `LandVehicle` or another appropriate base class.
   - Implement the required methods, such as `updateState()`.

   ```cpp
   #pragma once
   #include "LandVehicle.h"
   #include <iostream>

   class Motorcycle : public LandVehicle {
   public:
       Motorcycle(int id, double speed)
           : LandVehicle(id, speed, 2) {
       }

       ~Motorcycle() override = default;

       void updateState() override {
           std::cout << "[Motorcycle] ID=" << m_id << " updating state.\n";
       }
   };
   ```

2. **Update the `spawnVehicles` Method**:
   - Modify the `spawnVehicles` method in `TrafficSim.cpp` to include the new vehicle type.

   ```cpp
   void TrafficSim::spawnVehicles() {
       for (int i = 0; i < m_vehiclesPerStep; ++i) {
           int vehicleId = m_rng.randomInt(100, 999);
           double speed = m_rng.randomDouble(20.0, 80.0);

           int vehicleType = m_rng.randomInt(0, 2); // 0: Car, 1: Truck, 2: Motorcycle
           if (vehicleType == 0) {
               auto car = std::make_unique<Car>(vehicleId, speed);
               int interId = m_rng.randomInt(1, m_numIntersections);
               m_intersections.at(interId).addVehicle(std::move(car));
               logMessage("[Step " + std::to_string(m_currentStep) + "] Car spawned at intersection " + std::to_string(interId) + ".\n");
           } else if (vehicleType == 1) {
               auto truck = std::make_unique<Truck>(vehicleId, speed);
               int interId = m_rng.randomInt(1, m_numIntersections);
               m_intersections.at(interId).addVehicle(std::move(truck));
               logMessage("[Step " + std::to_string(m_currentStep) + "] Truck spawned at intersection " + std::to_string(interId) + ".\n");
           } else {
               auto motorcycle = std::make_unique<Motorcycle>(vehicleId, speed);
               int interId = m_rng.randomInt(1, m_numIntersections);
               m_intersections.at(interId).addVehicle(std::move(motorcycle));
               logMessage("[Step " + std::to_string(m_currentStep) + "] Motorcycle spawned at intersection " + std::to_string(interId) + ".\n");
           }
       }
   }
   ```

## Implementing New Features

To implement new features in the TrafficSimCPP project, follow these steps:

1. **Identify the Feature**:
   - Clearly define the new feature you want to implement.

2. **Modify or Add Classes**:
   - Create new classes or modify existing ones to support the new feature.

3. **Update the Simulation Logic**:
   - Modify the simulation logic in `TrafficSim.cpp` to incorporate the new feature.

4. **Test the Feature**:
   - Thoroughly test the new feature to ensure it works as expected.

### Example: Adding a Pedestrian Crossing

1. **Create a Pedestrian Class**:
   ```cpp
   #pragma once
   #include "TrafficObject.h"
   #include <iostream>

   class Pedestrian : public TrafficObject {
   public:
       Pedestrian(int id)
           : m_id(id) {
       }

       ~Pedestrian() override = default;

       void updateState() override {
           std::cout << "[Pedestrian] ID=" << m_id << " crossing.\n";
       }

   private:
       int m_id;
   };
   ```

2. **Update the `Intersection` Class**:
   - Add a method to handle pedestrian crossings.

   ```cpp
   void Intersection::addPedestrian(std::unique_ptr<Pedestrian> p) {
       m_pedestrians.push_back(std::move(p));
   }

   void Intersection::update() {
       // Existing vehicle update logic...

       // Handle pedestrian crossings
       for (auto& pedestrian : m_pedestrians) {
           pedestrian->updateState();
       }
       m_pedestrians.clear();
   }
   ```

3. **Update the `TrafficSim` Class**:
   - Modify the `spawnVehicles` method to include pedestrians.

   ```cpp
   void TrafficSim::spawnVehicles() {
       // Existing vehicle spawning logic...

       // Spawn pedestrians
       int pedestrianId = m_rng.randomInt(1000, 1999);
       auto pedestrian = std::make_unique<Pedestrian>(pedestrianId);
       int interId = m_rng.randomInt(1, m_numIntersections);
       m_intersections.at(interId).addPedestrian(std::move(pedestrian));
       logMessage("[Step " + std::to_string(m_currentStep) + "] Pedestrian spawned at intersection " + std::to_string(interId) + ".\n");
   }
   ```

## Calculations in the Project

The TrafficSimCPP project involves several calculations, including:

1. **Vehicle Speed and Arrival Times**:
   - Randomly generated using the `<random>` library.

2. **Traffic Light Timings**:
   - Configurable via the `config.txt` file.

3. **Intersection Throughput**:
   - Calculated based on the number of vehicles passing through each intersection.

### Example: Random Vehicle Speed Calculation

```cpp
double speed = m_rng.randomDouble(20.0, 80.0);
```

## Importance and Interesting Aspects of the Project

The TrafficSimCPP project is important and interesting for several reasons:

1. **Educational Value**:
   - Demonstrates advanced C++ programming concepts such as inheritance, polymorphism, smart pointers, and STL algorithms.

2. **Simulation Focus**:
   - Emphasizes data processing and simulation logic without relying on a graphical user interface.

3. **Real-World Application**:
   - Models real-world traffic scenarios, making it a valuable tool for understanding traffic flow and intersection management.

## Compiling the Project under Windows

To compile the TrafficSimCPP project under Windows, follow these detailed steps:

1. **Install Prerequisites**:
   - Install a C++14 compliant compiler (e.g., MSVC 2015+).
   - Install CMake 3.5+.

2. **Clone the Repository**:
   ```sh
   git clone https://github.com/MichalZak17/TrafficSimCPP.git
   cd TrafficSimCPP
   ```

3. **Create a Build Directory**:
   ```sh
   mkdir build
   cd build
   ```

4. **Generate Build Files with CMake**:
   ```sh
   cmake ..
   ```

5. **Build the Project**:
   ```sh
   cmake --build .
   ```

6. **Run the Executable**:
   ```sh
   traffic_sim.exe
   ```

### Troubleshooting Tips

- **Ensure CMake is in your PATH**:
  - Add the CMake binary directory to your system PATH.

- **Check Compiler Compatibility**:
  - Ensure your compiler supports C++14.

- **Verify Dependencies**:
  - Ensure all required libraries and headers are available.

- **Consult CMake Output**:
  - Review the CMake output for any errors or warnings.

## Detailed Documentation

### Class: `Car`

The `Car` class represents a car in the traffic simulation. It is derived from the `LandVehicle` class and has specific attributes and behaviors.

#### Constructor
```cpp
Car(int id, double speed);
```
- `id`: The unique identifier for the car.
- `speed`: The speed of the car.

#### Destructor
```cpp
~Car();
```

#### Method: `updateState`
```cpp
void updateState() override;
```
Updates the state of the car during each simulation step.

### Class: `Intersection`

The `Intersection` class represents a traffic intersection in the simulation. It manages the traffic light and the vehicles waiting at the intersection.

#### Constructor
```cpp
Intersection(int id);
```
- `id`: The unique identifier for the intersection.

#### Method: `setLightTimes`
```cpp
void setLightTimes(int green, int red);
```
Sets the traffic light times for the intersection.
- `green`: The duration of the green light.
- `red`: The duration of the red light.

#### Method: `addVehicle`
```cpp
void addVehicle(std::unique_ptr<Vehicle> v);
```
Adds a vehicle to the intersection's waiting queue.
- `v`: A unique pointer to the vehicle to be added.

#### Method: `update`
```cpp
void update();
```
Updates the state of the intersection, including the traffic light and the vehicles waiting at the intersection.

#### Method: `getId`
```cpp
int getId() const;
```
Returns the unique identifier of the intersection.

#### Method: `isGreen`
```cpp
bool isGreen() const;
```
Checks if the traffic light is green.

#### Method: `getWaitingCount`
```cpp
int getWaitingCount() const;
```
Returns the number of vehicles waiting at the intersection.

#### Method: `getThroughput`
```cpp
int getThroughput() const;
```
Returns the total number of vehicles that have passed through the intersection.

#### Method: `getPassedThisStep`
```cpp
int getPassedThisStep() const;
```
Returns the number of vehicles that passed through the intersection in the current step.

### Class: `LandVehicle`

The `LandVehicle` class represents a land vehicle in the traffic simulation. It is derived from the `Vehicle` class and has specific attributes and behaviors.

#### Constructor
```cpp
LandVehicle(int id, double speed, int wheels);
```
- `id`: The unique identifier for the land vehicle.
- `speed`: The speed of the land vehicle.
- `wheels`: The number of wheels of the land vehicle.

#### Destructor
```cpp
virtual ~LandVehicle();
```

#### Method: `getNumWheels`
```cpp
int getNumWheels() const;
```
Returns the number of wheels of the land vehicle.

### Class: `RandomGen`

The `RandomGen` class handles random number generation for the traffic simulation. It provides methods to generate random integers and doubles within specified ranges.

#### Constructor
```cpp
RandomGen();
```

#### Destructor
```cpp
~RandomGen();
```

#### Method: `randomInt`
```cpp
int randomInt(int minVal, int maxVal);
```
Generates a random integer within the specified range.
- `minVal`: The minimum value of the range (inclusive).
- `maxVal`: The maximum value of the range (inclusive).

#### Method: `randomDouble`
```cpp
double randomDouble(double minVal, double maxVal);
```
Generates a random double within the specified range.
- `minVal`: The minimum value of the range (inclusive).
- `maxVal`: The maximum value of the range (inclusive).

### Class: `TrafficObject`

The `TrafficObject` class is an abstract base class representing any traffic-related object. It defines a pure virtual method for updating the state of the object during each simulation step.

#### Destructor
```cpp
virtual ~TrafficObject();
```

#### Method: `updateState`
```cpp
virtual void updateState() = 0;
```
Pure virtual method for updating the state of the object. This method must be implemented by derived classes.

### Class: `TrafficSim`

The `TrafficSim` class manages the traffic simulation. It is responsible for initializing the simulation, loading the configuration, spawning vehicles, updating intersections, and logging the simulation progress.

#### Constructor
```cpp
TrafficSim();
```

#### Destructor
```cpp
~TrafficSim();
```

#### Method: `initialize`
```cpp
bool initialize(const std::string &configPath);
```
Initializes the simulation with the given configuration file.
- `configPath`: The path to the configuration file.

#### Method: `runSimulation`
```cpp
void runSimulation();
```
Runs the traffic simulation.

#### Method: `loadConfig`
```cpp
bool loadConfig(const std::string &path);
```
Loads the configuration from the specified file.
- `path`: The path to the configuration file.

#### Method: `logMessage`
```cpp
void logMessage(const std::string& message);
```
Logs a message to the simulation log file.
- `message`: The message to be logged.

#### Method: `spawnVehicles`
```cpp
void spawnVehicles();
```
Spawns vehicles at random intersections.

#### Method: `recordStepData`
```cpp
void recordStepData();
```
Records the state of the simulation at each step.

#### Method: `generateReport`
```cpp
void generateReport(const std::string &filename);
```
Generates a final report of the simulation.
- `filename`: The name of the report file.

### Class: `Truck`

The `Truck` class represents a truck in the traffic simulation. It is derived from the `LandVehicle` class and has specific attributes and behaviors.

#### Constructor
```cpp
Truck(int id, double speed);
```
- `id`: The unique identifier for the truck.
- `speed`: The speed of the truck.

#### Destructor
```cpp
~Truck();
```

#### Method: `updateState`
```cpp
void updateState() override;
```
Updates the state of the truck during each simulation step.

### Class: `Vehicle`

The `Vehicle` class is an abstract base class representing a vehicle in the traffic simulation. It defines common attributes and methods for vehicles, including ID, speed, and state update.

#### Constructor
```cpp
Vehicle(int id, double speed);
```
- `id`: The unique identifier for the vehicle.
- `speed`: The speed of the vehicle.

#### Destructor
```cpp
virtual ~Vehicle();
```

#### Copy Constructor
```cpp
Vehicle(const Vehicle& other);
```
- `other`: The Vehicle object to copy from.

#### Move Constructor
```cpp
Vehicle(Vehicle&& other) noexcept;
```
- `other`: The Vehicle object to move from.

#### Move Assignment Operator
```cpp
Vehicle& operator=(Vehicle&& other) noexcept;
```
- `other`: The Vehicle object to move from.

#### Method: `updateState`
```cpp
virtual void updateState() override = 0;
```
Pure virtual method for updating the state of the vehicle. This method must be implemented by derived classes.

#### Method: `getId`
```cpp
int getId() const;
```
Returns the unique identifier of the vehicle.

#### Method: `getSpeed`
```cpp
double getSpeed() const;
```
Returns the speed of the vehicle.
