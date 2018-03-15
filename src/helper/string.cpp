#include "helper/string.hpp"

namespace SamsungIoT {
namespace helpers {

std::vector<std::string> split(const std::string& str, char ch) {
    std::string next;
    std::vector<std::string> result;

    for (std::string::const_iterator it = str.begin(); it != str.end(); it++) {
        if (*it == ch) {
            if (!next.empty()) {
                result.push_back(next);
                next.clear();
            }
        } else {
            next += *it;
        }
    }
    if (!next.empty())
        result.push_back(next);
    return result;
}

std::string get_substr(const std::string& str, char ch, size_t num) {
    std::string temp = split(str, ch)[num];
    return temp;
}

}
}
