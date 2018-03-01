#include "params/default.hpp"


DefaultConnParams::DefaultConnParams() {
    proto = "tcp";
    ip = "127.0.0.1";
    port = 1883;
}

DefaultTopicParams::DefaultTopicParams() {
    qos = 0;
}
