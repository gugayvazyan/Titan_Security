#include "Notify.hpp"


void Notify::send(std::string sendWho) {
    if (sendWho == "Police") {
        std::cout << "Dialing 911..." << std::endl;
    } else if (sendWho == "FireDept") {
        std::cout << "Dialing Fire Department..." << std::endl;
    } else if (sendWho == "UserPhone") {
        std::cout << "Sending Push Notification to User..." << std::endl;
    } else {
        std::cout << "Invalid recipient" << std::endl;
    }
}