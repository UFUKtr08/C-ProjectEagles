#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <sstream>

// C++98 uyumlu integer to string çevirici
static std::string intToString(int value) {
    std::stringstream ss;
    ss << value;
    return ss.str();
}

#endif