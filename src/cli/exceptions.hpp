#ifndef ARGPARSE_HPP
#define ARGPARSE_HPP

#include <exception>
#include <string>

namespace SamsungIoT {
namespace mqttapp {

class ArgParseException :
        public std::exception
{
    public:
        ArgParseException(const std::string& what);

        virtual const char* what() const noexcept;

    private:
        std::string reason;
};

}
}

#endif // ARGPARSE_HPP
