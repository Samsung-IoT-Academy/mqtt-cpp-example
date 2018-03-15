#include "cli/exceptions.hpp"

namespace SamsungIoT {
namespace mqttapp {

ArgParseException::ArgParseException(const std::string &what)
{
    reason = what;
}

const char *ArgParseException::what() const noexcept
{
    return reason.c_str();
}

}
}
