/*
 * CliArgsParser.cpp
 *
 *  Created on: 12 февр. 2018 г.
 *      Author: krautcat
 */

#include <iostream>
#include <list>
#include <string>
#include <memory>
#include <stdexcept>

#include <cliargsparser.hpp>

CliArgsParser::CliArgsParser() :
    parser("This is a test program.", "This goes after the options."),

    proto(parser,
            "protocol",
            "Protocol for connecting to MQTT brocker",
            {"", "proto"}),
    ip(parser,
            "ip",
            "IP address of MQTT broker",
            {"", "ip"}),
    port(parser,
            "port",
            "Port of MQTT broker",
            {"", "port"}),

    topic_group(parser,
            "Possible variants of topics:",
            args::Group::Validators::DontCare),

    topics_based_group(topic_group,
            "Topics",
            args::Group::Validators::AtLeastOne),
    device_based_group(topic_group,
            "Device and sensors",
            args::Group::Validators::AtLeastOne),

    topics(topics_based_group,
            "topics",
            "List of topics to connect",
            {"", "topics"}),

    device(device_based_group,
            "device",
            "Device to connect",
            {"", "device"}),
    sensors_args(device_based_group,
            "sensors",
            "Sensors of devices",
            {"", "sensors"}),

    qos(parser,
            "qos-num-lists",
            "QOSes of topics",
            {"", "qos"}),

    help(parser,
            "help",
            "Display this help menu",
            {"", "help"})
{
}

CliArgsParser::~CliArgsParser() {
	// TODO Auto-generated destructor stub
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

    ConnParams mqtt_conn_params;
    DefaultConnParams default_conn_params;
    if (proto) {
        mqtt_conn_params.proto = args::get(proto);
        throw std::invalid_argument("Invalid protocol");
    } else {
        mqtt_conn_params.proto = default_conn_params.proto;
    }

    if (ip) {
        std::string ip_cli = args::get(ip);

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
        mqtt_conn_params.ip = join_stream.str();
    } else {
        mqtt_conn_params.ip = default_conn_params.ip;
    }

    if (port) {
        mqtt_conn_params.port = args::get(port);
    } else {
        mqtt_conn_params.port = default_conn_params.port;
    }


    TopicParams mqtt_topic_params;
    DefaultTopicParams default_topic_params;

    std::vector<std::string> deveuis_cli;
    std::vector<std::string> sensors_cli;
    std::vector<int> qos_cli;

    if (topics) {
        // List to vector conversion
        std::vector<std::string> topics_cli = args::get(topics);
        // List to vector conversion
        if (qos) {
            qos_cli = args::get(qos);
        }

        // Inserting additional elements to QOS vector
        while (qos_cli.size() < topics_cli.size()) {
            qos_cli.push_back(default_topic_params.qos);
        }

        // Split topics string by "/" delimetera and push parts to vectors.
        // If not sensor part was specified, assume, that subscribe to "#"
        for (auto t = topics_cli.begin(); t != topics_cli.end(); ++t) {
            std::vector<std::string> topic_parts;
            std::string topic_part;
            std::istringstream token_stream(*t);
            while (std::getline(token_stream, topic_part, '/')) {
                topic_parts.push_back(topic_part);
            }

            deveuis_cli.push_back(topic_parts[0]);
            if (topic_parts.size() == 1) {
                sensors_cli.push_back("#");
            } else {
                sensors_cli.push_back(topic_parts[1]);
            }
        }

        mqtt_topic_params.construct_topics(deveuis_cli, sensors_cli, qos_cli);
    } else if (device) {
        std::string device_cli = args::get(device);
        if (sensors_args) {
            sensors_cli = args::get(sensors_args);
        }
        if (qos) {
            qos_cli = args::get(qos);
        }
        if (sensors_cli.size() > 0) {
            if (qos_cli.size() < sensors_cli.size()) {
                qos_cli.push_back(default_topic_params.qos);
            }
            mqtt_topic_params.construct_topics(device_cli, sensors_cli, qos_cli);
        } else {
            mqtt_topic_params.construct_topics(device_cli,
                                               (qos)
                                                   ? args::get(qos)[0]
                                                   : default_topic_params.qos);
        }
    } else {
        std::cerr << "Connect to the default topic" << std::endl;
        mqtt_topic_params.construct_topics(
                    (qos)
                        ? args::get(qos)[0]
                        : default_topic_params.qos);
    }


    return Params(mqtt_conn_params, mqtt_topic_params);
}
