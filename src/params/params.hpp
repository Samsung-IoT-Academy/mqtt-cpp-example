/**
 * @file
 * @brief Заголовочный файл с описанием классов-обёрток параметров приложения.
 * 
 * Файл содержит определение классов, являющимися обёртками для параметров,
 * используемых в приложении для подключения к брокеру, подписки на топики и
 * обработки входящих сообщений.
 */
#ifndef PARAMS_HPP_
#define PARAMS_HPP_

#include <string>
#include <vector>
#include <tuple>
#include <memory>

#include "mqtt/string_collection.h"

#include "params/default.hpp"
#include "mqtt/msg_handlers/msghandlerfactory.hpp"

namespace SamsungIoT {
namespace mqttapp {

using namespace SamsungIoT::mqttapp;

/**
 * @brief Параметры соединения.
 * 
 * Класс-обёртка, содержащий необходимые параметры для соединения с
 * MQTT-брокером.
 */
class ConnParams
{
    public:
        /**
         * Конструктор.
         */
        ConnParams();

        /**
         * Геттер строки с URI MQTT-брокера.
         * @return Строка, содержащая URI в формате
         *  \<протокол\>://\<IP-адрес\>:\<номер порта\>, пригодном для аргумента
         *  методу подключения к брокеру из библиотеки Paho.
         */
        const std::string get_server_uri() const;

        /**
         * Геттер идентификатора клиента.
         * @return Строка, содержащая идентификатор клиента.
         */
        const std::string get_client_id() const;

        /**
         * Сеттер протокола.
         * @param value Строка, содержащая название протокола.
         */
        void set_proto(const std::string& value);

        /**
         * Сеттер IP-адреса.
         * @param value Строка, содержащая валидный IP-адрес.
         */
        void set_ip(const std::string& value);

        /**
         * Сеттер порта.
         * @param value Номер порта.
         */
        void set_port(unsigned int value);

        /**
         * Сеттер идентификатора клиента.
         * @param value Строка с идентификатором клиента.
         */
        void set_client_id(const std::string& value);

        /**
         * Функция, возвращающая список доступных протоколов.
         * @return Вектор со строками, содержащими названия протоколов.
         */
        static std::vector<std::string> avaliable_protocols();

    private:
        DefaultConnParams defaults; /**< Параметры по умолчанию для подключения */
        
        std::string proto;          /**< Протокол. */
        std::string ip;             /**< IP-адрес. */
        unsigned int port;          /**< Номер порта. */

        std::string client_id;      /**< Клиентский идентификатор. */
};

/**
 * @brief Параметры подписки на топики.
 * 
 * Класс-обёртка, содержащий необходимые параметры для подписки на
 * топики..
 */
class TopicParams
{
    public:
        /**
         * Коснтруктор по умолчанию.
         */
        TopicParams();

        /**
         * Конструктор.
         * @param topics_base База для топиков.
         */
        TopicParams(const std::string& topics_base);

        /**
         * Создание топика по умолчанию (\<база\>/#).
         */
        void construct_topics();

        /**
         * Создание топика вида \<база\>/\<device EUI\>/#.
         * @param deveui Уникальный ID устройства.
         */
        void construct_topics(const std::string& deveui);

        /**
         * Создание топиков вида \<база\>/\<device EUI\>/\<сенсор\>, где имя сенсора
         * берётся из вектора сенсоров.
         * @param deveui Уникальный ID устройства.
         * @param sensors Вектор сенсоров.
         */
        void construct_topics(const std::string& deveui,
                              const std::vector<std::string>& sensors);

        /**
         * Создание топиков вида \<база\>/\<i-ый device EUI\>/\<i-ый сенсор\>, где EUI
         * устройства берётся из вектора уникальных EUI устройств, имя сенсора
         * берётся из вектора сенсоров. Соответствие EUI и сенсору ведётся по
         * порядковому номеру элементов в векторах.
         * @param deveuis Вектор уникальных ID устройств.
         * @param sensors Вектор сенсоров.
         */
        void construct_topics(const std::vector<std::string>& deveuis,
                              const std::vector<std::string>& sensors);

        /**
         * Создание топиков вида \<база\>/+/\<сенсор\>, где сенсор берётся из вектора
         * сенсоров.
         * @param sensors Вектор сенсоров.
         */
        void construct_topics_sensors(const std::vector<std::string>& sensors);

        /**
         * Дополнение вектора со значениями QoS значением по умолчанию 
         * до длины length.
         * @param length Длина, до которой дополняется вектор QoS.
         */
        void supplement_qoses(int length);

        /**
         * Функция, возвращающая коллекцию топиков в формате, который принимают
         * функции подписки библиотеки Paho.
         * @return Умный указатель на коллекцию строк, содержащих топики.
         */
        std::shared_ptr<const mqtt::string_collection> get_topics();

        /**
         * Функция, возвращающая коллекцию топиков как вектор строк.
         * @return Вектор строк, содержащий строки с топиками.
         */
        std::vector<std::string> get_topics_strings();

        std::vector<std::string> topics;    /**< Вектор строк с топиками */
        std::vector<int> qos;               /**< Вектор со значениями QoS */

    private:
        /**
         * Конструктор топика вида \<база\>/\<deveui\>/\<sensor\>.
         * @param deveui Уникальный EUI устройства.
         * @param sensor Название сенсора.
         * @return Строка, содержащая топик.
         */
        std::string construct_topic(const std::string& deveui,
                                    const std::string& sensor);

        /**
         * Конструктор топика вида \<база\>/\<deveui\>/#.
         * @param deveui Уникальный EUI устройства.
         * @return Строка, содержащая топик.
         */
        std::string construct_topic(const std::string& deveui);

        DefaultTopicParams defaults;    /**< Параметры по умолчанию */

        std::string base;               /**< База для топиков */
};

/**
 * @brief Параметры для обработчика сообщений.
 * 
 * Класс-обёртка параметров, необходимых для создания обработчика сообщений.
 */
class MessageHandlerParams
{
    public:
        /**
         * Конструктор по умолчанию.
         */
        MessageHandlerParams();

        MessageHandlerFactory::HandlerType handler_type; /**< Тип обработчика */
};


/**
 * @brief Параметры для всего приложения.
 * 
 * Класс-обёртка, являющийся композицией всех классов-параметров, необходимых
 * для инициализации приложения.
 */
class Params
{
    public:
        /**
         * Конструктор по умолчанию.
         */
        Params();

        /**
         * Конструктор, перемещающий аргументы к себе во владение.
         * @param con Параметры подключения.
         * @param top Параметры подписки на топики.
         * @param msg_hndlr Параметры обработчика сообщений.
         */
        Params(ConnParams& con, TopicParams& top, MessageHandlerParams& msg_hndlr);

        ConnParams connection_params;               /**< Параметры подключений */
        TopicParams topic_params;                   /**< Параметры подписки на
                                                    топики */
        MessageHandlerParams msg_handler_params;    /**< Параметры обработчика
                                                    сообщений */
};

}
}
//

#endif /* PARAMS_HPP_ */
