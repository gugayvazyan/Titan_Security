#include "Alarm.hpp"

void Alarm::triggerAlarm(std::string severity, std::string sendWho) {
    std::cout << "!!! ALARM TRIGGERED [" << severity << "] !!!" << std::endl;
    makeSound(severity);
    send(sendWho);
    logToFile("ALARM: " + severity + " sent to " + sendWho);
};