# 🔒 Titan Security System - SOLID Principles Refactoring

[![C++](https://img.shields.io/badge/C++-17-blue.svg)](https://en.cppreference.com/w/cpp/17)
[![License](https://img.shields.io/badge/license-MIT-green.svg)](LICENSE)

> **A practical demonstration of SOLID principles applied to refactor a monolithic security system into a maintainable, extensible architecture**

## 📋 Overview

This project demonstrates the application of **SOLID principles** by refactoring a monolithic home security system into a well-structured, object-oriented design. The original code violated multiple SOLID principles, making it difficult to maintain and extend. Through systematic refactoring, each principle is now properly implemented, resulting in clean, modular, and extensible code.

## 🎯 Project Goals

- **Demonstrate SOLID principles** in a real-world refactoring scenario
- **Show before/after** comparison of code quality
- **Provide practical examples** of each SOLID principle
- **Create maintainable code** that's easy to extend and test

## 📑 Table of Contents

- [SOLID Principles Overview](#-solid-principles-overview)
- [Before: Violations of SOLID](#-before-violations-of-solid)
- [After: SOLID Principles Applied](#-after-solid-principles-applied)
  - [S - Single Responsibility Principle](#s---single-responsibility-principle)
  - [O - Open/Closed Principle](#o---openclosed-principle)
  - [L - Liskov Substitution Principle](#l---liskov-substitution-principle)
  - [I - Interface Segregation Principle](#i---interface-segregation-principle)
  - [D - Dependency Inversion Principle](#d---dependency-inversion-principle)
- [Architecture](#️-architecture)
- [Building and Running](#-building-and-running)
- [Code Structure](#-code-structure)
- [Example Usage](#-example-usage)

## 🧩 SOLID Principles Overview

**SOLID** is an acronym for five object-oriented design principles that make software more maintainable, flexible, and understandable:

1. **S** - **Single Responsibility Principle**: A class should have one reason to change
2. **O** - **Open/Closed Principle**: Open for extension, closed for modification
3. **L** - **Liskov Substitution Principle**: Derived classes must be substitutable for their base classes
4. **I** - **Interface Segregation Principle**: Clients shouldn't depend on interfaces they don't use
5. **D** - **Dependency Inversion Principle**: Depend on abstractions, not concretions

## ❌ Before: Violations of SOLID

### Original Monolithic Design (`TitanSecurityHub.cpp`)

The original code had a single `TitanSystem` class that violated all SOLID principles:

```cpp
class TitanSystem {
    // Violates SRP: Handles sensors, alarms, sound, notifications, logging
    // Violates OCP: Adding new sensors requires modifying this class
    // Violates LSP: No inheritance hierarchy
    // Violates ISP: No interfaces, everything is concrete
    // Violates DIP: Depends on concrete implementations
};
```

**Problems:**
- ❌ **SRP Violation**: One class handled sensors, alarms, sound, notifications, and logging
- ❌ **OCP Violation**: Adding new sensor types required modifying the core `pollSensors()` method
- ❌ **LSP Violation**: No inheritance hierarchy, sensors stored as parallel vectors
- ❌ **ISP Violation**: No interfaces, all functionality mixed together
- ❌ **DIP Violation**: Direct dependencies on concrete implementations

## ✅ After: SOLID Principles Applied

### S - Single Responsibility Principle

> **"A class should have one, and only one, reason to change."**

**Implementation:**

Each class now has a single, well-defined responsibility:

- **`Sensor`**: Manages sensor data (name, location, value)
- **`DoorSensor`**: Represents a door sensor specifically
- **`MotionSensor`**: Represents a motion sensor specifically
- **`HeatSensor`**: Represents a heat sensor specifically
- **`Sound`**: Handles only sound playback
- **`Notify`**: Handles only notifications
- **`Log`**: Handles only file logging
- **`Alarm`**: Coordinates alarm triggering (delegates to Sound, Notify, Log)
- **`TitanSecurity`**: Manages system state and sensor polling

**Example:**

```cpp
// BEFORE: One class does everything
class TitanSystem {
    void triggerAlarm() {
        // Sound logic
        // Notification logic  
        // Logging logic
        // All mixed together!
    }
};

// AFTER: Each class has one responsibility
class Sound {
    void makeSound(std::string severity);  // Only sound
};

class Notify {
    void send(std::string sendWho);  // Only notifications
};

class Log {
    static void logToFile(std::string message);  // Only logging
};

class Alarm {
    void triggerAlarm(std::string severity, std::string sendWho) {
        makeSound(severity);    // Delegates to Sound
        send(sendWho);          // Delegates to Notify
        logToFile(...);        // Delegates to Log
    }
};
```

### O - Open/Closed Principle

> **"Software entities should be open for extension, but closed for modification."**

**Implementation:**

The system is now open for extension (new sensor types) without modifying existing code:

- **Base `Sensor` class**: Defines the interface for all sensors
- **Derived sensor classes**: Extend functionality without changing base class
- **`TitanSecurity`**: Works with `Sensor` base class, doesn't need changes for new sensors

**Example:**

```cpp
// BEFORE: Must modify pollSensors() to add new sensor type
void pollSensors() {
    if (type == "DoorSensor") { /* ... */ }
    else if (type == "MotionSensor") { /* ... */ }
    else if (type == "HeatSensor") { /* ... */ }
    // Adding WindowSensor requires modifying this method!
}

// AFTER: Add new sensor without modifying existing code
class WindowSensor : public Sensor, public IWindow {
    // New sensor type - no changes to TitanSecurity needed!
};

// TitanSecurity works with Sensor base class
void TitanSecurity::pollSensors() {
    for (auto sensor : Sensors) {
        // Works with any Sensor-derived class
        if (auto windowSensor = std::dynamic_pointer_cast<WindowSensor>(sensor)) {
            // Handle window sensor
        }
    }
}
```

### L - Liskov Substitution Principle

> **"Objects of a superclass should be replaceable with objects of its subclasses without breaking the application."**

**Implementation:**

All sensor types can be used interchangeably through the `Sensor` base class:

- **`Sensor` base class**: Defines common interface (getName, getLocation, getData)
- **Derived classes**: Can be substituted anywhere a `Sensor` is expected
- **Polymorphism**: `TitanSecurity` stores `std::shared_ptr<Sensor>`, works with any sensor type

**Example:**

```cpp
// All sensor types are substitutable
std::vector<std::shared_ptr<Sensor>> Sensors;

Sensors.push_back(std::make_shared<DoorSensor>(...));
Sensors.push_back(std::make_shared<MotionSensor>(...));
Sensors.push_back(std::make_shared<HeatSensor>(...));

// All can be used the same way
for (auto sensor : Sensors) {
    std::string name = sensor->getName();      // Works for all
    std::string loc = sensor->getLocation();   // Works for all
    int data = sensor->getData();              // Works for all
}
```

### I - Interface Segregation Principle

> **"Clients should not be forced to depend on interfaces they do not use."**

**Implementation:**

Interfaces are segregated by functionality:

- **`IDoor`**: Interface for door-related functionality
- **`IMotion`**: Interface for motion-related functionality
- **`IHeat`**: Interface for heat-related functionality
- **Sensors implement only relevant interfaces**: `DoorSensor` implements `IDoor`, not `IMotion` or `IHeat`

**Example:**

```cpp
// BEFORE: No interfaces, everything mixed
class TitanSystem {
    // Forced to depend on all sensor types
};

// AFTER: Segregated interfaces
class IDoor {
    virtual ~IDoor() = default;
};

class IMotion {
    virtual ~IMotion() = default;
};

class IHeat {
    virtual ~IHeat() = default;
};

// Sensors only implement what they need
class DoorSensor : public Sensor, public IDoor {
    // Only door-related interface
};

class MotionSensor : public Sensor, public IMotion {
    // Only motion-related interface
};
```

### D - Dependency Inversion Principle

> **"Depend upon abstractions, not concretions."**

**Implementation:**

High-level modules depend on abstractions, not concrete implementations:

- **`TitanSecurity`**: Depends on `Sensor` abstraction, not concrete sensor types
- **`Alarm`**: Depends on `Sound`, `Notify`, `Log` abstractions
- **Polymorphism**: Uses base class pointers (`std::shared_ptr<Sensor>`)

**Example:**

```cpp
// BEFORE: Depends on concrete types
class TitanSystem {
    vector<string> sensorTypes;  // Concrete strings
    // Direct dependency on specific sensor implementations
};

// AFTER: Depends on abstractions
class TitanSecurity {
private:
    std::vector<std::shared_ptr<Sensor>> Sensors;  // Abstract base class
    std::shared_ptr<Alarm> alarm;                  // Abstract interface
    
    // Works with any Sensor-derived class
    void pollSensors() {
        for (auto sensor : Sensors) {  // Uses abstraction
            // Process sensor through base class interface
        }
    }
};
```

## 🏗️ Architecture

### Class Hierarchy

```
Sensor (Abstract Base Class)
├── DoorSensor (inherits Sensor + IDoor)
├── MotionSensor (inherits Sensor + IMotion)
└── HeatSensor (inherits Sensor + IHeat)

Alarm (Multiple Inheritance - Composition)
├── Sound (SRP: handles sound only)
├── Notify (SRP: handles notifications only)
└── Log (SRP: handles logging only)

TitanSecurity (High-level Module)
├── Depends on Sensor abstraction (DIP)
├── Manages collection of Sensor pointers (LSP)
└── Uses interfaces, not concrete types (ISP)
```

### SOLID Principles in Architecture

| Principle | Implementation |
|-----------|---------------|
| **SRP** | Each class (`Sound`, `Notify`, `Log`, `Sensor`) has one responsibility |
| **OCP** | New sensors extend `Sensor` without modifying `TitanSecurity` |
| **LSP** | All sensor types are substitutable through `Sensor` base class |
| **ISP** | Interfaces (`IDoor`, `IMotion`, `IHeat`) are segregated by functionality |
| **DIP** | `TitanSecurity` depends on `Sensor` abstraction, not concrete types |

## 🚀 Building and Running

### Prerequisites
- C++17 compatible compiler (g++ or clang++)
- Make

### Build Commands

```bash
# Build the project
make

# Build and run
make run

# Clean build artifacts
make clean

# Rebuild from scratch
make rebuild
```

### Output Files
- **Executable**: `titan_security`
- **Log File**: `info.txt` (created automatically when alarms trigger)

## 📁 Code Structure

```
TitanSec/
├── include/           # Header files
│   ├── Sensor.hpp           # Base class (SRP, LSP, DIP)
│   ├── DoorSensor.hpp       # Derived class (OCP, LSP)
│   ├── MotionSensor.hpp     # Derived class (OCP, LSP)
│   ├── HeatSensor.hpp       # Derived class (OCP, LSP)
│   ├── IDoor.hpp            # Interface (ISP)
│   ├── IMotion.hpp          # Interface (ISP)
│   ├── IHeat.hpp            # Interface (ISP)
│   ├── Alarm.hpp            # Coordinator (SRP, DIP)
│   ├── Sound.hpp            # Single responsibility (SRP)
│   ├── Notify.hpp           # Single responsibility (SRP)
│   ├── Log.hpp              # Single responsibility (SRP)
│   └── TitanSecurity.hpp    # High-level module (DIP)
├── src/              # Implementation files
│   ├── Alarm.cpp
│   ├── Sound.cpp
│   ├── Notify.cpp
│   ├── Log.cpp
│   └── TitanSecurity.cpp
├── main.cpp          # Entry point
├── Makefile          # Build configuration
└── README.md         # This file
```

## 💡 Example Usage

```cpp
#include "TitanSecurity.hpp"

int main() {
    // Create security system (uses abstractions - DIP)
    TitanSecurity homeSecurity;
    
    // Set mode
    homeSecurity.setMode("Away");
    
    // Poll sensors (works with any Sensor type - LSP)
    homeSecurity.pollSensors();
    
    // Simulate sensor input
    homeSecurity.simulateSensorInput(0, 1);  // Door opens
    homeSecurity.pollSensors();  // Triggers alarm
    
    // Generate report
    homeSecurity.generateReport();
    
    return 0;
}
```

## 📊 SOLID Principles Summary

| Principle | Before | After |
|-----------|--------|-------|
| **SRP** | ❌ One class does everything | ✅ Each class has one responsibility |
| **OCP** | ❌ Must modify code to add sensors | ✅ Extend via inheritance, no modification |
| **LSP** | ❌ No inheritance, parallel vectors | ✅ All sensors substitutable via base class |
| **ISP** | ❌ No interfaces, everything mixed | ✅ Segregated interfaces by functionality |
| **DIP** | ❌ Depends on concrete types | ✅ Depends on abstractions (Sensor base class) |

## 🎓 Key Takeaways

1. **Single Responsibility** makes code easier to understand and maintain
2. **Open/Closed** allows extension without breaking existing functionality
3. **Liskov Substitution** enables polymorphism and code reuse
4. **Interface Segregation** prevents unnecessary dependencies
5. **Dependency Inversion** makes code flexible and testable

## 📚 References

- [SOLID Principles (Wikipedia)](https://en.wikipedia.org/wiki/SOLID)
- [Clean Code by Robert C. Martin](https://www.amazon.com/Clean-Code-Handbook-Software-Craftsmanship/dp/0132350882)
- [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)
