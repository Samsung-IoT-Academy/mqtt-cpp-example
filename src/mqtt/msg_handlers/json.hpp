/**
 * @file
 * @brief Заголовочный файл с описанием обработчика JSON-сообщений.
 * 
 * Файл содержит определение класса обработчика сообщений в формате JSON.
 */
#ifndef MESSAGEHANDLERJSON_HPP
#define MESSAGEHANDLERJSON_HPP

#include <memory>

#include "mqtt/async_client.h"
#include "mqtt/message.h"
#include "json/reader.h"

#include "mqtt/msg_handlers/imessagehandler.hpp"
#include "mqtt/action_listeners/sendmsg.hpp"

namespace SamsungIoT {
namespace mqttapp {

using namespace SamsungIoT::mqttapp;

/**
 * @brief Обработчик JSON-сообщений
 * 
 * Класс реализует интерфейс обработчика сообщений и обработку JSON-сообщений.
 */
class MessageHandlerJson :
        public IMessageHandler
{
    public:
    	/**
    	 * Конструктор.
    	 * @param cli Ссылка на асинхронного клиента.
    	 */
        MessageHandlerJson(mqtt::async_client& cli);

        /**
         * Обработчик сообщения.
         * @param msg Умный указатель на сообщение.
         */
        virtual void handle(std::shared_ptr<const mqtt::message> msg);

    private:
        mqtt::async_client& client;			/**< Ссылка на асинхронного клиента */

        SendMsgActionListener sub_listener;	/**< Слушатель события по отправке
        										сообщения */

        Json::Reader json_reader;			/**< Парсер JSON */

};

}
}

#endif // MESSAGEHANDLERJSON_HPP
