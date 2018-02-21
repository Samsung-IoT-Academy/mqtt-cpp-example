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

class ConnParams
{
    public:
        std::string proto;
        std::string ip;
        unsigned int port;

        ConnParams();
        ConnParams(ConnParams &&params_rhs) = default;

        const std::string get_server_addr();

        void set_proto(std::string value, std::string def);
        void set_ip(std::string value, std::string def);
        void set_port(unsigned int value, unsigned int def);
};


class TopicParams
{
    public:
        TopicParams();
        TopicParams(TopicParams &&params_rhs) = default;

        void construct_topics(int q);
        void construct_topics(std::string deveui, int q);
        void construct_topics(std::string deveui,
                              const std::vector<std::string> &sensors,
                              const std::vector<int> &q);
        void construct_topics(const std::vector<std::string> &deveuis,
                              const std::vector<std::string> &sensors,
                              const std::vector<int> &q);

        std::shared_ptr<const mqtt::string_collection> get_topics();
        std::vector<std::string> get_topics_strings();
        std::vector<int> get_qos();

    private:
        std::string base;
        std::vector<std::string> topics;
        std::vector<int> qos;
};

class Params
{
    public:
        Params(ConnParams &con, TopicParams &top);
        Params(Params &params_lhs) = default;
        Params(Params &&params_rhs) = default;
        ~Params();

        ConnParams connection_params;
        TopicParams topic_params;
};

//

#endif /* SRC_HELPER_PARAMS_HPP_ */
