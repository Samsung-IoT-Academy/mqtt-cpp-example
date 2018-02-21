#ifndef CONNECTIONCALLBACK_HPP
#define CONNECTIONCALLBACK_HPP

#include <mqtt/iaction_listener.h>

class ConnectBroker :
        public virtual mqtt::iaction_listener
{
    public:
        ConnectBroker();
        ~ConnectBroker();

    private:
        void on_failure(const mqtt::token &tok);
        void on_success(const mqtt::token &tok);
};

#endif // CONNECTIONCALLBACK_HPP
