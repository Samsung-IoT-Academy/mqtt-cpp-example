#include <iostream>


#include "params.hpp"



ConnParams::ConnParams()
{

}

void ConnParams::set_proto(std::string value, std::string def)
{
    proto = (value.empty()) ? value : def;
}

void ConnParams::set_ip(std::string value, std::string def)
{
    ip = (value.empty()) ? value : def;
}

void ConnParams::set_port(unsigned int value, unsigned int def)
{
    port = (value == 0) ? value : def;
}

const std::string ConnParams::get_server_addr() {
    return proto + "://" + ip + ":" + std::to_string(port);
}

// ------------------------

TopicParams::TopicParams() {
    base = "devices/lora";
}

//TopicParams::TopicParams(TopicParams &&topic_params) :
//    base(topic_params.base),
//    topics(topic_params.topics),
//    qos(topic_params.qos)
//{
//    topic_params.base.clear();
//    topic_params.topics.clear();
//    topic_params.qos.clear();

//    std::cout << "Called constructor of moving";
//}

void TopicParams::construct_topics(int q) {
    topics.clear();
    qos.clear();
    topics.push_back(base + "/#");
    qos.push_back(q);
}

void TopicParams::construct_topics(std::string deveui, int q) {
    topics.clear();
    qos.clear();
    topics.push_back(base + "/" + deveui + "/#");
    qos.push_back(q);
}

void TopicParams::construct_topics(std::string deveui, const std::vector<std::string> &sensors, const std::vector<int> &q)
{
    topics.clear();
    qos.clear();
    for (auto sen_it = sensors.begin(); sen_it != sensors.end(); ++sen_it) {
        topics.push_back(base + "/" + deveui + "/" + *sen_it);
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
    do {
        topics.push_back(base + "/" + *dev_it + "/" + *sen_it);
        qos.push_back(*qos_it);
        dev_it++;
        sen_it++;
        qos_it++;
    } while (dev_it != deveuis.end() && sen_it != sensors.end() && qos_it != q.end());
}

std::shared_ptr<const mqtt::string_collection> TopicParams::get_topics()
{
    return std::make_shared<const mqtt::string_collection>(topics);
}

std::vector<std::string> TopicParams::get_topics_strings()
{
    return topics;
}


std::vector<int> TopicParams::get_qos()
{
    return qos;
}

Params::Params(ConnParams &con, TopicParams &top) :
    connection_params(std::move(con)),
    topic_params(std::move(top))
{
}

Params::~Params()
{

}
