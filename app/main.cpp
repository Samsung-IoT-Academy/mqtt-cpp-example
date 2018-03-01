#include <cstdlib>
#include <cstring>
#include <cctype>

#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <vector>
#include <regex>

#include "params/params.hpp"
#include "cli/argparser.hpp"
#include "cli/exceptions.hpp"
#include "mqtt/customclient.hpp"

int main(int argc, const char* argv[]) {
    CliArgsParser parser;
    Params params;
    try {
        params = parser.parse(argc, argv);
    } catch (ArgParseException &e) {
        if (std::string(e.what()) == "Help") {
            return 1;
        }
    }

    const std::string client_id {"sync_consume_cpp"};
    CustomClient client {params, client_id};

    client.get_messages();
    return 0;
}
