#include "cli/exceptions.hpp"

namespace SamsungIoT {
namespace mqttapp {

ArgParseException::ArgParseException(const std::string &what) :
	std::invalid_argument(what)
{
}

ProtoParseException::ProtoParseException(const std::string &what) :
	ArgParseException(what)
{
}

IpParseException::IpParseException(const std::string &what) :
	ArgParseException(what)
{
}

PortParseException::PortParseException(const std::string &what) :
	ArgParseException(what)
{
}

}
}
