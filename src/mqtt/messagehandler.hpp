#ifndef MESSAGEHANDLER_HPP
#define MESSAGEHANDLER_HPP

#include <memory>

#include "mqtt/async_client.h"
#include "mqtt/message.h"
#include "json/reader.h"

#include "mqtt/action_listeners/sendmsg.hpp"

class MessageHandler
{
    public:
        MessageHandler(mqtt::async_client &cli);

        void handle(std::shared_ptr<const mqtt::message> msg);

    private:
        mqtt::async_client &client;

        // An action listener to display the result of actions.
        CustomActionListener sub_listener;


        Json::Reader json_reader;

};

#endif // MESSAGEHANDLER_HPP
