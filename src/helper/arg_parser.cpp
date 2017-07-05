/*
 * ArgParser.cpp
 *
 *  Created on: 5 июл. 2017 г.
 *      Author: krautcat
 */
#include <algorithm>

#include "arg_parser.hpp"

using namespace std;

ArgParser::ArgParser(int& argc, char** argv) {
    for (int i=1; i < argc; ++i)
        this->tokens.push_back(string(argv[i]));
}

ArgParser::~ArgParser() {
    // TODO Auto-generated destructor stub
}

const string & ArgParser::getCmdOption(const string &option) const {
    vector<string>::const_iterator itr;

    itr =  find(this->tokens.begin(), this->tokens.end(), option);
    if (itr != this->tokens.end() && ++itr != this->tokens.end()){
        return *itr;
    }

    static const string empty_string("");
    return empty_string;
}

bool ArgParser::cmdOptionExists(const string &option) const {
    return find(this->tokens.begin(), this->tokens.end(), option)
            != this->tokens.end();
}
