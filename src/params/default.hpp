/**
 * @file
 * @brief Заголовочный файл с описанием классов параметров по умолчанию.
 * 
 * Файл содержит определение классов, содержащих параметры по умолчанию.
 */
#ifndef DEFAULTPARAMETERS_H
#define DEFAULTPARAMETERS_H

#include <string>
#include <vector>

namespace SamsungIoT {
namespace mqttapp {

/**
 * @brief Параметры для подключения по-умолчанию.
 * 
 * Класс содержит параметры для подключения к MQTT-брокеру, используемые
 * по умолчанию.
 */
class DefaultConnParams
{
    public:
        /**
         * Конструктор.
         */
        DefaultConnParams();

        std::string proto;      /**< Протокол */
        std::string ip;         /**< IP-адрес */
        unsigned int port;      /**< Порт */

        std::string client_id;  /**< Идентификатор клиента */
};

/**
 * @brief Параметры топиков.
 * 
 * Класс содержит параметры по умолчанию для топиков MQTT.
 */
class DefaultTopicParams
{
    public:
        /**
         * Конструктор.
         */
        DefaultTopicParams();

        std::string base;       /**< База топиков */
        std::string topic;      /**< Топик */
        int qos;                /**< Значение QoS */
};

}
}

#endif // DEFAULTPARAMETERS_H
