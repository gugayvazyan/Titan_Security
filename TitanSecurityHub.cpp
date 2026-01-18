#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include <ctime>

using namespace std;

class TitanSystem {
private:
    vector<string> sensorNames;
    vector<string> sensorTypes;
    vector<int> sensorData; // 0 or 1 for binary, 0-100 for analog
    vector<string> sensorLocations;
    

    bool systemArmed;
    string currentMode; // "Day", "Night", "Away"

public:
    TitanSystem() {
        systemArmed = false;
        currentMode = "Day";
        

        sensorNames.push_back("Front Door");
        sensorTypes.push_back("DoorSensor");
        sensorData.push_back(0); // Closed
        sensorLocations.push_back("Entry");

        sensorNames.push_back("Living Room Motion");
        sensorTypes.push_back("MotionSensor");
        sensorData.push_back(0); // No motion
        sensorLocations.push_back("Living Room");

        sensorNames.push_back("Kitchen Heat");
        sensorTypes.push_back("HeatSensor");
        sensorData.push_back(25); // 25 degrees Celsius
        sensorLocations.push_back("Kitchen");
    }


    void setMode(string mode) {
        if (mode == "Day" || mode == "Night" || mode == "Away") {
            currentMode = mode;
            cout << "[System] Mode set to: " << mode << endl;
            if (mode == "Away") {
                systemArmed = true;
            }
        } else {
            cout << "[Error] Unknown mode." << endl;
        }
    }

    void  pollSensors() {
        cout << "\n--- Polling Sensors (" << currentMode << " Mode) ---" << endl;

        for (size_t i = 0; i < sensorNames.size(); i++) {
            string name = sensorNames[i];
            string type = sensorTypes[i];
            int data = sensorData[i];

            if (type == "DoorSensor") {
                // Simulate reading hardware
                cout << "Reading " << name << "... ";
                if (data == 1 && systemArmed) {
                     cout << "! Triggering Alarm!" << endl;
                     triggerAlarm("High", "Police");
                } else {
                    cout << "Secure." << endl;
                }
            } 
            else if (type == "MotionSensor") {
                cout << "Reading " << name << "... ";
                
                if (data == 1 && currentMode == "Away") {
                    cout << "MOTION DETECTED!" << endl;
                    triggerAlarm("Medium", "UserPhone");
                } else {
                    cout << "No Motion." << endl;
                }
            } 
            else if (type == "HeatSensor") {
                cout << "Reading " << name << "... Temp: " << data << "C. ";
                if (data > 50) {
                    cout << "DANGER! FIRE!" << endl;
                    triggerAlarm("Critical", "FireDept");
                } else {
                    cout << "Normal." << endl;
                }
            } 
            else {
                cout << "[Warning] Unknown sensor type found in index " << i << endl;
            }
        }
    }
    // SIMULATION METHOD: Updates sensor values to test logic
    void simulateSensorInput(int index, int value) {
        if (index >= 0 && index < sensorData.size()) {
            sensorData[index] = value;
        }
    }               
    
    // This method handles Audio logic, Network logic, AND Logging logic.
    void triggerAlarm(string severity, string notifyWho) {
        cout << "!!! ALARM TRIGGERED [" << severity << "] !!!" << endl;
        
        // 1. Sound Logic
        if (severity == "High" || severity == "Critical") {
            cout << ">>> PLAYING LOUD SIREN SOUND <<<" << endl;
        } else {
            cout << ">>> Beeping Keypad <<<" << endl;
        }

        // 2. Notification Logic 
        if (notifyWho == "Police") {
            cout << "Dialing 911..." << endl;
        } else if (notifyWho == "FireDept") {
            cout << "Dialing Fire Department..." << endl;
        } else if (notifyWho == "UserPhone") {
            cout << "Sending Push Notification to User..." << endl;
        }

        // 3. Logging
        logToFile("ALARM: " + severity + " sent to " + notifyWho);
    }

    void logToFile(string message) {
        ofstream logFile;

        logFile.open("system_log.txt", ios_base::app); 
        if (logFile.is_open()) {
            // Get current time
            time_t result = time(nullptr);
            logFile << ctime(&result) << " - " << message << "\n";
            logFile.close();
        } else {
            cerr << "Failed to write to log file." << endl;
        }
    }

    // Method to create a summary report
    void generateReport() {
        cout << "\nGenerating System Report..." << endl;
        cout << "Sensors Online: " << sensorNames.size() << endl;
        cout << "System Armed: " << (systemArmed ? "YES" : "NO") << endl;
        // ... heavy logic for report formatting ...
    }
};

int main() {
    try {
        TitanSystem homeSecurity;

        cout << "--- Titan Security System v1.0 ---\n";


        homeSecurity.setMode("Away");

        // 3. Simulate "Normal" Check
        homeSecurity.pollSensors();

        // 4. Intruder scenario!
        cout << "\n[SIMULATION] Intruder breaks open the front door...\n";
        homeSecurity.simulateSensorInput(0, 1); // Index 0 is Door, set to 1 (Open)

        homeSecurity.pollSensors();

        // 5. Fire scenario!
        cout << "\n[SIMULATION] Kitchen catches fire...\n";
        homeSecurity.simulateSensorInput(2, 60); // Index 2 is Heat, set to 60C

        homeSecurity.pollSensors();

    } catch (const exception& e) {
        cout << "CRITICAL ERROR: " << e.what() << endl;
    }

    return 0;
}