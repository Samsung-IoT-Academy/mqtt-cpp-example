#ifndef MSGHANDLERFACTORY_H
#define MSGHANDLERFACTORY_H

#include "mqtt/msg_handlers/imessagehandler.hpp"
#include "mqtt/msg_handlers/raw.hpp"
#include "mqtt/msg_handlers/json.hpp"

class MessageHandlerFactory
{
    public:
        enum class HandlerType {
            Raw,
            JSON
        };

        IMessageHandler* create(HandlerType type, mqtt::async_client& client);
};

#endif // MSGHANDLERFACTORY_H
