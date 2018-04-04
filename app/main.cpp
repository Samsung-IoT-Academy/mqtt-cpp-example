#include <string>

#include "args.hxx"

#include "params/params.hpp"
#include "cli/argparser.hpp"
#include "cli/exceptions.hpp"
#include "mqtt/client.hpp"

enum class ExitCodes : int {
    Help = 1,
    CliGroupValidationError = 2,
    ParseError = 3,
    CliArgsValidationError = 4
};

template <typename T>
constexpr typename std::underlying_type<T>::type to_underlying(T t) noexcept 
{
    return static_cast<typename std::underlying_type<T>::type>(t);
}

int main(int argc, const char* argv[]) {
    SamsungIoT::mqttapp::CliArgsParser parser;
    SamsungIoT::mqttapp::Params params;
    try {
        params = parser.parse(argc, argv);
    } catch (args::Help &e) {
        return to_underlying(ExitCodes::Help);
    } catch (args::ValidationError &e) {
        return to_underlying(ExitCodes::CliGroupValidationError);
    } catch (args::ParseError &e) {
        return to_underlying(ExitCodes::ParseError);
    } catch (SamsungIoT::mqttapp::ArgParseException &e) {
        std::cerr << e.what() << std::endl;
        return to_underlying(ExitCodes::CliArgsValidationError);
    }

    SamsungIoT::mqttapp::Client client {params};

    client.get_messages();
    return 0;
}
