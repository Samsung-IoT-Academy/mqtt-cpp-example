/**
 * @file
 * @brief Заголовочный файл с определением класса, содержащего фабричный метод
 * 	создания обработчиков сообщений.
 */
#ifndef MSGHANDLERFACTORY_HPP_
#define MSGHANDLERFACTORY_HPP_

#include "mqtt/msg_handlers/imessagehandler.hpp"
#include "mqtt/msg_handlers/raw.hpp"
#include "mqtt/msg_handlers/json.hpp"

namespace SamsungIoT {
namespace mqttapp {

using namespace SamsungIoT::mqttapp;

/**
 * @brief Фабрика обработчиков сообщений.
 * 
 * Класс с фабричным методом создания инстанса обработчика сообщений.
 */
class MessageHandlerFactory
{
    public:
    	/// Возможные обработчики сообщений
        enum class HandlerType {
            Raw,	///< «Сырые» сообщения
            JSON 	///< Сообщения в формате JSON
        };

        /**
         * Фабричный метод создания объекта, реализующего интерфейс обработчика
         * сообщений.
         * @param type Тип обработчика.
         * @param client Ссылка на асинхронного клиента.
         * @return Указатель на созданный обработчик сообщения.
         */
        static IMessageHandler* create(HandlerType type, mqtt::async_client& client);
};

}
}

#endif // MSGHANDLERFACTORY_HPP_
