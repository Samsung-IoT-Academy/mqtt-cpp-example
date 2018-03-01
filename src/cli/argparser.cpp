/*
 * CliArgsParser.cpp
 *
 *  Created on: 12 февр. 2018 г.
 *      Author: krautcat
 */

#include <list>
#include <string>
#include <iostream>
#include <memory>
#include <algorithm>
#include <stdexcept>

#include "cli/exceptions.hpp"
#include "cli/argparser.hpp"

#include "mqtt/msg_handlers/msghandlerfactory.hpp"

CliArgsParser::CliArgsParser() :
    parser("MQTT-C++ example program"),

    proto(parser,
            "protocol",
            "Protocol for connecting to MQTT brocker",
            {"proto"}),
    ip(parser,
            "ip",
            "IP address of MQTT broker",
            {"ip"}),
    port(parser,
            "port",
            "Port of MQTT broker",
            {"port"}),

    topic_group(parser,
            "Possible variants of topics:",
            args::Group::Validators::DontCare),

    topics_based_group(topic_group,
            "Topics:",
            args::Group::Validators::AtLeastOne),
    topics(topics_based_group,
            "topics",
            "List of topics to connect",
            {"topics"}),

    device_based_group(topic_group,
            "Device and sensors:",
            args::Group::Validators::AtLeastOne),
    device(device_based_group,
            "device",
            "Device to connect",
            {"device"}),
    sensors_args(device_based_group,
            "sensors",
            "Sensors of devices",
            {"sensors"}),

    qos(parser,
            "qos-num-lists",
            "QOSes of topics",
            {"qos"}),

    msg_handler_group(parser,
            "Message handlers",
            args::Group::Validators::AtMostOne),
    raw(msg_handler_group,
            "Raw handler",
            "Raw message handler",
            {"raw"}),
    json(msg_handler_group,
            "JSON handler",
            "JSON message handler",
            {"json"}),

    help(parser,
            "help",
            "Display this help menu",
            {'h', "help"})
{
}

CliArgsParser::~CliArgsParser()
{
}

Params
CliArgsParser::parse(int argc, const char* argv[]) {
    try {
        parser.ParseCLI(argc, argv);
    } catch (args::Help) {
        std::cout << parser;
    } catch (args::ParseError e) {
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
    } catch (args::ValidationError e) {
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
    }

    if (help)
        throw ArgParseException("Help");

    ConnParams mqtt_conn_params;
    mqtt_conn_params.set_proto(parse_proto(mqtt_conn_params.avaliable_protocols()));
    mqtt_conn_params.set_ip(parse_ip());
    mqtt_conn_params.set_port(parse_port());


    TopicParams mqtt_topic_params;
    parse_mqtt_topics(mqtt_topic_params);


    MessageHandlerParams msg_handler_params;
    if (!json) {
        msg_handler_params.handler_type = MessageHandlerFactory::HandlerType::Raw;
    } else {
        msg_handler_params.handler_type = MessageHandlerFactory::HandlerType::JSON;
    }

    return Params(mqtt_conn_params, mqtt_topic_params, msg_handler_params);
}

std::string CliArgsParser::parse_proto(const std::vector<std::string>& avaliable_protocols)
{
    if (proto) {
        std::string parsed_proto {args::get(proto)};
        if (std::find(avaliable_protocols.begin(),
                      avaliable_protocols.end(),
                      parsed_proto)
                != avaliable_protocols.end())
        {
            return parsed_proto;
        }
    }
    return std::string {};
}

std::string CliArgsParser::parse_ip()
{
    if (ip) {
        std::string ip_cli {args::get(ip)};

        std::vector<int> tokens;
        std::string token;
        std::istringstream token_stream(ip_cli);
        while (std::getline(token_stream, token, '.')) {
           int part;
           try {
               part = std::stoi(token);
           } catch (std::invalid_argument) {
               throw std::invalid_argument("IP parts be numbers!");
           } catch (std::out_of_range) {
               throw std::invalid_argument("IP parts cannot contain such big numbers.");
           }

           if (part > 255 || part < 0) {
               throw std::invalid_argument("IP parts must be between 0 and 255");
           }
           tokens.push_back(part);

        }

        std::stringstream join_stream;
        for (auto t = tokens.begin(); t != tokens.end(); ++t){
            if (t != tokens.begin())
                join_stream << ".";
            join_stream << std::to_string(*t);
        }
        return join_stream.str();
    } else {
        return std::string {};
    }
}

int CliArgsParser::parse_port()
{
    if (port) {
        int parsed_port {args::get(port)};
        if (parsed_port > 0 && parsed_port < 65536)
            return parsed_port;
    }
    return 0;
}

void CliArgsParser::parse_mqtt_topics(TopicParams& mqtt_topic_params)
{
    DefaultTopicParams default_topic_params;

    if (topics) {
        parse_topics_param(mqtt_topic_params);
    } else if (device) {
        parse_device_param(mqtt_topic_params);
    } else {
        std::cerr << "Connect to the default topic" << std::endl;
        mqtt_topic_params.construct_topics(
                    (qos)
                        ? args::get(qos)[0]
                        : default_topic_params.qos);
    }
}

void CliArgsParser::parse_topics_param(TopicParams& mqtt_topic_params)
{
    std::vector<std::string> topics_cli = args::get(topics);

    if (qos)
        mqtt_topic_params.qos = args::get(qos);
    mqtt_topic_params.supplement_qoses(topics_cli.size() - mqtt_topic_params.qos.size());

    std::vector<std::string> deveuis_cli {};
    std::vector<std::string> sensors_cli {};
    // Split topics string by "/" delimetera and push parts to vectors.
    // If not sensor part was specified, assume, that subscribe to "#".
    for (auto t = topics_cli.begin(); t != topics_cli.end(); ++t) {
        std::vector<std::string> topic_parts;
        std::string topic_part;
        std::istringstream token_stream(*t);
        while (std::getline(token_stream, topic_part, '/')) {
            topic_parts.push_back(topic_part);
        }

        deveuis_cli.push_back(topic_parts[0]);
        if (topic_parts.size() == 1) {
            // If supplied '#' topic from command line, subscribing only
            // to this topic, ignore others.
            if (topic_parts[0] == "#") {
                mqtt_topic_params.qos.clear();
                mqtt_topic_params.supplement_qoses(1);
                return;
            }
            sensors_cli.push_back("#");
        } else {
            sensors_cli.push_back(topic_parts[1]);
        }
    }

    mqtt_topic_params.construct_topics(deveuis_cli, sensors_cli);
}

void CliArgsParser::parse_device_param(TopicParams& mqtt_topic_params)
{
    std::vector<std::string> sensors_cli {};
    std::string device_cli = args::get(device);
    if (sensors_args)
        sensors_cli = args::get(sensors_args);
    if (qos)
        mqtt_topic_params.qos = args::get(qos);

    if (sensors_cli.size() > 0) {
        mqtt_topic_params.supplement_qoses(sensors_cli.size() - mqtt_topic_params.qos.size());
        mqtt_topic_params.construct_topics(device_cli, sensors_cli);
    } else {
        if (qos) {
            mqtt_topic_params.construct_topics(device_cli, args::get(qos)[0]);
        } else {
            mqtt_topic_params.supplement_qoses(1);
            mqtt_topic_params.construct_topics(device_cli);
        }
    }
}
