/**
 * @file
 * @brief Заголовочный файл с описанием парсера опций команжной строки.
 * 
 * Файл содержит определение класса парсера опций командной строки.
 */

#ifndef CLIARGSPARSER_HPP_
#define CLIARGSPARSER_HPP_

#include <tuple>
#include <memory>

#include "args.hxx"

#include "params/default.hpp"
#include "params/params.hpp"

namespace SamsungIoT {
namespace mqttapp {

using namespace SamsungIoT::mqttapp;

/**
 * @brief Парсер опций командной строки
 * 
 * Класс реализует логику по обработке опций командной строки, используя
 * библиотеку args.
 */
class CliArgsParser {
    public:
        /**
         * Конструктор.
         */
        CliArgsParser();

        /**
         * Деструктор.
         */
        ~CliArgsParser();

        /**
         * Функция, которая парсит опции командной строки. 
         * @param argc Число параметров, переданных из командной строки.
         * @param argv Массив нуль-терминированных строк в стиле C.
         * 
         * @return Объект-обёртку, содержащий параметры.
         */
        Params parse(int argc, const char* argv[]);

    private:
        /**
         * Парсинг и валидация протокола, используемого для подключения к
         * брокеру.
         * @param mqtt_conn_params Ссылка на объект с параметрами для
         *  подключения к брокеру.
         */
        void parse_proto(ConnParams& mqtt_conn_params);

        /**
         * Парсинг и валидация IP-адреса брокера.
         * @param mqtt_conn_params Ссылка на объект с параметрами для
         *  подключения к брокеру.
         */
        void parse_ip(ConnParams& mqtt_conn_params);

        /**
         * Парсинг и валидация порта брокера.
         * @param mqtt_conn_params Ссылка на объект с параметрами для
         *  подключения к брокеру.
         */
        void parse_port(ConnParams& mqtt_conn_params);

        /**
         * @brief Парсинг опций, связанных с MQTT-топиком.
         * @details Функция верхнего уровня,
         *  вызывающая в зависимости от опций командной строки либо одну из
         *  функция paese_topics_param или parse_device_param, либо использующая
         *  параметры по умолчанию. 
         * @param mqtt_topic_params Ссылка на объект с параметрами MQTT-топиков. 
         */
        void parse_mqtt_topics(TopicParams& mqtt_topic_params);

        /**
         * Парсинг опций, если была передана опция --topics.
         * @param mqtt_topic_params Ссылка на объект с параметрами MQTT-топиков.
         */
        void parse_topics_param(TopicParams& mqtt_topic_params);

        /**
         * Парсинг опций, если была передана опция --device.
         * @param mqtt_topic_params Ссылка на объект с параметрами MQTT-топиков.
         */
        void parse_device_param(TopicParams& mqtt_topic_params);

        /**
         * Парсинг опций, если была передана только опция --sensors. 
         * @param mqtt_topic_params Ссылка на объект с параметрами MQTT-топиков.
         */
        void parse_sensors_param(TopicParams& mqtt_topic_params);

        /**
         * Парсинг опций, связанных с выбором обработчика сообщений. 
         * @param msg_handler_params Ссылка на объект с параметрами, необходимыми
         *  для создания обработчика сообщений.
         */
        void parse_message_handler(MessageHandlerParams& msg_handler_params);

        /**
         * Функция, выдающая необходимое диагностическое сообщение в зависимости
         * от поданных опций командной строки, в случае, если валидация групп
         * завершилась неудачей.
         */
        void handle_validation_error();

        args::ArgumentParser parser;        /**< Объект-парсер опций */

        args::ValueFlag<std::string> proto; /**< Опция --proto — протокол */
        args::ValueFlag<std::string> ip;    /**< Опция --ip — IP-адрес */
        args::ValueFlag<int> port;          /**< Опция --port — номер порта */

        args::Group topic_group;            /**< Группа опций, связанных с
                                                топиком */

        args::ValueFlagList<std::string> topics; /**< Опции --topics — топики */

        args::Group device_based_group;     /**< Группа опций, связанная с
                                                топиками, создаеваемыми для
                                                разных датчиков и актуаторов с
                                                одного устройства */
        args::ValueFlag<std::string> device; /**< Опция --device — устройство */
        args::ValueFlagList<std::string> sensors_args; /**< Опции --sensors —
                                                датчики */

        args::ValueFlagList<int> qos;       /**< Опции --qos — QoS */

        args::Group msg_handler_group;      /**< Группа опций, отвечающая за
                                                выбор обработчика сообщений */
        args::Flag raw;                     /**< Опция --raw — обработчик
                                                сообщений м обычным текстом */
        args::Flag json;                    /**< Опция --json — обработчик
                                                сообщений с JSON */

        args::HelpFlag help;                /**< Опция --help — помощь */
};

}
}
#endif /* CLIARGSPARSER_HPP_ */
