#ifndef DEFAULTPARAMETERS_H
#define DEFAULTPARAMETERS_H

#include <string>
#include <vector>

class DefaultConnParams
{
    public:
        std::string proto;
        std::string ip;
        unsigned int port;

        DefaultConnParams() {
            proto = "tcp";
            ip = "106.109.130.18";
            port = 1883;
        }
};

class DefaultTopicParams
{
    public:
        int qos;

        DefaultTopicParams() {
            qos = 0;
        }
};

#endif // DEFAULTPARAMETERS_H
