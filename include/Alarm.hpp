#pragma once
#include "Sound.hpp"
#include "Notify.hpp"
#include "Log.hpp"


class Alarm : public Sound, public Notify, public Log {
public: 
    void triggerAlarm(std::string severity, std::string sendWho);


};
