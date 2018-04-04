#include "helper/string.hpp"
#include "mqtt/msg_handlers/raw.hpp"

namespace SamsungIoT {
namespace mqttapp {

using namespace SamsungIoT::mqttapp;

MessageHandlerRaw::MessageHandlerRaw(mqtt::async_client& cli) :
    client(cli)
{

}

void MessageHandlerRaw::handle(std::shared_ptr<const mqtt::message> msg)
{
    std::string topic {msg->get_topic()};

    std::cout << "Message topic: " << topic << std::endl
              << "Message content: " << msg->to_string() << std::endl;
}

}
}
