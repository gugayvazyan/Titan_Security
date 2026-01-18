#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include "Sensor.hpp"
#include "DoorSensor.hpp"
#include "MotionSensor.hpp"
#include "HeatSensor.hpp"
#include "Alarm.hpp"

class TitanSecurity{
public:   
    TitanSecurity();
    void pollSensors();
    void setMode(std::string mode);
    void simulateSensorInput(int index, int value);
    void generateReport();

private:
    std::vector<std::shared_ptr<Sensor>> Sensors;
    std::shared_ptr<Alarm> alarm;
    bool systemArmed{false};
    std::string currentMode;
};