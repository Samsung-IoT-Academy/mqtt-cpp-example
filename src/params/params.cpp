#include <iostream>
#include <exception>

#include "params.hpp"


namespace SamsungIoT {
namespace mqttapp {

ConnParams::ConnParams() :
    defaults(),
    proto(defaults.proto),
    ip(defaults.ip),
    port(defaults.port),
    client_id(defaults.client_id)
{ 
}

const std::string ConnParams::get_server_uri() const
{
    return proto + "://" + ip + ":" + std::to_string(port);
}

const std::string ConnParams::get_client_id() const
{
    return client_id;
}

void ConnParams::set_proto(const std::string& value)
{
    proto = (value.empty()) ? defaults.proto : value;
}

void ConnParams::set_ip(const std::string& value)
{
    ip = (value.empty()) ? defaults.ip : value;
}

void ConnParams::set_port(unsigned int value)
{
    port = (value == 0) ? defaults.port : value;
}

std::vector<std::string> ConnParams::avaliable_protocols()
{
    return std::vector<std::string> {
            "tcp"
        };
}

// ------------------------

TopicParams::TopicParams() :
    base(defaults.base)
{
}

TopicParams::TopicParams(const std::string& topics_base) :
    base(topics_base)
{
}

void TopicParams::construct_topics()
{
    topics.clear();
    topics.push_back(construct_topic(defaults.topic));
}

void TopicParams::construct_topics(const std::string& deveui)
{
    topics.clear();
    topics.push_back(construct_topic(deveui, "#"));
}

void TopicParams::construct_topics(const std::string& deveui, const std::vector<std::string>& sensors)
{
    topics.clear();
    for (auto sen_it = sensors.begin(); sen_it != sensors.end(); ++sen_it) {
        topics.push_back(construct_topic(deveui, *sen_it));
    }
}

void TopicParams::construct_topics(const std::vector<std::string>& deveuis, const std::vector<std::string>& sensors)
{
    topics.clear();
    auto dev_it = deveuis.begin();
    auto sen_it = sensors.begin();
    while (dev_it != deveuis.end() && sen_it != sensors.end()) {
        topics.push_back(construct_topic(*dev_it, *sen_it));
        ++dev_it;
        ++sen_it;
    }
}

void TopicParams::construct_topics_sensors(const std::vector<std::string>& sensors)
{
    topics.clear();
    for (auto sen_it = sensors.begin(); sen_it != sensors.end(); sen_it++) {
        topics.push_back(construct_topic("+", *sen_it));
    }
}

void TopicParams::supplement_qoses(int length)
{
    qos.resize(length, defaults.qos);
}

std::shared_ptr<const mqtt::string_collection> TopicParams::get_topics()
{
    return std::make_shared<const mqtt::string_collection>(topics);
}

std::vector<std::string> TopicParams::get_topics_strings()
{
    return topics;
}

std::string TopicParams::construct_topic(const std::string& deveui,
                                         const std::string& sensor)
{
    return base + "/" + deveui + "/" + sensor;
}

std::string TopicParams::construct_topic(const std::string& deveui)
{
    return base + "/" + deveui;
}

// ------------------------

MessageHandlerParams::MessageHandlerParams() :
    handler_type(MessageHandlerFactory::HandlerType::Raw)
{
}

// ------------------------

Params::Params() :
    connection_params(ConnParams()),
    topic_params(TopicParams()),
    msg_handler_params(MessageHandlerParams())
{
}

Params::Params(ConnParams& con, TopicParams& top, MessageHandlerParams& msg_hndlr) :
    connection_params(std::move(con)),
    topic_params(std::move(top)),
    msg_handler_params(std::move(msg_hndlr))
{
}

}
}
