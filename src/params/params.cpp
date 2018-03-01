#include <iostream>
#include <exception>

#include "params.hpp"


ConnParams& ConnParams::operator=(const ConnParams &&source)
{
    proto = std::move(source.proto);
    ip = std::move(source.ip);
    port = std::move(source.port);

    return *this;
}

void ConnParams::set_proto(std::string value)
{
    proto = (value.empty())
            ? defaults.proto
            : value;
}

void ConnParams::set_ip(std::string value)
{
    ip = (value.empty())
            ? defaults.ip
            : value;
}

void ConnParams::set_port(unsigned int value)
{
    port = (value == 0)
            ? defaults.port
            : value;
}

const std::string ConnParams::get_server_uri()
{
    return proto + "://" + ip + ":" + std::to_string(port);
}

std::vector<std::string> ConnParams::avaliable_protocols()
{
    return std::vector<std::string> {
            "tcp"
        };
}

// ------------------------

TopicParams::TopicParams() :
    base("devices/lora")
{
}

TopicParams::TopicParams(const std::string& topics_base) :
    base(topics_base)
{
}

TopicParams& TopicParams::operator=(const TopicParams&& source)
{
    base = std::move(source.base);
    topics = std::move(source.topics);
    qos = std::move(source.qos);

    return *this;
}

void TopicParams::construct_topics(int q) {
    topics.clear();
    qos.clear();
    topics.push_back(construct_topic("#"));
    qos.push_back(q);
}

void TopicParams::construct_topics(std::string deveui, int q) {
    topics.clear();
    qos.clear();
    topics.push_back(construct_topic(deveui, "#"));
    qos.push_back(q);
}

void TopicParams::construct_topics(std::string deveui, const std::vector<std::string> &sensors, const std::vector<int> &q)
{
    topics.clear();
    qos.clear();
    for (auto sen_it = sensors.begin(); sen_it != sensors.end(); ++sen_it) {
        topics.push_back(construct_topic(deveui, *sen_it));
    }
    qos = q;
}

void TopicParams::construct_topics(const std::vector<std::string> &deveuis, const std::vector<std::string> &sensors, const std::vector<int> &q)
{
    topics.clear();
    qos.clear();
    auto dev_it = deveuis.begin();
    auto sen_it = sensors.begin();
    auto qos_it = q.begin();
    while (dev_it != deveuis.end() && sen_it != sensors.end() && qos_it != q.end()) {
        topics.push_back(construct_topic(*dev_it, *sen_it));
        qos.push_back(*qos_it);
        dev_it++;
        sen_it++;
        qos_it++;
    }
}

void TopicParams::construct_topics()
{
    topics.clear();
    topics.push_back(construct_topic("#"));
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

void TopicParams::construct_topics(const std::vector<std::string>& deveuis, const std::vector<std::__cxx11::string>& sensors)
{
    topics.clear();
    auto dev_it = deveuis.begin();
    auto sen_it = sensors.begin();
    while (dev_it != deveuis.end() && sen_it != sensors.end()) {
        topics.push_back(construct_topic(*dev_it, *sen_it));
        dev_it++;
        sen_it++;
    }

}

void TopicParams::supplement_qoses(int length)
{
    if (length > 0) {
        for (auto i = 0; i < length; ++i) {
            qos.push_back(defaults.qos);
        }
    }
}

std::shared_ptr<const mqtt::string_collection> TopicParams::get_topics()
{
    return std::make_shared<const mqtt::string_collection>(topics);
}

std::vector<std::string> TopicParams::get_topics_strings()
{
    return topics;
}

std::string TopicParams::construct_topic(const std::__cxx11::string& deveui,
                                         const std::__cxx11::string& sensor)
{
    return base + "/" + deveui + "/" + sensor;
}

std::string TopicParams::construct_topic(const std::string& deveui)
{
    return base + "/" + deveui;
}

// ------------------------

MessageHandlerParams::MessageHandlerParams()
{
}

MessageHandlerParams& MessageHandlerParams::operator=(const MessageHandlerParams&& source)
{
    handler_type = std::move(source.handler_type);

    return *this;
}

// ------------------------

Params::Params()
{
}

Params::Params(ConnParams &con, TopicParams &top, MessageHandlerParams &msg_hndlr) :
    connection_params(std::move(con)),
    topic_params(std::move(top)),
    msg_handler_params(std::move(msg_hndlr))
{
}

Params &Params::operator=(Params&& source)
{
    connection_params = std::move(source.connection_params);
    topic_params = std::move(source.topic_params);
    msg_handler_params = std::move(source.msg_handler_params);

    return *this;
}

Params::~Params()
{

}
