#ifndef MESSAGEHANDLERRAW_H
#define MESSAGEHANDLERRAW_H

#include <memory>

#include "mqtt/async_client.h"

#include "mqtt/msg_handlers/imessagehandler.hpp"
#include "mqtt/action_listeners/sendmsg.hpp"

class MessageHandlerRaw :
        public IMessageHandler
{
    public:
        MessageHandlerRaw(mqtt::async_client& cli);

        virtual void handle(std::shared_ptr<const mqtt::message> msg);

    private:
        mqtt::async_client &client;

        // An action listener to display the result of actions.
        SendMsgActionListener sub_listener;

};

#endif // MESSAGEHANDLERRAW_H
