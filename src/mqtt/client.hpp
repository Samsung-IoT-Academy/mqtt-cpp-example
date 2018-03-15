/*
 * CustomClient.hpp
 *
 *  Created on: 12 февр. 2018 г.
 *      Author: krautcat
 */

#ifndef SRC_MQTT_CUSTOMCLIENT_HPP_
#define SRC_MQTT_CUSTOMCLIENT_HPP_

#include "mqtt/async_client.h"

#include "params/params.hpp"
#include "mqtt/callback.hpp"
#include "mqtt/msg_handlers/imessagehandler.hpp"

namespace SamsungIoT {
namespace mqttapp {

using namespace SamsungIoT::mqttapp;

class Client {
	public:
        Client(SamsungIoT::mqttapp::Params& parameters);
        virtual ~Client();
        void connect();
        void disconnect();
        void get_messages();

	private:
        mqtt::connect_options conn_opts;
        mqtt::async_client async_client;

        IMessageHandler* msg_handler;
        Callback cb;

        std::string server_addr;
};

}
}

#endif /* SRC_MQTT_CUSTOMCLIENT_HPP_ */
