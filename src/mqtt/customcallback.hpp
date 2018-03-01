/*
 * CustomCallback.hpp
 *
 *  Created on: 12 февр. 2018 г.
 *      Author: krautcat
 */

#ifndef SRC_MQTT_CUSTOMCALLBACK_HPP_
#define SRC_MQTT_CUSTOMCALLBACK_HPP_

#include "mqtt/async_client.h"

#include "mqtt/msg_handlers/imessagehandler.hpp"

class CustomCallback :
    public virtual mqtt::callback
{
	public:
        CustomCallback(mqtt::async_client &cli_cl);
		virtual ~CustomCallback();

        void set_connopts(const mqtt::connect_options &opts);
        void set_msg_handler(IMessageHandler *msg_hndlr);

    private:
        std::vector<std::string> mqtt_topics;
        std::vector<int> qos;
        std::string client_id;

        mqtt::async_client& cli;

        // Options to use if we need to reconnect
        mqtt::connect_options connOpts;

        // Message handler
        IMessageHandler* msg_handler;

        void connection_lost(const std::string& cause) override;
        void message_arrived(mqtt::const_message_ptr msg) override;
        void reconnect();
};

#endif /* SRC_MQTT_CUSTOMCALLBACK_HPP_ */
