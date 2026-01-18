#pragma once
#include "IMotion.hpp"
#include "Sensor.hpp"

class MotionSensor: public Sensor, public IMotion {
public:
    MotionSensor(std::string _name, std::string _location, int _data) : Sensor(_name, _location, _data){}
};