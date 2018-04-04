/**
 * @file
 * @brief Заголовочный файл с описанием обработчика сообщений с обычным текстом.
 * 
 * Файл содержит определение класса обработчика сооьщений, которые обрабатываются
 * «как есть», в сыром виде. 
 */
#ifndef MESSAGEHANDLERRAW_H
#define MESSAGEHANDLERRAW_H

#include <memory>

#include "mqtt/async_client.h"

#include "mqtt/msg_handlers/imessagehandler.hpp"
#include "mqtt/action_listeners/sendmsg.hpp"

namespace SamsungIoT {
namespace mqttapp {

using namespace SamsungIoT::mqttapp;

/**
 * @brief Обработчик сообщений с обычным текстом.
 * 
 * Данный класс реализует обработчик сообщений, который подразумевает обработку
 * сообщений как есть, то есть сообщений, не содержащих текст в каком-либо
 * формате передачи данных, таких как JSON, XML, YAML и прочие.
 */
class MessageHandlerRaw :
        public IMessageHandler
{
    public:
    	/**
    	 * Конструктор. 
    	 * @param cli Ссылка на асинхронного клиента.
    	 */
        MessageHandlerRaw(mqtt::async_client& cli);

        /**
         * Обработчик сообщения.
         * @param msg Умный указатель на сообщение.
         */
        virtual void handle(std::shared_ptr<const mqtt::message> msg);

    private:
        mqtt::async_client& client;			/**< Ссылка на асинхронного клиента */

        SendMsgActionListener sub_listener; /**< Слушатель события по отправке
        										сообщения */
};

}
}

#endif // MESSAGEHANDLERRAW_H
