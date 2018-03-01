#ifndef MESSAGEHANDLER_HPP
#define MESSAGEHANDLER_HPP

#include <memory>

#include "mqtt/async_client.h"
#include "mqtt/message.h"
#include "json/reader.h"

#include "mqtt/msg_handlers/imessagehandler.hpp"
#include "mqtt/action_listeners/sendmsg.hpp"

class MessageHandlerJson :
        public IMessageHandler
{
    public:
        MessageHandlerJson(mqtt::async_client &cli);

        virtual void handle(std::shared_ptr<const mqtt::message> msg);

    private:
        mqtt::async_client& client;

        // An action listener to display the result of actions.
        SendMsgActionListener sub_listener;

        Json::Reader json_reader;

};

#endif // MESSAGEHANDLER_HPP
