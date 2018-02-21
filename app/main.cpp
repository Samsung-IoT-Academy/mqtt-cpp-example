#include <cstdlib>
#include <cstring>
#include <cctype>

#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <vector>
#include <regex>

#include "params.hpp"
#include "cliargsparser.hpp"
#include "mqtt/customclient.hpp"

int main(int argc, const char* argv[]) {
    CliArgsParser parser;
    Params params = parser.parse(argc, argv);

    const std::string CLIENT_ID { "sync_consume_cpp" };
    CustomClient client {params.connection_params, params.topic_params, CLIENT_ID};

    client.get_messages();
    return 0;
}
