/*
 * CliArgsParser.hpp
 *
 *  Created on: 12 февр. 2018 г.
 *      Author: krautcat
 */

#ifndef SRC_CLIARGSPARSER_HPP_
#define SRC_CLIARGSPARSER_HPP_

#include <tuple>
#include <memory>

#include "args.hxx"

#include "params/default.hpp"
#include "params/params.hpp"

class CliArgsParser {
    public:
        CliArgsParser();
        ~CliArgsParser();

        Params parse(int argc, const char* argv[]);

    private:
        std::string parse_proto(const std::vector<std::string>& avaliable_protocols);
        std::string parse_ip();
        int parse_port();
        void parse_mqtt_topics(TopicParams& mqtt_topic_params);
        void parse_topics_param(TopicParams& mqtt_topic_params);
        void parse_device_param(TopicParams& mqtt_topic_params);

        args::ArgumentParser parser;

        args::ValueFlag<std::string> proto;
        args::ValueFlag<std::string> ip;
        args::ValueFlag<int> port;

        args::Group topic_group;

        args::Group topics_based_group;
        args::ValueFlagList<std::string> topics;

        args::Group device_based_group;
        args::ValueFlag<std::string> device;
        args::ValueFlagList<std::string> sensors_args;

        args::ValueFlagList<int> qos;

        args::Group msg_handler_group;
        args::Flag raw;
        args::Flag json;

        args::HelpFlag help;
};
#endif /* SRC_CLIARGSPARSER_HPP_ */
