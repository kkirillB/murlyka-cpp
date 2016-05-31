#include "project_info.h"
#include "get_token_stream.h"
#include "line_scaner.h"
#include "syntax_parser.h"
#include "errors_and_tries.h"
#include <boost/optional.hpp>
#include <string>
#include <memory>

boost::optional<ProjectInfo> getMakeInfo(const std::string& txt){
	Errors_and_tries_ptr et = std::make_shared<Errors_and_tries>();
    et->ec                  = std::make_shared<Error_count>();
    et->ids_trie            = std::make_shared<Char_trie>();
    et->str_lit_trie        = std::make_shared<Char_trie>();
	TokenVector tv          = getTokenStream(txt, et);
	
  boost::optional<ProjectInfo> maybeInfo = boost::none;
	if(et->ec->get_number_of_errors()){
    et->ec->print();
    return maybeInfo;
	}
	Syntax_parser sp = Syntax_parser(tv, et);
  ProjectInfo info = sp.compile();
	if(et->ec->get_number_of_errors()){
    et->ec->print();
    return maybeInfo;
	}
	return info;
}
