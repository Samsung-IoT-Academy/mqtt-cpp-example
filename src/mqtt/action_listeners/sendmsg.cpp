/*
 * CustomActionListener.cpp
 *
 *  Created on: 12 февр. 2018 г.
 *      Author: krautcat
 */

#include <mqtt/action_listeners/sendmsg.hpp>

namespace SamsungIoT {
namespace mqttapp {

SendMsgActionListener::SendMsgActionListener()
{
}

SendMsgActionListener::~SendMsgActionListener()
{
}

bool SendMsgActionListener::is_done() const
{
    return done_;
}

void SendMsgActionListener::on_failure(const mqtt::token& tok) {
    done_ = true;
}

void SendMsgActionListener::on_success(const mqtt::token& tok) {
    done_ = true;
}

}
}
