/**
 * @file
 * @brief Заголовочный файл с описанием класса Callback
 * 
 * Файл содержит определение класса Callback, который содержит методы,
 * вызываемые клиентом, которому передаётся ссылка на объект этого класса,
 * при наступлении определённых событий
 */
#ifndef SRC_MQTT_CUSTOMCALLBACK_HPP_
#define SRC_MQTT_CUSTOMCALLBACK_HPP_

#include "mqtt/async_client.h"

#include "mqtt/msg_handlers/imessagehandler.hpp"

namespace SamsungIoT {
namespace mqttapp {

using namespace SamsungIoT::mqttapp;

/**
 * @brief Класс с функциями обратного вызова
 * 
 * Класс Callback реализует интерфейс mqtt::callback, предоставляя функции
 * обратного вызова по наступлению определённых событий.
 */
class Callback :
    public virtual mqtt::callback
{
	public:
        /**
         * Конструктор.
         * @param cli_cl Ссылка на асинхронного клиента.
         */
        Callback(mqtt::async_client& cli_cl);

        /**
         * Деструктор.
         */
        virtual ~Callback();

        /**
         * Устанавливает опции подключения.
         * @param opts Указатель на опции для подключения.
         */
        void set_connopts(const mqtt::connect_options* opts);

        /**
         * Устанавлиает обработчик сообщений.
         * @param msg_hndlr Указатель на обработчик сообщений.
         */
        void set_msg_handler(IMessageHandler *msg_hndlr);

    private:
        /**
         * Функция, вызываемая при потере соединения с сервером.
         * @param cause Причина потери соединения.
         */
        void connection_lost(const std::string& cause) override;

        /**
         * Функция, вызываемая при получении сообщения от сервера.
         * @param msg Указатель на сообщение.
         */
        void message_arrived(mqtt::const_message_ptr msg) override;

        /**
         * Функция переподключения к серверу.
         */
        void reconnect();

        mqtt::async_client& cli;                /**< Ссылка на асинхронного клиента. */

        const mqtt::connect_options* connOpts;  /**< Указатель на опции подключения  */

};

}
}

#endif /* SRC_MQTT_CUSTOMCALLBACK_HPP_ */
