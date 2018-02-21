/*
 * CustomActionListener.hpp
 *
 *  Created on: 12 февр. 2018 г.
 *      Author: krautcat
 */

#ifndef SRC_MQTT_CUSTOMACTIONLISTENER_HPP_
#define SRC_MQTT_CUSTOMACTIONLISTENER_HPP_

#include <atomic>

#include "mqtt/async_client.h"

class CustomActionListener  : public virtual mqtt::iaction_listener
{
	public:
        CustomActionListener();
		virtual ~CustomActionListener();

        bool is_done() const;

    private:
		void on_failure(const mqtt::token &tok) override;
		void on_success(const mqtt::token &tok) override;

        std::atomic<bool> done_;
};

#endif /* SRC_MQTT_CUSTOMACTIONLISTENER_HPP_ */
