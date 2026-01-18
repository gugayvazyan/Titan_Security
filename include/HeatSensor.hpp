#pragma once
#include "IHeat.hpp"
#include "Sensor.hpp"


class HeatSensor: public Sensor, public IHeat {
public:
    HeatSensor(std::string _name, std::string _location, int _data) : Sensor(_name, _location, _data) {}
};