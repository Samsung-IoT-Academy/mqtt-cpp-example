#ifndef CONNECTIONCALLBACK_HPP
#define CONNECTIONCALLBACK_HPP

#include <mqtt/iaction_listener.h>

namespace SamsungIoT {
namespace mqttapp {

class ConnectBrokerActionListener :
        public virtual mqtt::iaction_listener
{
    public:
        ConnectBrokerActionListener();
        ~ConnectBrokerActionListener();

    private:
        void on_failure(const mqtt::token& tok);
        void on_success(const mqtt::token& tok);
};

}
}

#endif // CONNECTIONCALLBACK_HPP
