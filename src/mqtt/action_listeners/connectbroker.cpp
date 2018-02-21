#include <iostream>

#include "mqtt/action_listeners/connectbroker.hpp"

ConnectBroker::ConnectBroker()
{

}

ConnectBroker::~ConnectBroker()
{

}

void ConnectBroker::on_failure(const mqtt::token& tok) {
    std::cout << "Connection failed" << std::endl;
}

void ConnectBroker::on_success(const mqtt::token& tok) {
    std::cout << "Connection success" << std::endl;
}
