/**
 * @file
 * @brief Заголовочный файл с описанием классов-исключений парсера опций
 *  командной строки.
 * 
 * Файл содержит определение классов, используемых при бросании исключений
 * при валидации опций командной строки.
 */
#ifndef CLIEXCEPTIONS_HPP_
#define CLIEXCEPTIONS_HPP_

#include <string>
#include <stdexcept>

namespace SamsungIoT {
namespace mqttapp {

/**
 * @brief Базовый класс исключений.
 * 
 * Базовый класс, от которого наследуются остальные классы исключений, бросаемые
 * при валидации опций командной строки.
 */
class ArgParseException :
        public std::invalid_argument
{
    public:
    	/**
    	 * Конструктор. 
    	 * @param what Описание исключения.
    	 */
        ArgParseException(const std::string& what);
};

/**
 * @brief Класс исключения, бросаемый при неудачной валидации протокола.
 * 
 * Данный класс используется в случае, когда валидация названия протокола,
 * который был передан через опции командной строки, заканчивается неуспехом.
 */
class ProtoParseException :
		public ArgParseException
{
	public:
		/**
		 * Конструктор.
		 * @param what Описание исключения.
		 */
		ProtoParseException(const std::string &what);	
};

/**
 * @brief Класс исключения, бросаемый при неудачной валидации IP-адреса.
 * 
 * Данный класс используется в случае, когда валидация IP-адреса, переданного
 * через опции командной строки, заканчивается неуспехом.
 */
class IpParseException :
		public ArgParseException
{
	public:
		/**
		 * Конструктор.
		 * @param what Описание исключения.
		 */
		IpParseException(const std::string& what);
};

/**
 * @brief Класс исключения, бросаемый при неудачной валидации порта.
 * 
 * Данный класс используется в случае, когда валидация порта, переданного
 * через опции командной строки, заканчивается неуспехом.
 */
class PortParseException :
		public ArgParseException
{
	public:
		/**
		 * Конструктор.
		 * @param what Описание исключения.
		 */
		PortParseException(const std::string& what);
};

}
}

#endif /* CLIEXCEPTIONS_HPP_ */
