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

class ConnParams
{
    public:
        ConnParams() = default;
        ConnParams(ConnParams &&params_rhs) = default;
        ConnParams& operator=(const ConnParams&& source);

        const std::string get_server_uri();

        std::vector<std::string> avaliable_protocols();

        void set_proto(std::string value);
        void set_ip(std::string value);
        void set_port(unsigned int value);

        std::string proto;
        std::string ip;
        unsigned int port;
    private:
        DefaultConnParams defaults;
};


class TopicParams
{
    public:
        TopicParams();
        TopicParams(const std::string& topics_base);
        TopicParams(TopicParams&& params_rhs) = default;
        TopicParams& operator=(const TopicParams&& source);

        void construct_topics(int q);
        void construct_topics(std::string deveui, int q);
        void construct_topics(std::string deveui,
                              const std::vector<std::string> &sensors,
                              const std::vector<int> &q);
        void construct_topics(const std::vector<std::string> &deveuis,
                              const std::vector<std::string> &sensors,
                              const std::vector<int> &q);
        void construct_topics();
        void construct_topics(const std::string& deveui);
        void construct_topics(const std::string& deveui,
                              const std::vector<std::string>& sensors);
        void construct_topics(const std::vector<std::string>& deveuis,
                              const std::vector<std::string>& sensors);
        void supplement_qoses(int length);

        std::shared_ptr<const mqtt::string_collection> get_topics();
        std::vector<std::string> get_topics_strings();

        std::string base;
        std::vector<std::string> topics;
        std::vector<int> qos;

    private:
        std::string construct_topic(const std::string& deveui,
                                    const std::string& sensor);
        std::string construct_topic(const std::string& deveui);

        DefaultTopicParams defaults;
};


class MessageHandlerParams
{
    public:
        MessageHandlerParams();
        MessageHandlerParams(MessageHandlerParams &&params_rhs) = default;
        MessageHandlerParams& operator=(const MessageHandlerParams&& source);

        MessageHandlerFactory::HandlerType handler_type;
};


class Params
{
    public:
        Params();
        Params(ConnParams &con, TopicParams &top, MessageHandlerParams &msg_hndlr);
        Params(Params &params_lhs) = default;
        Params(Params &&params_rhs) = default;
        Params& operator=(Params&& source);
        ~Params();

        ConnParams connection_params;
        TopicParams topic_params;
        MessageHandlerParams msg_handler_params;
};

//

#endif /* SRC_HELPER_PARAMS_HPP_ */
