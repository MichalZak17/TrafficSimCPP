# TrafficSimCPP 🚦

A **terminal-based Traffic Intersection Simulator** written in **C++14**.  
This project demonstrates advanced C++ programming concepts including **multi-level inheritance, operator overloading, smart pointers, STL algorithms, move semantics, and file I/O**. The simulator models vehicles arriving and passing through intersections, applying traffic rules and random event generation—all without any GUI or online dependency.

## 🚀 Features

- **Multi-Level Inheritance**: A clear vehicle hierarchy (`Vehicle` → `LandVehicle` → `Car`, `Truck`, `Bus`) with polymorphism.
- **Operator Overloading**: Custom overloads (e.g., `operator<` and `operator==`) for comparing and printing objects.
- **Move Semantics**: Efficient object transfers using move constructors and move assignment operators.
- **Smart Pointers**: Management of dynamic memory using `std::unique_ptr` (available in C++14).
- **STL Algorithms & Containers**: Usage of `std::vector`, `std::map`, `std::sort`, `std::for_each`, and other algorithms to process simulation data.
- **Random Data Generation**: Utilize C++ random libraries for generating vehicle arrival times, speeds, and traffic light cycles.
- **File I/O**: Read simulation settings from configuration files and output logs/results to text files.
- **Simulation-Focused Design**: Emphasizes processing data rather than simply storing it, with no keyboard input during simulation.

## 📦 Installation

### Prerequisites
- A C++14 compliant compiler (GCC 5+, Clang 3.4+, MSVC 2015+)
- CMake 3.5+ (optional for build automation)

### Clone the Repository
```sh
git clone https://github.com/MichalZak17/TrafficSimCPP.git
cd TrafficSimCPP
```

### Build and Run
#### Using Make (Linux/macOS)
```sh
mkdir build && cd build
cmake ..
make
./traffic_sim
```

#### Using MSVC (Windows)
```sh
mkdir build
cd build
cmake ..
cmake --build .
traffic_sim.exe
```

## 📖 Usage

The simulation runs automatically using parameters from a **configuration file**. You can modify `config/config.txt` to adjust:
- Number of intersections
- Vehicle arrival frequency
- Traffic light timings

### Example Configuration (`config/config.txt`)
```ini
intersections = 3
vehicles_per_step = 5
max_simulation_steps = 100
traffic_light_green_time = 30
traffic_light_red_time = 20
```

## 🔧 Project Structure
```
TrafficSimCPP/
│── src/
│   ├── main.cpp         # Entry point
│   ├── TrafficObject.h  # Base class for all traffic entities
│   ├── Vehicle.h        # Abstract vehicle class with common attributes and virtual functions
│   ├── LandVehicle.h    # Derived class adding land-specific features
│   ├── Car.h            # Further derived class for Car
│   ├── Truck.h          # Further derived class for Truck
│   ├── Intersection.h   # Manages traffic flow and vehicle queues
│   ├── TrafficSim.h     # Simulation coordinator class
│   ├── RandomGen.h      # Handles random number generation
│── config/
│   ├── config.txt       # Simulation settings
│── logs/
│   ├── simulation_log.txt # Output logs
│── build/               # Compiled binaries (ignored in git)
│── CMakeLists.txt       # CMake build script
│── README.md            # This file
│── LICENSE              # Open-source license
```

## 🎯 Example Output

```
[Step 1] Vehicle ID=101 (Car) entered Intersection #2
[Step 2] Traffic light turned RED at Intersection #2
[Step 3] Vehicle ID=102 (Truck) waiting at Intersection #2
...
[Simulation Complete] 100 steps processed.
```

## 🛠️ Technologies Used

- **C++14**
- **STL Containers & Algorithms**
- **Smart Pointers (`std::unique_ptr`)**
- **Lambda Functions**
- **Move Semantics**
- **File I/O (fstream)**
- **Random Number Generation**

## 📜 License

Licensed under the **MIT License**. See [LICENSE](LICENSE) for details.

## 🤝 Contributing

We welcome contributions! To contribute:
1. Fork the repository.
2. Create a feature branch (`git checkout -b feature-name`).
3. Commit your changes (`git commit -m "Add feature"`).
4. Push to your fork and create a Pull Request.

## 💡 Future Improvements
- Enhance simulation realism by adding multi-lane intersections.
- Implement adaptive traffic light timings.
- Introduce varying vehicle behaviors and environmental factors.

## 🏆 Acknowledgments

Thanks to the contributors and maintainers who help make TrafficSimCPP a robust learning tool for modern C++ development.
```

---

### Updated Project Requirements for C++14

1. **Core C++ Concepts:**
   - Use **function overloading**, **reference parameters**, **member initializer lists**, and **copy constructors**.
   - Implement aggregation of objects (has-a relationship) and manage object lifetimes with destructors.
   - Demonstrate the use of **operator overloading** (e.g., `operator<` and `operator==`), as C++14 does not include the spaceship operator.
   - Utilize **move constructors** and **move assignment operators** to efficiently manage resources.

2. **Inheritance and Polymorphism:**
   - Build a multi-level inheritance hierarchy:
     - Abstract base class (`TrafficObject`)
     - Derived abstract class (`Vehicle`)
     - Concrete intermediate class (`LandVehicle`)
     - Further specialized classes (`Car`, `Truck`, `Bus`)
   - Implement pure virtual functions and override them in derived classes.

3. **STL Containers and Algorithms:**
   - Employ at least two types of containers: one sequential (e.g., `std::vector`) and one associative (e.g., `std::map`).
   - Utilize STL algorithms such as `std::sort`, `std::for_each`, `std::remove_if`, and `std::copy`.

4. **Random Data Generation:**
   - Use the C++ `<random>` library for generating random vehicle attributes (arrival times, speeds) and traffic light cycles.

5. **File I/O:**
   - Read simulation configuration from a file.
   - Write simulation logs and final statistics to output files.

6. **Smart Pointers and Lambdas:**
   - Manage dynamic memory with `std::unique_ptr` to prevent memory leaks.
   - Replace manual loops with STL algorithms combined with lambda expressions where possible.

7. **Simulation-Oriented Design:**
   - Ensure the program's functionality is focused on data processing and simulation, avoiding direct keyboard input.
   - Maintain a clear separation between simulation logic and data storage.
