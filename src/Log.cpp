#include "Log.hpp"



void Log::logToFile(std::string message) {
    std::ofstream logFile;

    logFile.open("info.txt", std::ios_base::app); 
    if (logFile.is_open()) {
        std::time_t result = std::time(nullptr);
        logFile << std::ctime(&result) << " - " << message << "\n";
        logFile.close();
    } else {
        std::cerr << "Failed to write to log file." << std::endl;
    }
}