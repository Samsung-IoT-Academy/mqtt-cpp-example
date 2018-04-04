/**
 * @file
 * @brief Заголовочный файл с определением функций-хелперов для строк.
 * 
 * Файл содержит определение функций, используемых как вспомогательные 
 * функции для работы со строками в приложении.
 */

#ifndef HELPERSTRING_HPP_
#define HELPERSTRING_HPP_

#include <vector>
#include <string>

namespace SamsungIoT {
namespace helpers {

/**
 * @brief 			 Разбиение строки на подстроки по символу.
 *
 * Функция принимает на вход строку и символ, по которому разделяется исходная
 * строка на подстроки. При этом подстроки не содержат символ, по которому
 * разбивается исходная строка.
 *
 * @param[in]  str   Исходная строка.
 * @param[in]  ch    Символ-разделитель.
 *
 * @return     Вектор строк.
 */
std::vector<std::string> split(const std::string& str, char ch);

/**
 * @brief 			 Получение определённой подстроки из вектора строк
 *
 * Функция разбивает исходную строку на подстроки и возвращает подстроку, чей
 * индекс равен переданному в параметре num.
 * 
 * Вектор подстрок формируется вызовом функции @ref
 * SamsungIoT::helpers::split(const std::string&, char) "split(str, ch)".
 *
 * @param[in]  str   Исходная строка.
 * @param[in]  ch    Символ-разделитель.
 * @param[in]  num   Номер подстроки в векторе подстрок.
 *
 * @return     Подстрока с порядковым номером num.
 */
std::string get_substr(const std::string& str, char ch, size_t num);

}
}
#endif /* HELPERSTRING_HPP_ */
