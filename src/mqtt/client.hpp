/**
 * @file
 * @brief Заголовочный файл с описанием класса Client
 * 
 * Файл содержит определение класса Client, являющегося главной в примере.
 */
#ifndef SRC_MQTT_CUSTOMCLIENT_HPP_
#define SRC_MQTT_CUSTOMCLIENT_HPP_

#include "mqtt/async_client.h"

#include "params/params.hpp"
#include "mqtt/callback.hpp"
#include "mqtt/msg_handlers/imessagehandler.hpp"

namespace SamsungIoT {
namespace mqttapp {

using namespace SamsungIoT::mqttapp;

/**
 * @brief Клиентский класс, отвечающий за получение и обработку сообщений
 * 
 * Класс Client отвечает за получение сообщения и дальнейшую передачу сообщения
 * классу-обработчику, реализующему интерфейс IMessageHandler.
 */
class Client {
    public:

        /**
         * Конструктор класса Client.
         * @param parameters Ссылка на объект-обёртку с параметрами подключения,
         *  параметрами топиков и параметром, необходимым для создания
         *  объекта-обработчика сообщений.
         */
        Client(SamsungIoT::mqttapp::Params& parameters);

        /**
         * Деструктор.
         */
        ~Client();

        /**
         * Соединение с MQTT-брокером.
         * @throw mqtt::exception Если соединение завершилось неуспехом.
         */
        void connect();

        /**
         * Отключение от MQTT-брокера
         * @throw mqtt::exception В случае возникновении исключения при
         *  отсоединении от сервера.
         */
        void disconnect();

        /**
         * Блокирующая функция, в которой происходит получение сообщений от
         * клиента и дальнейшная их передача обработчику сообщений.
         */
        void get_messages();

	private:
        mqtt::connect_options conn_opts;    /**< Опции для подключения клиента */
        mqtt::async_client async_client;    /**< Асинхронный клиент */

        IMessageHandler* msg_handler;       /**< Указатель на обработчик сообщения */
        Callback cb;                        /**< Коллбэк, передающийся клиенту */

        std::string server_addr;            /**< Адрес сервера, к которому
                                                подключается клиент */
};

}
}

#endif /* SRC_MQTT_CUSTOMCLIENT_HPP_ */
