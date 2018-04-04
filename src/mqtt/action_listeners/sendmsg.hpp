/**
 * @file
 * @brief Заголовочный файл с описанием слушателя событий отправления
 *	сообщений.
 * 
 * Файл содержит определение класса слушателя событий отправления сообщений
 * асинхронным клиентом.
 */
#ifndef SENDMSGACTIONLISTENER_HPP_
#define SENDMSGACTIONLISTENER_HPP_

#include <atomic>

#include "mqtt/async_client.h"

namespace SamsungIoT {
namespace mqttapp {

/**
 * @brief Класс слушателя событий отправления сообщений
 * 
 * Класс реализует логику действий по наступлению успещного или неуспешного
 * отправления исхода отправления сообщения.
 */
class SendMsgActionListener :
        public virtual mqtt::iaction_listener
{
	public:
		/**
		 * Конструктор.
		 */
        SendMsgActionListener();

        /**
         * Деструктор.
         */
        virtual ~SendMsgActionListener();

        /**
         * Функция, возвращающая статус отправки сообщения.
         * @return Статус отправки.
         */
        bool is_done() const;

    private:
    	/**
    	 * Функция обратного вызова в случае неудачной отправки сообщения.
    	 * @param tok Токен, отслеживающий публикацию сообщения.
    	 */
		void on_failure(const mqtt::token& tok) override;

    	/**
    	 * Функция обратного вызова в случае успешной отправки сообщения.
    	 * @param tok Токен, оислеживающий публикацию сообщения.
    	 */
		void on_success(const mqtt::token &tok) override;

        std::atomic<bool> done_; 	/**< Статус отправки сообщения */
};

}
}

#endif /* SENDMSGACTIONLISTENER_HPP_ */
