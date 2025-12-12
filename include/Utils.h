#ifndef UTILS_H
#define UTILS_H
#include <string>
#include <sstream>
static std::string intToString(int value) {
    std::stringstream ss;
    ss << value;
    return ss.str();
}
#endif