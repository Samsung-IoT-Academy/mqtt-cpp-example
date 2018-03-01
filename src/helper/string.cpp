#include "helper/string.hpp"

namespace StringHelper
{
std::vector <std::string> split(const std::string& str, const char& ch) {
    std::string next;
    std::vector <std::string> result;

    // For each character in the string
    for (std::string::const_iterator it = str.begin(); it != str.end(); it++) {
        // If we've hit the terminal character
        if (*it == ch) {
            // If we have some characters accumulated
            if (!next.empty()) {
                // Add them to the result vector
                result.push_back(next);
                next.clear();
            }
        } else {
            // Accumulate the next character into the sequence
            next += *it;
        }
    }
    if (!next.empty())
        result.push_back(next);
    return result;
}

std::string get_substr(const std::string& str,
                       const char& ch,
                       const size_t num) {
    std::string temp = split(str, ch)[num];
    return temp;
}
}
