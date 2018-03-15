#include "params/default.hpp"

namespace SamsungIoT {
namespace mqttapp {

DefaultConnParams::DefaultConnParams() :
    proto("tcp"),
    ip("127.0.0.1"),
    port(1883),

    client_id("sync_consume_cpp")
{
}

DefaultTopicParams::DefaultTopicParams() :
    base("devices/lora"),
    topic("#"),
    qos(0)
{
}

}
}
