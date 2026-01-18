#pragma once
#include <string>

class Sensor {
public:
    Sensor(std::string _name, std::string _location, int _data) 
        : sensorName(_name), sensorLocation(_location), data(_data) {}
    
    virtual ~Sensor() = default;

    //getters
    std::string getName() const noexcept {return sensorName;}
    std::string getLocation() const noexcept {return sensorLocation;}
    int getData() const noexcept {return data;}

    //setters
    void setName(std::string name) { sensorName = name; }
    void setLocation(std::string loc) { sensorLocation = loc; }
    void setData(int ddata){ data = ddata; }

private:
    std::string sensorName;
    std::string sensorLocation;
    int data;
};
