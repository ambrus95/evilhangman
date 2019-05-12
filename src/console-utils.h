#ifndef CONSOLEUTILS_H
#define CONSOLEUTILS_H
#include <string>
#include <iostream>

std::string opt_plural(size_t s);
size_t get_pos_int(size_t min, size_t max, std::istream & is = std::cin, std::ostream & os = std::cout);
char get_single_char(std::istream & is = std::cin, std::ostream & os = std::cout);
#endif
