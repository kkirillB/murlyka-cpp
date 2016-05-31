#include "lines.h"

std::vector<std::string> lines(const std::string& text){
	std::vector<std::string> ls;
	std::string current_line;
	for(char c : text){
		if ('\n' != c){
			current_line += c;
		}else{
			ls.push_back(current_line);
			current_line.clear();
		}
	}
    //ls.push_back(current_line);
	
	for(auto& str : ls){
		if(!str.empty() && str.back() == '\r'){
            str.pop_back();
		}
	}
	
	return ls;
}
