#include "get_token_stream.h"
#include "line_scaner.h"
#include "errors_and_tries.h"
#include "lines.h"
#include "location.h"

#include <string>
#include <vector>
#include <utility>
#include <memory>

TokenVector getTokenStream(const std::string& txt, Errors_and_tries_ptr et){
	std::vector<std::string> ls = lines(txt);
	Location_ptr loc            = std::make_shared<Location>();
	Line_scaner_ptr sc          = std::make_shared<Line_scaner>(loc, et);
	size_t line_number          = 1;
	TokenVector tv;
	LScan_lexem_info lex_info;
	LScan_lexem_code lex_code;
	for(const auto& line : ls){
		unsigned char* s   = reinterpret_cast<unsigned char*>(const_cast<char*>(line.c_str()));
		loc->current_line  = line_number;
		loc->pcurrent_char = s;
		sc->update();
		while(lex_code = (lex_info = sc->current_lexem()).code){
			tv.push_back({lex_info, line_number});
		}
		line_number++;
	}
	return tv;
}
