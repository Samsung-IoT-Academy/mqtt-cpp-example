/*
 * json_helpers.hpp
 *
 *  Created on: 7 июл. 2017 г.
 *      Author: krautcat
 */

#ifndef SRC_HELPER_STRING_HPP_
#define SRC_HELPER_STRING_HPP_

#include <vector>
#include <string>

namespace SamsungIoT {
namespace helpers {

std::vector<std::string> split(const std::string& str, char ch);
std::string get_substr(const std::string& str, char ch, size_t num);

}
}
#endif /* SRC_HELPER_STRING_HPP_ */
