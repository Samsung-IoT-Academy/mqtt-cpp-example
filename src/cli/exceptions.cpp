#include "cli/exceptions.hpp"

ArgParseException::ArgParseException(const std::string &what)
{
    reason = what;
}

const char *ArgParseException::what() const noexcept
{
    return reason.c_str();
}
