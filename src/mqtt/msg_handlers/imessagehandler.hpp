/**
 * @file
 * @brief Заголовочный файл с описанием интерфейса обработчиков сообщений.
 * 
 * Файл содержит определение класса IMessageHandler, являющегося интерфейсом
 * для обработчиков сообщений.
 */
#ifndef IMESSAGEHANDLER_HPP
#define IMESSAGEHANDLER_HPP

#include <memory>

#include "mqtt/message.h"
#include "mqtt/async_client.h"

#include "mqtt/action_listeners/sendmsg.hpp"

namespace SamsungIoT {
namespace mqttapp {

/**
 * @brief Интерфейсный класс для обработчиков сообщений
 * 
 * Интерфейсный класс, описывающий интерфейс обработки сообщений.
 */
class IMessageHandler {
    public:
    	/**
    	 * Конструктор.
    	 */
        virtual ~IMessageHandler() {}

        /**
         * Обработчик сообщения.
         * @param msg Умный указатель на сообщение.
         */
        virtual void handle(std::shared_ptr<const mqtt::message> msg) = 0;
};

}
}

#endif // IMESSAGEHANDLER_HPP
