#include "TitanSecurity.hpp"
#include <iostream>
#include <exception>

int main() {
    try {
        TitanSecurity homeSecurity;

        std::cout << "--- Titan Security System v2.0 (Refactored) ---\n" << std::endl;

        // 1. Initial system report
        std::cout << "[INITIAL STATE]" << std::endl;
        homeSecurity.generateReport();

        // 2. Set system to Away mode
        std::cout << "\n[SETTING MODE]" << std::endl;
        homeSecurity.setMode("Away");

        // 3. Poll sensors in normal state
        std::cout << "\n[SCENARIO 1: Normal Check]" << std::endl;
        homeSecurity.pollSensors();

        // 4. Intruder scenario - door opens
        std::cout << "\n[SCENARIO 2: Intruder breaks open the front door...]" << std::endl;
        homeSecurity.simulateSensorInput(0, 1); // Index 0 is Door, set to 1 (Open)
        homeSecurity.pollSensors();

        // 5. Reset door and check motion sensor
        std::cout << "\n[SCENARIO 3: Door closed, but motion detected...]" << std::endl;
        homeSecurity.simulateSensorInput(0, 0); // Close door
        homeSecurity.simulateSensorInput(1, 1); // Index 1 is Motion, set to 1 (Motion detected)
        homeSecurity.pollSensors();

        // 6. Fire scenario
        std::cout << "\n[SCENARIO 4: Kitchen catches fire...]" << std::endl;
        homeSecurity.simulateSensorInput(2, 60); // Index 2 is Heat, set to 60C
        homeSecurity.pollSensors();

        // 7. Final system report
        std::cout << "\n[FINAL STATE]" << std::endl;
        homeSecurity.generateReport();

        // 8. Test Day mode
        std::cout << "\n[SCENARIO 5: Switching to Day mode...]" << std::endl;
        homeSecurity.setMode("Day");
        homeSecurity.simulateSensorInput(1, 1); // Motion in Day mode (should not trigger alarm)
        homeSecurity.pollSensors();

        std::cout << "\n--- System Test Complete ---" << std::endl;

    } catch (const std::exception& e) {
        std::cout << "CRITICAL ERROR: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
