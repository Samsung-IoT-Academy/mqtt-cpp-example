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

#include "defaultparameters.hpp"
#include "params.hpp"

class CliArgsParser {
public:
	CliArgsParser();
	virtual ~CliArgsParser();
    Params parse(int argc, const char* argv[]);
private:
    args::ArgumentParser parser;

    args::ValueFlag<std::string> proto;
    args::ValueFlag<std::string> ip;
    args::ValueFlag<int> port;

    args::Group topic_group;

    args::Group topics_based_group;
    args::Group device_based_group;

    args::ValueFlagList<std::string> topics;

    args::ValueFlag<std::string> device;
    args::ValueFlagList<std::string> sensors_args;

    args::ValueFlagList<int> qos;


    args::HelpFlag help;
};
#endif /* SRC_CLIARGSPARSER_HPP_ */
