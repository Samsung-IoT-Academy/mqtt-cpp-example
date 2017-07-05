/*
 * ArgParser.h
 *
 *  Created on: 5 июл. 2017 г.
 *      Author: krautcat
 */
#ifndef HELPER_ARG_PARSER_HPP_
#define HELPER_ARG_PARSER_HPP_

#include <string>
#include <vector>

using namespace std;

class ArgParser
{
    public:
        ArgParser(int &argc, char **argv);
        virtual ~ArgParser();

        const string & getCmdOption(const string &option) const;
        bool cmdOptionExists(const string &option) const;

    private:
        vector <string> tokens;
};

#endif /* HELPER_ARG_PARSER_HPP_ */
