#include "console-utils.h"
#include <string>
#include <iostream>
#include <sstream>
#include <cctype>

std::string opt_plural(size_t s) {
    return s == 1 ? "" : "s";
}

size_t get_pos_int(size_t min = 0, size_t max = -1, std::istream & is, std::ostream & os){
    std::string buffer;
    size_t result;
    const std::string message = "Enter an integer between " + std::to_string(min) + " and " + std::to_string(max) + ": ";
    while(true){
        os << message;
        std::getline(is,buffer);
        std::stringstream ss(buffer);
        if (ss >> result && result >= min && result <= max) // siker
            return result;
    }
}

char get_single_char(std::istream & is, std::ostream & os){
    std::string buffer;
    while(true){
        os << "Enter a single character: ";
        std::getline(is,buffer);
        if(buffer.length() == 1)
            return buffer[0];
    }
}
