/*
 * CustomClient.cpp
 *
 *  Created on: 12 февр. 2018 г.
 *      Author: krautcat
 */

#include <sstream>
#include <chrono>
#include <thread>

#include "mqtt/message.h"

#include "mqtt/client.hpp"
#include "mqtt/action_listeners/connectbroker.hpp"
#include "mqtt/msg_handlers/msghandlerfactory.hpp"

namespace SamsungIoT {
namespace mqttapp {

using namespace SamsungIoT::mqttapp;

Client::Client(SamsungIoT::mqttapp::Params& parameters) :
    async_client(parameters.connection_params.get_server_uri(),
                 parameters.connection_params.get_client_id()),
    cb(async_client),
    server_addr(parameters.connection_params.get_server_uri())
{
    msg_handler = MessageHandlerFactory::create(parameters.msg_handler_params.handler_type,
                                async_client);

    conn_opts.set_keep_alive_interval(20);
    conn_opts.set_clean_session(true);
    cb.set_connopts(&conn_opts);

    connect();

    try {
        std::cout << "Subscribing to topics:" << std::endl;
        std::vector<std::string> topics {parameters.topic_params.get_topics_strings()};
        std::vector<int> qoses {parameters.topic_params.qos};
        for (unsigned int i = 0; i < topics.size(); i++) {
            std::cout << "\t" << topics[i] << " with QoS " << qoses[i] << std::endl;
        }
        async_client.subscribe(parameters.topic_params.get_topics(),
                               parameters.topic_params.qos);
    } catch (const mqtt::exception &exp) {
        std::cerr << "Cannot subsribe to the following topics: " << std::endl;
        for (auto a : parameters.topic_params.get_topics_strings()) {
            std::cerr << "\t" << a;
        }
        std::cerr << std::endl;
        throw exp;
    }

    async_client.set_callback(cb);

}

Client::~Client() {
    disconnect();
    delete msg_handler;
    std::cout << "Client destroying" << std::endl;
}

void Client::connect() {
    try {
        ConnectBrokerActionListener con_action_listener;
        std::cout << "Connecting to the MQTT server " << async_client.get_server_uri() << std::endl;
        std::shared_ptr<mqtt::token> connect_token {async_client.connect(conn_opts, nullptr, con_action_listener)};
        long wait_interval {5000L};
        if (!connect_token->wait_for(wait_interval)) {
            std::ostringstream oss {};
            oss << "Cannot connect to server after " << (wait_interval / 1000)
                << " seconds";
            throw mqtt::exception(-1, oss.str());
        }
    } catch (const mqtt::exception& e) {
        std::cerr << "ERROR: Unable to connect to MQTT server: '"
                  << server_addr << "'" << std::endl;
        throw e;
    }
}

void Client::disconnect()
{
    try {
        std::cout << "\nDisconnecting from the MQTT server..." << std::flush;
        async_client.disconnect()->wait();
        std::cout << "OK" << std::endl;
    } catch (const mqtt::exception& exc) {
        std::cerr << exc.what() << std::endl;
        throw exc;
    }
}

void Client::get_messages()
{
    async_client.start_consuming();
    std::shared_ptr<const mqtt::message> msg;
    for (;;) {
        msg = async_client.consume_message();
        msg_handler->handle(msg);
    }
}

}
}
