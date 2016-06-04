#ifndef ERRORS_AND_TRIES_H
#define ERRORS_AND_TRIES_H

#include "error_count.h"
#include "trie.h"
#include <memory>
/* Структура для работы с классом подсчета ошибок
 * и синтаксическими деревьями */
struct Errors_and_tries{
    std::shared_ptr<Error_count> ec;
    std::shared_ptr<Char_trie>   ids_trie;
		std::shared_ptr<Char_trie>   str_lit_trie;   
    Errors_and_tries()  = default;
    ~Errors_and_tries() = default;
};

using Errors_and_tries_ptr = std::shared_ptr<Errors_and_tries>;

#endif
