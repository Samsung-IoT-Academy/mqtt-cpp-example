#include <iostream>

#include "mqtt/action_listeners/connectbroker.hpp"

namespace SamsungIoT {
namespace mqttapp {

ConnectBrokerActionListener::ConnectBrokerActionListener()
{
}

ConnectBrokerActionListener::~ConnectBrokerActionListener()
{
}

void ConnectBrokerActionListener::on_failure(const mqtt::token& tok) {
    std::cout << "Connection failed" << std::endl;
}

void ConnectBrokerActionListener::on_success(const mqtt::token& tok) {
    std::cout << "Connection success" << std::endl;
}

}
}

