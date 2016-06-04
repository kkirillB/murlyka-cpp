#ifndef SPLITBY_H
#define SPLITBY_H
#include <string>
#include <vector>

/*Функция разбирает строку s на токены типа std::string.
  Разделитель задается пользователем (символ е)*/
std::vector<std::string> splitBy(const char e, const std::string s);

#endif
