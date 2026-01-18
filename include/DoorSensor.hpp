#pragma once
#include "IDoor.hpp"
#include "Sensor.hpp"


class DoorSensor: public Sensor, public IDoor {
public:
    DoorSensor(std::string _name, std::string _location, int _data) : Sensor(_name, _location, _data) {}
};
