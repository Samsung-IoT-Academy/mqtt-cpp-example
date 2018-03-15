#ifndef IMESSAGEHANDLER_HPP
#define IMESSAGEHANDLER_HPP

#include <memory>

#include "mqtt/message.h"
#include "mqtt/async_client.h"

#include "mqtt/action_listeners/sendmsg.hpp"

namespace SamsungIoT {
namespace mqttapp {

class IMessageHandler {
    public:
        virtual ~IMessageHandler() {}
        virtual void handle(std::shared_ptr<const mqtt::message> msg) = 0;
};

}
}

#endif // IMESSAGEHANDLER_HPP
