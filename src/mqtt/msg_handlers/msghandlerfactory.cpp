#include "mqtt/msg_handlers/msghandlerfactory.hpp"

IMessageHandler* MessageHandlerFactory::create(HandlerType type, mqtt::async_client& client)
{
    switch (type) {
        case HandlerType::Raw :
            return new MessageHandlerRaw(client);
        case HandlerType::JSON :
            return new MessageHandlerJson(client);
        default:
            return new MessageHandlerRaw(client);
    }
}
