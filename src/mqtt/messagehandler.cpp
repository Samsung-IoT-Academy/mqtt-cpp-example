#include <json/json.h>
#include <json/value.h>
#include <json/writer.h>

#include "helper/json_helpers.hpp"

#include "messagehandler.hpp"

MessageHandler::MessageHandler(mqtt::async_client &cli) :
    client(cli)
{

}

void MessageHandler::handle(std::shared_ptr<const mqtt::message> msg)
{
    std::string topic = msg->get_topic();
    std::vector <std::string> topic_strings = jsonHelper::split(topic, '/');
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
        client.publish(pubmsg, nullptr, sub_listener);
        while (!sub_listener.is_done()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            std::cout << "Message didn't published!" << std::endl;

            std::vector<std::shared_ptr<mqtt::delivery_token>> toks = client.get_pending_delivery_tokens();
            if (!toks.empty()) {
                std::cout << "Error: There are pending delivery tokens!" << std::endl;
            } else {
                for (auto t : toks) {
                    std::cout << (*t).get_message() << std::endl;
                }
            }

        }
    }
}
