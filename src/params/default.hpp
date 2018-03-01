#ifndef DEFAULTPARAMETERS_H
#define DEFAULTPARAMETERS_H

#include <string>
#include <vector>

class DefaultConnParams
{
    public:
        DefaultConnParams();

        std::string proto;
        std::string ip;
        unsigned int port;
};

class DefaultTopicParams
{
    public:
        DefaultTopicParams();

        int qos;
};

#endif // DEFAULTPARAMETERS_H
