/*
 * CustomCallback.cpp
 *
 *  Created on: 12 февр. 2018 г.
 *      Author: krautcat
 */

#include <mqtt/callback.hpp>

namespace SamsungIoT {
namespace mqttapp {

using namespace SamsungIoT::mqttapp;

Callback::Callback(mqtt::async_client& cli_cl) :
    cli(cli_cl)
{
}

Callback::~Callback() {
    // TODO Auto-generated destructor stub
}

void Callback::set_connopts(const mqtt::connect_options& opts) {
    connOpts = opts;
    return;
}

void Callback::connection_lost(const std::string& cause) {
    std::cout << "Connection lost!" << std::endl;
    if (!cause.empty())
        std::cout << "\tCause: " << cause << std::endl;

    std::cout << "Reconnecting..." << std::endl;
    reconnect();
}

void Callback::message_arrived(mqtt::const_message_ptr msg) {
    std::cout << "Message arrived" << std::endl;
    std::cout << "\ttopic: '" << msg->get_topic() << "'" << std::endl;
    std::cout << "\tpayload: '" << msg->to_string() << "'\n"
            << std::endl;
}

void Callback::reconnect() {
    mqtt::token_ptr recon_tok = cli.reconnect();
    recon_tok->wait();
}

}
}