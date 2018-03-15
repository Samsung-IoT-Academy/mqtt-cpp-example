/*
 * ConParams.h
 *
 *  Created on: 6 июл. 2017 г.
 *      Author: krautcat
 */

#ifndef SRC_HELPER_PARAMS_HPP_
#define SRC_HELPER_PARAMS_HPP_

#include <string>
#include <vector>
#include <tuple>
#include <memory>

#include "mqtt/string_collection.h"

#include "params/default.hpp"
#include "mqtt/msg_handlers/msghandlerfactory.hpp"

namespace SamsungIoT {
namespace mqttapp {

using namespace SamsungIoT::mqttapp;

class ConnParams
{
    public:
        ConnParams();

        const std::string get_server_uri() const;
        const std::string get_client_id() const;

        void set_proto(const std::string& value);
        void set_ip(const std::string& value);
        void set_port(unsigned int value);
        void set_client_id(const std::string& value);

        static std::vector<std::string> avaliable_protocols();

    private:
        DefaultConnParams defaults;
        
        std::string proto;
        std::string ip;
        unsigned int port;

        std::string client_id;
};


class TopicParams
{
    public:
        TopicParams();
        TopicParams(const std::string& topics_base);

        void construct_topics();
        void construct_topics(const std::string& deveui);
        void construct_topics(const std::string& deveui,
                              const std::vector<std::string>& sensors);
        void construct_topics(const std::vector<std::string>& deveuis,
                              const std::vector<std::string>& sensors);
        void supplement_qoses(int length);

        std::shared_ptr<const mqtt::string_collection> get_topics();
        std::vector<std::string> get_topics_strings();

        std::vector<std::string> topics;
        std::vector<int> qos;

    private:
        std::string construct_topic(const std::string& deveui,
                                    const std::string& sensor);
        std::string construct_topic(const std::string& deveui);

        DefaultTopicParams defaults;

        std::string base;
};


class MessageHandlerParams
{
    public:
        MessageHandlerParams();

        MessageHandlerFactory::HandlerType handler_type;
};


class Params
{
    public:
        Params();
        Params(ConnParams &con, TopicParams &top, MessageHandlerParams &msg_hndlr);

        ConnParams connection_params;
        TopicParams topic_params;
        MessageHandlerParams msg_handler_params;
};

}
}
//

#endif /* SRC_HELPER_PARAMS_HPP_ */
