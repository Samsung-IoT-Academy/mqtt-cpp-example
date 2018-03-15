#ifndef DEFAULTPARAMETERS_H
#define DEFAULTPARAMETERS_H

#include <string>
#include <vector>

namespace SamsungIoT {
namespace mqttapp {

class DefaultConnParams
{
    public:
        DefaultConnParams();

        std::string proto;
        std::string ip;
        unsigned int port;

        std::string client_id;
};

class DefaultTopicParams
{
    public:
        DefaultTopicParams();

        std::string base;
        std::string topic;
        int qos;
};

}
}

#endif // DEFAULTPARAMETERS_H
