#include <string>

#include "params/params.hpp"
#include "cli/argparser.hpp"
#include "cli/exceptions.hpp"
#include "mqtt/client.hpp"

int main(int argc, const char* argv[]) {
    SamsungIoT::mqttapp::CliArgsParser parser;
    SamsungIoT::mqttapp::Params params;
    try {
        params = parser.parse(argc, argv);
    } catch (SamsungIoT::mqttapp::ArgParseException &e) {
        if (std::string(e.what()) == "Help") {
            return 1;
        }
    }

    SamsungIoT::mqttapp::Client client {params};

    client.get_messages();
    return 0;
}
