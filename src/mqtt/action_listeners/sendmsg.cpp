/*
 * CustomActionListener.cpp
 *
 *  Created on: 12 февр. 2018 г.
 *      Author: krautcat
 */

#include <mqtt/action_listeners/sendmsg.hpp>

CustomActionListener::CustomActionListener()
{
}

CustomActionListener::~CustomActionListener() {
    // TODO Auto-generated destructor stub
}

bool CustomActionListener::is_done() const
{
    return done_;
}

void CustomActionListener::on_failure(const mqtt::token &tok) {
    done_ = true;
}

void CustomActionListener::on_success(const mqtt::token &tok) {
    done_ = true;
}
