/*
 * CustomCallback.cpp
 *
 *  Created on: 12 февр. 2018 г.
 *      Author: krautcat
 */

#include <mqtt/customcallback.hpp>

CustomCallback::CustomCallback(mqtt::async_client &cli_cl) :
    cli(cli_cl)
{
}

CustomCallback::~CustomCallback() {
    // TODO Auto-generated destructor stub
}

void CustomCallback::set_connopts(const mqtt::connect_options& opts)
{
    connOpts = opts;
    return;
}

void CustomCallback::set_msg_handler(IMessageHandler* msg_hndlr)
{
    msg_handler = msg_hndlr;
}

void CustomCallback::connection_lost(const std::string& cause) {
    std::cout << "Connection lost!" << std::endl;
    if (!cause.empty())
        std::cout << "\tCause: " << cause << std::endl;

    std::cout << "Reconnecting..." << std::endl;
    reconnect();
}

void CustomCallback::message_arrived(mqtt::const_message_ptr msg) {
    std::cout << "Message arrived" << std::endl;
    std::cout << "\ttopic: '" << msg->get_topic() << "'" << std::endl;
    std::cout << "\tpayload: '" << msg->to_string() << "'\n"
            << std::endl;


    msg_handler->handle(msg);
}

void CustomCallback::reconnect() {
    cli.reconnect();
}
