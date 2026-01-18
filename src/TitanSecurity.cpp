#include "TitanSecurity.hpp"
#include <iostream>

TitanSecurity::TitanSecurity() {
    systemArmed = false;
    currentMode = "Day";
    alarm = std::make_shared<Alarm>();
    
    // Initialize sensors
    Sensors.push_back(std::make_shared<DoorSensor>("Front Door", "Entry", 0));
    Sensors.push_back(std::make_shared<MotionSensor>("Living Room Motion", "Living Room", 0));
    Sensors.push_back(std::make_shared<HeatSensor>("Kitchen Heat", "Kitchen", 25));
}

void TitanSecurity::setMode(std::string mode) {
    if (mode == "Day" || mode == "Night" || mode == "Away") {
        currentMode = mode;
        std::cout << "[System] Mode set to: " << mode << std::endl;
        if (mode == "Away") {
            systemArmed = true;
        } else {
            systemArmed = false;
        }
    } else {
        std::cout << "[Error] Unknown mode." << std::endl;
    }
}

void TitanSecurity::pollSensors() {
    std::cout << "\n--- Polling Sensors (" << currentMode << " Mode) ---" << std::endl;

    for (size_t i = 0; i < Sensors.size(); i++) {
        auto sensor = Sensors[i];
        std::string name = sensor->getName();
        std::string location = sensor->getLocation();
        int data = sensor->getData();

        // Check sensor type using dynamic_cast
        if (auto doorSensor = std::dynamic_pointer_cast<DoorSensor>(sensor)) {
            // DoorSensor logic
            std::cout << "Reading " << name << "... ";
            if (data == 1 && systemArmed) {
                std::cout << "! Triggering Alarm!" << std::endl;
                alarm->triggerAlarm("High", "Police");
            } else {
                std::cout << "Secure." << std::endl;
            }
        }
        else if (auto motionSensor = std::dynamic_pointer_cast<MotionSensor>(sensor)) {
            // MotionSensor logic
            std::cout << "Reading " << name << "... ";
            if (data == 1 && currentMode == "Away") {
                std::cout << "MOTION DETECTED!" << std::endl;
                alarm->triggerAlarm("Medium", "UserPhone");
            } else {
                std::cout << "No Motion." << std::endl;
            }
        }
        else if (auto heatSensor = std::dynamic_pointer_cast<HeatSensor>(sensor)) {
            // HeatSensor logic
            std::cout << "Reading " << name << "... Temp: " << data << "C. ";
            if (data > 50) {
                std::cout << "DANGER! FIRE!" << std::endl;
                alarm->triggerAlarm("Critical", "FireDept");
            } else {
                std::cout << "Normal." << std::endl;
            }
        }
        else {
            std::cout << "[Warning] Unknown sensor type found in index " << i << std::endl;
        }
    }
}

void TitanSecurity::simulateSensorInput(int index, int value) {
    if (index >= 0 && index < Sensors.size()) {
        Sensors[index]->setData(value);
    }
}

void TitanSecurity::generateReport() {
    std::cout << "\nGenerating System Report..." << std::endl;
    std::cout << "Sensors Online: " << Sensors.size() << std::endl;
    std::cout << "System Armed: " << (systemArmed ? "YES" : "NO") << std::endl;
    // ... heavy logic for report formatting ...
}
