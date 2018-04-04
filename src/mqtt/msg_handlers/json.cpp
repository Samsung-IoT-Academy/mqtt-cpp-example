#include "json/json.h"
#include "json/value.h"
#include "json/writer.h"
#include "mqtt/delivery_token.h"

#include "helper/string.hpp"
#include "mqtt/msg_handlers/json.hpp"

namespace SamsungIoT {
namespace mqttapp {

using namespace SamsungIoT::mqttapp;
using namespace SamsungIoT::helpers;

MessageHandlerJson::MessageHandlerJson(mqtt::async_client& cli) :
    client(cli),
    sub_listener()
{

}

void MessageHandlerJson::handle(std::shared_ptr<const mqtt::message> msg)
{
    std::string topic = msg->get_topic();
    std::vector <std::string> topic_strings = split(topic, '/');
    std::string lora_deveui = topic_strings[2];
    std::string device = topic_strings[3];

    Json::Value root;

    json_reader.parse(msg->to_string(), root);

    if (device == "opt3001") {
        std::cout << "Luminocity:\t" << root["data"]["luminocity"]
                << std::endl;
    } else if (device == "adc") {
        std::cout << "Humidity:\t"
                << root["data"]["adc2"].asString() << std::endl;
        std::cout << "Temperature:\t"
                << root["data"]["adc3"].asString() << std::endl;
    } else if (device == "4btn") {
        std::string topic {"devices/lora/807B859020000239/gpio"};
        std::string payload {};
        switch (root["data"]["btn"].asInt()) {
            case 1:
                payload = "set 16 1";
                break;
            case 2:
                payload = "set 17 1";
                break;
            case 3:
                payload = "set 16 0";
                break;
            case 4:
                payload = "set 17 0";
                break;
        }
        mqtt::message_ptr pubmsg = mqtt::make_message(topic, payload);
        std::shared_ptr<mqtt::delivery_token> delivery_tok = client.publish(pubmsg, nullptr, sub_listener);
        long check_timeout {5000L};
        while (!delivery_tok->wait_for(check_timeout)) {
            std::cout << "Message didn't published!" << std::endl;

            std::vector<std::shared_ptr<mqtt::delivery_token>> toks = client.get_pending_delivery_tokens();
            if (!toks.empty()) {
                std::cout << "Error: There are pending delivery tokens!" << std::endl;
                for (auto t : toks) {
                    std::cout << t->get_message() << std::endl;
                }
            }

        }
    }
}

}
}
