#ifndef ABSTRACT_SCANER_H
#define ABSTRACT_SCANER_H

#include <string>
#include <memory>
#include "error_count.h"
#include "trie.h"
#include "location.h"
#include "errors_and_tries.h"

template<typename Lexem_type>
class Scaner{
public:
    Scaner<Lexem_type>() = default;
    Scaner(Location_ptr location, Errors_and_tries_ptr et);
    Scaner(const Scaner<Lexem_type>& orig) = default;
    virtual ~Scaner() = default;
    /* Функция back() возвращает текущую лексему во входной поток.*/
    void back();
    /* Функция current_lexem() возвращает сведения о текущей
     * лексеме (код лексемы и значение лексемы). */
    virtual Lexem_type current_lexem() = 0;
    /* Функция lexem_begin_line_number() возвращает номер строки
     * обрабатываемого текста, с которой начинается лексема,
     * сведения о которой возвращены функцией current_lexem(). */
    size_t lexem_begin_line_number();
protected:
    int    state; /* текущее состояние текущего автомата */

    Location_ptr   loc;
    unsigned char* lexem_begin; /* указатель на начало лексемы */
    unsigned char  ch; /* текущий символ */

    /* множество категорий символов, которым принадлежит
     * текущий символ */
    unsigned long long char_categories;

    /* промежуточное значение сведений о лексеме */
    Lexem_type token;

    /* номер строки, с которой начинается текущая лексема */
    unsigned int lexem_begin_line;

    /* указатель на класс, подсчитывающий количество ошибок: */
    std::shared_ptr<Error_count> en;
    /* указатель на префиксное дерево для идентификаторов: */
    std::shared_ptr<Char_trie> ids;
    /*указатель на префиксное дерево для строковых литералов*/
    std::shared_ptr<Char_trie> str_lit;

    /*буфер для записи обрабатываемого идентификатора или строки: */
    std::string buffer;
};

template<typename Lexem_type>
Scaner<Lexem_type>::Scaner(Location_ptr location, Errors_and_tries_ptr et){
    ids              = et->ids_trie;
		str_lit          = et->str_lit_trie; 
		en               = et->ec;
    loc              = location;
    lexem_begin      = location->pcurrent_char;
    lexem_begin_line = 1;
}

template<typename Lexem_type>
void Scaner<Lexem_type>::back(){
    loc->pcurrent_char = lexem_begin;
    loc->current_line =  lexem_begin_line;
}

template<typename Lexem_type>
size_t Scaner<Lexem_type>::lexem_begin_line_number(){
    return lexem_begin_line;
}
#endif
