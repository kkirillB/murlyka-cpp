#ifndef GET_TOKEN_STREAM
#define GET_TOKEN_STREAM

#include "line_scaner.h"
#include "errors_and_tries.h"
#include <string>

/*Возвращает список токенов, где токен - пара, 
состоящая из лексемы и строки, где она была записана*/
TokenVector getTokenStream(const std::string& txt, Errors_and_tries_ptr et); 

#endif
