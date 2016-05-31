#ifndef LOCATION_H
#define LOCATION_H

#include <memory>
/* Cледующая структура описывает текущее положение в обрабатываемом
 * тексте.*/
struct Location {
		unsigned char* pcurrent_char; /*указатель на текущий символ */
    	/* номер текущей строки обрабатываемого текста */
    	size_t         current_line;      
      Location() : pcurrent_char(nullptr), current_line(1) {}
    	Location(unsigned char* txt) : pcurrent_char(txt),
                                   current_line(1) {}
};

using Location_ptr = std::shared_ptr<Location>;
#endif



