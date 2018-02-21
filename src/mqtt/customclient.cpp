/*
 * CustomClient.cpp
 *
 *  Created on: 12 февр. 2018 г.
 *      Author: krautcat
 */

#include <mqtt/message.h>

#include <mqtt/customclient.hpp>
#include <mqtt/action_listeners/connectbroker.hpp>

CustomClient::CustomClient(ConnParams &mqtt_conn_params,
                           TopicParams &mqtt_topic_params,
                           std::string client_id) :
    async_client(mqtt_conn_params.get_server_addr(), client_id),
    msg_handler(async_client),
    cb(async_client, msg_handler),
    server_addr(mqtt_conn_params.get_server_addr())
{
	// TODO Auto-generated constructor stub

    connOpts.set_keep_alive_interval(20);
    connOpts.set_clean_session(true);
    cb.set_connopts(connOpts);

    connect();

    try {
        async_client.subscribe(mqtt_topic_params.get_topics(),
                               mqtt_topic_params.get_qos());
    } catch (const mqtt::exception &exp) {
        std::cerr << "Cannot subsribe to the following topics: " << std::endl;
        for (auto a : mqtt_topic_params.get_topics_strings()) {
            std::cerr << "\t" << a;
        }
        std::cerr << std::endl;
        throw exp;
    }

    async_client.set_callback(cb);

}

CustomClient::~CustomClient() {
    disconnect();
}

void CustomClient::connect() {
    // Start the connection.
    // When completed, the callback will subscribe to topic.

    ConnectBroker con_action_listener;
    try {
        std::cout << "Connecting to the MQTT server..." << std::endl;
        async_client.connect(connOpts, nullptr, con_action_listener)->wait();
    } catch (const mqtt::exception&) {
        std::cerr << "ERROR: Unable to connect to MQTT server: '"
                << server_addr << "'" << std::endl;
    }

    // Just block till user tells us to quit.
}

void CustomClient::disconnect()
{
    try {
        std::cout << "\nDisconnecting from the MQTT server..." << std::flush;
        async_client.disconnect()->wait();
        std::cout << "OK" << std::endl;
    }
    catch (const mqtt::exception& exc) {
        std::cerr << exc.what() << std::endl;
    }
}

void CustomClient::get_messages()
{
    async_client.start_consuming();
    std::shared_ptr<const mqtt::message> msg;
    while (std::tolower(std::cin.get()) != 'q') { };
}


