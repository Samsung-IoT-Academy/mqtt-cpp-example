/**
 * @file
 * @brief Заголовочный файл с описанием слушателя событий подключения к
 *	MQTT-брокеру.
 * 
 * Файл содержит определение класса слушателя событий подключения клиента к
 * MQTT-брокеру.
 */
#ifndef CONNECTBROKERACTIONLISTENER_HPP_
#define CONNECTBROKERACTIONLISTENER_HPP_

#include <mqtt/iaction_listener.h>

namespace SamsungIoT {
namespace mqttapp {

/**
 * @brief Класс слушателя событий подключения к брокеру
 * 
 * Класс реализует логику действий по наступлению успещного или неуспешного
 * подключения к брокеру.
 */
class ConnectBrokerActionListener :
        public virtual mqtt::iaction_listener
{
    public:
    	/**
    	 * Конструктор.
    	 */
        ConnectBrokerActionListener();

        /**
         * Деструктор.
         */
        ~ConnectBrokerActionListener();

    private:
    	/**
    	 * Функция обратного вызова в случае неудачной попытки подключения к
    	 * серверу.
    	 * @param tok Токен, отслеживающий подключение к серверу.
    	 */
        void on_failure(const mqtt::token& tok);

    	/**
    	 * Функция обратного вызова в случае успешной попытки подключения к
    	 * серверу.
    	 * @param tok Токен, отслеживающий подключение к серверу.
    	 */
        void on_success(const mqtt::token& tok);
};

}
}

#endif // CONNECTBROKERACTOPNLISTENER_HPP_
